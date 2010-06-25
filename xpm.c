/* genetifex: xpm.c
 *
 * Copyright (c) 2010 Michael Forney <mforney@mforney.org>
 *
 * This file is a part of genetifex.
 *
 * genetifex is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License version 2, as published by the
 * Free Software Foundation.
 *
 * genetifex is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * genetifex.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <xcb/xcb.h>
#include <xcb/xcb_bitops.h>
#include <xcb/xcb_image.h>

#include "xpm.h"
#include "genetifex.h"

static uint32_t parse_color(const char const * color_string)
{
    uint8_t red, green, blue;

    if (color_string[0] == '#')
    {
        sscanf(color_string, "#%2hhx%2hhx%2hhx", &red, &green, &blue);

        return red << 16 | green << 8 | blue;
    }
    else
    {
        /* TODO: Named colors */
    }
}

bool load_xpm(const char const * xpm[], xcb_pixmap_t * pixmap, xcb_pixmap_t * mask,
    uint16_t * width, uint16_t * height)
{
    uint16_t w, h;
    uint16_t colors;
    uint8_t characters_per_color;
    uint16_t color_index;

    printf("%s\n", xpm[0]);

    sscanf(xpm[0], "%hu %hu %hu %hhu", &w, &h, &colors, &characters_per_color);

    if (width) *width = w;
    if (height) *height = h;

    printf("width: %u\n", width);
    printf("height: %u\n", height);
    printf("colors: %u\n", colors);
    printf("characters_per_color: %u\n", characters_per_color);

    {
        uint32_t color_map[0xff];
        char color_character;
        char color_string[256];
        char transparent_character;
        uint16_t x, y;
        uint32_t image_data[w * h];
        uint8_t image_mask[xcb_roundup_2(w, 32) * h / 8];

        memset(image_mask, 0, sizeof(image_mask));

        xcb_gcontext_t gc;

        for (color_index = 0; color_index < colors; ++color_index)
        {
            sscanf(xpm[color_index + 1], "%c %*c %s", &color_character, color_string);

            if (strcmp(color_string, "None") == 0)
            {
                transparent_character = color_character;
            }
            else
            {
                color_map[color_character] = parse_color(color_string);
            }
        }

        for (y = 0; y < h; ++y)
        {
            for (x = 0; x < w; ++x)
            {
                if (xpm[y + colors + 1][x] == transparent_character)
                {
                    image_mask[(y * xcb_roundup_2(w, 32) + x) / 8] |=
                        1 << ((y * xcb_roundup_2(w, 32) + x) % 8);
                }
                else
                {
                    image_data[y * w + x] = color_map[xpm[y + colors + 1][x]];
                }
            }
        }

        /* Create a new pixmap for the image */
        if (pixmap)
        {
            *pixmap = xcb_generate_id(c);
            xcb_create_pixmap(c, screen->root_depth, *pixmap, window, w, h);

            gc = xcb_generate_id(c);
            xcb_create_gc(c, gc, *pixmap, 0, NULL);

            xcb_put_image_checked(c, XCB_IMAGE_FORMAT_Z_PIXMAP, *pixmap, gc, w, h,
                0, 0, 0, 24, sizeof(image_data), (uint8_t *) image_data);

            xcb_free_gc(c, gc);
        }

        /* Create a clip mask for the image */
        if (mask)
        {
            *mask = xcb_generate_id(c);
            xcb_create_pixmap(c, 1, *mask, window, w, h);

            gc = xcb_generate_id(c);
            xcb_create_gc(c, gc, *mask, 0, NULL);

            xcb_put_image(c, XCB_IMAGE_FORMAT_XY_BITMAP, *mask, gc, w, h,
                0, 0, 0, 1, sizeof(image_mask), image_mask);

            xcb_free_gc(c, gc);
        }

        return true;
    }
}


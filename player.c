/* genetifex: player.c
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

#include <stdio.h>

#include "genetifex.h"
#include "player.h"
#include "xpm.h"

#include "sprites/gerald.xpm"

void setup_player(struct player * player)
{
    player->x = 50;
    player->y = 50;

    load_xpm((const char **) gerald_xpm, &player->pixmap, &player->mask,
        &player->width, &player->height);

    player->gc = xcb_generate_id(c);

    xcb_create_gc(c, player->gc, window, XCB_GC_CLIP_MASK, (uint32_t[]){ player->mask });

    player->moving_direction = MOVING_NONE;
}

void cleanup_player(struct player * player)
{
    xcb_free_pixmap(c, player->pixmap);
    xcb_free_pixmap(c, player->mask);
    xcb_free_gc(c, player->gc);
}

void draw_player(struct player * player)
{
    xcb_change_gc(c, player->gc, XCB_GC_CLIP_ORIGIN_X | XCB_GC_CLIP_ORIGIN_Y,
        (uint32_t[]){ player->x, player->y });

    xcb_copy_area(c, player->pixmap, window, player->gc, 0, 0, player->x, player->y, 22, 44);
}


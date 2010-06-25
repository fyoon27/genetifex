/* genetifex: screen.c
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

#include <xcb/composite.h>

#include "genetifex.h"
#include "screen.h"

void setup_screen()
{
    const xcb_setup_t * setup;
    xcb_screen_iterator_t screen_iterator;
    uint32_t mask;
    uint32_t values[2];

    c = xcb_connect(NULL, NULL);

    if (xcb_connection_has_error(c))
        die("Could not open display");

    setup = xcb_get_setup(c);

    screen_iterator = xcb_setup_roots_iterator(setup);

    screen = screen_iterator.data;

    window = xcb_generate_id(c);

    mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    values[0] = screen->white_pixel;
    values[1] = XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE |
        XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_STRUCTURE_NOTIFY;

    xcb_create_window(c, XCB_COPY_FROM_PARENT, window, screen->root,
        0, 0, 800, 600, 1, XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual,
        mask, values);

    xcb_composite_redirect_window(c, window, XCB_COMPOSITE_REDIRECT_AUTOMATIC);

    xcb_map_window(c, window);

    xcb_flush(c);
}


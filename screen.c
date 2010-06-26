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
    window = xcb_generate_id(c);

    xcb_create_window(c, XCB_COPY_FROM_PARENT, window, screen->root,
        0, 0, 800, 600, 1, XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual,
        XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK,
        (uint32_t[]){ screen->white_pixel,
            XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE |
            XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_STRUCTURE_NOTIFY |
            XCB_EVENT_MASK_FOCUS_CHANGE });

    xcb_change_property(c, XCB_PROP_MODE_REPLACE, window, WM_PROTOCOLS,
        XCB_ATOM_ATOM, 32, 1, (uint32_t[]){ WM_DELETE_WINDOW });

    xcb_composite_redirect_window(c, window, XCB_COMPOSITE_REDIRECT_AUTOMATIC);

    xcb_map_window(c, window);

    xcb_flush(c);
}


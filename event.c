/* genetifex: event.c
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

#include "event.h"
#include "genetifex.h"

static void key_press(xcb_key_press_event_t * event)
{
    printf("key press: %u\n", event->detail);

    if (event->detail == 113)
        player.moving_direction = MOVING_LEFT;
    else if (event->detail == 114)
        player.moving_direction = MOVING_RIGHT;
}

static void key_release(xcb_key_press_event_t * event)
{
    printf("key release: %u\n", event->detail);

    if ((event->detail == 113 && player.moving_direction == MOVING_LEFT) ||
        (event->detail == 114 && player.moving_direction == MOVING_RIGHT))
    {
        player.moving_direction = MOVING_NONE;
    }
}

void handle_event(xcb_generic_event_t * event)
{
    switch (event->response_type & ~0x80)
    {
        case XCB_KEY_PRESS:
            key_press((xcb_key_press_event_t *) event);
            break;
        case XCB_KEY_RELEASE:
            key_release((xcb_key_press_event_t *) event);
            break;
        case XCB_NO_EXPOSURE:
            break;
        default:
            printf("unhandled event: %u\n", event->response_type & ~0x80);
    }
}


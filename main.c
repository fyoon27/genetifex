/* genetifex: main.c
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

#include <xcb/xcb.h>

#include "genetifex.h"
#include "screen.h"

void setup()
{
    setup_screen();
}

void cleanup()
{
}

void event_loop()
{
    xcb_generic_event_t * event;

    while ((event = xcb_wait_for_event(c)))
    {
    }
}

int main(int argc, char * argv[])
{
    setup();

    event_loop();

    cleanup();
}


/* genetifex: genetifex.c
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

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <xcb/composite.h>

#include "genetifex.h"
#include "screen.h"
#include "timer.h"
#include "event.h"

bool running;

xcb_connection_t * c;
xcb_screen_t * screen;
xcb_window_t window;

struct timer timer;
struct player player;

const uint8_t target_fps = 60;

void __attribute__((noreturn, format (printf, 1, 2))) die(const char const * message, ...)
{
    va_list args;

    va_start(args, message);
    fputs("FATAL: ", stderr);
    vfprintf(stderr, message, args);
    fputc('\n', stderr);
    va_end(args);

    cleanup();

    exit(EXIT_FAILURE);
}

void update(uint64_t ticks)
{
    if (player.moving_direction == MOVING_RIGHT)
        player.x += ticks / 5000000;
    else if (player.moving_direction == MOVING_LEFT)
        player.x -= ticks / 5000000;
}

void draw()
{
    xcb_clear_area(c, false, window, 0, 0, 800, 600);
    draw_player(&player);
}

void event_loop()
{
    xcb_generic_event_t * event;
    uint64_t ticks;

    running = true;

    timer_update(&timer);
    timer_set_last_update(&timer);

    while (running)
    {
        event = xcb_poll_for_event(c);

        if (event)
        {
            handle_event(event);
            free(event);
        }

        timer_update(&timer);

        ticks = timer_elapsed_ticks(&timer);

        if (ticks > 1000000000 / target_fps)
        {
            printf("fps: %u\n", 1000000000 / ticks);

            timer_set_last_update(&timer);

            update(ticks);

            draw();
        }

        xcb_flush(c);
    }
}

void setup()
{
    setup_screen();
    setup_player(&player);
}

void cleanup()
{
    cleanup_player(&player);
}


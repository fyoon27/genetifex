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
#include <string.h>
#include <xcb/composite.h>

#include "genetifex.h"
#include "screen.h"
#include "timer.h"
#include "event.h"

bool running;

xcb_connection_t * c;
xcb_screen_t * screen;
xcb_window_t window;

xcb_font_t fps_font;
xcb_gcontext_t fps_gc;

/* Atoms */
xcb_atom_t WM_PROTOCOLS;
xcb_atom_t WM_DELETE_WINDOW;

struct timer timer;
struct player player;
uint8_t fps;

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

    /* Draw FPS */
    char fps_string[16];
    sprintf(fps_string, "%u FPS", fps);
    uint16_t length = strlen(fps_string);
    xcb_char2b_t text2b[length];
    xcb_query_text_extents_cookie_t text_extents_cookie;
    xcb_query_text_extents_reply_t * text_extents_reply;
    uint16_t index;

    for (index = 0; index < length; ++index)
    {
        text2b[index] = (xcb_char2b_t) { 0, fps_string[index] };
    }

    text_extents_cookie = xcb_query_text_extents_unchecked(c, fps_font, length, text2b);
    text_extents_reply = xcb_query_text_extents_reply(c, text_extents_cookie, NULL);

    xcb_image_text_8(c, length, window, fps_gc,
        800 - text_extents_reply->overall_width - 4, text_extents_reply->overall_ascent + 4,
        fps_string);

    free(text_extents_reply);
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
            fps = 1000000000 / ticks;

            timer_set_last_update(&timer);

            update(ticks);

            draw();
        }

        xcb_flush(c);
    }
}

void setup()
{
    const xcb_setup_t * setup;
    xcb_screen_iterator_t screen_iterator;
    xcb_intern_atom_cookie_t atom_cookies[2];
    xcb_intern_atom_reply_t * atom_reply;
    const char font_name[] = "-*-*-*-*-*-*-18-*-*-*-*-*-*-*";

    c = xcb_connect(NULL, NULL);

    if (xcb_connection_has_error(c))
        die("Could not open display");

    setup = xcb_get_setup(c);
    screen_iterator = xcb_setup_roots_iterator(setup);
    screen = screen_iterator.data;

    atom_cookies[0] = xcb_intern_atom(c, false, strlen("WM_PROTOCOLS"), "WM_PROTOCOLS");
    atom_cookies[1] = xcb_intern_atom(c, false, strlen("WM_DELETE_WINDOW"), "WM_DELETE_WINDOW");

    atom_reply = xcb_intern_atom_reply(c, atom_cookies[0], NULL);
    WM_PROTOCOLS = atom_reply->atom;
    free(atom_reply);
    atom_reply = xcb_intern_atom_reply(c, atom_cookies[1], NULL);
    WM_DELETE_WINDOW = atom_reply->atom;
    free(atom_reply);

    setup_screen();

    fps_font = xcb_generate_id(c);
    xcb_open_font(c, fps_font, strlen(font_name), font_name);

    fps_gc = xcb_generate_id(c);
    xcb_create_gc(c, fps_gc, window,
        XCB_GC_FOREGROUND | XCB_GC_BACKGROUND | XCB_GC_FONT,
        (uint32_t[]){ screen->black_pixel, screen->white_pixel, fps_font });

    setup_player(&player);
}

void cleanup()
{
    cleanup_player(&player);
}


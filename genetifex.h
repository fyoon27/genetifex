/* genetifex: genetifex.h
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

#ifndef GENETIFEX_GENETIFEX_H
#define GENETIFEX_GENETIFEX_H

#include <stdbool.h>
#include <xcb/xcb.h>

#include "player.h"

extern bool running;

extern xcb_connection_t * c;
extern xcb_screen_t * screen;
extern xcb_window_t window;

/* Atoms */
extern xcb_atom_t WM_PROTOCOLS;
extern xcb_atom_t WM_DELETE_WINDOW;

extern struct player player;

void die(const char const * message, ...);

void setup();
void cleanup();

void event_loop();

#endif


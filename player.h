/* genetifex: player.h
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

#ifndef GENETIFEX_PLAYER_H
#define GENETIFEX_PLAYER_H

enum player_jump_state
{
    JUMPING
};

struct player
{
    uint16_t x, y;
    uint16_t width, height;
    xcb_pixmap_t pixmap;
    xcb_pixmap_t mask;
    xcb_gcontext_t gc;
};

void setup_player(struct player * player);
void cleanup_player(struct player * player);

void draw_player(struct player * player);

#endif


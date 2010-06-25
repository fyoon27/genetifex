/* genetifex: xpm.h
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

#ifndef GENETIFEX_XPM_H
#define GENETIFEX_XPM_H

#include <stdbool.h>
#include <xcb/xcb.h>

bool load_xpm(const char const * xpm[], xcb_pixmap_t * pixmap, xcb_pixmap_t * mask,
    uint16_t * width, uint16_t * height);

#endif


/* genetifex: clock.h
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

#ifndef GENETIFEX_TIMER_H
#define GENETIFEX_TIMER_H

#include <stdint.h>

struct timer
{
    uint64_t ticks;
    struct timespec spec;
};

void setup_timer(struct timer * timer);

uint64_t update_timer(struct timer * timer);

#endif


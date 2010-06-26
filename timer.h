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
    struct timespec last_update_spec;
    struct timespec current_spec;
};

void timer_update(struct timer * timer);

uint64_t timer_elapsed_ticks(struct timer * timer);

void timer_set_last_update(struct timer * timer);


#endif


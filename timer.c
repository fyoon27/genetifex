/* genetifex: timer.c
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

#define _GNU_SOURCE 1
#include <time.h>
#include <assert.h>

#include "timer.h"

void timer_update(struct timer * timer)
{
    assert(timer);

    clock_gettime(CLOCK_MONOTONIC, &timer->current_spec);
}

uint64_t timer_elapsed_ticks(struct timer * timer)
{
    assert(timer);

    return (timer->current_spec.tv_sec - timer->last_update_spec.tv_sec) * 1000000000 +
        (timer->current_spec.tv_nsec - timer->last_update_spec.tv_nsec);
}

void timer_set_last_update(struct timer * timer)
{
    assert(timer);

    timer->last_update_spec = timer->current_spec;
}


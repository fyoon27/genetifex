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

#include "timer.h"

uint64_t update_timer(struct timer * timer)
{
    uint64_t elapsed_ticks;
    struct timespec spec;

    clock_gettime(CLOCK_MONOTONIC, &spec);

    elapsed_ticks = (spec.tv_sec - timer->spec.tv_sec) * 1000000000 +
        (spec.tv_nsec - timer->spec.tv_nsec);

    timer->spec = spec;

    return elapsed_ticks;
}


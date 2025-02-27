/* Copyright 2022 Sadek Baroudi <sadekbaroudi@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "quantum.h"

#if defined(KEYBOARD_fingerpunch_ffkb_byomcu_v1)
#    include "v1.h"
#elif defined(KEYBOARD_fingerpunch_ffkb_byomcu_v2)
#    include "v2.h"
#elif defined(KEYBOARD_fingerpunch_ffkb_byomcu_v3)
#    include "v3.h"
#endif

#include "keyboards/fingerpunch/fp.h"

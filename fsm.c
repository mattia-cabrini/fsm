/*
 *     FSM - Finite State Machine
 *     Copyright (C) 2022  Mattia Cabrini <dev@mattiacabrini.com>
 *
 *     This library is free software; you can redistribute it and/or
 *     modify it under the terms of the GNU Lesser General Public
 *     License as published by the Free Software Foundation; either
 *     version 3.0 of the License, or (at your option) any later version.
 *
 *     This library is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *     Lesser General Public License for more details.
 *
 *     You should have received a copy of the GNU Lesser General Public License
 *     along with this library.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "fsm.h"
#include <stdlib.h>

int fsm(int def, fsm_input_t (*input)(int), fsm_state_callable_t *S, fsm_mux_callable_t *M, int DIM) {
  int s = def;
  int p = -1;
  int i;
  fsm_input_t in;
  fsm_output_t out;

  if (input == NULL)
    return FSM_ERROR_INPUT_NOT_DEFINED;

  // No Mux can be NULL
  for(i = 0; i < DIM; ++i)
    if (M == NULL || M[i] == NULL)
      return FSM_ERROR_MUX_NOT_DEFINED;

  i = 0;
  in = input(i++);
  s = M[s](in, p);
  while (s >= 0 && s < DIM) {
    // Function Sj is not requested
    if(S != NULL && S[s] != NULL)
      out = S[s](in, out, p, i);
    in = input(i++);
    p = s;
    s = M[s](in, p);
  }

  return s == -1 ? 0 : FSM_ERROR_STATE_OUT_OF_BOUND;
}

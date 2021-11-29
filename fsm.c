#include "fsm.h"
#include <stdlib.h>

int fsm(int def, fsm_input_t (*input)(int), fsm_state_callable_t *S, mux_callable *M, int DIM) {
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

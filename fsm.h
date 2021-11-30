#ifndef FSM_H_INCLUDED
#define FSM_H_INCLUDED

/**
  * These are te input/output types, you can
  * replace them with any type you want.
  */
typedef void* fsm_input_t;
typedef void* fsm_output_t;

#define FSM_INPUT_DEFAULT_VALUE '\0'
#define FSM_OUTPUT_DEFAULT_VALUE NULL

/**
  * Error codes
*/
#define FSM_ERROR_MUX_NOT_DEFINED -3
#define FSM_ERROR_INPUT_NOT_DEFINED -2
#define FSM_ERROR_STATE_OUT_OF_BOUND -1

/**
 *
 */
#define FSM_INVALID_STATE -1

/**
 * State Function Type
 * - fsm_input_t input;
 * - fsm_output_t output;
 * - int previous_state;
 * - how many times the input has been read;
 */
typedef fsm_output_t (*fsm_state_callable_t)(fsm_input_t, fsm_output_t, int, int);

/**
  * State Multiplexer Type
  * - fsm_input_t input;
  * - int previous_state;
  */
typedef int (*fsm_mux_callable_t)(fsm_input_t, int);

/**
 * Finite State Machine
 * - Default state;
 * - Array of the states;
 * - Array of the multiplexers;
 * - Maximum states.
 */
int fsm(int def, fsm_input_t (*input)(int), fsm_state_callable_t *S, fsm_mux_callable_t *M, int DIM);

#endif // FSM_H_INCLUDED

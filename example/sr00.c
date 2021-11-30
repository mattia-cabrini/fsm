#include <stdio.h>
#include <stdlib.h>

#include "../fsm.h"

char* str = NULL;

fsm_output_t s0(fsm_input_t in, fsm_output_t out, int ps, int) {
  printf("Stato 0, Stato Precedente: %d\n", ps);
  return NULL;
}

fsm_output_t s1(fsm_input_t in, fsm_output_t out, int ps, int) {
  printf("Stato 1, Stato Precedente: %d\n", ps);
  return NULL;
}

fsm_output_t s2(fsm_input_t in, fsm_output_t out, int ps, int r) {
  printf("Stato 2, Stato Precedente: %d\nOK -- 00 @ %d.\n", ps, r - 2);
  return NULL;
}

int mux0(fsm_input_t in, int ps) {
  printf("MUX 0, PS: %d\n", ps);

  switch(*(char*)in) {
    case '0':
      return 1;
    case '1':
      return 0;
    default:
      return -1;
  }
}

int mux1(fsm_input_t in, int ps) {
  printf("MUX 1, PS: %d\n", ps);

  switch(*(char*)in) {
    case '0':
      return 2;
    case '1':
      return 0;
    default:
      return -1;
  }
}

int mux2(fsm_input_t in, int ps) {
  printf("MUX 2, PS: %d\n", ps);

  switch(*(char*)in) {
    case '0':
      return 2;
    case '1':
      return 0;
    default:
      return -1;
  }
}

fsm_input_t input(int i) {
  return &str[i];
}

void test_01_sr();

int main(int argc, char **argv) {

  test_01_sr();

}

void test_01_sr() {
  fsm_state_callable_t S[3];
  fsm_mux_callable_t M[3];

  S[0] = s0;
  S[1] = s1;
  S[2] = s2;

  M[0] = mux0;
  M[1] = mux1;
  M[2] = mux2;

  str = "11001001";

  fsm(0, &input, S, M, 3);
}

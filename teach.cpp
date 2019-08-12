#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tuple network(float tf_a, float tf_b, float tt_a, float tt_b);
const char* getfield(char* line, int num);

struct Tuple {
  float out_o_a, out_o_b;
};


void train_xor() {
  struct Tuple n;
  n = network(0,0,0,0);
  n = network(1,0,1,0);
  n = network(0,1,1,0);
  n = network(1,1,0,0);
//  printf("Outputs: %0.0f %0.0f\n", n.out_o_a, n.out_o_b);
}

void train_and() {
  struct Tuple n;
  n = network(0,0,0,0);
  n = network(1,0,0,0);
  n = network(0,1,0,0);
  n = network(1,1,1,0);
//  printf("Outputs: %0.0f %0.0f\n", n.out_o_a, n.out_o_b);
}
void train_nor() {
  struct Tuple n;
  n = network(0,0,1,0);
  n = network(1,0,0,0);
  n = network(0,1,0,0);
  n = network(1,1,0,0);
//  printf("Outputs: %0.0f %0.0f\n", n.out_o_a, n.out_o_b);
}
void train_or() {
  struct Tuple n;
  n = network(0,0,0,0);
  n = network(1,0,1,0);
  n = network(0,1,1,0);
  n = network(1,1,1,0);
//  printf("Outputs: %0.0f %0.0f\n", n.out_o_a, n.out_o_b);
}
void train_nand() {
  struct Tuple n;
  n = network(0,0,1,0);
  n = network(1,0,1,0);
  n = network(0,1,1,0);
  n = network(1,1,0,0);
//  printf("Outputs: %0.0f %0.0f\n", n.out_o_a, n.out_o_b);
}

void train_not() {
  struct Tuple n;
  n = network(0,0,1,0);
  n = network(1,0,0,0);
//  printf("Outputs: %0.0f %0.0f\n", n.out_o_a, n.out_o_b);
}

void train_xnor() {
  struct Tuple n;
  n = network(0,0,1,0);
  n = network(1,0,0,1);
  n = network(0,1,0,1);
  n = network(1,1,1,0);
//  printf("Outputs: %0.0f %0.0f\n", n.out_o_a, n.out_o_b);
}

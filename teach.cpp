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


void train_csv() {
  struct Tuple n;
    char line[512];
    FILE *stream = fopen("./testdata/blah.csv", "r");
    float in_a, in_b, out_a, out_b;
    char *tmp;
    while (fgets(line, 512, stream)) {
      // NOTE strtok clobbers tmp
      tmp = strdup(line);
      in_a = atof(getfield(tmp, 3));
      free(tmp);
      tmp = strdup(line);
      in_b = atof(getfield(tmp, 4));
      free(tmp);
      tmp = strdup(line);
      out_a = atof(getfield(tmp, 8));
      free(tmp);
      tmp = strdup(line);
      out_b = atof(getfield(tmp, 9));
      free(tmp);
      n = network(in_a, in_b, out_a, out_b);
//      printf("Outputs: %0.0f %0.0f\n", n.out_o_a, n.out_o_b);
    }
    fclose(stream);
}

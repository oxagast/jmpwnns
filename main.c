/*
 * jmpwnns
 * Just Me Playing With Neural Networks
 * Marshall Whittaker
 */

//    __ _  _  __   ___  __  ____ ____
//   /  ( \/ )/ _\ / __)/ _\/ ___(_  _)
//  (  O )  (/    ( (_ /    \___ \ )(
//   \__(_/\_\_/\_/\___\_/\_(____/(__)
//
//  gcc main.cpp -o main -lm

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define LEARNRATE 0.05
#define LEARNLOOPS 5000

float weight[] = {0.15, 0.20, 0.25, 0.30, 0.40, 0.45, 0.50, 0.55};
float bias_a = 0.35;
float bias_b = 0.60;
float net_err_per[1];

float sigmoid(float sigme) {
  //sigmoidal squashing function
  float s = 1.0 / (1.0 + exp(sigme * -1));
  return (s);
}

float calc_it(float ina, float inb, float f_weight, float s_weight,
              float bias) {
  float tni = f_weight * ina + s_weight * inb + bias * 1;
  return (tni);
}

struct Tuple {
  float out_o_a, out_o_b;
};

struct Tuple network(float tf_a, float tf_b, float tt_a, float tt_b) {
  struct Tuple tuple;
  printf("Trying for: %f, %f\n", tt_a, tt_b);
  printf("Inputs to neurons are: %f, %f\n", tf_a, tf_b);
  // first pass
  float out[2];
  float o_out[2];
  for (int ll; ll < LEARNLOOPS; ll++) { // learn loop
    out[1] = sigmoid(calc_it(tf_a, tf_b, weight[0], weight[1], bias_a));
    out[2] = sigmoid(calc_it(tf_a, tf_b, weight[2], weight[3], bias_a));
    // calculate out back through
    o_out[1] = sigmoid(calc_it(out[1], out[2], weight[4], weight[5], bias_b));
    o_out[2] = sigmoid(calc_it(out[1], out[2], weight[6], weight[7], bias_b));
    // printf("OUT1: %f OUT2: %f OUTo1: %f OUTo2: %f\n", out[1], out[2],
    // o_out[1], o_out[2]);
    // calculate the network error
    net_err_per[0] = 0.5 * pow((tt_a - o_out[1]), 2);
    net_err_per[1] = 0.5 * pow((tt_b - o_out[2]), 2);
    // target - output
    float tar_less_out[2];
    tar_less_out[1] = (o_out[1] - tt_a);
    tar_less_out[2] = (o_out[2] - tt_b);
    float der[2];
    // derrivitive
    der[1] = o_out[1] * (1 - o_out[1]);
    der[2] = o_out[2] * (1 - o_out[2]);
    float diff[8];
    float bp[2];
    // delta total
    float total[2];
    total[1] = tar_less_out[1] * der[1] * out[1];
    total[2] = tar_less_out[2] * der[2] * out[2];
    float nweight[7];
    // for each weight above 4
    nweight[4] = weight[4] - LEARNRATE * total[1];
    nweight[5] = weight[5] - LEARNRATE * total[1];
    nweight[6] = weight[6] - LEARNRATE * total[2];
    nweight[7] = weight[7] - LEARNRATE * total[2];
    // start the back prop
    bp[1] = tar_less_out[1] * der[1];
    bp[2] = tar_less_out[2] * der[2];
    float p[2];
    p[1] = bp[1] * weight[4];
    p[2] = bp[2] * weight[4];
    // printf("%f %f %f %f\n", nweight[4], nweight[5], nweight[6], nweight[7]);
    float hns[2];
    float hns_p[2];
    hns[1] = tar_less_out[1] * der[1];
    hns[2] = tar_less_out[2] * der[2];
    hns_p[1] = hns[1] * weight[4];
    hns_p[2] = hns[2] * weight[5];
    float out_h = hns_p[1] + hns_p[2];
    // for each weight
    // wish i could smoke a joint
    float outh_a = out[1] * (1 - out[1]);
    float outh_b = out[2] * (1 - out[2]);
    float backout_a = out_h * outh_a * tf_a;
    float backout_b = out_h * outh_b * tf_b;
    weight[0] = weight[0] - LEARNRATE * backout_a;
    weight[1] = weight[1] - LEARNRATE * backout_a;
    weight[2] = weight[2] - LEARNRATE * backout_b;
    weight[3] = weight[3] - LEARNRATE * backout_b;
    weight[4] = nweight[4];
    weight[5] = nweight[5];
    weight[6] = nweight[6];
    weight[7] = nweight[7];
  }
  tuple = {o_out[1], o_out[2]};
  return(tuple);
}

int train() {
  float out_o_a, out_o_b;
  struct Tuple tuple;
  // lets try to teach it XOR!!
  tuple = network(0,0,0,0);
  out_o_a = tuple.out_o_a;
  out_o_b = tuple.out_o_b;
  printf("Final: %f %f\n", out_o_a, out_o_b);
  tuple = network(0,1,1,1);
  out_o_a = tuple.out_o_a;
  out_o_b = tuple.out_o_b;
  printf("Final: %f %f\n", out_o_a, out_o_b);
  tuple = network(1,0,1,1);
  out_o_a = tuple.out_o_a;
  out_o_b = tuple.out_o_b;
  printf("Final: %f %f\n", out_o_a, out_o_b);
  tuple = network(1,1,0,0);
  out_o_a = tuple.out_o_a;
  out_o_b = tuple.out_o_b;
  printf("Final: %f %f\n", out_o_a, out_o_b);
  return(0);
}
int main() {
  int ret = train(); 
  printf("Final Weights:\nw1 %f w2 %f w3 %f w4 %f\nw5 %f w6 %f w7 %f w8 %f\n", 
		  weight[0], weight[1], weight[2], weight[3], weight[4],
		  weight[5], weight[6], weight[7]);
  printf("Network Error: A: %f  -  B: %f \n", net_err_per[0], net_err_per[1]);
  return(0);
}


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

#define LEARNRATE 0.25
#define LEARNLOOPS 10000

float weight[] = {0.15, 0.20, 0.25, 0.30, 0.40, 0.45, 0.50, 0.55};
float input[] = {0.05, 0.10};
float tryfor[] = {0.89, 0.52};
float bias_a = 0.35;
float bias_b = 0.60;

float sigmoid(float sigme) {
  float s = 1.0 / (1.0 + exp(sigme * -1));
  return (s);
}

float calc_it(float ina, float inb, float f_weight, float s_weight,
              float bias) {
  float tni = f_weight * ina + s_weight * inb + bias * 1;
  return (tni);
}

int main(int argc, char *argv[]) {
  printf("Trying for: %f, %f\n", tryfor[0], tryfor[1]);
  printf("Inputs to neurons are: %f, %f\n", input[0], input[1]);
  // learning rate
  // float lr = 0.5;
  float backout;
  // network error declare
  float net_err_per[2];
  // first pass
  float out[2];
  float o_out[2];
  for (int ll; ll < LEARNLOOPS; ll++) { // learn loop
    out[1] = sigmoid(calc_it(input[0], input[1], weight[0], weight[1], bias_a));
    out[2] = sigmoid(calc_it(input[0], input[1], weight[2], weight[3], bias_a));
    // calculate out back through
    o_out[1] = sigmoid(calc_it(out[1], out[2], weight[4], weight[5], bias_b));
    o_out[2] = sigmoid(calc_it(out[1], out[2], weight[6], weight[7], bias_b));
    // printf("OUT1: %f OUT2: %f OUTo1: %f OUTo2: %f\n", out[1], out[2],
    // o_out[1], o_out[2]);
    // calculate the network error
    net_err_per[1] = 0.5 * pow((tryfor[0] - o_out[1]), 2);
    net_err_per[2] = 0.5 * pow((tryfor[1] - o_out[2]), 2);
    // target - output
    float tar_less_out[2];
    tar_less_out[1] = (o_out[1] - tryfor[0]);
    tar_less_out[2] = (o_out[2] - tryfor[1]);
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
    backout = out_h * outh_a * input[0];
    weight[0] = weight[0] - LEARNRATE * backout;
    weight[1] = weight[1] - LEARNRATE * backout;
    weight[2] = weight[2] - LEARNRATE * backout;
    weight[3] = weight[3] - LEARNRATE * backout;
    weight[4] = nweight[4];
    weight[5] = nweight[5];
    weight[6] = nweight[6];
    weight[7] = nweight[7];
  }
  printf("Network Error: A: %f  -  B: %f \n", net_err_per[1], net_err_per[2]);
  printf("Output: A:%f  -  B: %f\n", o_out[1], o_out[2]);
}

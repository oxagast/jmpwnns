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
//  g++ main.cpp -o main -lm

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEARNRATE 0.05
#define LEARNLOOPS 20000

void train_csv();
void train_xor();
void train_and();
void train_nand();
void train_nor();
void train_or();
void train_not();
void train_xnor();

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
  struct Tuple n;
//  printf("Trying for: %0.0f %0.0f\n", tt_a, tt_b);
//  printf("Inputs to neurons are: %f %f\n", tf_a, tf_b);
  // first pass
  float out[3];
  float o_out[3];
//  for (int ll; ll < LEARNLOOPS; ll++) { // learn loop
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
    float diff[9];
    float bp[3];
    // delta total
    float total[3];
    total[1] = tar_less_out[1] * der[1] * out[1];
    total[2] = tar_less_out[2] * der[2] * out[2];
    float nweight[8];
    // for each weight above 4
    nweight[4] = weight[4] - LEARNRATE * total[1];
    nweight[5] = weight[5] - LEARNRATE * total[1];
    nweight[6] = weight[6] - LEARNRATE * total[2];
    nweight[7] = weight[7] - LEARNRATE * total[2];
    // start the back prop
    bp[1] = tar_less_out[1] * der[1];
    bp[2] = tar_less_out[2] * der[2];
    float p[3];
    p[1] = bp[1] * weight[4];
    p[2] = bp[2] * weight[4];
    // printf("%f %f %f %f\n", nweight[4], nweight[5], nweight[6], nweight[7]);
    float hns[3];
    float hns_p[3];
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
//}
  n = {o_out[1], o_out[2]};
  return(n);
}


void reset_weight() {
  weight[0] = 15;
  weight[1] = 20;
  weight[2] = 25;
  weight[3] = 30;
  weight[4] = 40;
  weight[5] = 45;
  weight[5] = 50;
  weight[6] = 55;
}

int main() {
  // predict
  struct Tuple prediction;
  float pin[2];
  pin[0] = 1;
  pin[1] = 0;
  for(int i; i < LEARNLOOPS; i++) {
    train_xor();
    reset_weight();
    train_and();
    reset_weight();
    train_nand();
    reset_weight();
    train_or();
    reset_weight();
    train_xnor();
    reset_weight();
    train_and();
    reset_weight();
    train_nor();
  }
  prediction = network(pin[0], pin[1], 0,0);
  printf("Prediction from %0.0f %0.0f: %0.0f %0.0f\n", 
		  pin[0], pin[1], prediction.out_o_a, prediction.out_o_b);
  printf("Final Weights:\nw1 %f w2 %f w3 %f w4 %f\nw5 %f w6 %f w7 %f w8 %f\n", 
		  weight[0], weight[1], weight[2], weight[3], weight[4],
		  weight[5], weight[6], weight[7]);
  printf("Network Error: A: %f  -  B: %f \n", net_err_per[0], net_err_per[1]);
  return(0);
}

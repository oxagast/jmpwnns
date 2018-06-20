#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float sigmoid (float sigme) {
  //printf("%f", sigme);
  float s = 1.0 / (1.0 + exp(sigme * -1)); 
  return(s);
}

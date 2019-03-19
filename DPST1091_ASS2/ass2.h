#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

void error_input() {
  printf("Error input.\n");
  exit(1);
}

void read_base_inputs(double* line_length, double* init_direction, double* angle_increment, double* init_color_r, double* init_color_g, double* init_color_b) {

  if (!scanf("%lf", line_length)) {
    error_input();
  }

  if (!scanf("%lf", init_direction)) {
    error_input();
  }

  if (!scanf("%lf", angle_increment)) {
    error_input();
  }

  if (!scanf("%lf", init_color_r) || *init_color_r < 0.0 || *init_color_r > 1.0) {
    error_input();
  }

  if (!scanf("%lf", init_color_g) || *init_color_g < 0.0 || *init_color_g > 1.0) {
    error_input();
  }

  if (!scanf("%lf", init_color_b) || *init_color_b < 0.0 || *init_color_b > 1.0) {
    error_input();
  }
}

void output_base_inputs(double line_length, double init_direction, double angle_increment, double init_color_r, double init_color_g, double init_color_b) {

  printf("Line Length: %.4f\n", line_length);
  printf("Initial Direction: %.4f\n", init_direction);
  printf("Angle Increment: %.4f\n", angle_increment);

  printf("Initial Colour: RGB(%.4f,%.4f,%.4f)\n", init_color_r, init_color_g, init_color_b);
}

void read_start_str(char* str) {
  if (!scanf("%s", str)) {
    error_input();
  }
}

void output_start_str(char* str) {
  printf("Start String: %s\n", str);
}

void read_rules() {
}

void output_rules() {
}








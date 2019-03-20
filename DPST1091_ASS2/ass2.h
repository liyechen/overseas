#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "ass2types.h"

#define true 1
#define false 0

// exit the program while error input happens
void error_input() {
  printf("Error input.\n");
  exit(1);
}

// read base configs
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

// output some base configs...
void output_base_inputs(double line_length, double init_direction, double angle_increment, double init_color_r, double init_color_g, double init_color_b) {

  printf("Line Length: %.4f\n", line_length);
  printf("Initial Direction: %.4f\n", init_direction);
  printf("Angle Increment: %.4f\n", angle_increment);

  printf("Initial Colour: RGB(%.4f,%.4f,%.4f)\n", init_color_r, init_color_g, init_color_b);
}

// read start string
void read_start_str(StrLinkList* node) {
  char* str = (char*)malloc(sizeof(char));
  if (!scanf("%s", str)) {
    error_input();
  }
  char* temp = str;
  node->ch = *temp;
  temp++;
  StrLinkList* head_node = node;
  while (*temp) {
    StrLinkList* temp_node = (StrLinkList*)malloc(sizeof(StrLinkList));
    temp_node->ch = *temp;
    temp_node->next = NULL;
    head_node->next = temp_node;
    head_node = temp_node;
    temp++;
  }
}

// output start string
void output_start_str(StrLinkList* node) {
  StrLinkList* t = node;
  printf("Start String: ");
  while(t->next != NULL) {
    printf("%c", t->ch);
    t = t->next;
  }
  putchar(t->ch);
  putchar('\n');
}

void read_rules() {
}

void output_rules() {
}








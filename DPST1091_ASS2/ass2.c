#include "ass2.h"

int main(void) {
  double line_length, init_direction, angle_increment;
  double init_color_r, init_color_g, init_color_b;
  char* start_str = (char *)malloc(sizeof(char));
  StrLinkList *head;

  read_base_inputs(&line_length, &init_direction, &angle_increment, &init_color_r, &init_color_g, &init_color_b);

  read_start_str(start_str);

  read_rules();

  output_base_inputs(line_length, init_direction, angle_increment, init_color_r, init_color_g, init_color_b);

  output_start_str(start_str);

  output_rules();

  return 0;
}

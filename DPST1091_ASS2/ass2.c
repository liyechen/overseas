#include "ass2.h"

int main(void) {
  double line_length, init_direction, angle_increment;
  double init_color_r, init_color_g, init_color_b;

  StrLinkList *str_head;
  str_head = (StrLinkList *)malloc(sizeof(StrLinkList));

  read_base_inputs(&line_length, &init_direction, &angle_increment, &init_color_r, &init_color_g, &init_color_b);

  read_start_str(str_head);

  read_rules();

  output_base_inputs(line_length, init_direction, angle_increment, init_color_r, init_color_g, init_color_b);

  output_start_str(str_head);

  output_rules();

  return 0;
}

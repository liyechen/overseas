#include "ass2.h"

int main(int argc, char *argv[]) {
  int iters = 0;
  char* flag = (char*)malloc(sizeof(char));

  if (argc > 1) {
    iters = atoi(argv[1]);
  }

  if (argc > 2) {
    flag = argv[2];
  }
  



  double line_length, init_direction, angle_increment;
  double init_color_r, init_color_g, init_color_b;

  StrLinkList *str_head;
  str_head = (StrLinkList*)malloc(sizeof(StrLinkList));

  RuleMap* rules = (RuleMap*)malloc(sizeof(RuleMap) * MAX_RULES);

  read_base_inputs(&line_length, &init_direction, &angle_increment, &init_color_r, &init_color_g, &init_color_b);

  read_start_str(str_head);

  read_rules(rules);

  output_base_inputs(line_length, init_direction, angle_increment, init_color_r, init_color_g, init_color_b);

  output_start_str(str_head);

  output_rules(rules);

  free(str_head);
  free(rules);

  return 0;
}

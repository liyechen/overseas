#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "ass2types.h"

#define true 1
#define false 0

#define COLOR_STEP 0.1

#define MAX_RULES 20

// function defines
void iter_node(StrLinkList* node, RuleMap* rule_maps);

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
  head_node->next = NULL;
}

// output start string
void output_start_str(StrLinkList* node, int prev) {
  StrLinkList* t = node;
  if (prev == 1) printf("Start String: ");
  while(t->next != NULL) {
    printf("%c", t->ch);
    t = t->next;
  }
  putchar(t->ch);
  putchar('\n');
}

void read_rules(RuleMap* rules) {
  int i;
  for (i = 0; i < MAX_RULES; i++) {
    char* chs = (char*)malloc(sizeof(char));
    if (!scanf("%s" , chs)) {
      error_input();
    }
    char* ruleStr = (char*)malloc(sizeof(char));
    if (!scanf("%s", ruleStr)) {
      error_input();
    }
    RuleMap* rule = (RuleMap*)malloc(sizeof(RuleMap));
    rule->ch = chs[0];
    rule->rule = ruleStr;
    rules[i] = *rule;
  }
}

void output_rules(RuleMap* rules) {
  printf("Rules:\n");
  int i;
  RuleMap* t = rules;
  for (i = 0; i < MAX_RULES; i++) {
    if (t->ch == '\0' || t->ch == '\n') {
      break;
    } else {
      printf("\'%c\' -> \"%s\"\n", t->ch, t->rule);
    }
    t++;
  }
}

void print_graphic(double x, double y, double end_x, double end_y, double r, double g, double b) {
  long long _x = x >= 0.0 ? floor(x) : ceil(x);
  long long _y = y >= 0.0 ? floor(y) : ceil(y);
  long long _end_x = end_x >= 0.0 ? floor(end_x) : ceil(end_x);
  long long _end_y = end_y >= 0.0 ? floor(end_y) : ceil(end_y);
  printf("%lld %lld %lld %lld %.6f %.6f %.6f\n", _x, _y, _end_x, _end_y, r, g, b);
}

void free_strs(StrLinkList* head) {
  StrLinkList* t = head;
  while (t->next != NULL) {
    StrLinkList* temp = t->next;
    free(t);
    t = temp;
  }
  free(t);
}

void handle_command(char cmd, double* x, double* y, double* next_x, double* next_y,double line, double* direction, double* r, double* g, double* b, double angle, PosStack* point_stack) {
  switch(cmd) {
    case 'F':
      *next_x = *x + line * sin(*direction);
      *next_y = *y + line * cos(*direction);
      print_graphic(*x, *y, *next_x, *next_y, *r, *g, *b);
      *x = *next_x;
      *y = *next_y;
      break;
    case 'f':
      *next_x = *x + sin(*direction);
      *next_y = *y + cos(*direction);
      *x = *next_x;
      *y = *next_y;
      break;
    case '+':
      *direction = *direction + angle;
      break;
    case '-':
      *direction = *direction - angle;
      break;
    case 'R':
      *r = *r + COLOR_STEP;
      if (*r > 1.0) *r = 1.0;
      break;
    case 'r':
      *r = *r - COLOR_STEP;
      if (*r < 0.0) *r = 0.0;
      break;
    case 'G':
      *g = *g + COLOR_STEP;
      if (*g > 1.0) *g = 1.0;
      break;
    case 'g':
      *g = *g - COLOR_STEP;
      if (*g < 0.0) *g = 0.0;
      break;
    case 'B':
      *b = *b + COLOR_STEP;
      if (*b > 1.0) *b = 1.0;
      break;
    case 'b':
      *b = *b - COLOR_STEP;
      if (*b < 0.0) *b = 0.0;
      break;
    case '[':
      point_stack->top++;
      point_stack->points[point_stack->top].x = *x;
      point_stack->points[point_stack->top].y = *y;
      break;
    case ']':
      *x = point_stack->points[point_stack->top].x;
      *y = point_stack->points[point_stack->top].y;
      point_stack->top--;
      break;
    default:
      break;
  }
}

// do the drawing
void draw_commands(StrLinkList* node, double line, double init_direction, double angle, double init_r, double init_g, double init_b) {
  double x = 0.0, y = 0.0;
  double next_x = 0.0, next_y = 0.0;
  double direction = init_direction;
  double r = init_r, g = init_g, b = init_b;
  StrLinkList* t = node;
  PosStack* point_stack = (PosStack*)malloc(sizeof(PosStack));
  point_stack->points = (PointPos*)malloc(sizeof(PointPos) * MAX_SIZE);
  point_stack->top = 0;

  point_stack->points[0].x = 0.0;
  point_stack->points[0].y = 0.0;

  while (t->next != NULL) {
    handle_command(t->ch, &x, &y, &next_x, &next_y, line, &direction, &r, &g, &b, angle, point_stack);
    t = t->next;
  }
  handle_command(t->ch, &x, &y, &next_x, &next_y, line, &direction, &r, &g, &b, angle, point_stack);

  free(point_stack);
}

void output_iter_times(int times) {
  printf("After %d iterations:\n", times);
}

void iter_node(StrLinkList* node, RuleMap* rules) {
  StrLinkList* tail = node->next;
  StrLinkList* temp = node;
  RuleMap* t = rules;

  int i;
  for (i = 0; i < MAX_RULES; i++) {
    if (t->ch == '\0' || t->ch == '\n') {
      break;
    } else {
      if (t->ch == temp->ch) {
        char* rule_str = t->rule;
        temp->ch = rule_str[0];
        rule_str++;
        while(*rule_str) {
          StrLinkList* ch_node = (StrLinkList*)malloc(sizeof(StrLinkList));
          ch_node->ch = *rule_str;
          temp->next = ch_node;
          temp = ch_node;
          rule_str++;
        }
        temp->next = tail;
        break;
      }
    }
    t++;
  }

}

void iter_str(StrLinkList* head, RuleMap* rules) {
  StrLinkList* t = head;
  while (t->next) {
    StrLinkList* next_node = t->next;
    iter_node(t, rules);
    t = next_node;
  }
  iter_node(t, rules);
}



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

  if (argc == 1) output_base_inputs(line_length, init_direction, angle_increment, init_color_r, init_color_g, init_color_b);

  if (argc == 1) output_start_str(str_head, 1);

  if (argc == 1) output_rules(rules);

  //logic codes for stage^1 here 
  if (argc > 1) {
    if (argc > 2) {
      output_start_str(str_head, 1);
    }
    output_iter_times(iters);
    int times = iters;
    while(times > 0) {
      times--;
      iter_str(str_head, rules);
    }
    if (argc == 2) {
      draw_commands(str_head, line_length, init_direction, angle_increment, init_color_r, init_color_g, init_color_b);

    } else {
      output_start_str(str_head, 0);
    }
  }



  // free linked space and rules space
  free_strs(str_head);
  free(rules);

  return 0;
}

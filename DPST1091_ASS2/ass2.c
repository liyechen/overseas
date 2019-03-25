#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>


#define MAX_SIZE 1024

#define MAX_CHARS 100

// linked list struct for new string
typedef struct str_node {
  char ch;
  struct str_node* next;
} StrLinkList;

// struct for rules
typedef struct rule_map {
  char ch;
  char rule[MAX_CHARS];
} RuleMap;

typedef struct position {
  double x;
  double y;
  double r;
  double g;
  double b;
  double direction;
} PointPos;

typedef struct position_node {
  PointPos* points;
  int top;
} PosStack;

typedef struct line {
  long long x;
  long long y;
  long long end_x;
  long long end_y;
  double r;
  double g;
  double b;
} Line;

typedef struct line_stack {
  Line lines[10000];
  int top;
} LineStack;

#define true 1
#define false 0

#define COLOR_STEP 0.1

#define MAX_RULES 21

// function defines
void iter_node(StrLinkList* node, RuleMap rule_maps[MAX_RULES]);

// exit the program while error input happens
void error_input() {
  printf("Error input.\n");
  exit(1);
}

void push_line(LineStack* lines, long long x, long long y, long long end_x, long long end_y, double r, double g, double b) {
  if (lines->top == 10000) return;
  lines->top = lines->top + 1;
  lines->lines[lines->top].x = x;
  lines->lines[lines->top].y = y;
  lines->lines[lines->top].end_x = end_x;
  lines->lines[lines->top].end_y = end_y;
  lines->lines[lines->top].r = r;
  lines->lines[lines->top].b = g;
  lines->lines[lines->top].b = b;
}

int dequals(double a, double b)
{
    double c=fabs(a-b);//一定要#include <math.h>  labs 针对long整数   fabs针对浮点数，abs针对整数
    return  c< 0.000001;
}

int has_line(LineStack* lines, long long x, long long y, long long end_x, long long end_y, double r, double g, double b) {
  int i;
  for (i = 0; i < lines->top; i++) {
    // if (lines->lines[i].x == x && lines->lines[i].y == y && lines->lines[i].end_x == end_x && lines->lines[i].end_y == end_y && dequals(lines->lines[i].r, r) && dequals(lines->lines[i].g, g) && dequals(lines->lines[i].b, b)) {
    // printf("before %lld %lld %lld %lld, after %lld %lld %lld %lld \n", lines->lines[i].x, lines->lines[i].y, lines->lines[i].end_x, lines->lines[i].end_y, x, y, end_x, end_y);
    if (lines->lines[i].x == x && lines->lines[i].y == y && lines->lines[i].end_x == end_x && lines->lines[i].end_y == end_y) {
      return 1;
    }
  }
  return 0;
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
  char* str = (char*)malloc(sizeof(char) * MAX_CHARS);
  // char* str;
  if (!scanf("%s", str)) {
    error_input();
  }
  char* temp = str;
  node->ch = *temp;
  temp++;
  StrLinkList* head_node = node;
  while (*temp) {
    StrLinkList* temp_node = (StrLinkList*)malloc(sizeof(StrLinkList));
   //  StrLinkList* temp_node;
    temp_node->ch = *temp;
    temp_node->next = NULL;

    head_node->next = temp_node;
    head_node = temp_node;

    temp++;
  }
  head_node->next = NULL;
  free(str);
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

void read_rules(RuleMap rules[MAX_RULES]) {
  int i;
  for (i = 0; i < MAX_RULES; i++) {
    // char* chs = (char*)malloc(sizeof(char) * 100);
    char chs[100];
    int j = 0;
    for (j = 0; j < 100; j++) {
      chs[j] = '#';
    }
    if (!scanf("%s", chs)) {
      error_input();
    }
    // char* ruleStr = (char*)malloc(sizeof(char) * MAX_CHARS);
    char ruleStr[MAX_CHARS];
    if (!scanf("%s", ruleStr)) {
      error_input();
    }
    if (chs[0] == '#') {
      break;
    }
    rules[i].ch = chs[0];
    strcpy(rules[i].rule, ruleStr);
    // rules[i].rule = ruleStr;
    // free(ruleStr);
  } 
}

void output_rules(RuleMap rules[MAX_RULES]) {
  printf("Rules:\n");
  int i;
  for (i = 0; i < MAX_RULES; i++) {
    RuleMap t = rules[i];
    if (t.ch == '#' || t.ch == '\n' || t.ch == EOF) {
      break;
    } else {
        printf("\'%c\' -> \"%s\"\n", t.ch, t.rule);
    }
  }
}

void print_graphic(LineStack* lines, double x, double y, double end_x, double end_y, double r, double g, double b) {
  long long _x = x >= 0.0 ? floor(x) : ceil(x);
  long long _y = y >= 0.0 ? floor(y) : ceil(y);
  long long _end_x = end_x >= 0.0 ? floor(end_x) : ceil(end_x);
  long long _end_y = end_y >= 0.0 ? floor(end_y) : ceil(end_y);
  /*long long _x = floor(x);*/
  /*long long _y = floor(y);*/
  /*long long _end_x = floor(x);*/
  /*long long _end_y = floor(y);*/
  /*if (has_line(lines, _x, _y, _end_x, _end_y, r, g, b) == 0) {*/
  /*  printf("%lld %lld %lld %lld %.6f %.6f %.6f\n", _x, _y, _end_x, _end_y, r, g, b);*/
  /*  push_line(lines, _x, _y, _end_x, _end_y, r, g, b);*/
  /*} else {*/
  /*  printf("!!!");*/
  /*}*/
  
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

void handle_command(LineStack* lines, char cmd, double* x, double* y, double* next_x, double* next_y,double line, double* direction, double* r, double* g, double* b, double angle, PosStack* point_stack) {
  switch(cmd) {
    case 'F':
      *next_x = *x + line * sin(*direction);
      *next_y = *y + line * cos(*direction);
      print_graphic(lines, *x, *y, *next_x, *next_y, *r, *g, *b);
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
      point_stack->points[point_stack->top].r = *r;
      point_stack->points[point_stack->top].g = *g;
      point_stack->points[point_stack->top].b = *b;
      point_stack->points[point_stack->top].direction = *direction;
      break;
    case ']':
      *x = point_stack->points[point_stack->top].x;
      *y = point_stack->points[point_stack->top].y;
      *r = point_stack->points[point_stack->top].r;
      *g = point_stack->points[point_stack->top].g;
      *b = point_stack->points[point_stack->top].b;
      *direction = point_stack->points[point_stack->top].direction;
      point_stack->top--;
      break;
    default:
      break;
  }
}

// do the drawing
void draw_commands(LineStack* lines, StrLinkList* node, double line, double init_direction, double angle, double init_r, double init_g, double init_b) {
  double x = 0.0, y = 0.0;
  double next_x = 0.0, next_y = 0.0;
  double direction = init_direction;
  double r = init_r, g = init_g, b = init_b;
  StrLinkList* t = node;
  PosStack* point_stack = (PosStack*)malloc(sizeof(PosStack));
 // PosStack* point_stack;
  point_stack->points = (PointPos*)malloc(sizeof(PointPos) * MAX_SIZE);

  point_stack->top = 0;

  point_stack->points[0].x = 0.0;
  point_stack->points[0].y = 0.0;
  point_stack->points[0].direction = init_direction;
  point_stack->points[0].r = init_r;
  point_stack->points[0].b = init_b;
  point_stack->points[0].g = init_g;

  while (t->next != NULL) {
    handle_command(lines, t->ch, &x, &y, &next_x, &next_y, line, &direction, &r, &g, &b, angle, point_stack);
    t = t->next;
  }
  handle_command(lines, t->ch, &x, &y, &next_x, &next_y, line, &direction, &r, &g, &b, angle, point_stack);

  free(point_stack->points);
  free(point_stack);
}

void output_iter_times(int times) {
  printf("After %d iterations:\n", times);
}

void iter_node(StrLinkList* node, RuleMap rules[MAX_RULES]) {
  StrLinkList* tail = node->next;
  StrLinkList* temp = node;

  int i;
  for (i = 0; i < MAX_RULES; i++) {
    RuleMap t = rules[i];
    if (t.ch == '#' || t.ch == '\0' || t.ch == '\n') {
      break;
    } else {
      if (t.ch == temp->ch) {
        char* rule_str = t.rule;
        temp->ch = rule_str[0];
        rule_str++;
        while(*rule_str) {
          StrLinkList* ch_node = (StrLinkList*)malloc(sizeof(StrLinkList));
          // StrLinkList* ch_node;
          ch_node->ch = *rule_str;
          temp->next = ch_node;
          temp = ch_node;
          rule_str++;
        }
        temp->next = tail;
        break;
      }
    }
  }

}

int is_normal_ch(char ch) {
    if (ch == 'f' || ch == 'F' || ch == '+' || ch == '-' || ch == 'R' || ch == 'G' || ch == 'B' || ch == 'r' || ch == 'g' || ch == 'b' || ch == '[' || ch == ']') {

      return 1;
    }
    return 0;
}

void iter_node_sec(StrLinkList* node, RuleMap rules[MAX_RULES]) {
  StrLinkList* tail = node->next;
  StrLinkList* temp = node;
  int i;
  for (i = 0; i < MAX_RULES; i++) {
    RuleMap t = rules[i];
    if (t.ch == '#' || t.ch == '\0' || t.ch == '\n') {
      break;
    } else {
      if (t.ch == temp->ch && is_normal_ch(t.ch) == 0) {
        char* rule_str = t.rule;
        temp->ch = rule_str[0];
        rule_str++;
        while(*rule_str) {
          StrLinkList* ch_node = (StrLinkList*)malloc(sizeof(StrLinkList));
          // StrLinkList* ch_node;
          ch_node->ch = *rule_str;
          temp->next = ch_node;
          temp = ch_node;
          rule_str++;
        }
        temp->next = tail;
        break;
      }
    }
  }
}

void iter_str_sec(StrLinkList* head, RuleMap rules[MAX_RULES]) {
  StrLinkList* t = head;
  while (t->next) {
    StrLinkList* next_node = t->next;
    iter_node_sec(t, rules);
    t = next_node;
  }
  iter_node_sec(t, rules);
}


void iter_str(StrLinkList* head, RuleMap rules[MAX_RULES]) {
  StrLinkList* t = head;
  while (t->next) {
    StrLinkList* next_node = t->next;
    iter_node(t, rules);
    t = next_node;
  }
  iter_node(t, rules);
  //iter_str_sec(head, rules);
}

int main(int argc, char *argv[]) {
  int iters = 0;
  // char* flag = (char*)malloc(sizeof(char));
  char* flag;

  if (argc > 1) {
    iters = atoi(argv[1]);
  }

  if (argc > 2) {
    flag = argv[2];
  }

  double line_length, init_direction, angle_increment;
  double init_color_r, init_color_g, init_color_b;

  LineStack* lines = (LineStack*)malloc(sizeof(LineStack));
  lines->top = 0;

  int m;
  for (m = 0; m < 10000; m++) {
    lines->lines[m].x = 0.0;
    lines->lines[m].y = 0.0;
    lines->lines[m].end_x = 0.0;
    lines->lines[m].end_y = 0.0;
    lines->lines[m].r = 0.0;
    lines->lines[m].g = 0.0;
    lines->lines[m].b = 0.0;
  }


  StrLinkList *str_head;
  str_head = (StrLinkList*)malloc(sizeof(StrLinkList));

  RuleMap rules[MAX_RULES];

  int rule_iter;
  for (rule_iter = 0; rule_iter < MAX_RULES; rule_iter++) {
    rules[rule_iter].ch = '#';
    int j;
    for (j = 0; j < MAX_CHARS; j++) {
      rules[rule_iter].rule[j] = '#';
    }
  }

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
    int times = iters;
    while(times > 0) {
      times--;
      iter_str(str_head, rules);
    }
    if (argc == 2) {
      draw_commands(lines, str_head, line_length, init_direction, angle_increment, init_color_r, init_color_g, init_color_b);

    } else {
      output_iter_times(iters);
      output_start_str(str_head, 0);
    }
  }



  // free linked space and rules space
  free_strs(str_head);
  free(lines);
  /*int k;*/
  /*for (k = 0; k < MAX_RULES; k++) {*/
  /*  free(rules[k].rule);*/
  /*}*/

  return 0;
}

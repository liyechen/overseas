#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define RULE_LENGTH 100
#define RULES_NUM 20
#define READ_STR_LENGTH 1000
#define COLOR_INCRE 0.1

typedef struct StrNode {
  char letter;
  struct StrNode* next;
} StrNode;

typedef struct Rule {
  char letter;
  char rule[RULE_LENGTH];
} Rule;

typedef struct Color {
  double r;
  double g;
  double b;
} Color;

typedef struct BasicConfig {
  double line;
  double direction;
  double angle;
  Color color;
} BasicConfig;

typedef struct BrushStatus {
  double x;
  double y;
  double direction;
  double angle;
  double line;
  Color color;
} BrushStatus;

typedef struct Brackets {
  int pos;
  BrushStatus status[1000];
} Brackets;

void printError();
void validColor(double r, double g, double b);
void printLinkedList(StrNode* head);
void printLinkedListPure(StrNode* head);
void printLine(double x, double y, double endX, double endY, Color color);
void transformCommands(StrNode* head, BasicConfig config);
void executeCommand(char cmd, BrushStatus* status, Brackets* brackets);
void appropriateColor(double* color);
void iterateStr(StrNode* head, Rule rules[RULES_NUM], unsigned int rulesAmount);

void printError() {
  printf("There are some errors in the input.\n");
  exit(1);
}

void validColor(double r, double g, double b) {
  if (r < 0.0 || r > 1.0 ||
      g < 0.0 || g > 1.0 ||
      b < 0.0 || b > 1.0) printError();
}

void printLinkedList(StrNode* head) {
  StrNode* iterNode = head;
  printf("Start String: ");
  while (iterNode != NULL) {
    printf("%c", iterNode->letter);
    iterNode = iterNode->next;
  }
  printf("\n");
}

void printLinkedListPure(StrNode* head) {
  StrNode* iterNode = head;
  while (iterNode != NULL) {
    printf("%c", iterNode->letter);
    iterNode = iterNode->next;
  }
  printf("\n");
}

void printLine(double x, double y, double endX, double endY, Color color) {
  long long llX, llY, llEndX, llEndY;
  if (x > 0.0) llX = floor(x); else llX = ceil(x);
  if (y > 0.0) llY = floor(y); else llY = ceil(y);
  if (endX > 0.0) llEndX = floor(endX); else llEndX = ceil(endX);
  if (endY > 0.0) llEndY = floor(endY); else llEndY = ceil(endY);
  printf("%lld %lld %lld %lld %.6f %.6f %.6f\n",llX, llY,llEndX, llEndY, color.r, color.g, color.b);
}

void transformCommands(StrNode* head, BasicConfig config) {
  StrNode* iterNode = head;
  BrushStatus* status = (BrushStatus*)malloc(sizeof(BrushStatus));
  status->x = 0.0;
  status->y = 0.0;
  status->direction = config.direction;
  status->color.r = config.color.r;
  status->color.g = config.color.g;
  status->color.b = config.color.b;
  status->angle = config.angle;
  status->line = config.line;

  Brackets* brackets = (Brackets*)malloc(sizeof(Brackets));
  brackets->pos = 0;

  while (iterNode != NULL) {
    executeCommand(iterNode->letter, status, brackets);
    iterNode = iterNode->next;
  }
  free(status);
  free(brackets);
}

void executeCommand(char cmd, BrushStatus* status, Brackets* brackets) {
  double x, y;
  switch(cmd) {
    case 'f':
      x = status->x + sin(status->direction) * status->line;
      y = status->y + cos(status->direction) * status->line;
      status->x = x;
      status->y = y;
      break;
    case 'F':
      x = status->x + sin(status->direction) * status->line;
      y = status->y + cos(status->direction) * status->line;
      printLine(status->x, status->y, x, y, status->color);
      status->x = x;
      status->y = y;
      break;
    case '+':
      status->direction = status->direction + status->angle;
      break;
    case '-':
      status->direction = status->direction - status->angle;
      break;
    case 'R':
      status->color.r = status->color.r + COLOR_INCRE;
      appropriateColor(&status->color.r);
      break;
    case 'r':
      status->color.r = status->color.r - COLOR_INCRE;
      appropriateColor(&status->color.r);
      break;
    case 'G':
      status->color.g = status->color.g + COLOR_INCRE;
      appropriateColor(&status->color.g);
      break;
    case 'g':
      status->color.g = status->color.g - COLOR_INCRE;
      appropriateColor(&status->color.g);
      break;
    case 'B':
      status->color.b = status->color.b + COLOR_INCRE;
      appropriateColor(&status->color.b);
      break;
    case 'b':
      status->color.b = status->color.b - COLOR_INCRE;
      appropriateColor(&status->color.b);
      break;
    case '[':
      brackets->status[brackets->pos].x = status->x;
      brackets->status[brackets->pos].y = status->y;
      brackets->status[brackets->pos].direction = status->direction;
      brackets->status[brackets->pos].color = status->color;
      brackets->status[brackets->pos].angle = status->angle;
      brackets->status[brackets->pos].line = status->line;
      brackets->pos = brackets->pos + 1;
      break;
    case ']':
      brackets->pos = brackets->pos - 1;
      status->x = brackets->status[brackets->pos].x;
      status->y = brackets->status[brackets->pos].y;
      status->direction = brackets->status[brackets->pos].direction;
      status->angle = brackets->status[brackets->pos].angle;
      status->line = brackets->status[brackets->pos].line;
      status->color = brackets->status[brackets->pos].color;
      break;
    default:
      break;
  }
}

void appropriateColor(double* color) {
  if (*color < 0.0) *color = 0.0;
  if (*color > 1.0) *color = 1.0;
}

void iterateStr(StrNode* head, Rule rules[RULES_NUM], unsigned int rulesAmount) {
  StrNode* iterNode = head;
  int i, j;
  while (iterNode != NULL) {
    StrNode* nextNode = iterNode->next;
    for (i = 0; i < rulesAmount; i++) {
      if (iterNode->letter == rules[i].letter) {
        StrNode* next = iterNode->next;
        iterNode->letter = rules[i].rule[0];
        for (j = 1; j < strlen(rules[i].rule); j++) {
          StrNode* temp = (StrNode*)malloc(sizeof(StrNode));
          temp->letter = rules[i].rule[j];
          iterNode->next = temp;
          iterNode = temp;
        }
        break;
      }
    }
    iterNode->next = nextNode;
    iterNode = nextNode;
  }
}

int main(int argc, char* argv[]) {
  double line = 1.0, direction = 1.0, angle = 1.0, r = 1.0, g = 1.0, b = 1.0;
  int iterTimes;

  if (!scanf("%lf", &line)) {
    printError();
  }

  if (!scanf("%lf", &direction)) {
      printError();
  }

  if (!scanf("%lf", &angle)) {
    printError();
  }
  
  if (!scanf("%lf", &r)) {
    printError();
  }

  if (!scanf("%lf", &g)) {
    printError();
  }

  if (!scanf("%lf", &b)) {
    printError();
  }

  validColor(r, g, b);  

  BasicConfig config;
  config.direction = direction;
  config.angle = angle;
  config.line = line;
  config.color.r = r;
  config.color.g = g;
  config.color.b = b;

  
  char readLine[READ_STR_LENGTH];
  if (!scanf("%s", readLine)) {
    printError();
  }

  StrNode* str = (StrNode*)malloc(sizeof(StrNode));
  str->letter = readLine[0];
  str->next = NULL;
  StrNode* iterNode = str;

  // init StrNode: str
  unsigned long i;
  for (i = 1; i < strlen(readLine); i++) {
    StrNode* temp = (StrNode*)malloc(sizeof(StrNode)); 
    temp->letter = readLine[i];
    temp->next = NULL;
    iterNode->next = temp;
    iterNode = temp;
  }

  Rule rules[RULES_NUM];
  unsigned int rulesAmount = 0;
  char ruleKey[100] = "";
  char rulesStr[RULE_LENGTH] = "";
  for (i = 0; i < RULES_NUM; i++) {
    scanf("%s", ruleKey);
    scanf("%s", rulesStr);
    if (strcmp(rulesStr, "") == 0) {
      break;
    }
    rules[i].letter = ruleKey[0];
    strcpy(rules[i].rule, rulesStr);
    strcpy(rulesStr, "");
    rulesAmount  = i + 1;
  }

  // stage 0 
  if (argc == 1) {
    printf("Line Length: %.4f\n", line);
    printf("Initial Direction: %.4f\n", direction);
    printf("Angle Increment: %.4f\n", angle);
    printf("Initial Colour: RGB(%.4f,%.4f,%.4f)\n", r, g, b);
    printLinkedList(str);

    printf("Rules:\n");
    for (i = 0; i < rulesAmount; i++) {
      printf("\'%c\' -> \"%s\"\n", rules[i].letter, rules[i].rule);
    }
  }

  if (argc == 2) {
    iterTimes = atoi(argv[1]);
    while (iterTimes > 0) {
      iterateStr(str, rules, rulesAmount);
      iterTimes--;
    }
    transformCommands(str, config);
  } else if (argc == 3) {
    printLinkedList(str);
    iterTimes = atoi(argv[1]);
    printf("After %d iterations:\n", iterTimes);
    while (iterTimes > 0) {
      iterateStr(str, rules, rulesAmount);
      iterTimes--;
    }
    printLinkedListPure(str);
  }

  while (str != NULL) {
    StrNode* temp = str->next;
    free(str);
    str = temp;
  }

  return 0;
}

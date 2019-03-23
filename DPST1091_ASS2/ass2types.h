#define MAX_SIZE 1024

// linked list struct for new string
typedef struct str_node {
  char ch;
  struct str_node* next;
} StrLinkList;

// struct for rules
typedef struct rule_map {
  char ch;
  char* rule;
} RuleMap;

typedef struct position {
  double x;
  double y;
} PointPos;

typedef struct position_node {
  PointPos* points;
  int top;
} PosStack;








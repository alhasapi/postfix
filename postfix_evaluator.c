#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VALUE int
#define LIMIT 100
#define MULTIOP(INS, OP) \
  case INS: { \
        result = op1 OP op2; \
        break;\
  }\

int extract_tokens(char *s, char *delim1, char *delim2, char **dst, int *sz) {
  char *str1, *str2, *token, *subtoken;
  char *saveptr1, *saveptr2;
  int j, i = 0;

  for (j = 1, str1 = s; ; j++, str1 = NULL) {
    token = strtok_r(str1, delim1, &saveptr1);
    if (token == NULL)
      break;
    for (str2 = token; ; str2 = NULL) {
      subtoken = strtok_r(str2, delim2, &saveptr2);
      if (subtoken == NULL) break;
      dst[i++] = strdup(subtoken);
    }
  }
  *sz = i;
}

typedef struct node {
  VALUE value;
  struct node *prev;
  struct node *next;
} node;


typedef struct stack {
  node *top;
  node *tail;
  int size;
} Stack;

node * new_Node(VALUE val) {
  node *n  = (node *)malloc(sizeof(node));
  n->value = val;
  n->next  = NULL;
  n->prev  = NULL;
  return n;
}

Stack *createStack() {
  Stack *new = (Stack *)malloc(sizeof(Stack));
  new->top  = NULL;
  new->tail = NULL;
  new->size = 0;
  return new;
}

int pushStack(Stack *stack, VALUE val) {
  node * n = new_Node(val);
  if (n == NULL) return 0;
  if (stack->top == NULL) {
    stack->top  = n;
    stack->tail = n;
  } else {
    stack->top->next = n;
    n->prev = stack->top;
    stack->top = n;
  }
  stack->size += 1;
  return 1;
}
int isEmpty(Stack * stack) {
  return stack->size == 0;
}

int popStack(Stack *stack, int *val) {
    if (isEmpty(stack)) return -1;
    node *q = stack->top;
    *val = stack->top->value;
    stack->top = stack->top->prev;
    free(q);
    stack->size -= 1;
    return 1;
}

void destroyStack(Stack *stack) {
  node *t;
  while(stack->top != NULL) {
    t = stack->tail;
    stack->tail = stack->tail->next;
    free(t);
  }
  free(stack);
}

int eval(char *s, int *res) {
  Stack * stack = createStack();
  int op1, op2, i, size, result;
  char **tokens = (char **)malloc(LIMIT * sizeof(char *));
  extract_tokens(s, " ", " ", tokens, &size);

  for(i = 0; i < size; ++s,i++) {
    int is_op = (tokens[i][0] == '+' ||
                 tokens[i][0] == '-' ||
                 tokens[i][0] == '*' ||
                 tokens[i][0] == '/');
    if (!is_op) {
      printf("%d\n", atoi(tokens[i]));
      pushStack(stack, atoi(tokens[i]));
    } else {
      printf("%d\n", tokens[i]);
      popStack(stack, &op1);
      popStack(stack, &op2);
      switch (tokens[i][0]) {
        MULTIOP('+', +)
        MULTIOP('-', -)
        MULTIOP('*', *)
        MULTIOP('/', /)
      }
      pushStack(stack, result);
    }
  }
  popStack(stack, res);
  destroyStack(stack);
  free(tokens);
  return 1;
}



int main(int ac, char **av) {
  int res;
  char *s;
  if (ac < 2) {
    printf("Usage: %s \"[postfix expression]\"\n", (char *)av[0]);
    return EXIT_FAILURE;
  }
  s = (char *)av[1];
  eval(s, &res);
  printf("Resultt: = %d\n", res);
  return EXIT_SUCCESS;
}

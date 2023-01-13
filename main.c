#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// SETUP
int stackSize = 100;

struct node {
  char value;
  struct node *next;
} * head, *current, *tail;

int isEmpty() {
  if (head == NULL) {
    return 1;
  } else {
    return 0;
  }
}

int isFull() {
  current = head;
  int count = 0;

  while (current != NULL) {
    count++;
    current = current->next;
  }

  if (count == stackSize) {
    return 1;
  } else {
    return 0;
  }
}

int getSize() {
  current = head;
  int count = 1;

  if (isEmpty() == 1) {
    return 0;
  } else {
    while (current != tail) {
      current = current->next;
      count++;
    }
  }

  return count;
}

void push(char value) { // Insert at last index

  if (isFull() == 1) {
    return;
  } else {
    current = (struct node *)malloc(sizeof(struct node));
    current->value = value;

    if (isEmpty() == 1) {
      current->next = NULL;
      head = current;
      tail = current;
    } else {
      tail->next = current;
      tail = current;
    }
  }
}

char pop() { // Returns last index
  char popchar;
  current = head;

  if (isEmpty() == 1) {
    printf("\nPop: Stack is Empty!\n");
    return '\0';
  } else {
    if (head == tail) {

      popchar = current->value;
      head = NULL;
      tail = NULL;
      current = NULL;

    } else {
      while (current->next != tail) {
        current = current->next;
      }
      popchar = current->next->value;
      tail = current;
      tail->next = NULL;
    }
  }
  return popchar;
}

char peek() {
  current = head;
  if (isEmpty() == 1) {
    return '\0';
  } else {
    while (current->next != NULL) {
      current = current->next;
    }
  }
  return current->value;
}

void display() {
  current = head;
  int counter = 1;

  /* printf("Stack Size:\n"); */
  while (current != NULL) {
    /* printf("%d. %c\n", counter++, current->value); */
    printf("%c", current->value);
    current = current->next;
  }
  printf("\n");
}
// SETUP

void postfix(char *input) {
  long unsigned int stringLength = strlen(input);
  char result[255] = "";
  char popchar;

  for (int i = 0; i < stringLength; i++) {
    display();
    printf("%c\t", input[i]);

    if (input[i] == '+' || input[i] == '-' || input[i] == '*' ||
        input[i] == '/' || input[i] == '^' || input[i] == '(' ||
        input[i] == '[' || input[i] == '{' || input[i] == ')' ||
        input[i] == ']' || input[i] == '}') {

      if (isEmpty() == 1 || (peek() == '(' || peek() == '[' || peek() == '{')) {

        if (input[i] == ')' || input[i] == ']' || input[i] == '}') {
          pop();
          continue;
        }
        push(input[i]);

      } else if (input[i] == '(' || input[i] == '[' || input[i] == '{') {

        push(input[i]);

      } else if (input[i] == ')' || input[i] == ']' || input[i] == '}') {
        if (peek() == '(' || peek() == '[' || peek() == '{') {
          printf("hello\n");
          pop();
        }

        switch (input[i]) {
        case ')':
          while (peek() != '(') {
            popchar = pop();
            strncat(result, &popchar, 1);
          }
          pop();
          break;
        case ']':
          while (peek() != '[') {
            popchar = pop();
            strncat(result, &popchar, 1);
          }
          pop();
          break;
        case '}':
          while (peek() != '{') {
            popchar = pop();
            strncat(result, &popchar, 1);
          }
          pop();
          break;
        }

      } else {

        if (input[i] == '^') {
          if (peek() == input[i]) {
            while (peek() != '(' || peek() != '[' || peek() != '{') {
              popchar = pop();
              strncat(result, &popchar, 1);
            }
          } else {
            push(input[i]);
          }
        } else if (input[i] == '*' || input[i] == '/') {
          if (peek() == '^') {
            push(input[i]);
          } else {
            while (peek() == '^' || peek() == '*' || peek() == '/') {
              if (peek() == '(' || peek() == '[' || peek() == '{') {
                break;
              }
              popchar = pop();
              strncat(result, &popchar, 1);
            }
            push(input[i]);
          }
        } else if (input[i] == '+' || input[i] == '-') {
          if (peek() == '+' || peek() == '-' || peek() == '*' ||
              peek() == '/' || peek() == '^') {
            while (peek() == '+' || peek() == '-' || peek() == '*' ||
                   peek() == '/' || peek() == '^') {
              if (peek() == '(' || peek() == '[' || peek() == '{') {
                break;
              }
              popchar = pop();
              strncat(result, &popchar, 1);
            }
            push(input[i]);
          } else {
            push(input[i]);
          }
        }
      }

    } else {
      strncat(result, &input[i], 1);
    }
  }
  /* printf("Remaining "); */
  /* display(); */
  while (isEmpty() != 1) {
    popchar = pop();
    strncat(result, &popchar, 1);
    /* printf("the letter is: %c\n", popchar); */
  }
  printf("\n\n\n");
  printf("Infix: %s\n", input);
  printf("Postfix: %s\n", result);

  /* display(); */
}

int main() {
  char input[255];
  printf("INFIX TO POSTFIX\n\n");
  printf("Enter an expression: ");
  scanf("%s", input);
  printf("\n");

  /* system("clear"); */
  postfix(input);

  return 0;
}

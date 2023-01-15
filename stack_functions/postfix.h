#include "essentials.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int postfix(char *input) {
  long unsigned int stringLength = strlen(input);
  char result[255] = "";
  char popchar, restart;

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

  do {
    printf("\nDo you want to try again? (Y/N): ");
    scanf(" %c", &restart);
    restart = toupper(restart);
    printf("%c\n", restart);
  } while (restart != 'Y' && restart != 'N');

  switch (restart) {
  case 'Y':
    return 1;
    break;
  case 'N':
    return 0;
    break;
  default:
    return -1;
  }
}

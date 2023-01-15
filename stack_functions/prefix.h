#include "essentials.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int prefix(char *input) {
  long unsigned int stringLength = strlen(input);
  char result[255] = "";
  char reverseResult[255] = "";
  char reverseInput[255] = "";
  char popchar, restart;

  for (int i = stringLength - 1; i >= 0; i--) {
    if (input[i] == ')' || input[i] == ']' || input[i] == '}') {
      switch (input[i]) {
      case ')':
        strcat(reverseInput, "(");
        break;
      case ']':
        strcat(reverseInput, "[");
        break;
      case '}':
        strcat(reverseInput, "{");
        break;
      }
    } else if (input[i] == '(' || input[i] == '[' || input[i] == '{') {
      switch (input[i]) {
      case '(':
        strcat(reverseInput, ")");
        break;
      case '[':
        strcat(reverseInput, "]");
        break;
      case '{':
        strcat(reverseInput, "}");
        break;
      }
    } else {
      strncat(reverseInput, &input[i], 1);
    }
  }

  // START
  for (int i = 0; i < stringLength; i++) {
    display();
    printf("%c\t", input[i]);

    if (reverseInput[i] == '+' || reverseInput[i] == '-' ||
        reverseInput[i] == '*' || reverseInput[i] == '/' ||
        reverseInput[i] == '^' || reverseInput[i] == '(' ||
        reverseInput[i] == '[' || reverseInput[i] == '{' ||
        reverseInput[i] == ')' || reverseInput[i] == ']' ||
        reverseInput[i] == '}') {

      if (isEmpty() == 1 || (peek() == '(' || peek() == '[' || peek() == '{')) {

        if (reverseInput[i] == ')' || reverseInput[i] == ']' ||
            reverseInput[i] == '}') {
          pop();
          continue;
        }
        push(reverseInput[i]);

      } else if (reverseInput[i] == '(' || reverseInput[i] == '[' ||
                 reverseInput[i] == '{') {

        push(reverseInput[i]);

      } else if (reverseInput[i] == ')' || reverseInput[i] == ']' ||
                 reverseInput[i] == '}') {
        if (peek() == '(' || peek() == '[' || peek() == '{') {
          pop();
        }

        switch (reverseInput[i]) {
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

        if (reverseInput[i] == '^') {
          push(reverseInput[i]);
        } else if (reverseInput[i] == '*' || reverseInput[i] == '/') {
          if (peek() == '^') {
            push(reverseInput[i]);
          } else {
            while (peek() == '^') {
              if (peek() == '(' || peek() == '[' || peek() == '{') {
                break;
              }
              popchar = pop();
              strncat(result, &popchar, 1);
            }
            push(reverseInput[i]);
          }
        } else if (reverseInput[i] == '+' || reverseInput[i] == '-') {
          if (peek() == '*' || peek() == '/' || peek() == '^') {
            while (peek() == '*' || peek() == '/' || peek() == '^') {
              if (peek() == '(' || peek() == '[' || peek() == '{') {
                break;
              }
              popchar = pop();
              strncat(result, &popchar, 1);
            }
            push(reverseInput[i]);
          } else {
            push(reverseInput[i]);
          }
        }
      }

    } else {
      strncat(result, &reverseInput[i], 1);
    }
  }

  while (isEmpty() != 1) {
    popchar = pop();
    strncat(result, &popchar, 1);
  }

  for (int i = stringLength - 1; i >= 0; i--) {
    if (result[i] == ')' || result[i] == ']' || result[i] == '}') {
      switch (result[i]) {
      case ')':
        strcat(reverseResult, "(");
        break;
      case ']':
        strcat(reverseResult, "[");
        break;
      case '}':
        strcat(reverseResult, "{");
        break;
      }
    } else if (result[i] == '(' || result[i] == '[' || result[i] == '{') {
      switch (result[i]) {
      case '(':
        strcat(reverseResult, ")");
        break;
      case '[':
        strcat(reverseResult, "]");
        break;
      case '{':
        strcat(reverseResult, "}");
        break;
      }
    } else {
      strncat(reverseResult, &result[i], 1);
    }
  }
  printf("\n\n\n");
  printf("Infix: %s\n", input);
  printf("Prefix: %s\n", result);

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

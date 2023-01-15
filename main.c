#include "stack_functions/postfix.h"
#include "stack_functions/prefix.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// SETUP
int stackSize = 100;
// SETUP

int main() {
  int repeater = 1;

  while (repeater == 1) {

    system("clear");

    char input[255];
    char choice;

    printf("Infix Converter\n");
    printf("[A] Prefix | [B] Postfix | [X] Exit\n\n");
    scanf(" %c", &choice);
    choice = toupper(choice);

    switch (choice) {
    case 'A':
      printf("INFIX TO PREFIX\n\n");
      printf("Enter an expression: ");
      scanf("%s", input);
      printf("\n");

      /* system("clear"); */
      prefix(input);
      break;

    case 'B':
      printf("INFIX TO POSTFIX\n\n");
      printf("Enter an expression: ");
      scanf("%s", input);
      printf("\n");

      /* system("clear"); */
      repeater = postfix(input);
      break;

    case 'X':
      printf("Thank you for using the program!\n");
      repeater = 0;
      break;

    default:
      printf("Invalid Choice\n");
      break;
    }
  }

  return 0;
}

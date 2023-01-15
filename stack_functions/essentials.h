#ifndef ESSENTIALS_H_
#define ESSENTIALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int stackSize;

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

#endif

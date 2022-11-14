#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Node
typedef struct node {
    char name[201];
    int age;
    // Higher values indicate higher priority
    int priority;
    struct node* next;
} Node;
 
// Function to Create A New Node
Node* newNode(char name[201], int age, int pri) {
  Node* temp = (Node*)malloc(sizeof(Node));
  strcpy(temp->name, name);
  temp->age = age;
  temp->priority = pri;
  temp->next = NULL;
  return temp;
}

// Function to return the age at head
int peek_age(Node** head) {
  return (*head)->age;
}

// Function to return the priority at head
int peek_priority(Node** head) {
  return (*head)->priority;
}

// Function to remove the element with the highest priority from the list
void pop(Node** head) {
  Node* temp = *head;
  (*head) = (*head)->next;
  free(temp);
}
 
// Function to push new node into the list according to priority
void push(Node** head, char name[201], int age, int pri) {
  Node* start = (*head);
  // Create new Node
  Node* temp = newNode(name, age, pri);
  // Special Case: The head of list has lesser priority than new node. 
  // So insert new node before head node and change head node.
  if ((*head)->priority < pri) {
    // Insert New Node before head
    temp->next = *head;
    (*head) = temp;
  }
  else {
    // Traverse the list and find a position to insert new node
    while (start->next != NULL && start->next->priority > pri) {
      start = start->next;
    }
    // Either at the ends of the list or at required position
    temp->next = start->next;
    start->next = temp;
  }
}

// Function that generates a list of patients
void list(Node* head) {
  if (head->next != NULL) {
    printf("%s (age: %d, priority: %d)\n", head->name, peek_age(&head), peek_priority(&head));
    list(head->next);
  }
}
 
// Function to check if list is empty
int isEmpty(Node** head) {
  return (*head) == NULL;
}

int main() {

  int count = 0;
  char command;
  Node* patients = newNode("X", 0, -1); 

  while (1) {
    printf("Currently there are %d patients in the queue.\n", count);
    if (count == 0) {
      printf("What do you want to do? [N]ew patient, [Q]uit:\n");
    } else {
      printf("What do you want to do? [N]ew patient, [T]reat patient, [L]ist, [Q]uit:\n");
    }
    scanf("%c", &command);
    getchar();  

    // Creating new patient and adding into list by priority
    if (command == 'N') {
      char name[201];
      printf("What is the name of the patient?\n");
      scanf("%200[^\n]", name);
      getchar(); 

      int age;
      printf("What is the age of the patient?\n");
      scanf("%d", &age);
      getchar(); 
      
      int priority;
      printf("What is the priority of the patient?\n");
      scanf("%d", &priority);
      getchar(); 
 
      push(&patients, name, age, priority);  
      count++;
    }

    // Treating the patient and removing from the list
    if (command == 'T') {
      printf("Treating the patient %s (age: %d, priority: %d).\n", patients->name, peek_age(&patients), peek_priority(&patients));
      pop(&patients);
      count--;
    }

    // Printing the list
    if (command == 'L') {
      list(patients);
    }

    // Quitting thr program
    if (command == 'Q') {
      printf("Goodbye!\n");
      exit(0);
    }
  }
}

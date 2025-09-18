// list/list.c
// 
// Implementation for linked list.
//
// Zamijah Shakeur-Tompkins

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

list_t *list_alloc() { 
  list_t* mylist =  (list_t *) malloc(sizeof(list_t)); 
  mylist->head = NULL;
}

void list_free(list_t *l) {
  node_t *prev = NULL;
  node_t *curr = l->head;
  while (curr != NULL) {
    prev = curr;
    curr = curr->next;
    free(prev);
  }
  free(curr);
  l->head = NULL;
}

void list_print(list_t *l) {
  node_t *curr = l->head;
  printf("[");
  while (curr != NULL) {
    printf("%d ", curr->value);
    curr = curr->next;
  }
  printf("]\n");
}

char * listToString(list_t *l) {
  char* buf = (char *) malloc(sizeof(char) * 10024);
  char tbuf[20];

	node_t* curr = l->head;
  while (curr != NULL) {
    sprintf(tbuf, "%d->", curr->value);
    curr = curr->next;
    strcat(buf, tbuf);
  }
  strcat(buf, "NULL");
  return buf;
}

int list_length(list_t *l) { 
  int count = 0;
  node_t *curr = l->head;
  while (curr != NULL) {
    count++;
    curr = curr->next;
  }
  return count;
 }

void list_add_to_back(list_t *l, elem value) {
      /* Create new node */
      node_t *new = (node_t *) getNode(value);
      node_t *curr = l->head;
      while (curr != NULL) { //Get to the end of the list
        if (curr->next == NULL) { //Check for the last element and add the new node to the end
          curr->next = new; 
          return;
        }
        curr = curr->next;
      } 
}
void list_add_to_front(list_t *l, elem value) {
     node_t *cur_node = (node_t *) getNode(value);

     /* Insert to front */
     node_t *head = l->head;  // get head of list

     cur_node->next = head;
     l->head = cur_node;
}

node_t * getNode(elem value) {
  node_t *mynode;

  mynode = (node_t *) malloc(sizeof(node_t));
  mynode->value = value;
  mynode->next = NULL;

  return mynode;
}

void list_add_at_index(list_t *l, elem value, int index) {
  if (index < 0) {
        int length = list_length(l);
        index = length + index + 1;
        if (index < 0) {
            // Index is out of bounds after calculation
            return;
        }
    }

  if (index == 0) {
    list_add_to_front(l, value);
    return;
  }
  node_t *new = (node_t *) getNode(value);
  node_t *curr = l->head;
  int i = 0;
  while (curr != NULL) { //Get to the end of the list
    if (i == index-1) { //Check for the last element and add the new node to the end
      new->next = curr->next; 
      curr->next = new;
      return;
    }
    i++;
    curr = curr->next;
  } 

}

elem list_remove_from_back(list_t *l) { 
  // Handle empty list case
  if (l->head == NULL) {
    return -1; // Or some other appropriate error value
  }

  // Handle single-node list case
  if (l->head->next == NULL) {
    elem value_to_return = l->head->value;
    free(l->head);
    l->head = NULL;
    return value_to_return;
  }
  
  // Traverse to the second-to-last node
  node_t *curr = l->head;
  while (curr->next->next != NULL) {
    curr = curr->next;
  }

  // curr is now the second-to-last node
  node_t *last_node = curr->next;
  elem value_to_return = last_node->value;
  
  // Remove the last node
  curr->next = NULL;
  free(last_node);

  return value_to_return;
}
elem list_remove_from_front(list_t *l) { 
  // 1. Handle an empty list
  if (l == NULL || l->head == NULL) {
    return -1; // Or some other appropriate error value
  }

  // 2. Get the node to remove and its value
  node_t *node_to_remove = l->head;
  elem value_to_return = node_to_remove->value;

  // 3. Update the head to the next node in the list
  l->head = node_to_remove->next;

  // 4. Free the memory of the removed node
  free(node_to_remove);

  // 5. Return the value
  return value_to_return;
 }
elem list_remove_at_index(list_t *l, int index) { 
  node_t *prev = NULL;
  node_t *curr = l->head;
  int i = 1;
  while (curr != NULL) {
    if (i == index) {
      if (prev == NULL) {
        l->head = curr->next; // Move the head to the next element, curr will still be the head
      }
      else {
        prev->next = curr->next; 
      }
      elem return_value = curr->value;
      free(curr);
      return return_value;
    }
    else {
      i++;
      prev = curr;
      curr = curr->next;
    }
  }
  return -1;
 }

bool list_is_in(list_t *l, elem value) { 
  // Handle case of an empty or null list
  if (l == NULL || l->head == NULL) {
    return false;
  }

  // Traverse the list
  node_t *curr = l->head;
  while (curr != NULL) {
    // Check if the current node's value matches the target value
    if (curr->value == value) {
      return true; // Value found, return true
    }
    curr = curr->next;
  }

  // Value not found after traversing the entire list
  return false;
 }
elem list_get_elem_at(list_t *l, int index) { 
  node_t *curr = l->head;
  int i = 0;
  if (index < 0) {
      index = index + list_length(l);
    }
  while (curr != NULL) {
    if (i == index) {
      return curr->value;
    }
    else {
      i++;
      curr = curr->next;
    }
  }
  return -1;
 }

int list_get_index_of(list_t *l, elem value) { 
   // Handle empty or null list
  if (l == NULL || l->head == NULL) {
    return -1;
  }

  int index = 0;
  node_t *curr = l->head;
  
  // Traverse the list
  while (curr != NULL) {
    // Check if the current node's value matches the target value
    if (curr->value == value) {
      return index; // Value found, return its index
    }
    
    // Move to the next node and increment the index
    curr = curr->next;
    index++;
  }
  
  // Value not found after traversing the entire list
  return -1;
 }


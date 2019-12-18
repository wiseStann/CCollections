/* Implementations of popular sorting algorithms for List data structure */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef LIST_SORTINGS_H
#define LIST_SORTINGS_H


void swap(void** a, void** b)
{
    int* temp = *a;
    *a = *b;
    *b = temp;
}

// Bubble sort algorithm
List* bubbleSort(List* list)
{
    bool swapped = true;
    while (swapped) {
        swapped = false;
        Node* curr_node = list->head;
        while (curr_node->next) {
            Node* next_node = curr_node->next;
            if (curr_node->data > next_node->data) {
                swap(&curr_node->data, &next_node->data);
                swapped = true;
            }
            curr_node = curr_node->next;
        }
    }
    return list;
}

// Selection sort algorithm
List* selectionSort(List* list)
{
    Node* head = list->head;
    while (head) {
        Node* min = head;
        Node* next_node = head->next;
        while (next_node) {
            if (min->data > next_node->data) {
                min = next_node;
            }
            next_node = next_node->next;
        }
        void* data = head->data; 
        head->data = min->data; 
        min->data = data; 
        head = head->next;
    }
    return list;
}

// Quick sort algorithm
void** quickSort(void** list, int n)
{
    return 0;
}


#endif // LIST_SORTINGS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    struct Node *next;
    int value;
} Node;

typedef struct LinkedList
{
    Node *head;
} LinkedList;

LinkedList *createList();
Node *createNode(int value);

void pushLeft(LinkedList *linkedList, int value);
void pushRight(LinkedList *linkedList, int value);

Node *removeValue(LinkedList *linkedList, int value);
Node *removeAt(LinkedList *linkedList, int index);
void freeList(LinkedList *linkedList);

Node *get(LinkedList *linkedList, int index);
int contains(LinkedList *linkedList, int value);
int size(LinkedList *linkedList);

int main()
{
     printf("=== CREATING LIST ===\n");

    LinkedList *list = createList();

    printf("Initial size: %d\n", size(list));

    printf("\n=== ADDING ELEMENTS ===\n");

    pushRight(list, 10);
    pushRight(list, 20);
    pushRight(list, 30);

    pushLeft(list, 5);
    pushLeft(list, 1);

    printf("List after insertions:\n");
    printList(list);

    printf("Current size: %d\n", size(list));

    printf("\n=== TESTING CONTAINS ===\n");

    printf("Contains 20? %d\n", contains(list, 20));
    printf("Contains 100? %d\n", contains(list, 100));

    printf("\n=== TESTING GET ===\n");

    Node *node = get(list, 2);

    if (node != NULL)
    {
        printf("Value at index 2: %d\n", node->value);
    }
    else
    {
        printf("Invalid index\n");
    }

    printf("\n=== REMOVING BY VALUE ===\n");

    Node *removedValue = removeValue(list, 20);

    if (removedValue != NULL)
    {
        printf("Removed value: %d\n", removedValue->value);
        free(removedValue);
    }
    else
    {
        printf("Value not found\n");
    }

    printList(list);

    printf("\n=== REMOVING BY INDEX ===\n");

    Node *removedIndex = removeAt(list, 1);

    if (removedIndex != NULL)
    {
        printf("Removed node at index 1: %d\n", removedIndex->value);
        free(removedIndex);
    }
    else
    {
        printf("Invalid index\n");
    }

    printList(list);

    printf("\n=== FINAL SIZE ===\n");

    printf("List size: %d\n", size(list));

    printf("\n=== FREEING MEMORY ===\n");

    freeList(list);
    free(list);

    printf("Memory freed successfully\n");

    return 0;
}

LinkedList *createList()
{
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));

    if (list == NULL)
    {
        printf("Error allocating memory to list\n");
        exit(1);
    }

    list->head = NULL;
    return list;
}

Node *createNode(int value)
{
    Node *node = (Node *)malloc(sizeof(Node));

    if (node == NULL)
    {
        printf("Error allocating memory to node\n");
        exit(1);
    }

    node->value = value;
    node->next = NULL;

    return node;
}

void pushLeft(LinkedList *linkedList, int value)
{
    Node *newNode = createNode(value);

    newNode->next = linkedList->head;
    linkedList->head = newNode;
}

void pushRight(LinkedList *linkedList, int value)
{
    Node *newNode = createNode(value);

    if (linkedList->head == NULL)
    {
        linkedList->head = newNode;
        return;
    }

    Node *current = linkedList->head;

    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = newNode;
}

Node *removeValue(LinkedList *linkedList, int value)
{

    if (linkedList->head == NULL)
        return NULL;

    if (linkedList->head->value == value)
    {
        Node *removed = linkedList->head;
        linkedList->head = linkedList->head->next;
        removed->next = NULL;
        return removed;
    }

    Node *current = linkedList->head;

    while (current->next != NULL)
    {

        if (current->next->value == value)
        {
            Node *removed = current->next;

            current->next = current->next->next;

            removed->next = NULL;

            return removed;
        }

        current = current->next;
    }

    return NULL;
}

Node *removeAt(LinkedList *linkedList, int index)
{

    if (linkedList->head == NULL)
        return NULL;

    if (index == 0)
    {
        Node *removed = linkedList->head;

        linkedList->head = linkedList->head->next;

        removed->next = NULL;

        return removed;
    }

    Node *current = linkedList->head;
    int currentIndex = 0;

    while (current->next != NULL)
    {

        if (currentIndex + 1 == index)
        {

            Node *removed = current->next;

            current->next = current->next->next;

            removed->next = NULL;

            return removed;
        }

        current = current->next;
        currentIndex++;
    }

    return NULL;
}

Node *get(LinkedList *linkedList, int index)
{

    if (linkedList->head == NULL)
        return NULL;

    Node *current = linkedList->head;
    int currentIndex = 0;

    while (current != NULL)
    {

        if (currentIndex == index)
            return current;

        current = current->next;
        currentIndex++;
    }

    return NULL;
}

int contains(LinkedList *linkedList, int value)
{

    if (linkedList->head == NULL)
        return 0;

    Node *current = linkedList->head;

    while (current != NULL)
    {

        if (current->value == value)
            return 1;

        current = current->next;
    }

    return 0;
}
int size(LinkedList *linkedList)
{
    if (linkedList->head == NULL) return 0;
    
    int size = 0;

    Node *current = linkedList->head;

    while (current != NULL)
    {
        size++;
        current = current->next;
    }

    return size;
}

void freeList(LinkedList* linkedList) {
    Node *current = linkedList->head;

    Node *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
}
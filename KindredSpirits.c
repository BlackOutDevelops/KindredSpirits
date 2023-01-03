// Joshua Frazer jo227789
// COP 3502, Spring 2020
// Using Atom & Linux Bash Shell on Windows 10.
#include <stdio.h>
#include <stdlib.h>
#include "KindredSpirits.h"

// Fancy linked list to maintain head and tail pointers
typedef struct listNode
{
  int data;
  struct listNode *next;
} listNode;

typedef struct linkedList
{
  listNode *head;
  listNode *tail;
} linkedList;

// Auxilary functions
node *createNode(int data);
node *makeReflectionHelper(node *root, node *reflection);
node *reflectionHelper(node *root, node *reflection);
int checkEquivalence(listNode *a, listNode *b);
linkedList *preorder(node *root);
linkedList *preorderHelper(node *root, linkedList *list);
linkedList *createLinkedList(void);
linkedList *postorder(node *root);
linkedList *postorderHelper(node *root, linkedList *list);
listNode *createListNode(int data);
void insertToList(linkedList *list, int data);
linkedList *destroyList(linkedList *list);
node *destroyTree(node *root);

// Checks if two roots passed are reflections of each other recursively
int isReflection(node *a, node *b)
{
    if (a == NULL && b == NULL)
        return 1;
    else if (a == NULL || b == NULL)
        return 0;
    else if (a->data != b->data)
        return 0;
    else
        return isReflection(a->right, b->left) && isReflection(a->left, b->right);
}

// Makes reflection of root passed
node *makeReflection(node *root)
{
    node *reflection;

    if (root == NULL)
        return NULL;

    reflection = makeReflectionHelper(root, reflection);

    return reflection;
}

// Helper to makeReflection that continues the function recursively
node *makeReflectionHelper(node *root, node *reflection)
{
    if (root == NULL)
        return 0;

    reflection = createNode(root->data);
    if (root->right != NULL)
        reflection->left = makeReflectionHelper(root->right, reflection->left);
    if (root->left != NULL)
        reflection->right = makeReflectionHelper(root->left, reflection->right);

    return reflection;
}

// Checks if two roots passed are kindred spirits
int kindredSpirits(node *a, node *b)
{
    linkedList *preorderA, *preorderB, *postorderA, *postorderB;

    if (a == NULL && b == NULL)
        return 1;

    // Creates a preorder linked list of root a
    preorderA = preorder(a);
    // Creates a postorder linked list of root a
    postorderA = postorder(a);
    // Creates a preorder linked list of root b
    preorderB = preorder(b);
    // Creates a postorder linked list of root b
    postorderB = postorder(b);

    if (checkEquivalence(preorderA->head, postorderB->head) == 1)
    {
        // Frees all linked lists that were created
        destroyList(preorderA);
        destroyList(preorderB);
        destroyList(postorderA);
        destroyList(postorderB);
        return 1;
    }
    else if (checkEquivalence(preorderB->head, postorderA->head) == 1)
    {
        // Frees all linked lists that were created
        destroyList(preorderA);
        destroyList(preorderB);
        destroyList(postorderA);
        destroyList(postorderB);
        return 1;
    }
    else
    {
        // Frees all linked lists that were created
        destroyList(preorderA);
        destroyList(preorderB);
        destroyList(postorderA);
        destroyList(postorderB);
        return 0;
    }
}

// Checks if two linked list equal each other
int checkEquivalence(listNode *a, listNode *b)
{
  if (a == NULL && b == NULL)
      return 1;
  else if (a->data != b->data)
      return 0;
  else
      return checkEquivalence(a->next, b->next);
}

// Creates a tree node
node *createNode(int data)
{
  	node *n = malloc(sizeof(node));

  	n->data = data;
  	n->left = n->right = NULL;

  	return n;
}

// Creates a linked list in preorder traversal from a tree root
linkedList *preorder(node *root)
{
    linkedList *list;
    if (root == NULL)
        return NULL;

    list = createLinkedList();

    // Calls helper function to do recursively
    list = preorderHelper(root, list);

    return list;
}

// Helper function to preorder to finish linked list recursively
linkedList *preorderHelper(node *root, linkedList *list)
{
    if (root == NULL)
        return NULL;

    insertToList(list, root->data);
    preorderHelper(root->left, list);
    preorderHelper(root->right, list);

    return list;
}

// Creates a linked list in postorder traversal from a tree root
linkedList *postorder(node *root)
{
    linkedList *list;
    if (root == NULL)
        return NULL;

    list = createLinkedList();

    list = postorderHelper(root, list);

    return list;
}

// Helper function to postorder to finish linked list recursively
linkedList *postorderHelper(node *root, linkedList *list)
{
    if (root == NULL)
        return NULL;

    postorderHelper(root->left, list);
    postorderHelper(root->right, list);
    insertToList(list, root->data);

    return list;
}

// Function to create a linked list
linkedList *createLinkedList(void)
{
    linkedList *list = malloc(sizeof(linkedList));
    return list;
}

// Function to create a linked list node
listNode *createListNode(int data)
{
    listNode *n = malloc(sizeof(listNode));

    n->data = data;
    n->next = NULL;

    return n;
}

// Copy of tail_insert in LinkedList.c from queues.zip
void insertToList(linkedList *list, int data)
{
    if (list == NULL)
        return;

    if (list->tail == NULL)
    {
        list->head = list->tail = createListNode(data);
        return;
    }

    list->tail->next = createListNode(data);
    list->tail = list->tail->next;
}

// Function to free allocated memory for a tree
node *destroyTree(node *root)
{
    if (root == NULL)
        return NULL;

    destroyTree(root->left);
    destroyTree(root->right);
    free(root);

    return NULL;
}

// Function to free allocated memory for a linked list
linkedList *destroyList(linkedList *list)
{
    listNode *current;
    listNode *temp;

    // Checks if linked list passed is NULL
    if (list == NULL)
        return NULL;

    // Pointer to hold linked list for freeing purposes
    current = list->head;

    // free loop for linked list
    while (current != NULL)
    {
        temp = current->next;
        free(current);
        current = temp;
    }

    // frees the last bit of linked list
    free(list);

    return NULL;
}

double difficultyRating(void)
{
    return 2.0;
}

double hoursSpent(void)
{
    return 10.0;
}

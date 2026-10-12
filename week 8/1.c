// 1. implement a function that, given the current tab, moves to next (forward) and one that moves to prev (backward), printing the tab visited each time.
// 2. averse and print the tab list left-to-right, then again right-to-left, to prove both directions work from any node.Do all the tasks before this one
// — implement "drag tab to new position": remove a node from its current position and reinsert it at a specified position, without allocating a new node. ("Reverse Tabs" power-user feature) — reverse the entire list in place by swapping prev and next at every node, without creating a new list.
// 3. delete a node from a given position, re-linking its previous and next neighbours directly to each other. Handle the edge case of closing the only open tab. as two separate special cases of deletion.




#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int tab_id;
    char url[100];
    struct Node *prev, *next;
};

struct Node *head = NULL, *tail = NULL;
int count = 0;

/* Create a new node */
struct Node *createNode(int id, char url[]) {
    struct Node *n = malloc(sizeof(struct Node));

    if (n == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    n->tab_id = id;
    strcpy(n->url, url);
    n->prev = n->next = NULL;

    return n;
}

/* Get node at a position (starting from 1) */
struct Node *getNode(int pos) {
    if (pos < 1 || pos > count)
        return NULL;

    struct Node *temp = head;

    for (int i = 1; i < pos; i++)
        temp = temp->next;

    return temp;
}

/* 1. Open the first tab */
void openFirst(int id, char url[]) {
    if (head != NULL) {
        printf("List is not empty.\n");
        return;
    }

    head = tail = createNode(id, url);
    count++;

    printf("First tab opened: %s\n", url);
}

/* 2. Insert at end (Ctrl+T) */
void insertEnd(int id, char url[]) {
    struct Node *n = createNode(id, url);

    if (head == NULL) {
        head = tail = n;
    } else {
        n->prev = tail;
        tail->next = n;
        tail = n;
    }

    count++;
}

/* 3. Insert after a given tab ID */
void insertAfter(int targetID, int id, char url[]) {
    struct Node *temp = head;

    while (temp != NULL && temp->tab_id != targetID)
        temp = temp->next;

    if (temp == NULL) {
        printf("Tab not found.\n");
        return;
    }

    struct Node *n = createNode(id, url);

    n->prev = temp;
    n->next = temp->next;

    if (temp->next != NULL)
        temp->next->prev = n;
    else
        tail = n;

    temp->next = n;
    count++;
}

/* 4. Insert at beginning */
void insertBeginning(int id, char url[]) {
    struct Node *n = createNode(id, url);

    if (head == NULL) {
        head = tail = n;
    } else {
        n->next = head;
        head->prev = n;
        head = n;
    }

    count++;
}

/* 5. Navigate forward */
void moveNext(struct Node **current) {
    if (*current != NULL && (*current)->next != NULL) {
        *current = (*current)->next;
        printf("Forward: %s\n", (*current)->url);
    } else {
        printf("No next tab.\n");
    }
}

/* 5. Navigate backward */
void movePrev(struct Node **current) {
    if (*current != NULL && (*current)->prev != NULL) {
        *current = (*current)->prev;
        printf("Backward: %s\n", (*current)->url);
    } else {
        printf("No previous tab.\n");
    }
}

/* 6. Display left to right */
void displayForward() {
    struct Node *temp = head;

    printf("Left to right: ");
    while (temp != NULL) {
        printf("%s ", temp->url);
        temp = temp->next;
    }
    printf("\n");
}

/* 6. Display right to left */
void displayBackward() {
    struct Node *temp = tail;

    printf("Right to left: ");
    while (temp != NULL) {
        printf("%s ", temp->url);
        temp = temp->prev;
    }
    printf("\n");
}

/* 7. Move a tab without creating a new node */
void moveTab(int oldPos, int newPos) {
    if (oldPos < 1 || oldPos > count ||
        newPos < 1 || newPos > count) {
        printf("Invalid position.\n");
        return;
    }

    if (oldPos == newPos)
        return;

    struct Node *n = getNode(oldPos);

    /* Remove node from its old position */
    if (n->prev != NULL)
        n->prev->next = n->next;
    else
        head = n->next;

    if (n->next != NULL)
        n->next->prev = n->prev;
    else
        tail = n->prev;

    count--;

    /* Insert the same node at the new position */
    if (newPos == 1) {
        n->prev = NULL;
        n->next = head;

        if (head != NULL)
            head->prev = n;
        else
            tail = n;

        head = n;
    } else {
        struct Node *temp = getNode(newPos - 1);

        n->prev = temp;
        n->next = temp->next;

        if (temp->next != NULL)
            temp->next->prev = n;
        else
            tail = n;

        temp->next = n;
    }

    count++;
}

/* 8. Reverse the entire list in place */
void reverseTabs() {
    struct Node *current = head;
    struct Node *temp = NULL;

    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;

        current = current->prev;
    }

    temp = head;
    head = tail;
    tail = temp;
}

/* 9 and 10. Delete a tab at a position */
void deleteTab(int pos, struct Node **current) {
    if (pos < 1 || pos > count) {
        printf("Invalid position.\n");
        return;
    }

    struct Node *n = getNode(pos);

    /* Special case: only one tab */
    if (count == 1) {
        free(n);
        head = tail = NULL;
        *current = NULL;
        count = 0;
        printf("Only tab closed. List is empty.\n");
        return;
    }

    /* Update current tab if it is deleted */
    if (*current == n)
        *current = (n->next != NULL) ? n->next : n->prev;

    /* Connect neighbouring nodes */
    if (n->prev != NULL)
        n->prev->next = n->next;
    else
        head = n->next;

    if (n->next != NULL)
        n->next->prev = n->prev;
    else
        tail = n->prev;

    free(n);
    count--;
}

/* Free all remaining nodes */
void freeList() {
    struct Node *temp = head;

    while (temp != NULL) {
        struct Node *nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }

    head = tail = NULL;
    count = 0;
}

int main() {
    struct Node *current = NULL;

    /* Task 1 */
    openFirst(1, "Google");
    current = head;

    /* Task 2 */
    insertEnd(2, "YouTube");
    insertEnd(3, "GitHub");

    /* Task 3 */
    insertAfter(1, 4, "Wikipedia");

    /* Task 4 */
    insertBeginning(5, "Gmail");

    /* Task 5 */
    current = head;
    moveNext(&current);
    movePrev(&current);

    /* Task 6 */
    displayForward();
    displayBackward();

    /* Task 7 */
    moveTab(2, 4);
    displayForward();

    /* Task 8 */
    reverseTabs();
    displayForward();
    displayBackward();

    /* Task 9: Delete a middle tab */
    deleteTab(3, &current);
    displayForward();

    /* Task 10: Delete the first tab */
    deleteTab(1, &current);
    displayForward();

    /* Close all remaining tabs */
    while (count > 0)
        deleteTab(1, &current);

    displayForward();

    freeList();
    return 0;
}


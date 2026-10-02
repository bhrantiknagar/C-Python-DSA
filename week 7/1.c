// Implement the single linked list & perform the following on it:
// 1. create a list.
// 2. traverse the list.  


#include <stdio.h>
#include <stdlib.h>

struct Link {
    int data;
    struct Link *ptr;
};

typedef struct Link Link;

int main() {
    Link *head = NULL, *temp, *newNode;
    int n, i;

    // 1. Create a linked list
    printf("Enter number of nodes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        newNode = (Link *)malloc(sizeof(Link));

        printf("Enter data: ");
        scanf("%d", &newNode->data);

        newNode->ptr = NULL;

        if (head == NULL) {
            head = newNode;
            temp = head;
        } else {
            temp->ptr = newNode;
            temp = newNode;
        }
    }

    // 2. Traverse the list
    printf("\nLinked List: ");
    temp = head;

    while (temp != NULL) {
        printf("%d > ", temp->data);
        temp = temp->ptr;
    }
 
    printf("NULL\n");

    return 0;
}

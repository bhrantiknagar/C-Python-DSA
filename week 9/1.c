// Create a program for the binary search tree 
// 1. Insert a Node
// 2. Search a node
// 3. Traversal
// 4. Exit




#include <stdio.h>
#include <stdlib.h>

// Structure of a Node
struct Node {
    int data;
    struct Node *left, *right;
};

// Create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// 1. Insert a Node
struct Node* insert(struct Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    }
    else if (value > root->data) {
        root->right = insert(root->right, value);
    }
    else {
        printf("Duplicate values are not allowed!\n");
    }

    return root;
}

// 2. Search a Node
void search(struct Node* root, int value) {
    if (root == NULL) {
        printf("Node not found!\n");
    }
    else if (root->data == value) {
        printf("Node found!\n");
    }
    else if (value < root->data) {
        search(root->left, value);
    }
    else {
        search(root->right, value);
    }
}

// 3(a). Inorder Traversal
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// 3(b). Preorder Traversal
void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// 3(c). Postorder Traversal
void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// Main Function
int main() {
    struct Node* root = NULL;
    int choice, value, ch;

    do {
        printf("\n\n--- BINARY SEARCH TREE ---\n");
        printf("1. Insert a Node\n");
        printf("2. Search a Node\n");
        printf("3. Traversal\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                printf("Node inserted successfully!\n");
                break;

            case 2:
                printf("Enter value to search: ");
                scanf("%d", &value);
                search(root, value);
                break;

            case 3:
                printf("\n--- TRAVERSAL MENU ---\n");
                printf("1. Inorder\n");
                printf("2. Preorder\n");
                printf("3. Postorder\n");
                printf("Enter your choice: ");
                scanf("%d", &ch);

                switch (ch) {
                    case 1:
                        printf("Inorder Traversal: ");
                        inorder(root);
                        break;

                    case 2:
                        printf("Preorder Traversal: ");
                        preorder(root);
                        break;

                    case 3:
                        printf("Postorder Traversal: ");
                        postorder(root);
                        break;

                    default:
                        printf("Invalid traversal choice!\n");
                }
                break;

            case 4:
                printf("Exiting Program...\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 4);

    return 0;
}

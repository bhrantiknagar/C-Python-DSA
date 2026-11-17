// Implementing Binary Search Tree (BST) and AVL Tree




#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int accession_no;
    char title[30];
    int height;
    struct Node *left, *right;
};

// Get height
int height(struct Node *n) {
    if (n == NULL)
        return 0;
    return n->height;
}

// Create new node
struct Node* createNode(int key) {
    struct Node *n = malloc(sizeof(struct Node));

    n->accession_no = key;
    sprintf(n->title, "Book-%d", key);
    n->height = 1;
    n->left = n->right = NULL;

    return n;
}

// 1. BST Insertion
struct Node* bstInsert(struct Node *root, int key) {
    if (root == NULL)
        return createNode(key);

    if (key < root->accession_no)
        root->left = bstInsert(root->left, key);
    else if (key > root->accession_no)
        root->right = bstInsert(root->right, key);

    return root;
}

// BST Search
void bstSearch(struct Node *root, int key) {
    int count = 0;

    while (root != NULL) {
        count++;

        if (root->accession_no == key) {
            printf("Book Found: %s\n", root->title);
            printf("Nodes Visited: %d\n", count);
            return;
        }

        if (key < root->accession_no)
            root = root->left;
        else
            root = root->right;
    }

    printf("Book Not Found!\n");
    printf("Nodes Visited: %d\n", count);
}

// Balance Factor
int balance(struct Node *n) {
    if (n == NULL)
        return 0;

    return height(n->left) - height(n->right);
}

// Right Rotation
struct Node* rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = 1 + (height(y->left) > height(y->right)
                     ? height(y->left) : height(y->right));

    x->height = 1 + (height(x->left) > height(x->right)
                     ? height(x->left) : height(x->right));

    return x;
}

// Left Rotation
struct Node* leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *t2 = y->left;

    y->left = x;
    x->right = t2;

    x->height = 1 + (height(x->left) > height(x->right)
                     ? height(x->left) : height(x->right));

    y->height = 1 + (height(y->left) > height(y->right)
                     ? height(y->left) : height(y->right));

    return y;
}

// 2. AVL Insertion
struct Node* avlInsert(struct Node *root, int key) {
    if (root == NULL)
        return createNode(key);

    if (key < root->accession_no)
        root->left = avlInsert(root->left, key);
    else if (key > root->accession_no)
        root->right = avlInsert(root->right, key);
    else
        return root;

    // Update height
    int lh = height(root->left);
    int rh = height(root->right);

    root->height = 1 + (lh > rh ? lh : rh);

    int bf = balance(root);

    // LL Case
    if (bf > 1 && key < root->left->accession_no)
        return rightRotate(root);

    // RR Case
    if (bf < -1 && key > root->right->accession_no)
        return leftRotate(root);

    // LR Case
    if (bf > 1 && key > root->left->accession_no) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL Case
    if (bf < -1 && key < root->right->accession_no) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Search in AVL Tree
void avlSearch(struct Node *root, int key) {
    int count = 0;

    while (root != NULL) {
        count++;

        if (root->accession_no == key) {
            printf("Book Found: %s\n", root->title);
            printf("Nodes Visited: %d\n", count);
            return;
        }

        if (key < root->accession_no)
            root = root->left;
        else
            root = root->right;
    }

    printf("Book Not Found!\n");
    printf("Nodes Visited: %d\n", count);
}

// Inorder Traversal
void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->accession_no);
        inorder(root->right);
    }
}

// Display Tree
void display(struct Node *root, int space) {
    if (root == NULL)
        return;

    space += 5;

    display(root->right, space);

    printf("\n");
    for (int i = 5; i < space; i++)
        printf(" ");

    printf("%d", root->accession_no);

    display(root->left, space);
}

int main() {
    struct Node *bst = NULL;
    struct Node *avl = NULL;

    int keys[] = {
        10, 20, 30, 40, 50,
        60, 70, 80, 90, 100,
        110, 120, 130, 140, 150
    };

    int i, key = 150;

    // Insert into both trees
    for (i = 0; i < 15; i++) {
        bst = bstInsert(bst, keys[i]);
        avl = avlInsert(avl, keys[i]);
    }

    printf("\n--- BINARY SEARCH TREE ---\n");
    display(bst, 0);

    printf("\n\nBST Inorder: ");
    inorder(bst);

    printf("\n\nBST Search for %d:\n", key);
    bstSearch(bst, key);

    printf("\n\n--- AVL TREE ---\n");
    display(avl, 0);

    printf("\n\nAVL Inorder: ");
    inorder(avl);

    printf("\n\nAVL Search for %d:\n", key);
    avlSearch(avl, key);

    return 0;
}

// University Admission Office using Binary Search Tree (BST)



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int application_id, score;
    char name[30];
    struct Node *left, *right;
};

// Create a new node
struct Node* createNode(int id, char name[], int score) {
    struct Node* newNode = malloc(sizeof(struct Node));

    newNode->application_id = id;
    strcpy(newNode->name, name);
    newNode->score = score;
    newNode->left = newNode->right = NULL;

    return newNode;
}

// Insert applicant
struct Node* insert(struct Node* root, int id, char name[], int score) {
    if (root == NULL)
        return createNode(id, name, score);

    if (score < root->score)
        root->left = insert(root->left, id, name, score);
    else if (score > root->score)
        root->right = insert(root->right, id, name, score);

    return root;
}

// Search applicant
void search(struct Node* root, int score) {
    int count = 0;

    while (root != NULL) {
        count++;

        if (root->score == score) {
            printf("\nApplicant Found!");
            printf("\nID: %d", root->application_id);
            printf("\nName: %s", root->name);
            printf("\nScore: %d", root->score);
            printf("\nNodes Visited: %d\n", count);
            return;
        }

        if (score < root->score)
            root = root->left;
        else
            root = root->right;
    }

    printf("\nApplicant Not Found!");
    printf("\nNodes Visited: %d\n", count);
}

// Inorder traversal
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->score);
        inorder(root->right);
    }
}

int main() {
    struct Node* root = NULL;
    int id[] = {101,102,103,104,105,106,107,108,109,110,111,112};
    int score[] = {75,60,85,50,68,80,90,45,55,65,72,88};

    char name[][30] = {
        "Aarav", "Priya", "Rahul", "Neha",
        "Aman", "Sneha", "Karan", "Riya",
        "Vikas", "Anjali", "Rohit", "Pooja"
    };

    int i;

    printf("Inserting 12 Applicants...\n");

    for (i = 0; i < 12; i++) {
        root = insert(root, id[i], name[i], score[i]);
    }

    printf("\nInorder Traversal (Ranking): ");
    inorder(root);

    printf("\n\n--- Successful Search ---");
    search(root, 65);

    printf("\n--- Unsuccessful Search ---");
    search(root, 67);

    return 0;
}

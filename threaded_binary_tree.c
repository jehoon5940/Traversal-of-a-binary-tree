#include <stdio.h>
#include <stdlib.h>

typedef struct ThreadedTreeNode {
    char data;
    struct ThreadedTreeNode* left;
    struct ThreadedTreeNode* right;
    int leftThread;
    int rightThread;
} ThreadedTreeNode;

ThreadedTreeNode* createNode(char data) {
    ThreadedTreeNode* node = (ThreadedTreeNode*)malloc(sizeof(ThreadedTreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->leftThread = 0;
    node->rightThread = 0;
    return node;
}

ThreadedTreeNode* leftMost(ThreadedTreeNode* node) {
    if (node == NULL) return NULL;
    while (node->left != NULL && node->leftThread == 0) {
        node = node->left;
    }
    return node;
}

void inOrder(ThreadedTreeNode* root) {
    ThreadedTreeNode* current = leftMost(root);
    while (current != NULL) {
        printf("%c ", current->data);
        if (current->rightThread == 1) {
            current = current->right;
        } else {
            current = leftMost(current->right);
        }
    }
}

void addThreadedTreeNode(ThreadedTreeNode** root, char data) {
    ThreadedTreeNode* newNode = createNode(data);
    if (*root == NULL) {
        *root = newNode;
        return;
    }

    ThreadedTreeNode* current = *root;
    ThreadedTreeNode* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            if (current->leftThread == 0) {
                current = current->left;
            } else {
                break;
            }
        } else {
            if (current->rightThread == 0) {
                current = current->right;
            } else {
                break;
            }
        }
    }

    if (data < parent->data) {
        newNode->left = parent->left;
        newNode->right = parent;
        parent->leftThread = 0;
        parent->left = newNode;
    } else {
        newNode->left = parent;
        newNode->right = parent->right;
        parent->rightThread = 0;
        parent->right = newNode;
    }
}

int main() {
    ThreadedTreeNode* root = NULL;
    addThreadedTreeNode(&root, 'D');
    addThreadedTreeNode(&root, 'B');
    addThreadedTreeNode(&root, 'A');
    addThreadedTreeNode(&root, 'C');
    addThreadedTreeNode(&root, 'F');
    addThreadedTreeNode(&root, 'E');
    addThreadedTreeNode(&root, 'G');

    printf("스레드 이진 트리의 중위 순회: ");
    inOrder(root);
    printf("\n");

    return 0;
}

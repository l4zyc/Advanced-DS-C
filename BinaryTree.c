#include <stdio.h>
#include <stdlib.h>

// Create a node
struct Node {
    struct Node *left, *right;
    int value;
} *root = NULL;

struct Node* newNode(int value) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->value = value;
    node->left = node->right = NULL;
    return node;
}

// Insert node
struct Node* insert(struct Node* root, int value) {
    if (root == NULL) {
        return newNode(value);
    } else if (root->value > value) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }
    return root;
}

struct Node* delete(struct Node* root, int value) {
    if (root == NULL) {
        return root;
    } else if (root->value > value) {
        root->left = delete(root->left, value);
    } else if (root->value < value) {
        root->right = delete(root->right, value);
    } else {
        if (root->left == NULL && root->right == NULL) {
            // No children
            free(root);
            return NULL;
        } else if (root->left == NULL) {
            // One child (right)
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            // One child (left)
            struct Node* temp = root->left;
            free(root);
            return temp;
        } else {
            // Two children
            struct Node* temp = findMin(root->right);
            root->value = temp->value;
            root->right = delete(root->right, temp->value);
        }
    }
    return root;
}

void inOrder(struct Node* root) {
    if (root == NULL) {
        return;
    } else {
        inOrder(root->left);
        printf("%d\n", root->value);
        inOrder(root->right);
    }
}

void update(struct Node* root, int value, int newValue) {
    if (root == NULL) {
        return;
    } else {
        update(root->left, value, newValue);
        if (root->value == value) {
            root->value = newValue;
            return;
        }
        update(root->right, value, newValue);
    }
}

struct Node* search(struct Node* root, int val) {
    if (root == NULL || root->value == val) {
        return root;
    }

    if (root->value > val) {
        return search(root->left, val);
    }

    return search(root->right, val);
}

struct Node* findMin(struct Node* root) {
    if (root == NULL) {
        return root;
    }

    if (root->left != NULL) {
        return findMin(root->left);
    }

    return root;
}

int main() {
    root = insert(root, 4);
    root = insert(root, 2);
    root = insert(root, 1);
    root = insert(root, 3);
    root = insert(root, 5);
    root = insert(root, 6);

    inOrder(root);
    printf("%d\n", search(root, 2)->value);
    return 0;
}
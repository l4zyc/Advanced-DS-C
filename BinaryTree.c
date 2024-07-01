#include <stdio.h>
#include <stdlib.h>

//Create a node
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

//insert node
struct Node* insert(struct Node* root, int value) {
    if(root == NULL) {
        return newNode(value);
    } else if(root->value > value) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }
    return root;
}

struct Node* delete(struct Node* root, int value) {
    if(root == NULL) {
        return root;
    } else if(root->value > value) {
        root->left = delete(root->left, value);
    } else if(root->value < value) {
        root->right = delete(root->right, value);
    } else {
        struct Node* child = root->left ? root->left : root->right;

        if(!child) {
            struct Node* temp = root;
            root = NULL;
            free(temp);
        } else {
            if(root->left || root->right) {
                root = child;
            } else {
                struct Node* ptr = root->left;
                while(ptr->right)  ptr = ptr->right;
                root->value = ptr->value;

                root->left = delete(root->left, ptr->value);
            }
        }
    }
}

void inOrder(struct Node* root) {
    if(root == NULL) {
        return;
    } else {
        inOrder(root->left);
        printf("%d\n", root->value);
        inOrder(root->right);
    }
}

void update(struct Node *root, int value, int newValue) {
    if(root == NULL) {
        return;
    } else {
        update(root->left, value , newValue);
        if(root->value == value) {
            root->value = newValue;
            return;
        }
        update(root->right, value , newValue);
    }
}

struct Node* search(struct Node* root, int val) {
    if(root == NULL || root->value == val) {
        return root;
    }

    if(root->value > val) {
        return search(root->left, val);
    }

    return search(root->right, val);
}

struct Node* findMin(struct Node* root) {
    if(root == NULL) {
        return root;
    }

    if(root->left != NULL) {
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
    printf("%d", search(root,2)->value);
    return 0;
}
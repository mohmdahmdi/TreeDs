#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* parent;
    struct Node** children;
    int childCount;
} Node;

Node* createNode(int data, Node* parent) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->parent = parent;
    newNode->children = NULL;
    newNode->childCount = 0;
    return newNode;
}

int NodeDepth(Node* node) {
    int depth = 0;
    while (node->parent != NULL) {
        depth++;
        node = node->parent;
    }
    return depth;
}

int IsParentChild(Node* parent, Node* child) {
    return (child->parent == parent);
}

int IsAncestor(Node* ancestor, Node* node) {
    while (node != NULL) {
        if (node->parent == ancestor) {
            return 1;
        }
        node = node->parent;
    }
    return 0;
}

int IsInternal(Node* node) {
    return (node->childCount > 0);
}

void NodeDescendants(Node* node) {
    if (node == NULL) return;
    for (int i = 0; i < node->childCount; i++) {
        printf("%d ", node->children[i]->data);
        NodeDescendants(node->children[i]);
    }
}

void GetSiblings(Node* node) {
    if (node->parent == NULL) return; 

    Node* parent = node->parent;
    for (int i = 0; i < parent->childCount; i++) {
        if (parent->children[i] != node) {
            printf("%d ", parent->children[i]->data);
        }
    }
}

// ----------------------------------------------------------------
void AddChild(Node* parent, Node* child) {
    parent->children = (Node**)realloc(parent->children, sizeof(Node*) * (parent->childCount + 1));
    parent->children[parent->childCount] = child;
    parent->childCount++;
}

int main() {
    Node* root = createNode(1, NULL);
    Node* child1 = createNode(2, root);
    Node* child2 = createNode(3, root);
    AddChild(root, child1);
    AddChild(root, child2);

    printf("Depth of child1: %d\n", NodeDepth(child1));
    printf("Is root parent of child1? %d\n", IsParentChild(root, child1));

    Node* grandchild = createNode(4, child1);
    AddChild(child1, grandchild);

    printf("Is root ancestor of grandchild? %d\n", IsAncestor(root, grandchild));
    printf("Descendants of root: ");
    NodeDescendants(root);
    printf("\n");

    printf("Siblings of child1: ");
    GetSiblings(child1);
    printf("\n");

    return 0;
}

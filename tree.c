#include <stdio.h>
#include <stdlib.h>

// define a structure template for a node in the tree.
typedef struct NodeStruct {
    int data;
    struct NodeStruct* parent;
    struct NodeStruct** children;
    int childCount;      // number of children the node currently has.
} NodeStruct;

NodeStruct* CreateNode_Function(int data, NodeStruct* parent);
int NodeDepth_Function(NodeStruct* node);
int IsParentChild_Function(NodeStruct* parent, NodeStruct* child);
int IsAncestor_Function(NodeStruct* ancestor, NodeStruct* node);
int IsInternal_Function(NodeStruct* node);
void NodeDescendants_Function(NodeStruct* node);
void GetSiblings_Function(NodeStruct* node);
void AddChild_Function(NodeStruct* parent, NodeStruct* child) ;   // DRY
void FreeNode_Function(NodeStruct* node);

int main() {
    NodeStruct* root = CreateNode_Function(1, NULL);
    NodeStruct* child1 = CreateNode_Function(2, root);
    NodeStruct* child2 = CreateNode_Function(3, root);
    AddChild_Function(root, child1);
    AddChild_Function(root, child2);

    printf("Depth of child1: %d\n", NodeDepth_Function(child1));
    printf("Is root parent of child1? %d\n", IsParentChild_Function(root, child1));

    NodeStruct* grandchild = CreateNode_Function(4, child1);
    AddChild_Function(child1, grandchild);

    printf("Is root ancestor of grandchild? %d\n", IsAncestor_Function(root, grandchild));
    printf("Descendants of root: ");
    NodeDescendants_Function(root);
    printf("\n");

    printf("Siblings of child1: ");
    GetSiblings_Function(child1);
    printf("\n");

    FreeNode_Function(root);
    printf("memory freed successfully\n");

    return 0;
}

NodeStruct* CreateNode_Function(int data, NodeStruct* parent) {
    // allocate memory for a new node and cast it to the appropriate type
    NodeStruct* newNode = (NodeStruct*)malloc(sizeof(NodeStruct));
    newNode->data = data;
    newNode->parent = parent;
    newNode->children = NULL;
    newNode->childCount = 0;
    return newNode;
}

int NodeDepth_Function(NodeStruct* node) {
    int depth = 0;
    while (node->parent != NULL) {
        depth++;
        node = node->parent;
    }
    return depth;
}

int IsParentChild_Function(NodeStruct* parent, NodeStruct* child) {
    return (child->parent == parent);
}

int IsAncestor_Function(NodeStruct* ancestor, NodeStruct* node) {
    while (node != NULL) {
        if (node->parent == ancestor) {
            return 1;
        }
        node = node->parent;
    }
    return 0;
}

int IsInternal_Function(NodeStruct* node) {
    return (node->childCount > 0);
}

void NodeDescendants_Function(NodeStruct* node) {
    if (node == NULL) return;        
    for (int i = 0; i < node->childCount; i++) {
        printf("%d ", node->children[i]->data);
        NodeDescendants_Function(node->children[i]);
    }
}

void GetSiblings_Function(NodeStruct* node) {
    if (node->parent == NULL) return;      // if node is root, return

    NodeStruct* parent = node->parent;
    for (int i = 0; i < parent->childCount; i++) {
        if (parent->children[i] != node) {
            printf("%d ", parent->children[i]->data);
        }
    }
}

void AddChild_Function(NodeStruct* parent, NodeStruct* child) {
    // Resize the children array to accommodate the new child.
    parent->children = (NodeStruct**)realloc(parent->children, sizeof(NodeStruct*) * (parent->childCount + 1));
    parent->children[parent->childCount] = child;
    parent->childCount++;
}

// function to free node and its children recursively 
void FreeNode_Function(NodeStruct* node) {
    if (node == NULL) return;

    // free memory for all children
    for (int i = 0; i < node->childCount; i++) {
        FreeNode_Function(node->children[i]);
    }

    // free children array
    free(node->children);
    // free the node
    free(node);
}
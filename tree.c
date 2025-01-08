#include <stdio.h>
#include <stdlib.h>

// define a structure template for a node in the tree.
typedef struct NodeStruct {
    int data;
    struct NodeStruct* parent;
    struct NodeStruct** children;
    int childCount;      // number of children the node currently has.
} NodeStruct;

NodeStruct* Create_Node(int data, NodeStruct* parent);
int Node_Depth(NodeStruct* node);
int Is_Parent_Child(NodeStruct* parent, NodeStruct* child);
int Is_Ancestor(NodeStruct* ancestor, NodeStruct* node);
int Is_Internal(NodeStruct* node);
void Node_Descendants(NodeStruct* node);
void Get_Siblings(NodeStruct* node);
void Add_Child(NodeStruct* parent, NodeStruct* child) ;   // DRY
void Free_Node(NodeStruct* node);

int main() {
    NodeStruct* root = Create_Node(1, NULL);
    NodeStruct* child1 = Create_Node(2, root);
    NodeStruct* child2 = Create_Node(3, root);
    Add_Child(root, child1);
    Add_Child(root, child2);

    printf("Depth of child1: %d\n", Node_Depth(child1));
    printf("Is root parent of child1? %d\n", Is_Parent_Child(root, child1));

    NodeStruct* grandchild = Create_Node(4, child1);
    Add_Child(child1, grandchild);

    printf("Is root ancestor of grandchild? %d\n", Is_Ancestor(root, grandchild));
    printf("Descendants of root: ");
    Node_Descendants(root);
    printf("\n");

    printf("Siblings of child1: ");
    Get_Siblings(child1);
    printf("\n");

    Free_Node(root);
    printf("memory freed successfully\n");

    return 0;
}

NodeStruct* Create_Node(int data, NodeStruct* parent) {
    // allocate memory for a new node and cast it to the appropriate type
    NodeStruct* newNode = (NodeStruct*)malloc(sizeof(NodeStruct));
    newNode->data = data;
    newNode->parent = parent;
    newNode->children = NULL;
    newNode->childCount = 0;
    return newNode;
}

int Node_Depth(NodeStruct* node) {
    int depth = 0;
    while (node->parent != NULL) {
        depth++;
        node = node->parent;
    }
    return depth;
}

int Is_Parent_Child(NodeStruct* parent, NodeStruct* child) {
    return (child->parent == parent);
}

int Is_Ancestor(NodeStruct* ancestor, NodeStruct* node) {
    while (node != NULL) {
        if (node->parent == ancestor) {
            return 1;
        }
        node = node->parent;
    }
    return 0;
}

int Is_Internal(NodeStruct* node) {
    return (node->childCount > 0);
}

void Node_Descendants(NodeStruct* node) {
    if (node == NULL) return;        
    for (int i = 0; i < node->childCount; i++) {
        printf("%d ", node->children[i]->data);
        Node_Descendants(node->children[i]);
    }
}

void Get_Siblings(NodeStruct* node) {
    if (node->parent == NULL) return;      // if node is root, return

    NodeStruct* parent = node->parent;
    for (int i = 0; i < parent->childCount; i++) {
        if (parent->children[i] != node) {
            printf("%d ", parent->children[i]->data);
        }
    }
}

void Add_Child(NodeStruct* parent, NodeStruct* child) {
    // Resize the children array to accommodate the new child.
    parent->children = (NodeStruct**)realloc(parent->children, sizeof(NodeStruct*) * (parent->childCount + 1));
    parent->children[parent->childCount] = child;
    parent->childCount++;
}

// function to free node and its children recursively 
void Free_Node(NodeStruct* node) {
    if (node == NULL) return;

    // free memory for all children
    for (int i = 0; i < node->childCount; i++) {
        Free_Node(node->children[i]);
    }

    // free children array
    free(node->children);
    // free the node
    free(node);
}
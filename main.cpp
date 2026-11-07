#include <stdio.h>
#include <malloc.h>
#include <assert.h>
//----------------------------------------------------------------------------
struct tree_node_t{
    int data;
    tree_node_t* left;
    tree_node_t* right;
    tree_node_t* parent;
};

struct tree_t{
    tree_node_t* root;
    int height;
};
//----------------------------------------------------------------------------
tree_node_t* createNode();
void nodeInit   (tree_node_t* node, int data, tree_node_t* left, tree_node_t* right, tree_node_t* parent);
void deleteNode (tree_node_t* node);
//----------------------------------------------------------------------------
void setNodeData   (tree_node_t* node, int data);
void setNodeLeft   (tree_node_t* node, tree_node_t* left);
void setNodeRight  (tree_node_t* node, tree_node_t* right);
void setNodeParent (tree_node_t* node, tree_node_t* parent);
//----------------------------------------------------------------------------
int main(){
    tree_node_t* node1 = createNode();
    tree_node_t* node2 = createNode();
    tree_node_t* node3 = createNode();

    nodeInit(node1, 50, node2, node3, NULL);
    nodeInit(node2, 20, NULL, NULL, node1);
    nodeInit(node3, 60, NULL, NULL, node1);


    return 0;
}
//----------------------------------------------------------------------------
tree_node_t* createNode(){
    tree_node_t* node = (tree_node_t*) calloc(1, sizeof(tree_node_t));
    assert(node);

    node->data = 0;
    node->left   = NULL;
    node->right  = NULL;
    node->parent = NULL;
    return node;
}
//----------------------------------------------------------------------------
void deleteNode(tree_node_t* node){
    assert(node);

    node->data = 0;
    node->left   = NULL;
    node->right  = NULL;
    node->parent = NULL;
    node =         NULL;

    return;
}
//----------------------------------------------------------------------------
void nodeInit(tree_node_t* node, int data, tree_node_t* left, tree_node_t* right, tree_node_t* parent){
    assert(node);

    node->data = data;
    node->left = left;
    node->right = right;
    node->parent = parent;

    return;
}
//----------------------------------------------------------------------------
void setNodeData(tree_node_t* node, int data){
    assert(node);
    node->data = data;
    return;
}
//----------------------------------------------------------------------------
void setNodeLeft(tree_node_t* node, tree_node_t* left){
    assert(node);
    assert(left);
    node->left = left;
    return;
}
//----------------------------------------------------------------------------
void setNodeRight(tree_node_t* node, tree_node_t* right){
    assert(node);
    assert(right);
    node->right = right;
    return;
}
//----------------------------------------------------------------------------
void setNodeParent(tree_node_t* node, tree_node_t* parent){
    assert(node);
    assert(parent);
    node->parent = parent;
    return;
}
//----------------------------------------------------------------------------
void treeViz(tree_node_t* node){
    assert(node);


    return;
}
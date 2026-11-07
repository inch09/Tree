#include <stdio.h>
#include <malloc.h>
#include <assert.h>

typedef int tree_data_type;
//----------------------------------------------------------------------------
struct tree_node_t{
    tree_data_type data;
    tree_node_t* left;
    tree_node_t* right;
    tree_node_t* parent;
};
//----------------------------------------------------------------------------
struct tree_t{
    tree_node_t* root;
    int height;
};
//----------------------------------------------------------------------------
tree_node_t* createNode();
void nodeInit   (tree_node_t* node, tree_data_type data, tree_node_t* left, tree_node_t* right, tree_node_t* parent);
void deleteNode (tree_node_t* node);
//----------------------------------------------------------------------------
void setNodeData   (tree_node_t* node, tree_data_type data);
void setNodeLeft   (tree_node_t* node, tree_node_t* left);
void setNodeRight  (tree_node_t* node, tree_node_t* right);
void setNodeParent (tree_node_t* node, tree_node_t* parent);
void linkNodes     (tree_node_t* parent, tree_node_t* left, tree_node_t* right);
//----------------------------------------------------------------------------
int main(){
    tree_node_t* node1 = createNode();
    tree_node_t* node2 = createNode();
    tree_node_t* node3 = createNode();

    linkNodes(node1, node2, node3);


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
void nodeInit(tree_node_t* node, tree_data_type data, tree_node_t* left, tree_node_t* right, tree_node_t* parent){
    assert(node);

    node->data = data;
    node->left = left;
    node->right = right;
    node->parent = parent;

    return;
}
//----------------------------------------------------------------------------
void setNodeData(tree_node_t* node, tree_data_type data){
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
void linkNodes(tree_node_t* parent, tree_node_t* left, tree_node_t* right){
    assert(parent);
    assert(left && right);
    
    if(left != NULL){
        setNodeLeft   (parent, left);
        setNodeParent (left, parent);
    }
    if(right != NULL){
        setNodeRight  (parent, right);
        setNodeParent (right, parent);
    }
}
//----------------------------------------------------------------------------
void treeViz(tree_node_t* node, const char* vizFileName){
    assert(node);
    assert(vizFileName);
    return;
}

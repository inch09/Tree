#include <stdio.h>
#include <malloc.h>
#include <assert.h>
//----------------------------------------------------------------------------
typedef int tree_data_type;
#define SPECIFIER "%d"
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
bool isNodeHaveLeft  (tree_node_t* node);
bool isNodeHaveRight (tree_node_t* node); 
//----------------------------------------------------------------------------
void createNodeViz(tree_node_t* node, FILE* vizFile);
void createEdgeViz(tree_node_t* node, FILE* vizFile);
void treeViz(tree_t* tree, FILE* vizFile);
//----------------------------------------------------------------------------
void createPreOrder(tree_node_t* node, FILE* preOrderFile);
//----------------------------------------------------------------------------
int countNodes(FILE* preOrderFile);
//----------------------------------------------------------------------------
int main(){
    tree_node_t* node1 = createNode();
    tree_node_t* node2 = createNode();
    tree_node_t* node3 = createNode();
    tree_node_t* node4 = createNode();
    tree_node_t* node5 = createNode();
    tree_node_t* node6 = createNode();
    tree_node_t* node7 = createNode();
    tree_t tree = {node1, 0};
    linkNodes(node1, node2, node3);
    linkNodes(node2, node4, node5);
    linkNodes(node3, node6, node7);
    setNodeData(node1, 10);
    setNodeData(node2, 30);
    setNodeData(node3, 40);


    FILE* treeVizFile = fopen("tree_viz.txt", "w");
    assert(treeVizFile);
    treeViz(&tree, treeVizFile);
    fclose(treeVizFile);

    FILE* preOrderFileWrite = fopen("pre_order.txt", "w");
    assert(preOrderFileWrite);
    createPreOrder(tree.root, preOrderFileWrite);
    fclose(preOrderFileWrite);

    FILE* preOrderFileRead = fopen("pre_order.txt", "r");
    assert(preOrderFileRead);
    printf("%d", countNodes(preOrderFileRead));
    fclose(preOrderFileRead);

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
    assert(left || right);
    
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
bool isNodeHaveLeft(tree_node_t* node){
    assert(node);
    if(node->left != NULL) return true;
    return false;
}
//----------------------------------------------------------------------------
bool isNodeHaveRight(tree_node_t* node){
    assert(node);
    if(node->right != NULL) return true;
    return false;
}
//----------------------------------------------------------------------------
void createNodeViz(tree_node_t* node, FILE* vizFile){
    assert(node);
    assert(vizFile);

    fprintf(vizFile, "node%p[shape = Mrecord, label = \"data = " SPECIFIER "\"];\n", (void*) node, node->data);

    if(isNodeHaveLeft(node))  createNodeViz(node->left, vizFile); 
    if(isNodeHaveRight(node)) createNodeViz(node->right, vizFile);
    
    if(isNodeHaveLeft(node) && isNodeHaveRight(node)){
        fprintf(vizFile, "{rank = same; node%p; node%p};\n", (void*) node->left, (void*) node->right);
    }
}
//----------------------------------------------------------------------------
void createEdgeViz(tree_node_t* node, FILE* vizFile){
    assert(node);
    assert(vizFile);

    if(isNodeHaveLeft(node)){ 
        fprintf(vizFile, "node%p->node%p;\n", (void*) node, (void*) node->left);
        createEdgeViz(node->left, vizFile);
    }
    if(isNodeHaveRight(node)){ 
        fprintf(vizFile, "node%p->node%p;\n", (void*) node, (void*) node->right);
        createEdgeViz(node->right, vizFile);
    }      
}
//----------------------------------------------------------------------------
void treeViz(tree_t* tree, FILE* vizFile){
    assert(tree);
    assert(vizFile);

    fprintf(vizFile, "digraph{\n");
    createNodeViz(tree->root, vizFile);
    createEdgeViz(tree->root, vizFile);
    fprintf(vizFile, "}");
}
//----------------------------------------------------------------------------
void createPreOrder(tree_node_t* node, FILE* preOrderFile){
    assert(node);
    assert(preOrderFile);

    fprintf(preOrderFile, "( ");
    fprintf(preOrderFile, SPECIFIER, node->data);

    if(isNodeHaveLeft(node) || isNodeHaveRight(node)){

    if(isNodeHaveLeft (node)) createPreOrder(node->left,  preOrderFile);
    else fprintf(preOrderFile, "#");

    if(isNodeHaveRight(node)) createPreOrder(node->right, preOrderFile);
    else fprintf(preOrderFile, "#");

    }

    fprintf(preOrderFile, ")");
}
//----------------------------------------------------------------------------
void preOrderParsing(FILE* preOrderFile){
    assert(preOrderFile);

    int countNodes = countNodes(preOrderFile);
    tree_node_t** arrOfNodes = (tree_node_t**) calloc(countNodes, sizeof(tree_node_t*));

    char symbol = fgetc(preOrderFile);
    if(symbol == EOF){
        free(arrOfNodes);
        return;
    }
    free(arrOfNodes);
}
//----------------------------------------------------------------------------
int countNodes(FILE* preOrderFile){
    assert(preOrderFile);

    int countOpeningBrackets = 0; 
    int countCloseBrackets = 0;

    while(true){

    char symbol = fgetc(preOrderFile);
    if(symbol == EOF){
        if(countOpeningBrackets != countCloseBrackets) return -1;
        else return countOpeningBrackets;
    }
    if(symbol == '(') countOpeningBrackets++;
    if(symbol == ')') countCloseBrackets++;

    }
}
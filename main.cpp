#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
//----------------------------------------------------------------------------
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
//----------------------------------------------------------------------------
typedef char* tree_data_type;
#define SPECIFIER "%s"
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
void deleteTree (tree_node_t* node);
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
void treeViz(tree_node_t* root, FILE* vizFile);
//----------------------------------------------------------------------------
void createPreOrder(tree_node_t* node, FILE* preOrderFile);
//----------------------------------------------------------------------------
int countNodes(const char* strTree);
char* createStrBuffer(const char* fileName);
size_t getFileSize(const char* fileName);
//----------------------------------------------------------------------------
tree_node_t* parsePreOrder(const char* strBuf);
char* parseNodeData(const char* strBuf);
//----------------------------------------------------------------------------
void akinator(tree_node_t* node);
void addNewNodeAkinator(tree_node_t* currentNode);
//----------------------------------------------------------------------------
void deleteEnterInStr(char* str);
void cleanBuffer();
//----------------------------------------------------------------------------
int main(){
    // tree_node_t* node1 = createNode();
    // tree_node_t* node2 = createNode();
    // tree_node_t* node3 = createNode();
    // tree_node_t* node4 = createNode();
    // tree_node_t* node5 = createNode();
    // tree_node_t* node6 = createNode();
    // tree_node_t* node7 = createNode();
    // tree_t tree = {node1, 0};
    // linkNodes(node1, node2, node3);
    // linkNodes(node2, node4, node5);
    // linkNodes(node3, node6, NULL);
    // setNodeData(node1, 10);
    // setNodeData(node2, 30);
    // setNodeData(node3, 40);


    // FILE* treeVizFile = fopen("tree_viz.txt", "w");
    // assert(treeVizFile);
    // treeViz(&tree, treeVizFile);
    // fclose(treeVizFile);

    // FILE* preOrderFileWrite = fopen("pre_order.txt", "w");
    // assert(preOrderFileWrite);
    // createPreOrder(tree.root, preOrderFileWrite);
    // fclose(preOrderFileWrite);

    FILE* preOrderFileRead = fopen("pre_order.txt", "r");
    assert(preOrderFileRead);
    //printf("%d\n", countNodes(preOrderFileRead));
    fclose(preOrderFileRead);

    //printf("%d\n", getFileSize("pre_order.txt"));
    char* preOrderStr = createStrBuffer("pre_order.txt");
    tree_node_t* root = parsePreOrder(preOrderStr);
    assert(root);
    
    FILE* treeVizFile = fopen("tree_viz.txt", "w");
    assert(treeVizFile);
    //printf("%s\n", preOrderStr);
    //treeViz(root, treeVizFile);
    akinator(root);

    FILE* preOrderFileWrite = fopen("pre_order.txt", "w");
    assert(preOrderFileWrite);

    createPreOrder(root, preOrderFileWrite);

    treeViz(root, treeVizFile);

    deleteTree(root);
    fclose(preOrderFileWrite);
    fclose(treeVizFile);
    free(preOrderStr);

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
void deleteTree(tree_node_t* node){
    assert(node);

    if(node->left)  deleteTree(node->left);
    if(node->right) deleteTree(node->right);

    deleteNode(node);

    return;
}
//----------------------------------------------------------------------------
void deleteNode(tree_node_t* node){
    assert(node);

    node->data =   NULL;
    free(node->data);

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
    assert(data);
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
void treeViz(tree_node_t* root, FILE* vizFile){
    assert(root);
    assert(vizFile);

    fprintf(vizFile, "digraph{\n");
    createNodeViz(root, vizFile);
    createEdgeViz(root, vizFile);
    fprintf(vizFile, "}");
}
//----------------------------------------------------------------------------
void createPreOrder(tree_node_t* node, FILE* preOrderFile){
    assert(node);
    assert(preOrderFile);

    fprintf(preOrderFile, "(");
    fprintf(preOrderFile, SPECIFIER, node->data);

    if(isNodeHaveLeft(node) || isNodeHaveRight(node)){

    if(isNodeHaveLeft (node)) createPreOrder(node->left,  preOrderFile);
    else fprintf(preOrderFile, "(#)");

    if(isNodeHaveRight(node)) createPreOrder(node->right, preOrderFile);
    else fprintf(preOrderFile, "(#)");

    }

    fprintf(preOrderFile, ")");
}
//----------------------------------------------------------------------------
int countNodes(const char* strTree){
    assert(strTree);

    size_t strTreeLen = strlen(strTree);

    int countOpeningBrackets = 0; 
    int countCloseBrackets = 0;

    size_t i = 0;
    while(i < strTreeLen){
    if(strTree[i] == '(') countOpeningBrackets++;
    if(strTree[i] == ')') countCloseBrackets++;
    i++;
    }

    if(countOpeningBrackets != countCloseBrackets) return -1;
    else return countOpeningBrackets;
}
//----------------------------------------------------------------------------
char* createStrBuffer(const char* fileName){
    assert(fileName);

    FILE* filePtr = fopen(fileName, "r");
    assert(filePtr);

    size_t fullFileSize = getFileSize(fileName);
    char* strBuf = (char*) calloc(fullFileSize + 1, sizeof(char));
    assert(strBuf);

    size_t realFileSize = fread(strBuf, sizeof(char), fullFileSize, filePtr);
    realloc(strBuf, realFileSize * sizeof(char));
    assert(strBuf);

    fclose(filePtr);

    return strBuf;
}
//----------------------------------------------------------------------------
size_t getFileSize(const char* fileName){
    assert(fileName);

    struct stat fileInfo = {};
    stat(fileName, &fileInfo);
    return fileInfo.st_size;
}
//----------------------------------------------------------------------------
tree_node_t* parsePreOrder(const char* strBuf){
    assert(strBuf);

    tree_node_t* node = createNode();
    assert(node);

    int numOfChild = 0;
    static int i = -1;
    i++;

    node->data = parseNodeData(strBuf + i);

    while(strBuf[i] != '\0'){
        if(strBuf[i] == '('){ 
            numOfChild++;
            tree_node_t* childNode = parsePreOrder(strBuf); 
            setNodeParent(childNode, node);
            if(numOfChild == 1) setNodeLeft (node, childNode);
            if(numOfChild == 2) setNodeRight(node, childNode);
        }
        else if(strBuf[i] == ')'){
            i++; 
            return node;
        }    
        else i++;
    }

    i = -1;
    return node;
}
//----------------------------------------------------------------------------
char* parseNodeData(const char* strBuf){
    assert(strBuf);

    size_t i = 0;
    while(strBuf[i] != '\0'){
        if(strBuf[i] == '(' || strBuf[i] == ')'){
            break;
        }
        i++;
    }

    size_t countDataSymbols = i;
    char* nodeData = (char*) calloc(countDataSymbols + 1, sizeof(char));
    assert(nodeData);

    i = 0;
    while(i < countDataSymbols){
        nodeData[i] = strBuf[i];
        i++;
    }

    return nodeData;
}
//----------------------------------------------------------------------------
void akinator(tree_node_t* node){
    assert(node);

    if(!isNodeHaveLeft(node) && !isNodeHaveRight(node)){
        printf("%s\n", node->data);
        addNewNodeAkinator(node);
        return;
    }
    printf("%s\n", node->data);
    printf("yes / no\n");

    char strAns[10] = {};

    fgets(strAns, sizeof(strAns), stdin);
    cleanBuffer();

    printf("%s\n", strAns);
    deleteEnterInStr(strAns);
    printf("%s\n", strAns);


    if(strcmp(strAns, "yes") == 0){
        akinator(node->left);
    }
    else if(strcmp(strAns, "no") == 0){
        akinator(node->right);
    }

    return;
}
//----------------------------------------------------------------------------
void addNewNodeAkinator(tree_node_t* currentNode){
    assert(currentNode);

    printf("Chto esche imeet takie zhe svoistva?\n");

    char* strObject = (char*) calloc(100, sizeof(char));
    assert(strObject);

    fgets(strObject, sizeof(strObject), stdin);
    cleanBuffer();

    printf("strObj = %s\n", strObject);
    deleteEnterInStr(strObject);
    printf("strObj = %s\n", strObject);

    //scanf("%s", strObject);

    printf("Chem %s otlichaetsya ot %s?\n", strObject, currentNode->data);
    printf("%s... ", strObject);

    char* newCompare = (char*) calloc(100, sizeof(char));
    assert(newCompare);
    
    fgets(newCompare, sizeof(newCompare), stdin);   
    cleanBuffer();

    printf("%s\n", newCompare);
    deleteEnterInStr(newCompare); 
    printf("%s\n", newCompare);


    tree_node_t* newFeature = createNode();
    assert(newFeature);

    tree_node_t* newObject = createNode();
    assert(newObject);

    setNodeData  (newObject, strObject);
    setNodeParent(newObject, newFeature);

    setNodeData  (newFeature, newCompare);
    setNodeLeft  (newFeature, newObject);
    setNodeRight (newFeature, currentNode);
    setNodeParent(newFeature, currentNode->parent);

    if((currentNode->parent)->left == currentNode){
        setNodeLeft(currentNode->parent, newFeature);
    }
    else if((currentNode->parent)->right == currentNode){
        setNodeRight(currentNode->parent, newFeature);
    }

    setNodeParent(currentNode, newFeature);
    

}
//----------------------------------------------------------------------------
void deleteEnterInStr(char* str){
    assert(str);

    size_t len = strlen(str);
    for(int i = 0; i < len; i++){
        if( str[i] == '\n'){
            str[i] = '\0';
        }
    }
}
//----------------------------------------------------------------------------
void cleanBuffer(){
    char ch = getchar();
    while(ch != EOF){
        ch = getchar();
    }
}
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
struct param_tree_viz{
    char* rootColor;
    char* leftColor;
    char* rightColor;
    char* edgeWithLeftName;
    char* edgeWithRightName; 
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
void createNodeViz (tree_node_t* node, FILE* vizFile, const char* nodeColor, const char* leftColor, const char* rightColor);
void createEdgeViz (tree_node_t* node, FILE* vizFile, const char* edgeWithLeftName, const char* edgeWithRightName);
void treeViz       (tree_node_t* root, FILE* vizFile, param_tree_viz* parameters);
//----------------------------------------------------------------------------
void parametersTreeVizInit(param_tree_viz* parameters, const char* rootColor, const char* leftColor, const char* rightColor, const char* edgeWithLeftName, const char* edgeWithRightName);
void parametersTreeVizDestroy(param_tree_viz* parameters);
//----------------------------------------------------------------------------
void createPreOrder(tree_node_t* node, FILE* preOrderFile);
//----------------------------------------------------------------------------
int countNodes                 (const char* strTree);
char* createStrBuffer          (const char* fileName);
char* convertStrToReadPreOrder (const char* strBuf);
size_t getFileSize             (const char* fileName);
//----------------------------------------------------------------------------
tree_node_t* parsePreOrder (const char* strBuf);
char* parseNodeData        (const char* strBuf);
//----------------------------------------------------------------------------
void akinator                      (tree_node_t* node);
void addNewNodeAkinator            (tree_node_t* currentNode);
tree_node_t* findRoot              (tree_node_t* node);
tree_node_t* findNodeByValue       (tree_node_t* node, const char* nameObject);
bool isThisLeftChild               (tree_node_t* node);
bool isThisRightChild              (tree_node_t* node);
int* findWayFromRootToNode         (tree_node_t* node);
int provideDefinitionNodeAkinator  (tree_node_t* node, const char* nameObject);
void reverseArr(int* arr, size_t lenOfArr);
//----------------------------------------------------------------------------
void deleteEnterInStr(char* str);
void cleanBuffer();
//----------------------------------------------------------------------------
int main(){

    char* preOrderStr = createStrBuffer("pre_order.txt");
    char* preOrderStrToProcess = convertStrToReadPreOrder(preOrderStr);
    assert(preOrderStrToProcess);

    tree_node_t* root = parsePreOrder(preOrderStrToProcess);
    assert(root);
    free(preOrderStrToProcess);
    
    akinator(root);

    param_tree_viz parameters = {};
    parametersTreeVizInit(&parameters, "#e8ec9d", "#7fe2a8", "#e59494", "da", "net");
    FILE* treeVizFile = fopen("tree_viz.txt", "w");
    assert(treeVizFile);

    treeViz(root, treeVizFile, &parameters);

    parametersTreeVizDestroy(&parameters);
    fclose(treeVizFile);


    FILE* preOrderFileWrite = fopen("pre_order.txt", "w");
    assert(preOrderFileWrite);
    createPreOrder(root, preOrderFileWrite);
    fclose(preOrderFileWrite);


    deleteTree(root);
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
void createNodeViz(tree_node_t* node, FILE* vizFile, const char* nodeColor, const char* leftColor, const char* rightColor){
    assert(node);
    assert(vizFile);
    assert(nodeColor);
    assert(leftColor);
    assert(rightColor);

    fprintf(vizFile, "node%p[shape = Mrecord, style = \"filled\", fillcolor = \"%s\", label = \"" SPECIFIER "\"];\n", (void*) node, nodeColor , node->data);

    if(isNodeHaveLeft(node))  createNodeViz(node->left,  vizFile, leftColor,  leftColor, rightColor); 
    if(isNodeHaveRight(node)) createNodeViz(node->right, vizFile, rightColor, leftColor, rightColor);
    
    if(isNodeHaveLeft(node) && isNodeHaveRight(node)){
        fprintf(vizFile, "{rank = same; node%p; node%p};\n", (void*) node->left, (void*) node->right);
    }
}
//----------------------------------------------------------------------------
void createEdgeViz(tree_node_t* node, FILE* vizFile, const char* edgeWithLeftName, const char* edgeWithRightName){
    assert(node);
    assert(vizFile);
    assert(edgeWithLeftName);
    assert(edgeWithRightName);

    if(isNodeHaveLeft(node)){ 
        fprintf(vizFile, "node%p->node%p[label = \"%s\"];\n", (void*) node, (void*) node->left, edgeWithLeftName);
        createEdgeViz(node->left, vizFile, edgeWithLeftName, edgeWithRightName);
    }
    if(isNodeHaveRight(node)){ 
        fprintf(vizFile, "node%p->node%p[label = \"%s\"];\n", (void*) node, (void*) node->right, edgeWithRightName);
        createEdgeViz(node->right, vizFile, edgeWithLeftName, edgeWithRightName);
    }      
}

//----------------------------------------------------------------------------
void treeViz(tree_node_t* root, FILE* vizFile, param_tree_viz* parameters){
    assert(root);
    assert(vizFile);
    assert(parameters);

    fprintf(vizFile, "digraph{\n");
    createNodeViz(root, vizFile, parameters->rootColor, parameters->leftColor, parameters->rightColor);
    createEdgeViz(root, vizFile, parameters->edgeWithLeftName, parameters->edgeWithRightName);
    fprintf(vizFile, "}");
}
//----------------------------------------------------------------------------
void parametersTreeVizInit(param_tree_viz* parameters, const char* rootColor, const char* leftColor, const char* rightColor, const char* edgeWithLeftName, const char* edgeWithRightName){
    assert(parameters);
    assert(rootColor);
    assert(leftColor);
    assert(rightColor);
    assert(edgeWithLeftName);
    assert(edgeWithRightName);

    parameters->rootColor = (char*) calloc(strlen(rootColor) + 1, sizeof(char));
    assert(parameters->rootColor);
    strcpy(parameters->rootColor, rootColor);
    
    parameters->leftColor = (char*) calloc(strlen(leftColor) + 1, sizeof(char));
    assert(parameters->leftColor);
    strcpy(parameters->leftColor, leftColor);

    parameters->rightColor = (char*) calloc(strlen(rightColor) + 1, sizeof(char));
    assert(parameters->rightColor);
    strcpy(parameters->rightColor, rightColor);

    parameters->edgeWithLeftName = (char*) calloc(strlen(edgeWithLeftName) + 1, sizeof(char));
    assert(parameters->edgeWithLeftName);
    strcpy(parameters->edgeWithLeftName, edgeWithLeftName);   

    parameters->edgeWithRightName = (char*) calloc(strlen(edgeWithRightName) + 1, sizeof(char));
    assert(parameters->edgeWithRightName);
    strcpy(parameters->edgeWithRightName, edgeWithRightName);
}
//----------------------------------------------------------------------------
void parametersTreeVizDestroy(param_tree_viz* parameters){
    assert(parameters);

    free(parameters->rootColor);
    free(parameters->leftColor);
    free(parameters->rightColor);
    free(parameters->edgeWithLeftName);
    free(parameters->edgeWithRightName);
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
char* convertStrToReadPreOrder(const char* strBuf){
    assert(strBuf);

    size_t len = strlen(strBuf);
    size_t j = 0;
    while(j < len){
         if(strBuf[j] == '('){
            break;
         }
        j++;
    }

    size_t newLen = len - j - 1;

    char* newBuf = (char*) calloc(newLen + 1, sizeof(char));
    assert(newBuf);
    strcpy(newBuf, strBuf + j + 1);

    int i = newLen - 1;
    while(i >= 0){
        if( newBuf[i] == ')'){
            newBuf[i] = '\0';
            break; 
        }
        i--;
    }
    free((void*) strBuf);

    return newBuf;
}
//----------------------------------------------------------------------------
tree_node_t* parsePreOrder(const char* strBuf){ //todo CONTEXT(tam index v stroke, proverki etogo symbola)
    assert(strBuf);

    tree_node_t* node = createNode();
    assert(node);

    int numOfChild = 0;
    static int indInStr = 0; //nado ubrat static i peredavat v functsiu parameter

    node->data = parseNodeData(strBuf + indInStr);

    while (strBuf[indInStr] != '\0'){
        if(strBuf[indInStr] == '('){ 
            numOfChild++;
            indInStr++;
            tree_node_t* childNode = parsePreOrder(strBuf); 
            setNodeParent(childNode, node);
            if(numOfChild == 1) setNodeLeft (node, childNode);
            if(numOfChild == 2) setNodeRight(node, childNode);
        }
        else if(strBuf[indInStr] == ')'){
            indInStr++; 
            return node;
        }    
        else indInStr++;
    }

    indInStr = 0;
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

    const size_t maxSizeAns = 100;

    if(!isNodeHaveLeft(node) && !isNodeHaveRight(node)){
        printf("%s\n", node->data);

        printf("Nazovite object\n");
        char ans[maxSizeAns] = {};
        fgets(ans, maxSizeAns, stdin);
        deleteEnterInStr(ans);
        printf("%d", provideDefinitionNodeAkinator(findRoot(node), ans));
        //addNewNodeAkinator(node);
        return;
    }
    printf("%s\n", node->data);
    printf("yes / no\n");

    char strAns[maxSizeAns] = {};

    fgets(strAns, maxSizeAns, stdin);
    deleteEnterInStr(strAns);

    if(strcmp(strAns, "yes") == 0){
        akinator(node->left);
    }
    else if(strcmp(strAns, "no") == 0){
        akinator(node->right);
    }
    else{
        printf("ERROR ENTER");
    }

    return;
}
//----------------------------------------------------------------------------
void addNewNodeAkinator(tree_node_t* currentNode){
    assert(currentNode);

    const size_t maxSizeAns = 100;

    printf("Chto esche imeet takie zhe svoistva?\n");

    char* strObject = (char*) calloc(maxSizeAns, sizeof(char));
    assert(strObject);

    fgets(strObject, maxSizeAns, stdin);
    deleteEnterInStr(strObject);

    printf("Chem %s otlichaetsya ot %s?\n", strObject, currentNode->data);
    printf("%s... ", strObject);

    char* newCompare = (char*) calloc(maxSizeAns, sizeof(char));
    assert(newCompare);
    
    fgets(newCompare, maxSizeAns, stdin);   
    deleteEnterInStr(newCompare);

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
tree_node_t* findRoot(tree_node_t* node){
    assert(node);

    tree_node_t* currentNode = node;
    while(true){
        if(currentNode->parent == NULL) return currentNode;
        currentNode = currentNode->parent;
    }    
    return NULL;
}
//----------------------------------------------------------------------------
tree_node_t* findNodeByValue(tree_node_t* node, const char* nameObject){
    assert(node);
    assert(nameObject);

    static tree_node_t* returnNode = NULL;
    if(strcmp(node->data, nameObject) == 0){
        returnNode = node;
        return NULL;
    }

    if( isNodeHaveLeft(node)) findNodeByValue(node->left, nameObject);
    if(isNodeHaveRight(node)) findNodeByValue(node->right, nameObject);


    //printf("67\n");
    return returnNode;
}
//----------------------------------------------------------------------------
bool isThisLeftChild(tree_node_t* node){
    assert(node);
    if(node->parent == NULL) return false;
    return ((node->parent)->left == node); 
}
//----------------------------------------------------------------------------
bool isThisRightChild(tree_node_t* node){
    assert(node);
    if(node->parent == NULL) return false;
    return ((node->parent)->right == node); 
}
//----------------------------------------------------------------------------
int* findWayFromRootToNode(tree_node_t* node, size_t* lenOfArr){
    assert(node);

    tree_node_t* currentNode = node;
    size_t lenOfWay = 0;

    while(true){
        if(currentNode->parent == NULL) break;
        currentNode = currentNode->parent;
        lenOfWay++;
    }

    int* arrOfTransitions = (int*) calloc(lenOfWay, sizeof(int));
    assert(arrOfTransitions);

    currentNode = node;
    for(int i = 0; i < lenOfWay; i++){
        if     (isThisLeftChild(currentNode))  arrOfTransitions[i] = 0;
        else if(isThisRightChild(currentNode)) arrOfTransitions[i] = 1;
        currentNode = currentNode->parent;
    }

    reverseArr(arrOfTransitions, lenOfWay);
    *lenOfArr = lenOfWay;

    return arrOfTransitions;
}
//----------------------------------------------------------------------------
void reverseArr(int* arr, size_t lenOfArr){
    assert(arr);

    for(size_t i = 0; i < (lenOfArr / 2); i++){
        int temp = arr[i];
        arr[i] = arr[lenOfArr - 1 - i];
        arr[lenOfArr - 1 - i] = temp;
    }
} 
//----------------------------------------------------------------------------
int provideDefinitionNodeAkinator(tree_node_t* root, const char* nameObject){
    assert(root);
    assert(nameObject);

    printf("<%s>\n", nameObject);
    tree_node_t* node = findNodeByValue(root, nameObject);
    if(node == NULL) return -1;

    size_t lenOfWay = 0;
    int* arrOfTransitions = findWayFromRootToNode(node, &lenOfWay);
    assert(arrOfTransitions);


    node = root;
    printf("%s: ", nameObject);
    for(int i = 0; i < lenOfWay; i++){
        if(arrOfTransitions[i] == 0){
            printf("%s ",    node->data);
            node = node->left;
        }        
        else if(arrOfTransitions[i] == 1){
            printf("ne %s ", node->data);
            node = node->right;
        }    
    }

    free(arrOfTransitions);
    return 0;
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
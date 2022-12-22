//
// Created by nizni on 12/19/2022.
//

#ifndef WET2MIVNEINIRNIZ_AVL_RANK_H
#define WET2MIVNEINIRNIZ_AVL_RANK_H

#include <iostream>
using namespace std;

#include <iostream>
#include <memory>

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

template<class T>
class AvlRankTree {
private:

    struct AvlNode {
        AvlNode *right_son;
        AvlNode *left_son;
        AvlNode *father;
        int height;
        T data;
        int w = 1;
        AvlNode()=default;
        AvlNode(const T& data):height(0), data(data)
        {
            this->left_son = nullptr;
            this->right_son = nullptr;
            this->father = nullptr;
        }
        AvlNode& operator=(const AvlNode& other){
            if(this==&other){
                return *this;
            }
            this->data=other.data;
            this->left_son=other.left_son;
            this->right_son=other.left_son;
            this->father=other.father;
            this->height=other.height;
            this->w = other.w;
        }

        int getBalanceFactor(){
            int leftSonHeight, rightSonHeight;
            if (left_son){
                leftSonHeight = left_son->height;
            }
            else{
                leftSonHeight = -1;
            }
            if (right_son){
                rightSonHeight = right_son->height;
            }
            else{
                rightSonHeight = -1;
            }
            return leftSonHeight - rightSonHeight;
        }

        AvlNode(const AvlNode& other):data(other.data), height(0), w(other.w)
        {
            this->left_son = nullptr;
            this->right_son = nullptr;
            this->father = nullptr;
        }
    };
    AvlNode *root;
    int size;
public:
    int getSize() const;

private:

    bool (*bigger)(const T&, const T&);

    bool (*equals)(const T&, const T&);
    AvlNode* insertAvlNode(const T& data, AvlNode* current, AvlNode* father);
    AvlNode* findAvlNode(AvlNode *current, const T& data);
    AvlNode* SelectAvlNode(AvlNode *current, int K);
    int RankAvlNode(AvlNode *current, const T& data, int r);
    bool removeAvlNode(T& data, AvlRankTree<T>::AvlNode *current);


    void swap_data(AvlNode* first, AvlNode* second);
    int AvlNodeHeight(const AvlNode* node) const;
    int AvlNodeW(const AvlNode* node) const;

    void LLroll(AvlNode *node);
    void LRroll(AvlNode *node);
    void RLroll(AvlNode *node);
    void RRroll(AvlNode *node);

    void deleteAllAux(AvlNode* current);

    void printInOrder(const AvlNode* node);

    int fillInOrderArrayAux(AvlNode *current, T arr[], int idx) const;

    AvlNode* treeFromListHelp(T arr[], int begin, int end, AvlNode* father);

    void balanceAvlNode(AvlNode* node);


    AvlNode* copyTree(AvlNode* currentInOtherTree, AvlNode* fatherInTree);

public:
    AvlRankTree(bool (*bigger)(const T&, const T&), bool (*equals)(const T&, const T&));
    AvlRankTree(const AvlRankTree<T>& tree);
    AvlRankTree(const AvlRankTree<T>& first, const AvlRankTree<T>& second);
    AvlRankTree &operator=(const AvlRankTree<T> &tree) ;
    ~AvlRankTree();

    T* insert(const T& data);
    T* find(const T& data);
    T* Select(int k);
    int Rank(const T& data);
    bool remove(T& data);
    void empty();
    bool isEmpty() const;
    T* getMaxData() const;

    void printTreeInOrder();

    bool fillInOrderArray(T arr[], int arrSize) const;


    T* FindInRange(const T& minInRange, const T& maxInRange);
    T* FindInRange_Aux(AvlNode* node,const T& minInRange, const T& maxInRange);
};

template<class T>
T* AvlRankTree<T>::getMaxData() const {
    if (size == 0){
        return nullptr;
    }
    if (size == 1){
        return &(root->data);
    }
    AvlNode* current = root;
    while(current->right_son){
        current = current->right_son;
    }
    return &(current->data);
}


template<class T>
void AvlRankTree<T>::printTreeInOrder()/////////////
{
    printInOrder(root);
}

template<class T>
T* AvlRankTree<T>::FindInRange(const T& minInRange, const T& maxInRange) {
    return FindInRange_Aux(this->root,minInRange,maxInRange);
}
template<class T>
T* AvlRankTree<T>::FindInRange_Aux(AvlNode *node, const T& minInRange, const T& maxInRange) {
    if(!node){
        return NULL;
    }
    if(equals(node->data, minInRange) || equals(node->data, maxInRange)){
        return &node->data;
    }
    if(bigger(node->data, minInRange) && bigger(maxInRange, node->data)){
        return &node->data;
    }
    if(bigger(minInRange, node->data)){
        return FindInRange_Aux(node->right_son,minInRange,maxInRange);
    }
    if(bigger(node->data, maxInRange)){
        return FindInRange_Aux(node->left_son,minInRange,maxInRange);
    }
    return NULL;

}






template<class T>
void AvlRankTree<T>::printInOrder(const AvlNode* node)/////////////////////////
{
    if (!node)
    {
        return;
    }
    printInOrder(node->left_son);
    cout << node->data << ",\n";
    printInOrder(node->right_son);
}


template<class T>
bool AvlRankTree<T>::fillInOrderArray(T arr[], int arrSize) const////arrSize must be true, maybe think of a way to verify
{
    if (arrSize != size)
    {
        return false;
    }
    else{
        fillInOrderArrayAux(root, arr, 0);
        return true;
    }
}


template<class T>
int AvlRankTree<T>::fillInOrderArrayAux(AvlNode *current, T arr[], int idx) const
{
    if (!current)
    {
        return 0;
    }
    int offset = fillInOrderArrayAux(current->left_son, arr, idx);
    arr[idx + offset] = current->data;
    offset += 1;
    offset += fillInOrderArrayAux(current->right_son, arr, idx+offset);
    return offset;////requires check
}

template<class T>
AvlRankTree<T>::AvlRankTree(bool (*bigger)(const T&, const T&), bool (*equals)(const T&, const T&)) :
        root(nullptr), size(0), bigger(bigger), equals(equals){//////////////
}




template<class T>
void AvlRankTree<T>::swap_data(AvlRankTree::AvlNode *first, AvlRankTree::AvlNode *second) {
    T tmp = first->data;
    first->data = second->data;
    second->data = tmp;
}


template<class T>
AvlRankTree<T>::~AvlRankTree(){//////////////////////
    deleteAllAux(root);
    root = nullptr;
    size = 0;
}


template<class T>
void AvlRankTree<T>::deleteAllAux(AvlRankTree<T>::AvlNode* current) {/////////////////////
//postorder delete
    if(!current){
        return;
    }
    deleteAllAux(current->left_son);
    deleteAllAux(current->right_son);
    if (current->father){
        if (current->father->right_son == current){
            current->father->right_son = nullptr;
        }
        else{
            current->father->left_son = nullptr;
        }
    }
    if (root == current){
        root = nullptr;
    }
    delete current;
}


template<class T>
AvlRankTree<T>::AvlRankTree(const AvlRankTree<T>& tree):root(nullptr), size(0){///////////////
    bigger = tree.bigger;
    equals = tree.equals;
    copyTree(tree.root, nullptr);
    size = tree.size;
}


template<class T>
typename AvlRankTree<T>::AvlNode* AvlRankTree<T>::copyTree(AvlNode* currentInOtherTree, AvlNode* fatherInTree) {
    if(!currentInOtherTree){
        return nullptr;
    }
    AvlNode* newNode = new AvlNode(currentInOtherTree->data);
    newNode->father = fatherInTree;
    newNode->height = currentInOtherTree->height;
    newNode->left_son = copyTree(currentInOtherTree->left_son,newNode);
    newNode->right_son = copyTree(currentInOtherTree->right_son,newNode);
    return newNode;
}


template<class T>
AvlRankTree<T>::AvlRankTree(const AvlRankTree<T> &first, const AvlRankTree<T> &second) {
    size = first.size + second.size;
    bigger = first.bigger;
    equals = first.equals;
    T* firstArr = new T[first.size];
    T* secondArr = new T[second.size];
    first.fillInOrderArray(firstArr, first.size);
    second.fillInOrderArray(secondArr, second.size);

    ///merging the two arrays:
    T* newArr = new T[first.size + second.size];
    int firstIdx = 0, secondIdx = 0;

    for (int i = 0; i < first.size + second.size; ++i) {
        if (firstIdx >= first.size){
            newArr[i] = secondArr[secondIdx];
            secondIdx++;
        }
        else if (secondIdx >= second.size){
            newArr[i] = firstArr[firstIdx];
            firstIdx++;
        }
        else{
            if (bigger(secondArr[secondIdx], firstArr[firstIdx])){
                newArr[i] = firstArr[firstIdx];
                firstIdx++;
            }
            else{
                newArr[i] = secondArr[secondIdx];
                secondIdx++;
            }
        }
    }

    this->root = treeFromListHelp(newArr, 0, this->size-1, nullptr);

    delete [] firstArr;
    delete [] secondArr;
    delete [] newArr;

}


template<class T>
typename AvlRankTree<T>::AvlNode* AvlRankTree<T>::treeFromListHelp(T arr[], int begin, int end, AvlRankTree::AvlNode *father)
{
    if(begin > end)
    {
        return nullptr;
    }

    int middle = (begin + end)/2;

    AvlNode* newNode = new AvlNode(arr[middle]);
    newNode->father = father;
    newNode->right_son = treeFromListHelp(arr, middle + 1, end, newNode);
    newNode->left_son = treeFromListHelp(arr, begin, middle - 1, newNode);

    newNode->height = max(AvlNodeHeight(newNode->left_son), AvlNodeHeight(newNode->right_son)) + 1;
    return newNode;
}



template<class T>
T* AvlRankTree<T>::insert(const T& data) {
    ///inserting a node with the data. returning a reference to the data of the father,
    ///if it's the root- return a reference to it's data.
    if (!data) {
        return nullptr;
    }
    if (size == 0){//both should be always together
        root = new AvlNode(data);
        size++;
        return &(root->data);
    }
    else{
        AvlNode* newNodeFatherAtInsert = insertAvlNode(data, root, nullptr);
        if (!newNodeFatherAtInsert){////already exists
            return nullptr;
        }
        size++;
        return &(newNodeFatherAtInsert->data);
    }
}


template<class T>
typename AvlRankTree<T>::AvlNode*
AvlRankTree<T>::insertAvlNode(const T& data, AvlRankTree<T>::AvlNode* current, AvlRankTree<T>::AvlNode* father) {
    if (!current){
        AvlNode* newNode = new AvlNode(data);///create the node and insert it
        newNode->father = father;
        if (bigger(father->data, data)){
            father->left_son = newNode;
        }
        else{
            father->right_son = newNode;
        }
        return newNode->father;////returning a pointer to the new node's father at insertion (before rolling)
    }

    if (equals(current->data, data)){////exists in tree
        return nullptr;
    }
    AvlNode* newNodeFather;
    if (bigger(data, current->data)) {
        newNodeFather = insertAvlNode(data, current->right_son, current);
    } else {
        newNodeFather = insertAvlNode(data, current->left_son, current);
    }

    current->w = AvlNodeW(current->left_son) + AvlNodeW(current->right_son) + 1;

    balanceAvlNode(current);


    current->w = AvlNodeW(current->left_son) + AvlNodeW(current->right_son) + 1;////maybe redundant


    current->height = max(AvlNodeHeight(current->right_son), AvlNodeHeight(current->left_son)) + 1;////maybe no need
    return newNodeFather;
}


template<class T>
T* AvlRankTree<T>::find(const T& data){
    ///finding the node with the data and returning a pointer to its data
    AvlNode* nodeFound = findAvlNode(root, data);
    if(nodeFound){
        return &(nodeFound->data);
    }
    else{
        return nullptr;
    }
}


template<class T>
typename AvlRankTree<T>::AvlNode*
AvlRankTree<T>::findAvlNode(AvlRankTree<T>::AvlNode* current, const T& data){///cool, can be recursive
    if(!current) {///node not found
        return nullptr;
    }
    if (equals(data, current->data)) {
        return current;
    }
    else {
        if (bigger(data, current->data)) {
            return findAvlNode(current->right_son, data);
        }
        else {
            return findAvlNode(current->left_son, data);
        }
    }
}



template<class T>
int AvlRankTree<T>::Rank(const T& data){
    ///finding the node with the data and returning its rank. -1 if not found
    return RankAvlNode(root, data, 0);
}


template<class T>
int AvlRankTree<T>::RankAvlNode(AvlRankTree<T>::AvlNode* current, const T& data, int r){///cool, can be recursive
    if(!current) {///node not found
        return -1;
    }
    if (equals(data, current->data)) {
        r += AvlNodeW(current->left_son) + 1;
        return r;
    }
    else {
        if (bigger(data, current->data)) {
            r += AvlNodeW(current->left_son) + 1;
            return RankAvlNode(current->right_son, data, r);
        }
        else {
            return RankAvlNode(current->left_son, data, r);
        }
    }
}


template<class T>
T* AvlRankTree<T>::Select(int k){
    ///finding the node with the rank k and returning a pointer to its data
    AvlNode* nodeFound = SelectAvlNode(root, k);
    if(nodeFound){
        return &(nodeFound->data);
    }
    else{
        return nullptr;
    }
}


template<class T>
typename AvlRankTree<T>::AvlNode*
AvlRankTree<T>::SelectAvlNode(AvlRankTree<T>::AvlNode* current, int k){
    if(!current) {///node not found
        return nullptr;
    }
    if (AvlNodeW(current->left_son) == k-1) {
        return current;
    }
    else {
        if (AvlNodeW(current->left_son) > k-1) {
            return SelectAvlNode(current->left_son, k);
        }
        else {
            return SelectAvlNode(current->right_son, k - AvlNodeW(current->left_son) - 1);
        }
    }
}


template<class T>
bool AvlRankTree<T>::remove(T& data) {
    if (!data || size == 0) {
        return false;
    }
    T dataCopy = data;
    bool deletedStatus = removeAvlNode(dataCopy, root);
    size--;
    return deletedStatus;
}


template<class T>
bool AvlRankTree<T>::removeAvlNode(T& data, AvlRankTree<T>::AvlNode *current) {
    if (!current->left_son && !current->right_son) {
        ////its a leaf
        if (!equals(current->data, data)){
            return false;///not found
        }
    }
    bool success;
    if (equals(current->data, data)) {
        if (!current->left_son && !current->right_son) {
            ////its a leaf
            if (current->father){
                if (current->father->left_son == current){
                    current->father->left_son = nullptr;
                }
                else{
                    current->father->right_son = nullptr;
                }
            }
            else{
                this->root = nullptr;
            }
            delete current;



            ///check if ok for pointer, maybe smart ptr
            return true;
        }
        else if (!current->left_son) {
            ///has right_son son only, balanced tree, so the son is a leaf
            swap_data(current->right_son, current);////in the place of current is its child with height 0
            delete current->right_son;
            current->right_son = nullptr;
            success = true;
        }
        else if (!current->right_son) {
            ///has left_son son only, balanced tree, so the son is a leaf
            swap_data(current->left_son, current);////in the place of current is its child
            delete current->left_son;
            current->left_son = nullptr;
            success = true;
        }
        else {
            ///has both sons- requires check, weirdly works in theory
            AvlNode* new_father;
            if (current->right_son->left_son){
                new_father = current->right_son;
                while (new_father->left_son){
                    new_father = new_father->left_son;//min in right
                }
            }
            else{
                new_father = current->right_son;
            }
            swap_data(new_father, current);
            success = removeAvlNode(data, current->right_son);
        }
    }
    else if (bigger(data, current->data)) {
        success = removeAvlNode(data, current->right_son);
    } else {
        success = removeAvlNode(data, current->left_son);
    }


    current->w = AvlNodeW(current->left_son) + AvlNodeW(current->right_son) + 1;

    current->height = max(AvlNodeHeight(current->left_son), AvlNodeHeight(current->right_son)) + 1;

    balanceAvlNode(current);


    current->w = AvlNodeW(current->left_son) + AvlNodeW(current->right_son) + 1;////maybe redundant

    return success;
}


template<class T>
void AvlRankTree<T>::balanceAvlNode(AvlRankTree::AvlNode *node) {
    if (node->getBalanceFactor() == 2) {
        if ((node->left_son)->getBalanceFactor() >= 0) {
            LLroll(node);
        } else {
            LRroll(node);
        }
    } else if (node->getBalanceFactor() == -2) {
        if ((node->right_son)->getBalanceFactor() == 1) {
            RLroll(node);
        } else {
            RRroll(node);
        }
    }
}

template<class T>
int AvlRankTree<T>::AvlNodeHeight(const AvlNode* node) const{///////////////
    return node == nullptr ? -1 : node->height;
}

template<class T>
int AvlRankTree<T>::AvlNodeW(const AvlNode* node) const{///////////////
    return node == nullptr ? 0 : node->w;
}

template<class T>
void AvlRankTree<T>::LLroll(AvlRankTree<T>::AvlNode *node) {///////////////
    AvlNode* father = node->father;
    AvlNode *tmp = node->left_son;
    node->left_son->father = node->father;
    node->father = tmp;
    if(tmp->right_son){
        tmp->right_son->father =node;
    }
    node->left_son = node->father->right_son;
    node->father->right_son = node;
    node->height = max(AvlNodeHeight(node->right_son), AvlNodeHeight(node->left_son)) + 1;
    node->w = AvlNodeW(node->left_son) + AvlNodeW(node->right_son) + 1;
    node->father->height = max(AvlNodeHeight(node->father->right_son), AvlNodeHeight(node->father->left_son)) + 1;
    node->father->w = AvlNodeW(node->father->right_son) + AvlNodeW(node->father->left_son) + 1;

    if(father) {
        if (bigger(father->data, node->father->data)){
            father->left_son = node->father;
        }
        else{
            father->right_son = node->father;
        }
    }
    else{
        root = tmp;
    }
}

template<class T>
void AvlRankTree<T>::RRroll(AvlRankTree<T>::AvlNode *node) {///////////////
    AvlNode* father = node->father;
    AvlNode *tmp = node->right_son;
    tmp->father = father;

    node->father = tmp;
    node->right_son = tmp->left_son;
    if(node->right_son)
        node->right_son->father = node;
    node->father->left_son = node;

    node->height = max(AvlNodeHeight(node->right_son), AvlNodeHeight(node->left_son)) + 1;
    node->w = AvlNodeW(node->left_son) + AvlNodeW(node->right_son) + 1;
    node->father->height = max(AvlNodeHeight(node->father->right_son), AvlNodeHeight(node->father->left_son)) + 1;
    node->father->w = AvlNodeW(node->father->right_son) + AvlNodeW(node->father->left_son) + 1;
    if(father){
        if (bigger(father->data, node->father->data)){
            father->left_son = node->father;
        }
        else{
            father->right_son = node->father;
        }
    }
    else{
        root = tmp;
    }
}

template<class T>
void AvlRankTree<T>::LRroll(AvlRankTree<T>::AvlNode *node) {///////////
    RRroll(node->left_son);
    LLroll(node);
}

template<class T>
void AvlRankTree<T>::RLroll(AvlRankTree<T>::AvlNode *node) {////////////
    LLroll(node->right_son);
    RRroll(node);
}

template<class T>
int AvlRankTree<T>::getSize() const {
    return size;
}

#endif //WET2MIVNEINIRNIZ_AVL_RANK_H

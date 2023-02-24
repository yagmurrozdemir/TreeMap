#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <cmath>

#include "Node.h"
#include "NoSuchItemException.h"

enum TraversalMethod {preorder, inorder, postorder};

template<class T>
class ScapegoatTree {
public: 
    ScapegoatTree();

    ScapegoatTree(const ScapegoatTree<T> &obj);

    ~ScapegoatTree();

    bool isEmpty() const;

    int getHeight() const;

    int getSize() const;

    bool insert(const T &element);

    bool remove(const T &element);

    void removeAllNodes();

    const T &get(const T &element) const;

    void print(TraversalMethod tp=inorder) const;

    void printPretty() const;

    ScapegoatTree<T> &operator=(const ScapegoatTree<T> &rhs);

    void balance();

    const T &getCeiling(const T &element) const;

    const T &getFloor(const T &element) const;

    const T &getMin() const;

    const T &getMax() const;

    const T &getNext(const T &element) const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(Node<T> *node, TraversalMethod tp) const;
    void printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const;
    int getHeight(Node<T>* node) const
    {
        int h;
        if (node==NULL) return -1;
        if((node->right==NULL)&&(node->left==NULL)) return 0;
    
    h = (getHeight(node->right)>=getHeight(node->left))?  (getHeight(node->right)+1) : (getHeight(node->left)+1);
    return h;
    }
    int getSize(Node<T>* node)const 
    {
        int s;
        
        if (node==NULL) return 0;
        if((node->right==NULL)&&(node->left==NULL)) return 1;
        
        s=(getSize(node->right)+getSize(node->left)+1);
        return s;
    }
    void removeAllNodes(Node<T>* &node)
    {
        if (node==NULL){
            return;
        }
        
        removeAllNodes(node->right);
        removeAllNodes(node->left);
        delete node;
        node=NULL;
        
        
    }
    
    void insert(Node<T>* &node, const T &element)
    {
        if(getP(root, element)!=NULL) return ;
       
        else if(node==NULL)
        {
        node = new Node<T> (element,NULL,NULL);
        
        }

        else if(element < node -> element){
            insert(node->left, element);
        }
        else if(element > node -> element){
            insert(node->right, element);
        }
        
    }
    
    Node<T>* getP(Node<T>* node, const T &element)const
    {
    
        while(node!=NULL){
        
            if(node->element == element) return node;
        
            if(node->element > element) node = node -> left;
        
            else if(node->element < element) node = node -> right;
        
        }
    
        if(node==NULL) return NULL;
    }
    
    Node<T>* getMin(Node<T>* node) const {
        
        if(node==NULL) return NULL;
        while(node->left!=NULL){
            node=node->left;
        }
        return node;
    }
    
    Node<T>* getMax(Node<T>* node) const {
    
        if(node==NULL) return NULL;
        while(node->right!=NULL){
            node=node->right;
        }
        return node;
    }
    
    Node<T>* findMom(Node<T>* node, const T &element) const{
        
        if(node==NULL) return NULL;
        if(getP(node, element)==NULL) return NULL;
        
        if(node->element==element) return node;
        
        if(node->element > element) {
            
            if ((node->left!=NULL)&&(node->left->element==element)) return node;
            else return findMom(node->left, element);
        }
        
        else if(node->element < element){ 
            if ((node->right!=NULL) && (node->right->element==element)) return node;
            else return findMom(node->right, element);
        }
        
    }
    
    
    void remove( Node<T>* &node, const T &element){
        if (node==NULL) return ;
        Node<T>* iter=getP(node,element);
        T newValue;
        Node<T>* iterLeft;
        Node<T>* iterRight;
        if(iter==NULL) return ;
        if((iter->right==NULL)&&(iter->left==NULL)){
            
            if(iter==root){
                delete iter;
                root = NULL;
                return ;
            } 

            if(findMom(root,element)->element > element ){
                findMom(root,element)->left=NULL;
            }
            else if (findMom(root,element)->element < element ){
                findMom(root,element)->right=NULL;
            }
            delete iter;
            return ;
        }
        else if(iter->left==NULL){
            newValue = iter->right->element;
            iter->left = iter->right->left;
            iterRight = iter->right->right;
            delete iter->right;
            iter->element = newValue;
            iter->right=iterRight;
            return ;
        }
        else if(iter->right==NULL){
            newValue = iter->left->element;
            iter->right = iter->left->right;
            iterLeft = iter->left->left;
            delete iter->left;
            iter->element = newValue;
            iter->left=iterLeft;
            return ;
        }
        
        else{
            newValue = getMax(iter->left)->element;
            remove(iter, getMax(iter->left)->element);
            iter->element= newValue;
            
        }
        
        
    }
    
    Node<T>* copy(Node<T>* node){
        if (node==NULL) return NULL;
        
        Node<T>* head = new Node<T>(node->element, NULL, NULL);
        head->left = copy(node->left);
        head->right = copy(node->right);
        return head;
    }
    
    void arrcons(Node<T>* node, T *&arr, int &i)const{
        if(node!=NULL){
            arrcons(node->left, arr, i);
            arr[i]=node->element;
            i++;
            arrcons(node->right, arr, i);
        }
    }
    
    Node<T>* helperBalance(Node<T>* &node, T* arr, int start, int end){
        if(start>end) return NULL;
        node= new Node<T>(arr[(start+end)/2], NULL, NULL);
        helperBalance(node->left, arr, start, ((start+end)/2)-1);
        helperBalance(node->right, arr, ((start+end)/2)+1, end);
        
        return node;
        return NULL;
    }
    
    Node<T>* scapeGoat(Node<T>* node)const{
        Node<T>* temp = node;
        while(3*getSize(node)<=2*getSize(findMom(root, node->element))){
            node=findMom(root, node->element);
        }
        temp = findMom(root, node->element);
        return temp;
    }
    
    Node<T> *getCeiling(Node <T> *node, const T &element) const
    {
        if(!node) return NULL;
        if(node -> element == element) return node;
            
        if(node -> element < element) return getCeiling(node -> right, element);
            
        if(node -> element > element)
        {
            Node<T> *temp = getCeiling(node -> left, element);
            if(!temp) return node;
            return temp;
        }
    }
    
    Node<T> *getFloor(Node <T> *node, const T &element) const
    {
        if(!node) return NULL;
        if(node -> element == element) return node;
            
        if(node -> element > element) return getFloor(node -> left, element);
            
        if(node -> element < element)
        {
            Node<T> *temp = getFloor(node -> right, element);
            if(!temp) return node;
            return temp;
        }
    }


private:
    Node<T> *root;

    int upperBound;
};

#endif //TREE_H

template<class T>
ScapegoatTree<T>::ScapegoatTree() {
    
    root=NULL;
    upperBound=0;
}

template<class T>
ScapegoatTree<T>::ScapegoatTree(const ScapegoatTree<T> &obj) {
    
    root=NULL;
    upperBound= obj.upperBound;
    *this = obj;
    
}

template<class T>
ScapegoatTree<T>::~ScapegoatTree() {
    this->removeAllNodes();

}

template<class T>
bool ScapegoatTree<T>::isEmpty() const {
    return (root==NULL)? 1 : 0;
}

template<class T>
int ScapegoatTree<T>::getHeight() const {
    return getHeight(this->root);
}

template<class T>
int ScapegoatTree<T>::getSize() const {
    return getSize(this->root);

}

template<class T>
bool ScapegoatTree<T>::insert(const T &element) {
    
    if(getP(root, element)) return false;
    insert(root,element);
    
    upperBound++;
    
    if(getHeight()>(log2(upperBound)/log2(1.5))){
        
        Node<T>* temp = scapeGoat(getP(root,element));
        int i = 0;
        int n = 0;
        int m = getSize(temp);
        bool k;
        T* arr = new T[m];
        
        
        Node<T>* temp2 = findMom(root, temp->element);
        if(temp2->left == temp) k=1;
        else k=0;
        
        arrcons(temp,arr,n );
        
    
        removeAllNodes(temp);

        m--;
        if(k){
            temp2 -> left = helperBalance(temp,arr,i,m);
        }
        
        else{
            temp2 -> right = helperBalance(temp,arr,i,m);
        }
    
        delete [] arr;
        
    }
    return 1;
    
}

template<class T>
bool ScapegoatTree<T>::remove(const T &element) {
    
    if(!getP(root, element)) return 0;
    
    remove(root, element);
    
    if(((upperBound)>2*getSize())||(getSize()>upperBound)) {
        
        balance();
        
        upperBound=getSize();
        
    }
    
    return 1;

}

template<class T>
void ScapegoatTree<T>::removeAllNodes() {
    removeAllNodes(root);
    upperBound=0;
}

template<class T>
const T &ScapegoatTree<T>::get(const T &element) const {
    
    Node<T>* temp = this->root;
    
    while(temp!=NULL){
        
        if(temp->element == element) return temp->element;
        
        if(temp->element > element) temp = temp -> left;
        
        else if(temp->element < element) temp = temp -> right;
        
    }
    
    if(temp==NULL) throw NoSuchItemException();
}

template<class T>
void ScapegoatTree<T>::print(TraversalMethod tp) const {

    if (tp == preorder) 
    {
        
        if (isEmpty()) 
        {
            
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }
        
        std::cout << "BST_preorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
        
        
    } 
    else if (tp == inorder) 
    {
        
        if (isEmpty()) {
            
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        
        std::cout << "BST_inorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    } 
    else if (tp == postorder) 
    {
        if (isEmpty()) {
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }


        std::cout << "BST_postorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    }
}

template<class T>
void ScapegoatTree<T>::print(Node<T> *node, TraversalMethod tp) const {

    if (tp == preorder) 
    {
        if (node == NULL)
          return;

        
        std::cout << "\t" << node->element;
        
        
        if (node->left) {
            std::cout << "," << std::endl;
        }
        
        print(node->left, preorder);

        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);
    } 
    
    
    else if (tp == inorder) 
    {
    
        if (node == NULL)
          return;

        print(node->left, inorder);
        if (node->left) {
                std::cout << "," << std::endl;
            }
            
            std::cout << "\t" << node->element;
    
            if (node->right) {
                std::cout << "," << std::endl;
            }
            print(node->right, inorder);
        } 
        else if (tp == postorder) 
        {
            if (node == NULL)
              return;
    
            print(node->left, postorder);
            if (node->left) {
                std::cout << "," << std::endl;
            }
    
            print(node->right, postorder);
            
            if (node->right) {
                std::cout << "," << std::endl;
            }
            
            
            std::cout << "\t" << node->element;
        } 
}

template<class T>
void ScapegoatTree<T>::printPretty() const {

    // check if the tree is empty?
    if (isEmpty()) {
        // the tree is empty.
        std::cout << "BST_pretty{}" << std::endl;
        return;
    }

    // the tree is not empty.

    // recursively output the tree.
    std::cout << "BST_pretty{" << std::endl;
    printPretty(root, 0, false);
    std::cout << "}" << std::endl;

}

template<class T>
void ScapegoatTree<T>::printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    // output the indentation and the node.
    std::cout << "\t";
    for (int i = 0; i < indentLevel; ++i) {
        std::cout << "---";
    }
    std::cout << (indentLevel == 0 ? "root:" : (isLeftChild ? "l:" : "r:")) << node->element << std::endl;

    // first, output left subtree with one more indentation level.
    printPretty(node->left, indentLevel + 1, true);

    // then, output right subtree with one more indentation level.
    printPretty(node->right, indentLevel + 1, false);
}

template<class T>
ScapegoatTree<T> &ScapegoatTree<T>::operator=(const ScapegoatTree<T> &rhs) {
    
    if(&rhs == this) return *this;
    this->removeAllNodes();
    root = copy(rhs.root);
    upperBound=rhs.upperBound;
    return *this;
}

template<class T>
void ScapegoatTree<T>::balance() {
    int i = 0;
    int n = 0;
    int m = getSize();
    T* arr = new T[m];
    arrcons(root,arr,n );
    int temp = upperBound;
    this->removeAllNodes();
    upperBound = temp;
    m--;
    helperBalance(root,arr,i,m);
    
    delete [] arr;
    
}

template<class T>
const T &ScapegoatTree<T>::getCeiling(const T &element) const {

    Node<T> *node = getCeiling(this -> root, element);
    
    if(!node) throw NoSuchItemException();
    return node -> element;
}

template<class T>
const T &ScapegoatTree<T>::getFloor(const T &element) const {
    Node<T> *node = getFloor(this -> root, element);
    
    if(!node) throw NoSuchItemException();
    return node -> element;
}

template<class T>
const T &ScapegoatTree<T>::getMin() const {
    if(getMin(root)==NULL) throw NoSuchItemException();
    else return getMin(root)->element;

}

template<class T>
const T &ScapegoatTree<T>::getMax() const {
    if(getMax(root)==NULL) throw NoSuchItemException();
    else return getMax(root)->element;
}

template<class T>
const T &ScapegoatTree<T>::getNext(const T &element) const {
    
    if(getP(root, element)==NULL) return this->getCeiling(element);
    if(this->getMax()==element) throw NoSuchItemException();
    if(getP(root, element)->right!=NULL) return getMin(getP(root, element)->right)->element;
    else if(findMom(root, element)->left == getP(root, element)) {
        return findMom(root, element)->element;
    }
    else{
        T newElement=element;
        while(findMom(root, newElement)->left != getP(root, newElement)){
            newElement = findMom(root, newElement)->element;
        }
        return findMom(root, newElement)->element;
        
    }
}





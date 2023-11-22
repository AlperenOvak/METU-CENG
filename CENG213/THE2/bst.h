#ifndef BST_H
#define BST_H

#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

// do not add any other library.
// modify parts as directed by assignment text and comments here.

template <class T>
class BST {
private:
    // Define TreeNode for the second phase (Binary Search Tree)
    /* DO NOT CHANGE */
    struct TreeNode {
        std::string key;
        T data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(const std::string &k, const T& value) : key(k), data(value), left(NULL), right(NULL) {}
        
    };

    TreeNode* root;


public: // Do not change.

    BST();
    ~BST();
    void destroyTree(TreeNode* node); //remove it later
    TreeNode* getRoot() { return root; }
    bool isEmpty() { return root == NULL; }

    BST& insert(const std::string key, const T& value);
    TreeNode* insertRecursive(TreeNode* node, const std::string& key, const T& value);

    bool search(std::string value) const;
    TreeNode* finder(TreeNode* root,std::string key);

    void remove(std::string value);
    TreeNode* deleteNode(TreeNode* node, std::string key);

    BST<T>* merge(BST<T>* bst);
    BST<T>* intersection(BST<T>* bst);
    std::vector<TreeNode> tree2vector(TreeNode* root);
    void tree2vector(TreeNode* node, std::vector<TreeNode>& result);
    void print();
    
private:// you may add your own utility member functions here.

    void print(TreeNode* node, std::string indent, bool last, bool isLeftChild); // Do not change.
    
};

    // Constructor
    template <class T>
    BST<T>::BST() : root(NULL) {}

    // Destructor
    template <class T>
    BST<T>::~BST() {    // write again !!!!!!!
    /* IMPLEMENT THIS */
        destroyTree(root);
    }

    template <class T>
    void BST<T>::destroyTree(TreeNode* node) {
        if (node != NULL) {
            destroyTree(node->left);  // Recursively delete left subtree
            destroyTree(node->right); // Recursively delete right subtree
            delete node;              // Delete the current node
        }
    }

    // Insert function for BST.    
    template <class T>
    BST<T>& BST<T>::insert(const string key, const T& value) {
            /* IMPLEMENT THIS */
            root=insertRecursive(root,key,value);
            
            return *this;
    }

    template <class T>
    typename BST<T>::TreeNode* BST<T>::insertRecursive(TreeNode* node, const std::string& key, const T& value) {
        if (node == nullptr) {
            // If the tree is empty or we reached a leaf, create a new node
            return new TreeNode(key, value);
        }

        // Traverse the tree to find the appropriate position based on the key
        if (key < node->key) {
            // Go to the left subtree
            node->left = insertRecursive(node->left, key, value);
        } else if (key > node->key) {
            // Go to the right subtree
            node->right = insertRecursive(node->right, key, value);
        } else {
            // If the key already exists, update the value (or handle accordingly)
            node->data = value;
        }

        return node;
    }

    
    // Search function for BST.
    template <class T>
    bool BST<T>::search(std::string value) const {
     /* IMPLEMENT THIS */
        TreeNode* temp = root;
        while(temp){
            if(temp->key==value){
                return true;
            }else if(temp->key > value){
                if(temp->left){
                    temp=temp->left;
                }else{
                    return false;
                }
            }else{
                if(temp->right){
                    temp=temp->right;
                }else{
                    return false;
                }
            }
        }
        return false;
    }

    template <class T>
    typename BST<T>::TreeNode* BST<T>::finder(TreeNode* node,std::string key) {   // no need??
     /* IMPLEMENT THIS */
        if (node == NULL)
            return NULL;
        if (node->key > key){
            return finder(node->left,key);
        }else if (node->key < key){
            return finder(node->right,key);
        }else{
            return node;
        }
    }
    
    // Remove a node from BST for given key. If key not found, do not change anything.
    template <class T>
    void BST<T>::remove(std::string key) {
        /* IMPLEMENT THIS */
        root= deleteNode(root,key);
    }

    template <class T>
    typename BST<T>::TreeNode* BST<T>::deleteNode(TreeNode* node, std::string key){
    // Base case
    if (node == NULL)
        return node;
 
    // Recursive calls for ancestors of
    // node to be deleted
    if (node->key > key) {
        node->left = deleteNode(node->left, key);
        return node;
    }
    else if (node->key < key) {
        node->right = deleteNode(node->right, key);
        return node;
    }
 
    // We reach here when root is the node
    // to be deleted.
 
    // If one of the children is empty
    if (node->left == NULL) {
        TreeNode* temp = node->right;
        delete node;
        return temp;
    }
    else if (node->right == NULL) {
        TreeNode* temp = node->left;
        delete node;
        return temp;
    }
 
    // If both children exist
    else {
 
        TreeNode* succParent = node;
 
        // Find successor
        TreeNode* succ = node->right;
        while (succ->left != NULL) {
            succParent = succ;
            succ = succ->left;
        }
 
        // Delete successor.  Since successor
        // is always left child of its parent
        // we can safely make successor's right
        // right child as left of its parent.
        // If there is no succ, then assign
        // succ->right to succParent->right
        if (succParent != node)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;
 
        // Copy Successor Data to root
        node->key = succ->key;
 
        // Delete Successor and return root
        delete succ;
        return node;
    }
}
    
    // A helper function for converting a BST into vector.
    template <class T>
    vector<typename BST<T>::TreeNode> BST<T>::tree2vector(TreeNode* root) {
        vector<TreeNode> result;
        tree2vector(root, result);
        return result;
    }

    template <class T>
    void BST<T>::tree2vector(TreeNode* node, std::vector<TreeNode>& result){
        while(node){
            tree2vector(node->left, result);
            result.push_back(node);
            tree2vector(node->right, result);
        }
    }
    
    // Merge two BST's and return merged BST.
    template <class T>
    BST<T>* BST<T>::merge(BST<T>* bst) {
    /* IMPLEMENT THIS */
        vector<TreeNode> LHS =tree2vector(root);
        vector<TreeNode> RHS =tree2vector(bst->getRoot());
        vector<TreeNode> result;
        BST<T> a();
        int i=0;
        int j=0;
        while(i<LHS.size() && j<RHS.size()){
            if(LHS[i].key < RHS[j].key){
                result.push_back(LHS[i++]);
            }else if(LHS[i].key > RHS[j].key){
                result.push_back(RHS[j++]);
            }else{
                result.push_back(RHS[j++]);
                i++;
            }
        }

        while(i<LHS.size()){
            result.push_back(LHS[i++]);
        }
        while(j<RHS.size()){
            result.push_back(RHS[j++]);
        }

        for(i=0;i<result.size();i++){
            a.insert(result[i].key, result[i].data);
        }
        return a;
    }
        
    // Intersect two BST's and return new BST.
    template <class T>
    BST<T>* BST<T>::intersection(BST<T>* bst) {
    /* IMPLEMENT THIS */
        return this;
    }
    
    /* DO NOT CHANGE */
    template <class T>
    void BST<T>::print() {
        print(root, "", true, false);
    
    }
    
    /* DO NOT CHANGE */
    template <class T>
    void BST<T>::print(TreeNode* node, string indent, bool last, bool isLeftChild) {
        if (node != NULL) {
            cout << node->key << endl;
            print(node->left, indent, false, true);
            print(node->right, indent, true, false);
        }
    
    }

#endif
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
    TreeNode* getRoot() { return root; }
    bool isEmpty() { return root == NULL; }

    BST& insert(const std::string key, const T& value);
    bool search(std::string value) const;
    void remove(std::string value);
    BST<T>* merge(BST<T>* bst);
    BST<T>* intersection(BST<T>* bst);
    std::vector<TreeNode> tree2vector(TreeNode* root);
    void print();
    
private:// you may add your own utility member functions here.

    void destroyTree(TreeNode* node); 
    TreeNode* insertRecursive(TreeNode* node, const std::string& key, const T& value);
    void print(TreeNode* node, std::string indent, bool last, bool isLeftChild); // Do not change.
    void tree2vector(TreeNode* node, std::vector<TreeNode>& result);
    TreeNode* remove(TreeNode* node, std::string key);
    
};

    // Constructor
    template <class T>
    BST<T>::BST() : root(NULL) {}

    // Destructor
    template <class T>
    BST<T>::~BST() {    // write again !!!!!!!
        destroyTree(root);
    }

    template <class T>
    void BST<T>::destroyTree(TreeNode* node) {                    //DONE
        if (node != NULL) {
            destroyTree(node->left);  // Recursively delete left subtree
            destroyTree(node->right); // Recursively delete right subtree
            delete node;              // Delete the current node
        }
        root=NULL;
    }

    // Insert function for BST.    
    template <class T>
    BST<T>& BST<T>::insert(const string key, const T& value) {      //DONE
            
            root=insertRecursive(root,key,value);
            
            return *this;
    }

    template <class T>
    typename BST<T>::TreeNode* BST<T>::insertRecursive(TreeNode* node, const std::string& key, const T& value) {  //DONE
        if (node == NULL) {
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
    bool BST<T>::search(std::string value) const {    //DONE
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

    
    // Remove a node from BST for given key. If key not found, do not change anything.
    template <class T>
    void BST<T>::remove(std::string key) {   //DONE
        root= remove(root,key);
    }

    template <class T>
    typename BST<T>::TreeNode* BST<T>::remove(TreeNode* node, std::string key){       //DONE
    // Base case
    if (node == NULL)
        return node;
 
    // Recursive calls for ancestors of node to be deleted
    if (node->key > key) {
        node->left = remove(node->left, key);
        return node;
    }
    else if (node->key < key) {
        node->right = remove(node->right, key);
        return node;
    }
 
    // when root is the node to be deleted.
 
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
        // is left child of its parent
        // make successor's right
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
    vector<typename BST<T>::TreeNode> BST<T>::tree2vector(TreeNode* root) {        //DONE
        vector<TreeNode> result;
        tree2vector(root, result); //create a flatten vector for tree, it will be alphabetic order
        return result;
    }

    template <class T>  
    void BST<T>::tree2vector(TreeNode* node, std::vector<TreeNode>& result){         //DONE
        if(node){   
            tree2vector(node->left, result);
            result.push_back(*node);
            tree2vector(node->right, result);
        }
    }
    
    // Merge two BST's and return merged BST.
    template <class T>
BST<T>* BST<T>::merge(BST<T>* bst) {      //DONE      //test it with empty sets
    /* IMPLEMENT THIS */
    vector<TreeNode> LHS = tree2vector(getRoot());
    vector<TreeNode> RHS = bst->tree2vector(bst->getRoot());
    vector<TreeNode> result;

    int i = 0;
    int j = 0;

    while (i < LHS.size() && j < RHS.size()) {  // U union
        if (LHS[i].key < RHS[j].key) {
            result.push_back(LHS[i++]);
        } else if (LHS[i].key > RHS[j].key) {
            result.push_back(RHS[j++]);
        } else {
            result.push_back(RHS[j++]);
            i++;
        }
    }

    while (i < LHS.size()) {
        result.push_back(LHS[i++]);
    }

    while (j < RHS.size()) {
        result.push_back(RHS[j++]);
    }

    BST<T>* mergedBST = new BST<T>();

    for (int i = 0; i < result.size(); i++) {
        mergedBST->insert(result[i].key, result[i].data);
    }

    return mergedBST;
}
        
    // Intersect two BST's and return new BST.
    template <class T>
    BST<T>* BST<T>::intersection(BST<T>* bst) {    //DONE

        vector<TreeNode> LHS = tree2vector(getRoot());
        //std::cout<<"vector1 done" << std::endl;
        vector<TreeNode> RHS = bst->tree2vector(bst->getRoot());
        //std::cout<<"vector2 done" << std::endl;
        vector<TreeNode> result;
        

        int i = 0;
        int j = 0;

        while (i < LHS.size() && j < RHS.size()) {   // ∩ intersection
            if (LHS[i].key < RHS[j].key) {
                i++;
            } else if (LHS[i].key > RHS[j].key) {
                j++;
            } else {
                result.push_back(RHS[j++]);
                i++;
            }
        }


        BST<T>* interBST = new BST<T>();

        for (int i = 0; i < result.size(); i++) {
            interBST->insert(result[i].key, result[i].data);
        }

        return interBST;
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
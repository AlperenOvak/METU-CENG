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
    void remove(std::string value);
    BST<T>* merge(BST<T>* bst);
    BST<T>* intersection(BST<T>* bst);
    std::vector<TreeNode> tree2vector(TreeNode* root);
    void print();
    
private:// you may add your own utility member functions here.

    void print(TreeNode* node, std::string indent, bool last, bool isLeftChild); // Do not change.
    
};

    // Constructor
    template <class T>
    BST<T>::BST() : root(NULL) {}

    // Destructor
    template <class T>
    BST<T>::~BST() {
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

     return false;
    }
    
    // Remove a node from BST for given key. If key not found, do not change anything.
    template <class T>
    void BST<T>::remove(std::string key) {
        /* IMPLEMENT THIS */
    }
    
    // A helper function for converting a BST into vector.
    template <class T>
    vector<typename BST<T>::TreeNode> BST<T>::tree2vector(TreeNode* root) {
        vector<TreeNode> result;
        return result;
    }
    
    // Merge two BST's and return merged BST.
    template <class T>
    BST<T>* BST<T>::merge(BST<T>* bst) {
    /* IMPLEMENT THIS */
        return this;
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
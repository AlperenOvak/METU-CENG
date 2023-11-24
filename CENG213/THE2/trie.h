#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;


template <class T>
class Trie {    
private:
    // Define TrieNode for the first phase (Trie)
    /* DO NOT CHANGE */
    struct TrieNode {
        static const int ALPHABET_SIZE = 128;
        TrieNode* children[ALPHABET_SIZE];
        char keyChar;
        bool isEndOfKey;
        T* data;

        TrieNode(char c) : keyChar(c), isEndOfKey(false), data(NULL) {

                for (int i = 0; i< ALPHABET_SIZE; i++) {
                children[i] = NULL;
                
            }
            
            }
    };

    TrieNode* root;

public: // Do not change.

    Trie(); 
    ~Trie();
    void deleteTrieNode(TrieNode* node);
    Trie& insert(const string& username); 
    void remove(std::string username);
    T* search(std::string username); 
    void findStartingWith(std::string prefix, std::vector<T*> &results); 
    void wildcardSearch(const std::string &wildcardKey, std::vector<T*> &results); 
    void print(); 

private: // you may add your own utility member functions here.
    void findAllKeys(TrieNode* root,vector<T*> &results);
    void wildcardRecursive(TrieNode* node,const std::string &text,std::string prefix, int index, std::vector<T*> &results);
    void print(const std::string& primaryKey); // Do not change this line.
    void printTrie(TrieNode* node, const std::string& currentKey); // Do not change this line.
    
};
/* DO NOT CHANGE */
template <class T>
Trie<T>::Trie() : root(new TrieNode('\0')) {}

template <class T>
Trie<T>::~Trie() {
    deleteTrieNode(root);
}


template <class T>
void Trie<T>::deleteTrieNode(TrieNode* node) {
    if (node) {
        for (int i = 0; i < TrieNode::ALPHABET_SIZE; i++) {
            deleteTrieNode(node->children[i]);
        }
        delete node->data;  // Free associated data if it's dynamically allocated
        delete node;
    }
}

template <class T>
Trie<T>& Trie<T>::insert(const string& key) {

    TrieNode* current=root;
    int i=0;
    
    while(key[i]){

        int c=key[i];
        if (!current->children[c]) {
            current->children[c] = new TrieNode(key[i]);
        }

        current = current->children[c];
        i++;
    }
    
    current->isEndOfKey = true;
    current->data = new T(key);
    return *this;
}

template <class T>
T* Trie<T>::search(std::string username) {

    TrieNode* current = root;
    int level = 0;

    // Traverse the trie based on the characters of the input key
    while (level < (int)username.length()) {
        int index = (username[level]);

        // If the current node does not exist, the key is not present in the trie
        if (current->children[index] == NULL) {
            return NULL;
        }

        current = current->children[index];
        ++level;
    }

    // If the key is found, return a pointer to the associated data
    return (current != NULL && current->isEndOfKey) ? current->data : NULL;
}

template <class T>
void Trie<T>::remove(std::string username) {
    if (root == NULL) {
        // The trie is empty, nothing to remove
        return;
    }

    TrieNode* current = root;
    int level = 0;

    while (level <  (int)username.length()) {
        int index = username[level];

        // If the current node does not exist, the key is not present in the trie
        if (current->children[index] == NULL) {
            return;
        }
        current->isEndOfKey = false;
        current = current->children[index];
        ++level;
    }

    // Mark the last node as not the end of the key
    if (current != NULL) {
        current->isEndOfKey = false;
    }
}

template <class T>
void Trie<T>::findStartingWith(string prefix,vector<T*> &results) {

    TrieNode* current = root;
    int level = 0;

    // Traverse the trie based on the characters of the input key
    while (level < (int)prefix.length()) {
        int index = (prefix[level]);
        // If the current node does not exist, the key is not present in the trie
        if (current->children[index] == NULL) {
            current=NULL;  //WTF
            level=(int)prefix.length();
        }
        current = current->children[index];
        ++level;
    }  //we find the node that has the last char of prefix
    findAllKeys(current,results); //add all Keys under this node
    
}

template <class T>
void Trie<T>::findAllKeys(TrieNode* root,vector<T*> &results){     //recursive helper function for "findStartingWith"
    if(root){
        if(root->isEndOfKey){
            results.push_back(root->data);   //I find it, then push
        }
        for(int i=0;i<128;i++){  // take a look at each node
            if(root->children[i]){
                findAllKeys(root->children[i],results);
            }
        }
    }
}

template <class T>
void Trie<T>::wildcardSearch(const std::string &wildcardKey, std::vector<T*> &results) {

    std::string prefix = "";
    if((wildcardKey.length()>0) && (root!=NULL)){
        if(wildcardKey[0]!='*' && wildcardKey[0]!='?' && root->keyChar==wildcardKey[0]){
            prefix+=root->keyChar;                                                          //I don't know how it works, but it works LoL
        }
    }
    wildcardRecursive(root,wildcardKey,prefix,0,results);     
}
template <class T>
void Trie<T>::wildcardRecursive(TrieNode* node,const std::string &text,std::string prefix, int index, std::vector<T*> &results) {  //DONE
/* IMPLEMENT THIS */
    if(node!=NULL){
        if(index == text.length()){
            if(node->isEndOfKey){
                std::cout<<prefix<<std::endl;
                results.push_back(node->data);
            }
        }else{
            if(text[index]=='?'){
                for(int i=0;i<128;i++){
                    if(node->children[i]){
                        wildcardRecursive(node->children[i],text,prefix+node->children[i]->keyChar,index+1,results);
                    }
                }
            }else if(text[index]=='*'){
                wildcardRecursive(node,text,prefix,index+1,results); 
                for(int i=0;i<128;i++){
                    if(node->children[i]){
                        wildcardRecursive(node->children[i],text,prefix+node->children[i]->keyChar,index,results);
                    }
                }
            }else{
                wildcardRecursive(node->children[(int)text[index]],text,prefix+text[index],index+1,results); 
            }   
        }
    }

}

/* DO NOT CHANGE */
template<class T>
void Trie<T>::print() {
    print("");
}
/* DO NOT CHANGE */
template <class T>
void Trie<T>::print(const std::string& primaryKey) {
    if (primaryKey.empty()) {
        // Print the entire tree.
        printTrie(root, "");
    } else {
        // Print specific keys.
        TrieNode* primaryNode = root;
        for (int i = 0; i < primaryKey.length(); i++) {
            
            int index = primaryKey[i];
            if (!primaryNode->children[index]) {
                std::cout << "{}" << std::endl; // Primary key not found, nothing to print.
                return ;
            }
            primaryNode = primaryNode->children[index];
        }
    }
}
/* DO NOT CHANGE */
template <class T>
void Trie<T>::printTrie(TrieNode* node, const std::string& currentKey) {
    if (!node) {
        return;
    }
    if (node->isEndOfKey) {
        std::cout << currentKey <<std::endl;
        std::cout << "Watched Movies:" << std::endl;
        if(node->data) {
            node->data->printMovies();
        }
    }
    for (int i = 0; i < 128; ++i) {
        if (node->children[i]) {
            printTrie(node->children[i], currentKey + static_cast<char>(i));
        }
    }
}

#endif
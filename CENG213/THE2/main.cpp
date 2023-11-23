#include <iostream>
#include <string>
#include "trie.h"
#include "user_interface.h"
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include "bst.h"
#include "movie.h"
#include "user.h"

using namespace std;
int main(){
    string key1="titanic";
    string key2="araasy";
    string key3="beray";
    string key4="yusuf";
    string key5="zuyokamk";
    string key6="sadadsa";
    string mov1="titanic";
    string mov2="edsadasray";
    string mov3="vvveray";
    string mov4="cghb";
    string mov5="sadsada";
    string mov6="asdjasdkasdas";
    Movie movie1(mov1,3432,331);
    Movie movie2(mov2,342,31231231);
    Movie movie3(mov3,32,3131);
    Movie movie4(mov4,11,3232);
    Movie movie5(mov5,11,3232);
    Movie movie6(mov6,21312,211321);
    BST<Movie> a ,b;
    BST<Movie> *result;
    b.insert(key6,movie6);
    a.insert(key1,movie1);
    a.insert(key2,movie2);
    a.insert(key3,movie3);
    a.insert(key4,movie4);
    a.insert(key5,movie5);
    /*result=a.merge(&b);*/
    Trie<User> c;
    c.insert("eray");
    c.insert("Berat");
    c.insert("Alperen");
    c.insert("Alper");
    User* user = c.search("eray");
    
    user->addMovie("titanic",movie1);
    user->addMovie("edsadasray",movie2);
    user->printMovies();
    cout<<"\n ************************\n";
    c.print();
    c.remove("Berat");
    user->removeMovie(movie2);
    User* user1 = c.search("Alperen");
    if(c.search("eray")){
        cout<<"zort";
    }
    cout<<"\n ************************\n";
    //c.print();
    ////////////////////////////////////////////////////////////////////////////////////////////
    /*BST<Movie> emptyBST1, emptyBST2;
    BST<Movie> *resultEmpty = emptyBST1.merge(&emptyBST2);
    cout << "Merged Empty BSTs: ";
    resultEmpty->print();    // boş bastırmıyor??
    cout << "\n ************************\n";

    // Test case 2: Merge one empty BST with a non-empty BST
    BST<Movie> emptyBST, nonEmptyBST;
    nonEmptyBST.insert("testKey", Movie("testMovie", 42, 123));
    BST<Movie> *resultNonEmpty = emptyBST.merge(&nonEmptyBST);
    cout << "Merged Empty and Non-Empty BSTs: ";
    resultNonEmpty->print();
    cout << "\n ************************\n";*/

    // Test case 3: Merge two non-empty BSTs
    BST<Movie> bst1, bst2;
    bst1.insert("key8", Movie("movie8", 1, 1));
    bst1.insert("key2", Movie("movie2", 2, 2));
    bst1.insert("key3", Movie("movie3", 3, 3));
    bst2.insert("key4", Movie("movie4", 4, 4));
    bst2.insert("key9", Movie("movie9", 5, 5));
    bst2.insert("key8", Movie("movie8", 6, 6));
    cout<< bst2.search("key7") <<"\n" ;
    bst2.print();
    //bst1.printvector();
    cout << "\n ************************\n";
    BST<Movie> *resultMerged = bst1.merge(&bst2);
    cout << "Merged BSTs: \n" ;
    resultMerged->print();

    BST<Movie> *resultinter = bst1.intersection(&bst2);
    cout << "Intersection BSTs: \n" ;
    resultinter->print();

    
}
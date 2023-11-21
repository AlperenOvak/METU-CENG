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
    if(c.search("eray")){
        cout<<"zort";
    }
    cout<<"\n ************************\n";
    c.print();
}
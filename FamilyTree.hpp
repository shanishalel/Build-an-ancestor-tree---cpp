#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

/*
struct node{
    node *father;
    node *mother;
    string name;
};
*/

namespace family{
class Tree{
    public:
    Tree *root;
    Tree *father;
    Tree *mother;
    string name;

    public:
    Tree(){
        root =NULL;
    }
    Tree(string name){
        root=new Tree;
        root->name=name;
        root->father=NULL;
        root->mother=NULL;
    }
    Tree &addFather ( string name,string father);
    Tree &addMother ( string name,string Mother);
    string relation (string rel);
    string find(string rel);
    void remove(string name);
    void display();
    Tree* findTree(string name, Tree *root);
    Tree* remove_all_parents(Tree *root);
};

};
/*
void addFather (string name,string father);
void addMother (string name,string Mother);
string relation (string rel);
string find(string rel);
void remove(string name);
void display();
*/
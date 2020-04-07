#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "FamilyTree.hpp"

using namespace std;

struct node{
    node *father;
    node *mather;
    string name;
} ;

class Tree{
    node *root;
    Tree(){
        root =NULL;
    }
    Tree(string name){
        root->name=name;
    }
    void addFather ( string name,string father);
    void addMother ( string name,string Mother);
    string relation (string rel);
    string find(string rel);
    void remove(string name);
    void display();
};

void Tree::addFather(string name , string father){


}
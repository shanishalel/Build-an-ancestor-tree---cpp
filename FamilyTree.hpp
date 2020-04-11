#pragma once
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

namespace family{
class Tree{
    public:
    Tree *child;
    Tree *father;
    Tree *mother;
    string name;
    string rel;

    public:
    Tree(){
        child =NULL;
        father=NULL;
        mother=NULL;
    };
    Tree(string n){
        name=n;
        rel="me";
        father=NULL;
        mother=NULL;
        child=NULL;
    };
    ~Tree(){        
      if(father) {delete(father); }
      if(mother){delete(mother);}       
    };
    
    Tree &addFather ( string name,string father);
    Tree &addMother ( string name,string Mother);
    string relation (string relat);
    string find(string rel);
    void remove(string name);
    void display();
    Tree* findTree(string name, Tree *root);
    Tree* findTreerel(string s ,Tree *temp);
    void remove_all_parents(Tree *root);
    void print_all_rel(Tree *c);


};

};

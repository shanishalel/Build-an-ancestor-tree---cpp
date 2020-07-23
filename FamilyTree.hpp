#pragma once
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

namespace family{

class Tree{
    public:
    Tree *child; //root
    Tree *father; 
    Tree *mother;
    string name;
    string rel; //relation (father, mother, grandmother and so on...)

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

    /*adding a father to the name we gets */
    Tree &addFather ( string name,string father);
    
    /*adding a mother*/
    Tree &addMother ( string name,string Mother);

    /* getting name of someone and return 
    the relation between me and him*/
    string relation (string relat);
    
    /*getting a string that represents a relation
    and return a name of him*/
    string find(string rel);
    
    /*remove this man and all of him parents*/
    void remove(string name);

    /*printing the tree*/
    void display();
    
    /*this function will return pointer to the rel that the name that we enter bilong to*/
    Tree* findTree(string name, Tree *root);
   
   /*finding the root that his relation equals to the one we gets */
    Tree* findTreerel(string s ,Tree *temp);

    /*remove all the parents of this man*/
    void remove_all_parents(Tree *root);

    /*print all the tree*/
    void print_all_rel(Tree *c);


};

};

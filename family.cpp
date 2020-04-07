#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "FamilyTree.hpp"

using namespace std;

struct node{
    node *father;
    node *mother;
    string name;
};

class Tree{
    public:
    node *root;
    Tree(){
        root =NULL;
    }
    Tree(string name){
        root=new node;
        root->name=name;
        root->father=NULL;
        root->mother=NULL;

    }
    void addFather ( string name,string father);
    void addMother ( string name,string Mother);
    string relation (string rel);
    string find(string rel);
    void remove(string name);
    void display();
    node* findnode(string name, node *root);
};

void Tree::addFather(string name , string father){
node *c=findnode(name ,root);
if (c == NULL){
    return;
}
    else{
        node *p=new node();
        p->name=father;
        p->father=NULL;
        p->mother=NULL;
        c->father=p;
    }
}



void Tree::addMother(string name , string mother){
node *c=findnode(name ,root);
if (c == NULL){
    return;
}
    else{
        node *p=new node();
        p->name=mother;
        p->father=NULL;
        p->mother=NULL;
        c->mother=p;
    }
}

/*this function will return the node that the name that we enter bilong to*/
node* Tree:: findnode(string name ,node *root){
    if (root ==NULL){
        return NULL;
    }
    if (root->name==name){
        return root;  
    }
    if(root->father != NULL)  {
      return findnode(name, root->father);
    } 
    if (root->mother != NULL) {
     return findnode(name, root->mother);
    }
}

void Tree:: display(){
cout << root ->father->name << "\n"  << root ->mother->name  << "\n"  << root -> name;
}



int main(){
    Tree T ("Yosef");
   T.addFather("Yosef", "Yaakov");
   T.addMother("Yosef", "NIII");
    T.display();
}

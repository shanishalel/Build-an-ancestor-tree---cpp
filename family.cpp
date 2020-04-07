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
    node* remove_all_parents(node *root);
};

void Tree::addFather(string name , string father){
node *c=findnode(name ,root);
if (c == NULL){
    return;
}
    else{
        if(root->father!=NULL){
            throw std::out_of_range{" This person already have a father"};
        }
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
 if(root->mother!=NULL){
            throw std::out_of_range{" This person already have a mother"};
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
    return NULL;
}

/*this function will remove the person that the name of him we entered and all his parents*/
void Tree :: remove(string name){
node *tmp=findnode(name, root);
    if(tmp->father!=NULL){
    remove_all_parents(root);
    }


}

/*this function will remove all the fathers of this node*/
node* Tree::remove_all_parents(node *root){
   if(root==NULL){
       return root;
   }
   if(root->father!=NULL){
        remove_all_parents(root->father);
   }
   else if(root->mother!=NULL){
        remove_all_parents(root->mother);
   }
   else{
       if(root->father==NULL){
           node *tmp=root->mother;
           root=NULL;
           return tmp;
       }
       else if(root->mother==NULL){
           node *tmp=root->father;
           root=NULL;
           return tmp;
       }
   }
   return root;

}


void Tree:: display(){
cout << root ->father->name << "\n"  << root ->mother->name  << "\n"  << root -> name;
}



int main(){
    Tree T ("Yosef");
   T.addFather("Yosef", "Yaakov");
   T.addMother("Yosef", "NIII");
       T.display();
    T.display();
}

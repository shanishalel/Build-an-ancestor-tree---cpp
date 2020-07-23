#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "FamilyTree.hpp"

using namespace std;
using namespace family;


/*this function will return pointer to the rel that the name that we enter bilong to*/
Tree* Tree:: findTree(string name ,Tree *temp){
    Tree *current= NULL;
    //if root==temp
    if ((temp->name).compare(name) ==0 ){
        return temp;
    }
    if ( temp != NULL){
        if (temp->father != NULL ) current = findTree(name , temp->father);//call in recursia
        if (current != NULL && (current->name).compare(name)==0){ // we gets to temp 
            return current; 
        }
        if (temp->mother != NULL) current = findTree(name , temp->mother);//call in recursia
        if (current != NULL){ 
            return current;
        }
    }
    return current;
}

/*adding a father to the name we gets */
Tree &Tree::addFather(string name , string father){
Tree *c=findTree(name ,this); //finding the root 
    if (c == NULL){//if the root is empty
        throw runtime_error(name+" is not in the tree");
    }
    else{
        if(c->father!=NULL){ //if he already have one
            throw std::out_of_range{" This person already have a father"};
        }
        Tree *p=new Tree();
        p->name=father;
        p->father=NULL;
        p->mother=NULL;
        p->child=c;
        c->father=p;
        //changing the relation
        if((c->rel).compare("me") ==0) p->rel = "father";
        else if((c->rel).compare("father") ==0) p->rel = "grandfather";
        else if((c->rel).compare("mother") ==0) p->rel = "grandfather";
        else if((c->rel).compare("grandfather") ==0) p->rel = "great-grandfather";
        else if((c->rel).compare("grandmother") ==0) p->rel = "great-grandfather";
        //great-great...
        else {
            string t ="great-"+ c->rel;//adding another great
            for (int i = 0; i < 6; i++) t.pop_back(); //remove father/mother at the end
            t=t+"father"; //add father at the end
            p->rel=t;
        }
    }
    return *this;
}

/*adding a mother by the string we gets*/
Tree &Tree::addMother(string name , string mother){
Tree *c=findTree(name ,this); //finding the root 
if (c == NULL){//if the root is empty
    throw runtime_error(name+" is not in the tree");
}
 if(c->mother!=NULL){//if he already have one
            throw std::out_of_range{" This person already have a mother"};
        }
    else{
        Tree *p=new Tree();
        p->name=mother;
        p->father=NULL;
        p->mother=NULL;
        p->child=c;
        c->mother=p;
        //changing the relation
        if((c->rel).compare("me") ==0) p->rel = "mother";
        else if((c->rel).compare("mother") ==0) p->rel = "grandmother";
        else if((c->rel).compare("father") ==0) p->rel = "grandmother";
        else if((c->rel).compare("grandfather") ==0) p->rel = "great-grandmother";
        else if((c->rel).compare("grandmother") ==0) p->rel = "great-grandmother";
        //great-great...
         else {
            string t ="great-"+ c->rel; //adding another great
            for (int i = 0; i < 6; i++) t.pop_back(); //remove father/mother at the end
            t=t+"mother";//add father at the end
            p->rel=t;
        }
    }
    return *this;
}

/*remove this man and all of him parents*/
void Tree :: remove(string name){
Tree *tmp=findTree(name, this); //finding the man that we gets his name  
    if ( tmp == this || tmp == NULL){ //if the name is the root / null invaild
         throw std::out_of_range{"You cant delete the root"};
    }
    else if(tmp!=nullptr){
        if (tmp->child->father != NULL){//if tmp has a father
            if((tmp->child->father->name).compare(name) ==0){ //if the child father is the name we gets
                tmp->child->father=NULL; //we delete
            }
        }
        if (tmp->child->mother != NULL){//if tmp has a mother
            if((tmp->child->mother->name).compare(name) ==0){//if the child mother is the name we gets
                tmp->child->mother=NULL; //we delete
            }
        }
      delete tmp;
    }
}
    
/*finding the root that his relation equals to the one we gets */
Tree* Tree:: findTreerel(string s ,Tree *temp){
    Tree *current= NULL;
    if ((temp->rel).compare(s) ==0 ){
        return temp;
    }
    if ( temp != NULL){ 
        if (temp->father != NULL ) current = findTreerel(s , temp->father); //search in father in recursia
        if (current != NULL && (current->rel).compare(s)==0){//if we find the rel
            return current;
        }
        if (temp->mother != NULL) current = findTreerel(s , temp->mother);//search in mother in recursia
        if (current != NULL){//if we find in mother
            return current;
        }
    }
    return current;
}

/*getting a string that represents a relation
    and return a name of him*/
string Tree:: find(string s){
    Tree *tmp=findTreerel(s, this); //function that search in recursia the node
    if ( tmp == NULL){
        throw std::out_of_range{"This is not valid"};
    }
    else {
        return tmp->name;
    }
}

/* getting name of someone and return 
    the relation between me and him */
string Tree:: relation (string relat){
    Tree *c =  findTree(relat , this); //function that search in recursia the node
    if (c == NULL){
        return "unrelated";
    }
    return  c->rel;
   
}

/* print all the tree ,
by : <relation>:<name> 
by recursia */

void Tree:: print_all_rel(Tree *c){
    if(c!=nullptr){
        cout<< c->rel+": "+c->name<<endl; //<relation>:<name>
        if(c->father!=NULL && c->mother!=NULL ){
            print_all_rel(c->father); //recursia
             print_all_rel(c->mother); //recursia
        }
        else if(c->father !=NULL){
           print_all_rel(c->father); 
        }
        else if(c->mother!=NULL){
            print_all_rel(c->mother); 

        }   
    }
}

/*printing the tree*/
void Tree:: display(){
print_all_rel(this);

}


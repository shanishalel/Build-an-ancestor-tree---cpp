#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "FamilyTree.hpp"

using namespace std;
using namespace family;

/*this function will return pointer to the rel that the name that we enter bilong to*/
Tree* Tree:: findTree(string name ,Tree *temp){
    Tree *current= NULL;
    if ((temp->name).compare(name) ==0 ){
        return temp;
    }
    if ( temp != NULL){
        if (temp->father != NULL ) current = findTree(name , temp->father);
        if (current != NULL && (current->name).compare(name)==0){
            return current;
        }
        if (temp->mother != NULL) current = findTree(name , temp->mother);
        if (current != NULL){
            return current;
        }
    }
    return current;
}

Tree &Tree::addFather(string name , string father){
Tree *c=findTree(name ,this);
if (c == NULL){
    throw runtime_error(name+" is not in the tree");
}
    else{
        if(c->father!=NULL){
            throw std::out_of_range{" This person already have a father"};
        }
        Tree *p=new Tree();
        p->name=father;
        p->father=NULL;
        p->mother=NULL;
        p->child=c;
        c->father=p;
        if((c->rel).compare("me") ==0) p->rel = "father";
        else if((c->rel).compare("father") ==0) p->rel = "grandfather";
        else if((c->rel).compare("mother") ==0) p->rel = "grandfather";
        else if((c->rel).compare("grandfather") ==0) p->rel = "great-grandfather";
        else if((c->rel).compare("grandmother") ==0) p->rel = "great-grandfather";
        else {
            string t ="great-"+ c->rel;
            for (int i = 0; i < 6; i++) t.pop_back();
            t=t+"father";
            p->rel=t;
        }
    }
    return *c;
}

Tree &Tree::addMother(string name , string mother){
Tree *c=findTree(name ,this);
if (c == NULL){
    throw runtime_error(name+" is not in the tree");
}
 if(c->mother!=NULL){
            throw std::out_of_range{" This person already have a mother"};
        }
    else{
        Tree *p=new Tree();
        p->name=mother;
        p->father=NULL;
        p->mother=NULL;
        p->child=c;
        c->mother=p;
        if((c->rel).compare("me") ==0) p->rel = "mother";
        else if((c->rel).compare("mother") ==0) p->rel = "grandmother";
        else if((c->rel).compare("father") ==0) p->rel = "grandmother";
         else if((c->rel).compare("grandfather") ==0) p->rel = "great-grandmother";
        else if((c->rel).compare("grandmother") ==0) p->rel = "great-grandmother";
         else {
            string t ="great-"+ c->rel;
            for (int i = 0; i < 6; i++) t.pop_back();
            t=t+"mother";
            p->rel=t;
        }
    }
    return *c;
}

/*this function will remove the person that the name of him we entered and all his parents*/
void Tree :: remove(string name){
Tree *tmp=findTree(name, this);
    if ( tmp == this){
        if (this->father != NULL){
            this->father =NULL;
        }
        if (this->mother != NULL){
            this->mother =NULL;
        }
    }
    else if(tmp!=nullptr){
        if (tmp->child->father != NULL){
        if((tmp->child->father->name).compare(name) ==0){
            tmp->child->father=NULL;
        }
        }
         if (tmp->child->mother != NULL){
        if((tmp->child->mother->name).compare(name) ==0){
            tmp->child->mother=NULL;
        }
        }
      delete tmp;
    }
}
    

Tree* Tree:: findTreerel(string s ,Tree *temp){
    Tree *current= NULL;
    if ((temp->rel).compare(s) ==0 ){
        return temp;
    }
    if ( temp != NULL){
        if (temp->father != NULL ) current = findTreerel(s , temp->father);
        if (current != NULL && (current->rel).compare(s)==0){
            return current;
        }
        if (temp->mother != NULL) current = findTreerel(s , temp->mother);
        if (current != NULL){
            return current;
        }
    }
    return current;
}

string Tree:: find(string s){
Tree *tmp=findTreerel(s, this);
if ( tmp == NULL){
    throw std::out_of_range{"This is not valid"};
}
else {
    return tmp->name;
}
}


/*this function will return the relation of the name that we entered if there isn't relation
she will retunr unrelated*/
string Tree:: relation (string relat){
    Tree *c =  findTree(relat , this);
    if (c == NULL){
        return "unrelated";
    }
         return  c->rel;
   
}


void Tree:: print_all_rel(Tree *c){
    if(c!=nullptr){
        cout<< c->rel+": "+c->name<<endl;
        if(c->father!=NULL && c->mother!=NULL ){
            print_all_rel(c->father);
             print_all_rel(c->mother);
        }
        else if(c->father !=NULL){
           print_all_rel(c->father); 
        }
        else if(c->mother!=NULL){
            print_all_rel(c->mother); 

        }   
    }
}

void Tree:: display(){
print_all_rel(this);

}
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "FamilyTree.hpp"

using namespace std;
using namespace family;

Tree &Tree::addFather(string name , string father){
Tree *c=findTree(name ,root);
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
        c->father=p;
        if((c->rel).compare("child") ==0) p->rel = "father";
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
}

Tree &Tree::addMother(string name , string mother){
Tree *c=findTree(name ,root);
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
        c->mother=p;
        if((c->rel).compare("child") ==0) p->rel = "mother";
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
}

/*this function will return pointer to the rel that the name that we enter bilong to*/
Tree* Tree:: findTree(string name ,Tree *temp){
    Tree *current;
    if ((temp->name).compare(name) ==0 ){
        return temp;
    }
    if ( temp != NULL){
        if (temp->father != NULL ) current = findTree(name , temp->father);
        if (temp->mother != NULL) current = findTree(name , temp->mother);
        if (current != NULL){
            return current;
        }
    }
    return current;
}

/*this function will remove the person that the name of him we entered and all his parents*/
void Tree :: remove(string name){
Tree *tmp=findTree(name, root);
    if(tmp!=nullptr){
        if(tmp->father!=NULL){
            tmp->father=NULL;
        }
        if(tmp->mother!=NULL){
            tmp->mother=NULL;
        }
      delete tmp;
    }
}
    


string Tree:: find(string s){
    if (s.size() < 5){
    throw std::out_of_range{"This is not valid"};
    }
    string temp="";
    int x=0,i=0;
    Tree *left_root = root;
    Tree *right_root = root;
    if (s.compare("father")==0){
        return root->father->name;
    }
    else if (s.compare("mother")==0){
        return root->mother->name;
    }
    else if (s.compare("grandfather")==0){
        return root->father->father->name;
    }
    else if (s.compare("grandmother")==0){
        return root->mother->mother->name;
    }
    else{
        while (i < s.size()){
        while (s.at(i) >= 'a' || s.at(i) <= 'z' ){
            temp = temp+ s.at(i);
            i++;
        }
        if (temp.compare("great")==0){
            x++;
            temp="";
        }
        else if (temp.compare("grandmother")==0 || temp.compare("grandfather")==0){
            i++;
            break;
        }
        else{
             throw std::out_of_range{"This is not valid"};
        }
        i++;
    }
    if (i != s.size()){
         throw std::out_of_range{"This is not valid"};
    }
    else{
        int z=x;
        while ( z != 0){
            left_root = left_root->mother;
            right_root = right_root->father;
            z--;
        }
        if(temp.compare("grandmother")==0){

            if ((left_root->mother->name).compare(NULL) != 0 ){
            return left_root->mother->name;
            }
            else if ((right_root->mother->name).compare(NULL)!=0 ){
                return right_root->mother->name;
            }
            else   throw std::out_of_range{"No have this person"};
        }
        else if (temp.compare("grandfather")==0){
                if ((left_root->father->name).compare(NULL) != 0){
            return left_root->father->name;
            }
            else if ((right_root->father->name).compare(NULL)!=0){
                return right_root->father->name;
            }
            else   throw std::out_of_range{"No have this person"};
            }
        }
    }

}

/*this function will return the relation of the name that we entered if there isn't relation
she will retunr unrelated*/
string Tree:: relation (string relat){
    Tree *c =  findTree(relat , root);
         return  c->rel;
   
}


void Tree:: display(){
print_all_rel(root);

}

 void Tree :: print_all_rel(Tree *c){
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



int main(){
    Tree T ("Yosef");
   T.addFather("Yosef", "Yaakov");
   T.addMother("Yosef", "NIII");
    T.addMother("NIII", "yiiysa");
    T.display();
   T.remove("NIII");
    T.display();
    
    // cout<< T.find("grandmother") << endl;
    // cout << T.relation("yiiysa")<<endl;
    // cout<<T.relation("shani")<<endl;
}

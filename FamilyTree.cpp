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
    if(tmp!=nullptr){
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
    


string Tree:: find(string s){
    if (s.size() < 5){
    throw std::out_of_range{"This is not valid"};
    }
    string temp="";
    int x=0,i=0;
    Tree *left_root = this;
    Tree *right_root = this;
    if (s.compare("father")==0){
        return this->father->name;
    }
    else if (s.compare("mother")==0){
        return this->mother->name;
    }
    else if (s.compare("grandfather")==0){
        return this->father->father->name;
    }
    else if (s.compare("grandmother")==0){
        return this->mother->mother->name;
    }
    else{
        while (i < s.size()){
        while ( i < s.size() && (s.at(i) >= 97 && s.at(i) <= 122) ){
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
    if (i-1 != s.size()){
         throw std::out_of_range{"This is not valid"};
    }
    else{
        int z=x;
        while ( z >= 0){
            if (left_root->mother != NULL){
            left_root = left_root->mother;
            }
            if(right_root->father != NULL){
            right_root = right_root->father;
            }
            z--;
        }
        if(temp.compare("grandmother")==0){

            if (left_root->mother != NULL ){
            return left_root->mother->name;
            }
            else if (right_root->mother!= NULL ){
                return right_root->mother->name;
            }
            else   throw std::out_of_range{"No have this person"};
        }
        else if (temp.compare("grandfather")==0){
                if (left_root->father != NULL){
            return left_root->father->name;
            }
            else if (right_root->father != NULL){
                return right_root->father->name;
            }
            else   throw std::out_of_range{"No have this person"};
            }
        }
    }
    return "";
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

 

/*
int main() {
	family::Tree T ("Yosef"); // Yosef is the "root" of the tree (the youngest person).
	T.addFather("Yosef", "Yaakov")   // Tells the tree that the father of Yosef is Yaakov.
	 .addMother("Yosef", "Rachel")   // Tells the tree that the mother of Yosef is Rachel.
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka")
	 .addFather("Isaac", "Avraham")
	 .addFather("Avraham", "Terah");

	T.display();                        // displays the tree in a human-friendly format.


	cout << T.relation("Yaakov") << endl;  // prints "father"
	cout << T.relation("Rachel") << endl;  // prints "mother"
	cout << T.relation("Rivka") << endl;  // prints "grandmother"
	cout << T.relation("Avraham") << endl;  // prints "great-grandfather"
	cout << T.relation("Terah") << endl;  // prints "great-great-grandfather"
	cout << T.relation("xyz") << endl;  // prints "unrelated"
	cout << T.relation("Yosef") << endl;  // prints "me"

    cout << T.find("mother") << endl;  // prints "Rachel"
	cout << T.find("great-great-grandfather") << endl;  // prints "Terah"

	try {
		cout << T.find("uncle") << endl;  // throws an exception
	} catch (const exception& ex) {
	 	cout << ex.what() << endl;  // prints "The tree cannot handle the 'uncle' relation"
	}

	T.remove("Avraham"); // removes Avraham and Terah
	cout << T.relation("Terah") << endl;  // prints "unrelated"
    T.display();
    return 0;
}
*/
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
        if(c->father!=NULL){
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
 if(c->mother!=NULL){
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
node* Tree:: findnode(string name ,node *temp){
    node *current;
    if ((temp->name).compare(name) ==0 ){
        return temp;
    }
    if ( temp != NULL){
        if (temp->father != NULL ) current = findnode(name , temp->father);
        if (temp->mother != NULL) current = findnode(name , temp->mother);
        if (current != NULL){
            return current;
        }
    }
    return current;
}

/*this function will remove the person that the name of him we entered and all his parents*/
void Tree :: remove(string name){
node *tmp=findnode(name, root);
    if(tmp->father!=NULL){
    remove_all_parents(root);
    }
    delete(tmp);
}

/*this function will remove all the fathers of this node*/
node* Tree::remove_all_parents(node *root){
   if(root==NULL){
       return root;
   }
   if(root->father!=NULL){
       return remove_all_parents(root->father);
   }
   else if(root->mother!=NULL){
       return remove_all_parents(root->mother);
   }
   else{
       if(root->father==NULL){
           node *tmp=root->mother;
           delete(root);
           return tmp;
       }
       else if(root->mother==NULL){
           node *tmp=root->father;
           delete(root);
           return tmp;
       }
   }
   return root;

}

string Tree:: find(string s){
    if (s.size() < 5){
    throw std::out_of_range{"This is not valid"};
    }
    string temp="";
    int x=0,i=0;
    node *temp_root = root;
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
        while ( x != 0){
            temp_root = temp_root->mother;
            x--;
        }
        if(temp.compare("grandmother")==0){
            return temp_root->mother->name;
        }
        else if (temp.compare("grandfather")==0){
                return temp_root->father->name;
            }
        }
    }

}


void Tree:: display(){
cout << root ->father->name << "\n"  << root ->mother->name  << "\n"  << root -> name;
node *temp = root->mother;
cout << endl << temp->mother->name;
}



int main(){
    Tree T ("Yosef");
   T.addFather("Yosef", "Yaakov");
   T.addMother("Yosef", "NIII");
    T.addMother("NIII", "yiiysa");
  //     T.display();
   // T.remove("Yosef");
    T.display();
    cout<<" "<<endl;
    cout<< T.find("grandmother");
}

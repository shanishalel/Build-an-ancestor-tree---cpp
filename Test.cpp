#define CHECK DOCTEST_CHECK

#include "FamilyTree.hpp"
#include "doctest.h"
#include <iostream>
#include <stdexcept>
using namespace std;
using namespace family;

TEST_CASE("v and w")
{
    family::Tree T ("Yosef"); // Yosef is the "root" of the tree (the youngest person).
	T.addFather("Yosef", "Yaakov")   // Tells the tree that the father of Yosef is Yaakov.
	 .addMother("Yosef", "Rachel")   // Tells the tree that the mother of Yosef is Rachel.
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka")
	 .addFather("Isaac", "Avraham")
	 .addFather("Avraham", "Terah");

    cout << T.relation("Yaakov") << endl;  // prints "father"
	cout << T.relation("Rachel") << endl;  // prints "mother"
	cout << T.relation("Rivka") << endl;  // prints "grandmother"
	cout << T.relation("Avraham") << endl;  // prints "great-grandfather"
	cout << T.relation("Terah") << endl;  // prints "great-great-grandfather"
	cout << T.relation("xyz") << endl;  // prints "unrelated"
	cout << T.relation("Yosef") << endl;  // prints "me"


    CHECK(T.relation("Yaakov").compare("father") == 0 );
    CHECK(T.relation("Rachel").compare("mother") == 0 );
    CHECK(T.relation("Rivka").compare("grandmother") == 0 );
    CHECK(T.relation("Avraham").compare("great-grandfather") == 0 );
    CHECK(T.relation("Terah").compare("great-great-grandfather") == 0 );
    CHECK(T.relation("xyz").compare("unrelated") == 0 );
    CHECK(T.relation("Yosef").compare("me") == 0 );


    CHECK(T.find("mother").compare("Rachel") == 0 );
    CHECK(T.find("great-great-grandfather").compare("Terah") == 0 );
    //This is not valid



	try {
		cout << T.find("uncle") << endl;  // throws an exception
	} catch (const exception& ex) {
	 	cout << ex.what() << endl;  // prints "The tree cannot handle the 'uncle' relation"
	}

	T.remove("Avraham"); // removes Avraham and Terah
	cout << T.relation("Terah") << endl;  // prints "unrelated"
    T.display();
    
    
}

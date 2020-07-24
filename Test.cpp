#define CHECK DOCTEST_CHECK

#include "FamilyTree.hpp"
#include "doctest.h"
#include <iostream>
#include <stdexcept>


TEST_CASE("Tree build")
{
    family::Tree T ("Yosef"); // Yosef is the "root" of the tree (the youngest person).
	T.addFather("Yosef", "Yaakov")   // Tells the tree that the father of Yosef is Yaakov.
	 .addMother("Yosef", "Rachel")   // Tells the tree that the mother of Yosef is Rachel.
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka")
	 .addFather("Isaac", "Avraham")
	 .addFather("Avraham", "Terah");


    CHECK(T.relation("Yaakov").compare("father") == 0 );
		
    CHECK(T.relation("Rachel").compare("mother") == 0 );
    CHECK(T.relation("Rivka").compare("grandmother") == 0 );
    CHECK(T.relation("Avraham").compare("great-grandfather") == 0 );
    CHECK(T.relation("Terah").compare("great-great-grandfather") == 0 );
    CHECK(T.relation("xyz").compare("unrelated") == 0 );
    CHECK(T.relation("Yosef").compare("me") == 0 );
	
    CHECK(T.find("mother").compare("Rachel") == 0 );
	CHECK(T.find("great-great-grandfather").compare("Terah") == 0 );
	CHECK(T.find("grandmother").compare("Rivka") == 0 );
    CHECK(T.find("great-grandfather").compare("Avraham") == 0 );

	T.remove("Terah");
	CHECK(T.relation("Terah").compare("unrelated") == 0 );
    CHECK_THROWS(T.find("uncle")); 


	T.addMother("Rachel","Noa");
	CHECK_THROWS(T.addMother("Rachel","shani"));//adding mother when he has one
	T.remove("Noa");
	T.addMother("Rachel", "shani");
	CHECK(T.relation("shani").compare("grandmother")==0);//adding greatmother after remove

	T.addFather("Rachel","shai");
	CHECK_THROWS(T.addFather("Rachel","shai"));//adding father with the same name when he has one
	T.remove("shai");
	T.addFather("Rachel", "Dar");
	CHECK(T.relation("Dar").compare("grandfather")==0);//adding greatfather after remove

	//remove rachel and check the relation of Dar
	T.remove("Rachel");
	CHECK(T.relation("Dar").compare("unrelated") == 0 );
	CHECK(T.relation("shani").compare("unrelated") == 0 );
	CHECK(T.relation("Rachel").compare("unrelated") == 0 );
	CHECK(T.relation("Yosef").compare("me") == 0 );

	

}

TEST_CASE("Tree S")
{
 family::Tree S ("Gal");
 S.addMother("Gal","Shelly");
 S.addFather("Gal","Natan");
 S.addMother("Shelly","Liza");
 S.addFather("Shelly","Guy");
 S.addFather("Guy","Moshe");
 S.addMother("Guy","Daniella");
 S.addMother("Moshe","Mor");
 S.addMother("Mor","Shai");
CHECK(S.relation("polina").compare("unrelated")==0 );
CHECK(S.relation("Gal").compare("me")==0 );
CHECK(S.relation("Shelly").compare("mother")==0 );
CHECK(S.relation("Guy").compare("grandfather")==0 );
CHECK(S.relation("Liza").compare("grandmother")==0 );
CHECK(S.relation("Moshe").compare("great-grandfather")==0 );
CHECK(S.relation("Daniella").compare("great-grandmother")==0 );
CHECK(S.relation("Mor").compare("great-great-grandmother")==0 );
CHECK(S.relation("Shai").compare("great-great-great-grandmother")==0);
CHECK(S.relation("Dar").compare("unrelated")==0 );
CHECK(S.relation("shani").compare("unrelated")==0 );
CHECK(S.relation("Lior").compare("unrelated")==0 );
CHECK(S.relation("Mathan").compare("unrelated")==0 );

CHECK(S.find("me").compare("Gal")==0);
CHECK(S.find("father").compare("Natan")==0);
CHECK(S.find("mother").compare("Shelly")==0);
CHECK(S.find("grandmother").compare("Liza")==0);
CHECK(S.find("grandfather").compare("Guy")==0);
CHECK(S.find("great-grandfather").compare("Moshe")==0);
CHECK(S.find("great-grandmother").compare("Daniella")==0);
CHECK(S.find("great-great-grandmother").compare("Mor")==0);
CHECK(S.find("great-great-great-grandmother").compare("Shai")==0);

CHECK_THROWS(S.find("uncle"));
CHECK_THROWS(S.find("grat-great-grandfather"));
CHECK_THROWS(S.find("great-great-great-gradfather"));
CHECK_THROWS(S.find("great-great-great-great-grandmother"));
CHECK_THROWS(S.find("great-great-great-great-grandfather"));
CHECK_THROWS(S.find("great"));
CHECK_THROWS(S.find("shani"));


//remove telative that not exist

CHECK(S.find("me").compare("Gal")==0);
CHECK(S.find("father").compare("Natan")==0);
CHECK(S.find("mother").compare("Shelly")==0);
CHECK(S.find("grandmother").compare("Liza")==0);
CHECK(S.find("grandfather").compare("Guy")==0);
CHECK(S.find("great-grandfather").compare("Moshe")==0);
CHECK(S.find("great-grandmother").compare("Daniella")==0);
CHECK(S.find("great-great-grandmother").compare("Mor")==0);
CHECK(S.find("great-great-great-grandmother").compare("Shai")==0);

CHECK(S.relation("Gal").compare("me")==0 );
CHECK(S.relation("Shelly").compare("mother")==0 );
CHECK(S.relation("Guy").compare("grandfather")==0 );
CHECK(S.relation("Liza").compare("grandmother")==0 );
CHECK(S.relation("Moshe").compare("great-grandfather")==0 );
CHECK(S.relation("Daniella").compare("great-grandmother")==0 );
CHECK(S.relation("Mor").compare("great-great-grandmother")==0 );
CHECK(S.relation("Shai").compare("great-great-great-grandmother")==0);

//remove shai
S.remove("Shai");
CHECK(S.relation("Gal").compare("me")==0 );
CHECK(S.relation("Shelly").compare("mother")==0 );
CHECK(S.relation("Guy").compare("grandfather")==0 );
CHECK(S.relation("Liza").compare("grandmother")==0 );
CHECK(S.relation("Moshe").compare("great-grandfather")==0 );
CHECK(S.relation("Daniella").compare("great-grandmother")==0 );
CHECK(S.relation("Mor").compare("great-great-grandmother")==0 );
CHECK(S.relation("Shai").compare("unrelated")==0);

CHECK(S.find("me").compare("Gal")==0);
CHECK(S.find("father").compare("Natan")==0);
CHECK(S.find("mother").compare("Shelly")==0);
CHECK(S.find("grandmother").compare("Liza")==0);
CHECK(S.find("grandfather").compare("Guy")==0);
CHECK(S.find("great-grandfather").compare("Moshe")==0);
CHECK(S.find("great-grandmother").compare("Daniella")==0);
CHECK(S.find("great-great-grandmother").compare("Mor")==0);

CHECK_THROWS(S.find("Shai"));

//remove Mor
S.remove("Mor");
CHECK(S.relation("Gal").compare("me")==0 );
CHECK(S.relation("Shelly").compare("mother")==0 );
CHECK(S.relation("Guy").compare("grandfather")==0 );
CHECK(S.relation("Liza").compare("grandmother")==0 );
CHECK(S.relation("Moshe").compare("great-grandfather")==0 );
CHECK(S.relation("Daniella").compare("great-grandmother")==0 );
CHECK(S.relation("Mor").compare("unrelated")==0 );
CHECK(S.relation("Shai").compare("unrelated")==0);

CHECK(S.find("me").compare("Gal")==0);
CHECK(S.find("father").compare("Natan")==0);
CHECK(S.find("mother").compare("Shelly")==0);
CHECK(S.find("grandmother").compare("Liza")==0);
CHECK(S.find("grandfather").compare("Guy")==0);
CHECK(S.find("great-grandfather").compare("Moshe")==0);
CHECK(S.find("great-grandmother").compare("Daniella")==0);

CHECK_THROWS(S.find("Shai"));
CHECK_THROWS(S.find("Mor"));

//remove Moshe
S.remove("Moshe");
CHECK(S.relation("Gal").compare("me")==0 );
CHECK(S.relation("Shelly").compare("mother")==0 );
CHECK(S.relation("Guy").compare("grandfather")==0 );
CHECK(S.relation("Liza").compare("grandmother")==0 );
CHECK(S.relation("Moshe").compare("unrelated")==0 );
CHECK(S.relation("Daniella").compare("great-grandmother")==0 );
CHECK(S.relation("Mor").compare("unrelated")==0 );
CHECK(S.relation("Shai").compare("unrelated")==0);

CHECK(S.find("me").compare("Gal")==0);
CHECK(S.find("father").compare("Natan")==0);
CHECK(S.find("mother").compare("Shelly")==0);
CHECK(S.find("grandmother").compare("Liza")==0);
CHECK(S.find("grandfather").compare("Guy")==0);
CHECK(S.find("great-grandmother").compare("Daniella")==0);

CHECK_THROWS(S.find("Shai"));
CHECK_THROWS(S.find("Mor"));
CHECK_THROWS(S.find("Moshe"));

//remove Daniella
S.remove("Daniella");
CHECK(S.relation("Gal").compare("me")==0 );
CHECK(S.relation("Shelly").compare("mother")==0 );
CHECK(S.relation("Guy").compare("grandfather")==0 );
CHECK(S.relation("Liza").compare("grandmother")==0 );
CHECK(S.relation("Moshe").compare("unrelated")==0 );
CHECK(S.relation("Daniella").compare("unrelated")==0 );
CHECK(S.relation("Mor").compare("unrelated")==0 );
CHECK(S.relation("Shai").compare("unrelated")==0);

CHECK(S.find("me").compare("Gal")==0);
CHECK(S.find("father").compare("Natan")==0);
CHECK(S.find("mother").compare("Shelly")==0);
CHECK(S.find("grandmother").compare("Liza")==0);
CHECK(S.find("grandfather").compare("Guy")==0);

CHECK_THROWS(S.find("Shai"));
CHECK_THROWS(S.find("Mor"));
CHECK_THROWS(S.find("Moshe"));
CHECK_THROWS(S.find("Daniella"));



//remove Guy
S.remove("Guy");
CHECK(S.relation("Gal").compare("me")==0 );
CHECK(S.relation("Shelly").compare("mother")==0 );
CHECK(S.relation("Guy").compare("unrelated")==0 );
CHECK(S.relation("Liza").compare("grandmother")==0 );
CHECK(S.relation("Moshe").compare("unrelated")==0 );
CHECK(S.relation("Daniella").compare("unrelated")==0 );
CHECK(S.relation("Mor").compare("unrelated")==0 );
CHECK(S.relation("Shai").compare("unrelated")==0);

CHECK(S.find("me").compare("Gal")==0);
CHECK(S.find("father").compare("Natan")==0);
CHECK(S.find("mother").compare("Shelly")==0);
CHECK(S.find("grandmother").compare("Liza")==0);

CHECK_THROWS(S.find("Shai"));
CHECK_THROWS(S.find("Mor"));
CHECK_THROWS(S.find("Moshe"));
CHECK_THROWS(S.find("Daniella"));
CHECK_THROWS(S.find("Guy"));

//remove Liza
S.remove("Liza");
CHECK(S.relation("Gal").compare("me")==0 );
CHECK(S.relation("Shelly").compare("mother")==0 );
CHECK(S.relation("Guy").compare("unrelated")==0 );
CHECK(S.relation("Liza").compare("unrelated")==0 );
CHECK(S.relation("Moshe").compare("unrelated")==0 );
CHECK(S.relation("Daniella").compare("unrelated")==0 );
CHECK(S.relation("Mor").compare("unrelated")==0 );
CHECK(S.relation("Shai").compare("unrelated")==0);

CHECK(S.find("me").compare("Gal")==0);
CHECK(S.find("father").compare("Natan")==0);
CHECK(S.find("mother").compare("Shelly")==0);

CHECK_THROWS(S.find("Shai"));
CHECK_THROWS(S.find("Mor"));
CHECK_THROWS(S.find("Moshe"));
CHECK_THROWS(S.find("Daniella"));
CHECK_THROWS(S.find("Guy"));
CHECK_THROWS(S.find("Liza"));

//remove Shelly
S.remove("Shelly");
CHECK(S.relation("Gal").compare("me")==0 );
CHECK(S.relation("Shelly").compare("unrelated")==0 );
CHECK(S.relation("Guy").compare("unrelated")==0 );
CHECK(S.relation("Liza").compare("unrelated")==0 );
CHECK(S.relation("Moshe").compare("unrelated")==0 );
CHECK(S.relation("Daniella").compare("unrelated")==0 );
CHECK(S.relation("Mor").compare("unrelated")==0 );
CHECK(S.relation("Shai").compare("unrelated")==0);

CHECK(S.find("me").compare("Gal")==0);
CHECK(S.find("father").compare("Natan")==0);

CHECK_THROWS(S.find("Shai"));
CHECK_THROWS(S.find("Mor"));
CHECK_THROWS(S.find("Moshe"));
CHECK_THROWS(S.find("Daniella"));
CHECK_THROWS(S.find("Guy"));
CHECK_THROWS(S.find("Liza"));
CHECK_THROWS(S.find("Shelly"));

//remove Natan
S.remove("Natan");
CHECK(S.relation("Natan").compare("unrelated")==0 );
CHECK(S.relation("Shelly").compare("unrelated")==0 );
CHECK(S.relation("Shelly").compare("unrelated")==0 );
CHECK(S.relation("Guy").compare("unrelated")==0 );
CHECK(S.relation("Liza").compare("unrelated")==0 );
CHECK(S.relation("Moshe").compare("unrelated")==0 );
CHECK(S.relation("Daniella").compare("unrelated")==0 );
CHECK(S.relation("Mor").compare("unrelated")==0 );
CHECK(S.relation("Shai").compare("unrelated")==0);

CHECK(S.find("me").compare("Gal")==0);

CHECK_THROWS(S.find("Shai"));
CHECK_THROWS(S.find("Mor"));
CHECK_THROWS(S.find("Moshe"));
CHECK_THROWS(S.find("Daniella"));
CHECK_THROWS(S.find("Guy"));
CHECK_THROWS(S.find("Liza"));
CHECK_THROWS(S.find("Shelly"));
CHECK_THROWS(S.find("Natan"));


//
CHECK_THROWS(S.find("tttttt"));
CHECK_THROWS(S.find("tttttt"));
CHECK_THROWS(S.find("tttttt"));
CHECK_THROWS(S.find("tttttt"));
CHECK_THROWS(S.find("tttttt"));
CHECK_THROWS(S.find("tttttt"));
CHECK_THROWS(S.find("tttttt"));
CHECK_THROWS(S.find("tttttt"));
CHECK_THROWS(S.find("tttttt"));
CHECK_THROWS(S.find("tttttt"));
CHECK_THROWS(S.find("tttttt"));
CHECK_THROWS(S.find("tttttt"));




}
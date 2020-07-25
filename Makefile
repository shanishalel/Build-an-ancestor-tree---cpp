#!make -f

CXX=clang++-9 
CXXFLAGS=-std=c++2a

HEADERS=FamilyTree.hpp
OBJECTS=FamilyTree.o

run: demo
	./$^

demo: Demo.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o demo

test: TestRunner.o Test_ariel.o Test_hila.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o test

Test: TestCounter.o Test.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o Test

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o demo test

hoku1 : hoku1.cpp hoku1.hpp
	g++ hoku1.cpp -std=c++11 -Wall -g -lpng -o hoku1 -DSPECIAL_PATCH

clean :
	rm hoku1
	rm *.o

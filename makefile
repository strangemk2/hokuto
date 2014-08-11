hoku1 : hoku1.cpp hoku1.hpp hoku_picture.o hoku_screenshot.o hoku_font.o hoku_matching.o
	g++ hoku1.cpp hoku_picture.o hoku_matching.o hoku_font.o hoku_screenshot.o -std=c++11 -Wall -g -lpng -o hoku1 -DSPECIAL_PATCH

hoku2 : hoku2.cpp hoku1.hpp hoku_picture.o hoku_screenshot.o hoku_font.o
	 g++ hoku2.cpp hoku_picture.o  hoku_font.o hoku_screenshot.o -std=c++11 -Wall -g -lpng -o hoku2

hoku3 : hoku3.cpp hoku1.hpp hoku_picture.o hoku_screenshot.o hoku_font.o hoku_matching.o
	 g++ hoku3.cpp hoku_picture.o  hoku_font.o hoku_screenshot.o -std=c++11 -Wall -g -lpng -o hoku3

hoku_picture.o : hoku_picture.hpp hoku_picture.cpp hoku_common.hpp
	g++ hoku_picture.cpp -std=c++11 -Wall -g -c -DSPECIAL_PATCH

hoku_matching.o : hoku_matching.hpp hoku_matching.cpp hoku_common.hpp
	g++ hoku_matching.cpp -std=c++11 -Wall -g -c -DSPECIAL_PATCH

hoku_font.o : hoku_font.hpp hoku_font.cpp hoku_common.hpp
	g++ hoku_font.cpp -std=c++11 -Wall -g -c -DSPECIAL_PATCH

hoku_screenshot.o : hoku_screenshot.hpp hoku_screenshot.cpp hoku_common.hpp
	g++ hoku_screenshot.cpp -std=c++11 -Wall -g -c -DSPECIAL_PATCH

clean :
	rm hoku1
	rm *.o

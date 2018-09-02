EXENAME = lab_intro

CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpthread -lm

all : mp1

mp1 : main.o mp1.o
	$(CXX) $(CXXFLAGS) -o mp1

mp1.o: mp1.cpp mp1.h
	$(CXX) $(CXXFLAGS) mp1.cpp

main.o: main.cpp mp1.h cs225/PNG.h cs225/HSLAPixel.h
	$(CXX) $(CXXFLAGS) main.cpp

#below is the stuff from lab_intro
PNG.o : cs225/PNG.cpp cs225/PNG.h cs225/HSLAPixel.h cs225/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs225/PNG.cpp

HSLAPixel.o : cs225/HSLAPixel.cpp cs225/HSLAPixel.h
	$(CXX) $(CXXFLAGS) cs225/HSLAPixel.cpp

lodepng.o : cs225/lodepng/lodepng.cpp cs225/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs225/lodepng/lodepng.cpp


test: catchmain.o part1.o part2.o PNG.o HSLAPixel.o lodepng.o lab_intro.o
	$(LD) catchmain.o part1.o part2.o PNG.o HSLAPixel.o lodepng.o lab_intro.o $(LDFLAGS) -o test

catchmain.o : tests/catchmain.cpp tests/catch.hpp
	$(CXX) $(CXXFLAGS) tests/catchmain.cpp

part1.o : tests/part1.cpp tests/catch.hpp lab_intro.cpp lab_intro.h
	$(CXX) $(CXXFLAGS) tests/part1.cpp

part2.o : tests/part2.cpp tests/catch.hpp lab_intro.cpp lab_intro.h
	$(CXX) $(CXXFLAGS) tests/part2.cpp

clean :
	-rm -f *.o $(EXENAME) test


#the following for make test
test : unit_tests.o mp1.o PNG.o HSLAPixel.o lodepng.o
    $(LD) unit_tests.o mp1.o PNG.o HSLAPixel.o lodepng.o $(LDFLAGS) -o test

unit_tests.o : tests/unit_tests.cpp tests/catch.hpp cs225/PNG.h cs225/HSLAPixel.h
    $(CXX) $(CXXFLAGS) tests/unit_tests.cpp

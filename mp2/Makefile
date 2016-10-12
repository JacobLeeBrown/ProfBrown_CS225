EXENAME = testimage testscene

OBJS = png.o rgbapixel.o image.o
OBJS1 = $(OBJS) testimage.o
OBJS2 = $(OBJS) testscene.o scene.o

OUTS1 = flipped.png brightened.png inverted.png
OUTS2 = scene*.png

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread

all : $(EXENAME)

testimage : $(OBJS1)
	$(LD) $(OBJS1) $(LDFLAGS) -o testimage

testscene : $(OBJS2)
	$(LD) $(OBJS2) $(LDFLAGS) -o testscene

testimage.o : testimage.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) testimage.cpp
	
testscene.o : testscene.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) testscene.cpp
	
png.o : png.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp

image.o : image.cpp image.h png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) image.cpp
	
scene.o : scene.cpp scene.h image.h png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) scene.cpp

mydiff : mydiff1 mydiff2
	
mydiff1 :
	./testimage
	diff flipped.png soln_flipped.png
	diff inverted.png soln_inverted.png
	diff brightened.png soln_brightened.png
	
mydiff2 :
	./testscene
	diff scene.png soln_scene.png
	diff scene2.png soln_scene2.png
	diff scene3.png soln_scene3.png
	diff scene4.png soln_scene4.png
	diff scene5.png soln_scene5.png
	diff scene6.png soln_scene6.png
	diff scene7.png soln_scene7.png
	diff scene8.png soln_scene8.png
	
clean :
	-rm -f *.o $(EXENAME) $(OUTS1) $(OUTS2)

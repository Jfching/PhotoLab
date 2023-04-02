# design names
DESIGN = PhotoLab PhotoLabTest

#libs
LIBS   = libFilter.a libFileIO.a

CC     = gcc
DEBUG  = -DDEBUG
CFLAGS = -ansi -std=c99 -Wall -c
LFLAGS = -ansi -std=c99 -Wall
AR     = ar rc
RANLIB = ranlib

IMAGES = bw.ppm \
         sharpen.ppm \
         hue.ppm \
         noise.ppm \
         posterize.ppm \
         blur.ppm \
         enlarge.ppm \
         brightnessandcontrast.ppm \
         square.ppm \

all: PhotoLab PhotoLabTest


########### generate object files ###########

#target to generate FileIO.o

#Image.o: Image.c Image.h Constants.h
#       $(CC) $(CFLAGS) Image.c -o Image.o

FileIO.o: FileIO.h FileIO.c Constants.h Image.h
        $(CC) $(CFLAGS) FileIO.c -o FileIO.o

#target to generate DIPs.o
DIPs.o: DIPs.h DIPs.c Constants.h Image.h
        $(CC) $(CFLAGS) DIPs.c -o DIPs.o

#target to generate Advanced.o
Advanced.o: Advanced.h Advanced.c Constants.h Image.h
        $(CC) $(CFLAGS) Advanced.c -o Advanced.o

Image.o: Image.c Image.h Constants.h
        $(CC) $(CFLAGS) Image.c -o Image.o

#target to generate PhotoLab.o
PhotoLab.o: PhotoLab.c DIPs.h Advanced.h FileIO.h Constants.h Image.h
        $(CC) $(CFLAGS) PhotoLab.c -o PhotoLab.o

Test.o: Test.h Test.c Constants.h
        $(CC) $(CFLAGS)  Test.c -o Test.o

########### generate debug files ###########################################

#############################################################################

#target to generate FileIO_DEBUG.o
PhotoLab_DEBUG.o: PhotoLab.c DIPs.h Advanced.h FileIO.h Constants.h
        $(CC) $(CFLAGS) $(DEBUG) -c PhotoLab.c -o PhotoLab_DEBUG.o


########### generate library files ###########

#target to generate libFilter.a
libFilter.a: DIPs.o Advanced.o
        $(AR) libFilter.a Advanced.o DIPs.o
        $(RANLIB) libFilter.a


########### generate executables ###########

#target to generate PhotoLab
PhotoLab: PhotoLab.o FileIO.o libFilter.a Image.o Test.o
        $(CC) $(LFLAGS) PhotoLab.o FileIO.o Image.o Test.o -L. -lFilter -o PhotoLab -lm

#target to generate test
PhotoLabTest: PhotoLab_DEBUG.o FileIO.o Image.o Test.o libFilter.a
        $(CC) $(LFLAGS) PhotoLab_DEBUG.o FileIO.o Image.o Test.o -L. -lFilter -o PhotoLabTest -lm

#target to clean the directory
clean:
        rm -f *.o *.jpg $(DESIGN) $(IMAGES) $(LIBS)

#ifndef FILE_IO_H
#define FILE_IO_H

#include "Image.h"

/* Read image from a file                                               */
/* The size of the image needs to be pre-set                            */
/* The memory spaces of the image will be allocated in this function    */
/* Return values:                                                       */
/* NULL: fail to load or create an image                                */
/* image: load or create an image successfully                          */
IMAGE *LoadImage(const char *fname);

/* Save a processed image               */
/* Return values:                       */
/* 0: successfully saved the image      */
/* 1: Cannot open the file for writing  */
/* 2: File error while writing to file  */
int SaveImage(const char *fname, const IMAGE *image);

#endif

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
[chingj3@bondi hw4]$
[chingj3@bondi hw4]$ clear
[chingj3@bondi hw4]$ ls
Advanced.c  applestore.ppm  DIPs.c  FileIO.c  Image.c  Makefile      PhotoLab.c       PhotoLab.txt  Test.h
Advanced.h  Constants.h     DIPs.h  FileIO.h  Image.h  original.ppm  PhotoLab.script  Test.c
[chingj3@bondi hw4]$ cat Image.c
#include "Image.h"

#include <stdio.h>

#include <assert.h>
#include <stdlib.h>

/* Get the color intensity of the Red channel of pixel (x, y) in image */
unsigned char GetPixelR(const IMAGE *image, unsigned int x, unsigned int y)
{
        return image -> R[x+(y *image-> W)];
}

unsigned char GetPixelG(const IMAGE *image, unsigned int x, unsigned int y)
{
        return image -> G[x+(y *image->W)];
}

unsigned char GetPixelB(const IMAGE *image, unsigned int x, unsigned int y)
{
        return image -> B[x+(y *image->W)];
}

/* Set the color intensity of the Red channel of pixel (x, y) in image to r */
void SetPixelR(IMAGE *image, unsigned int x, unsigned int y, unsigned char r)
{
        image -> R[x+(y *image->W)] = r;
}

void SetPixelG(IMAGE *image, unsigned int x, unsigned int y, unsigned char g)
{
        image -> G[x+(y *image->W)] = g;
}

void SetPixelB(IMAGE *image, unsigned int x, unsigned int y, unsigned char b)
{
        image -> B[x+(y *image->W)] = b;
}

/* Return the image’s width in pixels */
//unsigned int ImageWidth(IMAGE *image);

/* Return the image’s height in pixels */
//unsigned int ImageHeight(IMAGE *image);

IMAGE *CreateImage(unsigned int Width, unsigned int Height)
{
        IMAGE *image = malloc(sizeof(IMAGE));                           //allocating space for IMAGE

        if(image != NULL)                                               //provided image isn't equal to null
        {
                image -> W = Width;
                image -> H = Height;
                                                                                                //setting variables to their RGB values
                image -> R = (unsigned char *) malloc((image -> W) * (image -> H));
                image -> G = (unsigned char *) malloc((image -> W) * (image -> H));
                image -> B = (unsigned char *) malloc((image -> W) * (image -> H));
        }

        else if(image == NULL)                  //no image
        {
                printf("Error");
                return 0;
        }
        return image;
}

void DeleteImage(IMAGE *image)
{
        assert(image -> R);
        free(image -> R);
                                                //asserts and free are used to delete the image properly without memory leaks, so each RGB value is deleted individually alongside the image after
        assert(image -> G);
        free(image -> G);

        assert(image -> B);
        free(image -> B);

        free(image);
}

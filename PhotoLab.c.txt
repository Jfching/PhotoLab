#include <stdio.h>
#include <string.h>

#include "DIPs.h"
#include "Advanced.h"
#include "FileIO.h"
#include "Constants.h"
#include "Test.h"
#include "Image.h"

/*** function declarations ***/

/* print a menu */
void PrintMenu();

/* Test all functions */
//void AutoTest(void);

int main()
{

#ifdef DEBUG
    AutoTest();
#else
    IMAGE *image;
    int rc;

    int option;            /* user input option */
    char fname[SLEN];        /* input file name */

    rc = 1;
    PrintMenu();
    scanf("%d", &option);

    /* Hue() parameter */
    int hue;

    /* Posterize() parameter */
    unsigned char rbits, gbits, bbits;

    /* Noise() parameter */
    int n;

    /* MotionBlur() parameter */
    int motion;

    //brightness and contrast parameters
    int brightness;

    int contrast;

    //enlarge parameters
    int enlarge_percentage;

    //square parameters
    int x, y, L;

    while (option != EXIT) {
        if (option == 1) {
            printf("Please input the file name to load: ");
            scanf("%s", fname);
//            rc = LoadImage(fname, image);
            image = LoadImage(fname);
                rc = SUCCESS;
        }

        else if(option < 1 || option > 13)
        {
                printf("Invalid selection!\n");
                printf("Exiting\n");
                return 0;
        }
        /* menu item 2 - 14 requires image is loaded first */
        else if (option >= 2 && option < 12) {
            if (rc != SUCCESS)     {
                printf("No image is read.\n");
            }
            /* now image is loaded */
            else {
                switch (option) {
                    case 2:
                        printf("Please input the file name to save: ");
                        scanf("%s", fname);
                        SaveImage(fname, image);
                        break;

                    case 3:
                        BlackNWhite(image);
                        printf("\"Black and White\" operation is done!\n");
                        break;
                    case 4:
                        Sharpen(image);
                        printf("\"Sharpen\" operation is done!\n");
                        break;
                    case 5:
                        printf("Please input the degree of changing hue: ");
                        scanf("%d", &hue);
                        Hue(image, hue);
                        printf("\"Hue\" operation is done!\n");
                        break;
                    case 6:
                        printf("Please input noise percentage: ");
                        scanf("%d", &n);
                        Noise(image, n);
                        printf("\"Noise\" operation is done!\n");
                        break;
                    case 7:
                        printf("Enter the number of posterization bits for R chennel (1 to 8):");
                        scanf("%hhu", &rbits);
                        printf("Enter the number of posterization bits for G chennel (1 to 8):");
                        scanf("%hhu", &gbits);
                        printf("Enter the number of posterization bits for B chennel (1 to 8):");
                        scanf("%hhu", &bbits);
                        Posterize(image, rbits, gbits, bbits);
                        printf("\"Posterize\" operation is done!\n");
                        break;
                    case 8:
                        printf("Please input the amount of blur: ");
                        scanf("%d", &motion);
                        MotionBlur(image, motion);
                        printf("\"Motion Blur Filter\" operation is done!\n");
                        break;
                    case 9:
                        printf("Please input the enlarging percentage (integer between 100 - 200): ");
                        scanf("%d",&enlarge_percentage);

                                while(enlarge_percentage < 100 || enlarge_percentage > 200 || enlarge_percentage == 100)
                                {
                                        printf("\nInvalid value.");
                                        printf("\nPlease enter a valid value: ");
                                        scanf("%d",&enlarge_percentage);
                                }

                        image = Enlarge(image,enlarge_percentage);
                        printf("\"Enlarge\" operation is done!\n");
                        break;
                    case 10:
                        printf("Please enter the x offset value: ");
                        scanf("%d", &x);
                        printf("\nPlease enter the y offset value: ");
                        scanf("%d", &y);
                        printf("\nPlease input cropped square size: \n");
                        scanf("%d", &L);
                        Square(image, x, y, L);
                        printf("\"Square\" operation is done!\n");
                        break;
                    case 11:
                        printf("\nPlease input the brightness level (integer between -255 and 255): ");
                        scanf("%d", &brightness);
                        printf("\nPlease input the contrast level (integer between -255 and 255): ");
                        scanf("%d", &contrast);
                        BrightnessandContrast(image, brightness, contrast);
                        printf("\"Brightness and Contrast\" operation is done!\n");
                        break;
                    default:
                        break;

                }
            }
        }

        else if (option == 12) {
            AutoTest();
            rc = SUCCESS;    /* set returned code SUCCESS, since image is loaded */
        }
        else {
            printf("Invalid selection!\n");
        }

        /* Process finished, waiting for another input */
        PrintMenu();
        scanf("%d", &option);
    }
    printf("You exit the program.\n");
#endif

    return 0;
}


/*******************************************/
/* Function implementations should go here */
/*******************************************/

/* Menu */
void PrintMenu()
{

    printf("\n-------------------------\n");
    printf("1: Load a PPM image\n");
    printf("2: Save the image in PPM and JPEG format\n");
    printf("3: Change the color image to black and white\n");
    printf("4: Sharpen the image\n");
    printf("5: Change the hue of image\n");
    printf("6: Add Noise to an image\n");
    printf("7: Posterize an image\n");
    printf("8: Motion blur an image\n");
    printf("9: Enlarge the picture by percentage\n");
    printf("10: Crop a square portion of the image\n");
    printf("11: Adjust the Brightness and Contrast of an image\n");
    printf("12: Test all functions\n");
    printf("13: Exit\n");
    printf("\n-------------------------\n");
    printf("Please make your choise: ");
}


/* auto test*/
/*
void AutoTest(void) {

    IMAGE *image = NULL;
    char fname[SLEN] = "applestore";

    image =  LoadImage(fname);
    BlackNWhite(image);
    SaveImage("bw", image);
    printf("Black and White tested!\n\n");

//    LoadImage(fname, image);
    image =  LoadImage(fname);
    Sharpen(image);
    SaveImage("sharpen", image);
    printf("Sharpen tested!\n\n");

//    LoadImage(fname, image);
    image =  LoadImage(fname);
    Hue(image, 120);
    SaveImage("hue", image);
    printf("Hue tested!\n\n");

//    LoadImage(fname, image);
    image =  LoadImage(fname);
    Noise(image, 30);
    SaveImage("noise", image);
    printf("Noise tested!\n\n");

//    LoadImage(fname, image);
    image =  LoadImage(fname);
    Posterize(image, 7, 7, 7);
    SaveImage("posterize", image);
    printf("Posterize tested!\n\n");

//    LoadImage(fname, image);
    image =  LoadImage(fname);
    MotionBlur(image, 10);
    SaveImage("blur", image);
    printf("MotionBlur tested!\n\n");

//  image =  LoadImage(fname);
    image =  LoadImage(fname);
    image = Enlarge(image, 170);
    SaveImage("enlarge", image);
    printf("Enlarge tested!\n\n");

    image =  LoadImage(fname);
    Square(image, 100, 0 , 400);
    SaveImage("square", image);
    printf("Square tested! \n\n");

    image =  LoadImage(fname);
    BrightnessandContrast(image, 20, 200);
    SaveImage("brightnessandcontrast", image);
    printf("Brightness and contrast tested!\n\n");
}*/

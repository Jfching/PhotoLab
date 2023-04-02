#include "Advanced.h"
#include "Image.h"
#include "Constants.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

/* Add noise to an image */
IMAGE *Noise(IMAGE *image, int n)
{
        int x, y, i;
        int num;
        num = (n * image->H * image->W)/100;
        srand(time(NULL));                              //time(NULL) is used here to prevent srand producing the same values each run

        for(i = 0; i < num; i++)
        {
                x = ( rand() ) % image->W;              //formula used in calculation the noise pixels
                y = ( rand() ) % image->H;

                SetPixelR(image, x, y, 255);            //setting the values to the new image
                SetPixelG(image, x, y, 255);
                SetPixelB(image, x, y, 255);
        }

        return image;
}



/* make the image posterized */
IMAGE *Posterize(IMAGE *image, int rbits, int gbits, int bbits)
{
        int x, y;
        for(x = 0; x <  image->W; x++) {                //for loops to access each pixel within the image
                for(y = 0; y <  image->H; y++) {
                        unsigned char one = 1;          //the one value is used for binary calculations
                        int i;
                        for(i = 0; i < rbits - 1; i++) {
                                SetPixelR(image, x, y, GetPixelR(image, x, y) | one);
                                one <<= 1;                                                      //bitwise operators used to set values to their respective variables
                        }
                        one = ~one;
                        SetPixelR(image, x, y, GetPixelR(image, x, y) & one);                   //variable is reset back to 1 to prevent contamination

                        one = 1;
                        for(i = 0; i < gbits - 1; i++) {
                                SetPixelG(image, x, y, GetPixelG(image, x, y) | one);
                                one <<= 1;
                        }
                        one = ~one;
                        SetPixelG(image, x, y, GetPixelG(image, x, y) & one);

                        one = 1;
                        for(i = 0; i < bbits - 1; i++) {
                                SetPixelB(image, x, y, GetPixelB(image, x, y) | one);
                                one <<= 1;
                        }
                        one = ~one;
                        SetPixelB(image, x, y, GetPixelB(image, x, y) & one);
                }
        }

        return image;
}

/* add motion blur to the image */
IMAGE *MotionBlur(IMAGE *image, unsigned char BlurAmount)
{
        int x, y, m, n;
        double temp_r , temp_g , temp_b;                //declarations

        for(x = 0; x <  image->W - 1; x++)
        {                                               //for loops to access the image pixels
                for(y = 0; y <  image->H ; y++)
                {
//                      printf("\n\njust testing: %lf", image->H);
                        temp_r = GetPixelR(image, x, y) * 0.5;
                        temp_g = GetPixelG(image, x, y) * 0.5;          //setting temporary variable values from a 1/2 factor within the RGB values
                        temp_b = GetPixelB(image, x, y) * 0.5;

//                      printf("\namount: %lf", temp_b);

                        for(m = 1; m < BlurAmount; m++)
                        {                                               //loops to access each value within the image that's less than the blur amount
                                if((x + m) <  image->W)
                                {
                                        if(BlurAmount < image->W - x - 1)
                                        {
//                                              printf("\n\njust testing");
                                                n = BlurAmount;
                                        }

                                        else
                                        {
                                                n =  image->W - x - 1;

                                        }
//                                              printf("\namount: %lf", temp_r);

                                                temp_r = temp_r + GetPixelR(image, x + m, y) * 0.5/n;
                                                temp_g = temp_g + GetPixelG(image, x + m, y) * 0.5/n;   //temporary variables being set to the new values after dividing by blur amount
                                                temp_b = temp_b + GetPixelB(image, x + m, y) * 0.5/n;

                                }
                        }
//                      printf("\namount: %lf", );

                        SetPixelR(image, x, y, temp_r);
                        SetPixelG(image, x, y, temp_g);         //setting temp values to new image
                        SetPixelB(image, x, y, temp_b);
                }
        }
        return image;
}


/*IMAGE *MotionBlur(IMAGE *image, unsigned char BlurAmount)
{
        int x,y,m;
        double temp_r = 0;
        double temp_g = 0;
        double temp_b = 0;
//        int n;
        int Width = image->W;
        int Height = image->H;
        int count = 0;

        for (x = 0; x < Width; x++)
        {
                for (y = Height - 1; y >= 0; y--)
                {
//                        temp_r = (GetPixelR(image, x, y))/2;
//                        temp_g = (GetPixelG(image, x, y))/2;
//                        temp_b = (GetPixelB(image, x ,y))/2;

//                      printf("\namount1: %lf", temp_r);

                        for (m = 1; m <= BlurAmount ; m++)
                        {
                                if ((x-m) >= 0 )
                                {
//                                        if (BlurAmount < (image->W) -x-1)
 ///                                       {
 //                                               n = BlurAmount;
                                                temp_r = GetPixelR(image, x, y - m);
                                                temp_g = GetPixelG(image, x, y - m);
                                                temp_b = GetPixelB(image, x, y - m);
                                }
      //                                  }
//                                        else
//                                        {
//                                                n = (image->W) -x-1;
//                                        }
                        }
                                        count = (count == 0)?1:count;

                                        SetPixelR(image, x, y, temp_r / 2.0 / count + GetPixelR(image, x, y) / 2.0);
                                        SetPixelG(image, x, y, temp_g / 2.0 / count + GetPixelG(image, x, y) / 2.0);
                                        SetPixelB(image, x, y, temp_b / 2.0 / count + GetPixelB(image, x, y) / 2.0);


  //                                      temp_r = GetPixelR(image, x+m, y)+ temp_r * 0.5/n;
 //                                       temp_g = GetPixelG(image, x+m, y)+ temp_g * 0.5/n;
 //                                       temp_b = GetPixelB(image, x+m, y)+ temp_b * 0.5/n;

                }

//                        SetPixelR(image, x, y, temp_r);
//                        SetPixelG(image, x, y, temp_g);
//                        SetPixelB(image, x, y, temp_b);

        }
        return image;
}*/

IMAGE *BrightnessandContrast(IMAGE *image, int brightness, int contrast)
{
        int x, y;
        int tmp_r, tmp_g, tmp_b;                //declarations
        double factor;

        if(brightness < 0)
        {brightness = 0;}

        if(brightness > 255)
        {brightness = 255;}
                                        //setting max and min values in the case the user inputs a too high or low value
        if(contrast < 0)
        {contrast = 0;}

        if(contrast > 255)
        {contrast = 255;}

        factor = (double)(259 * (contrast + 255))/(double)(255 *(259 - contrast));      //formula to calculate the factor for contrast

        for(x = 0; x < image->W; x++)
        {
                for(y = 0; y < image->H; y++)
                {
                        tmp_r = (int)(factor * (GetPixelR(image, x, y) + brightness - 128) + 128);
                        tmp_g = (int)(factor * (GetPixelG(image, x, y) + brightness - 128) + 128);      //setting values to a temporary variable
                        tmp_b = (int)(factor * (GetPixelB(image, x, y) + brightness - 128) + 128);

                        if(tmp_r > 255)
                        {tmp_r = 255;}
                        if(tmp_g > 255)         //if statements to set temporary values to their max or lowest value to prevent completely white or black images
                        {tmp_g = 255;}
                        if(tmp_b > 255)
                        {tmp_b = 255;}

                        if(tmp_r < 0)
                        {tmp_r = 0;}
                        if(tmp_g < 0)
                        {tmp_g = 0;}
                        if(tmp_b < 0)
                        {tmp_b = 0;}

                        SetPixelR(image, x, y, tmp_r);  //setting image to new values
                        SetPixelG(image, x, y, tmp_g);
                        SetPixelB(image, x, y, tmp_b);
                }
        }
        return image;
}

IMAGE *Enlarge(IMAGE *image, int percentage)
{
        int x, y;               //declarations

        assert(image);          //check image

        double new_width  = (image->W) * (percentage/100.00);           //formulas to calculate the new dimensions for the enlarged image
        double new_height = (image->H) * (percentage/100.00);

//      double tmpx = (100 * x)/percentage;
//      double tmpy = (100 * y)/percentage;

//      for (x = 0; y < image->W; x++)
//                {
//                        for (y = 0; y < image->H ; y++)
//                        {
//                                SetPixelR(enlarged, x, y, GetPixelR(image, x, y));
//                                SetPixelG(enlarged, x, y, GetPixelG(image, x, y));
//                                SetPixelB(enlarged, x, y, GetPixelB(image, x, y));
//                      }
//              }
//

        IMAGE *enlarged = CreateImage(new_width, new_height);           //creating a new image to set values to

                for (x = 0; x < enlarged->W; x++)               //for loops cannot exceed the value of whatever the new calculation of the dimensions are
                {
                        for (y = 0; y < enlarged->H; y++)
                        {
                                double tmpx = (100 * x)/percentage;
                                double tmpy = (100 * y)/percentage;

                                SetPixelR(enlarged, x, y, GetPixelR(image, tmpx, tmpy));
                                SetPixelG(enlarged, x, y, GetPixelG(image, tmpx, tmpy));                //setting values from old image to new image
                                SetPixelB(enlarged, x, y, GetPixelB(image, tmpx, tmpy));
                        }
                }

        DeleteImage(image);     //deleting image and setting it to NULL to prevent memory leaks
        image = NULL;

        return enlarged;
}

IMAGE *Square(IMAGE *image, int x, int y, int L)
{
        assert(image);                  //check if image exists

        int w, h;                       //declarations

        IMAGE *cropped = CreateImage(image->W, image->H);                       //creating a new temporary image to hold old values

                for (w = 0; w < image->W; w++)
                {
                        for (h = 0; h < image->H ; h++)
                        {
                                SetPixelR(cropped, w, h, GetPixelR(image, w, h));       //setting the old image values
                                SetPixelG(cropped, w, h, GetPixelG(image, w, h));
                                SetPixelB(cropped, w, h, GetPixelB(image, w, h));

//                              DeleteImage(image);
//                              image = CreateImage(L, L);
                        }
                }

        DeleteImage(image);

        image = NULL;                                   //setting image to NULL and deleting to prevent memory leaks
        image = CreateImage(L, L);                      //a new image is created using the cropped values

                for (w = 0; w < L ; w++)                //for loop values cannot exceed whatever the user inputted for crop
                {
                        for (h = 0; h < L; h++)
                        {

//                              SetPixelR(cropped, w, h, GetPixelR(image, w + x, h + y));
//                              SetPixelG(cropped, w, h, GetPixelG(image, w + x, h + y));
//                              SetPixelB(cropped, w, h, GetPixelB(image, w + x, h + y));

                                SetPixelR(image, w, h, GetPixelR(cropped, w + x, h + y));               //setting cropped image values to the new image
                                SetPixelG(image, w, h, GetPixelG(cropped, w + x, h + y));
                                SetPixelB(image, w, h, GetPixelB(cropped, w + x, h + y));
                        }
                }

//      DeleteImage(image);
//      image = NULL;

//      return cropped;

        DeleteImage(cropped);                   //Setting the image to null and deleting it to prevent memory leaks
        cropped = NULL;

        return image;
}

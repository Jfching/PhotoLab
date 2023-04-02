#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "DIPs.h"
#include "Image.h"

/* Example of DIP */
/* make the picture color black & white */

/* make the picture color black & white */
IMAGE *BlackNWhite(IMAGE *image)
{
        int x, y, z;                                            //declarations
        for(x = 0; x <  image->W; x++)
        {                                                       //for loops to access pixel values
                for(y = 0; y <  image->H; y++)
                {
                        z = (GetPixelR(image, x, y) +                   //calculation for new pixel values
                             GetPixelG(image, x, y) +
                             GetPixelB(image, x, y))/3;

                        SetPixelR(image, x, y, z);                      //setting new values to new image
                        SetPixelG(image, x, y, z);
                        SetPixelB(image, x, y, z);
                }
        }

        return image;
}


// Sharpen function
IMAGE *Sharpen(IMAGE *image)
{
        int x, y;
        int tmpr = 0, tmpg = 0, tmpb = 0;                               //declarations

        unsigned char R_tmp[ image->W][ image->H];
        unsigned char G_tmp[ image->W][ image->H];
        unsigned char B_tmp[ image->W][ image->H];

        for(x = 0; x <  image->W; x++)
        {
                for(y = 0; y <  image->H; y++)
                {
                        R_tmp[x][y] = GetPixelR(image, x, y);
                        G_tmp[x][y] = GetPixelG(image, x, y);                   //setting temp values to old image values to prevent contamination
                        B_tmp[x][y] = GetPixelB(image, x, y);
                }
        }

        for( x = 1; x <  image->W - 1; x++)                     //for loops to access image pixels
        {
                for( y = 1; y <  image->H - 1; y++)
                {
//                      tmpr = 9 * R[x][y] - R[x-1][y-1] - R[x-1][y] - R[x-1][y+1] - R[x][y-1] - R[x][y+1] - R[x+1][y-1] - R[x+1][y] - R[x+1][y+1];
//                      tmpg = 9 * G[x][y] - G[x-1][y-1] - G[x-1][y] - G[x-1][y+1] - G[x][y-1] - G[x][y+1] - G[x+1][y-1] - G[x+1][y] - G[x+1][y+1];
//                      tmpb = 9 * B[x][y] - B[x-1][y-1] - B[x-1][y] - B[x-1][y+1] - B[x][y-1] - B[x][y+1] - B[x+1][y-1] - B[x+1][y] - B[x+1][y+1];


                        tmpr = 9 * GetPixelR(image, x, y) - GetPixelR(image, x-1, y-1) - GetPixelR(image, x-1, y) - GetPixelR(image, x-1, y+1) -
                                   GetPixelR(image, x, y-1) - GetPixelR(image, x, y+1) - GetPixelR(image, x+1, y-1) - GetPixelR(image, x+1, y) -
                                   GetPixelR(image, x+1, y+1);                                                           //calculation of new pixels being set into another triplet of temp variables

                        tmpg = 9 * GetPixelG(image, x, y) - GetPixelG(image, x-1, y-1) - GetPixelG(image, x-1, y) - GetPixelG(image, x-1, y+1) -
                                   GetPixelG(image, x, y-1) - GetPixelG(image, x, y+1) - GetPixelG(image, x+1, y-1) - GetPixelG(image, x+1, y) -
                                   GetPixelG(image, x+1, y+1);

                        tmpb = 9 * GetPixelB(image, x, y) - GetPixelB(image, x-1, y-1) - GetPixelB(image, x-1, y) - GetPixelB(image, x-1, y+1) -
                                   GetPixelB(image, x, y-1) - GetPixelB(image, x, y+1) - GetPixelB(image, x+1, y-1) - GetPixelB(image, x+1, y) -
                                   GetPixelB(image, x+1, y+1);


//                      R_temp[x][y] = (tmpr > 255)?255:(tmpr < 0)?0:tmpr;
//                      G_temp[x][y] = (tmpg > 255)?255:(tmpg < 0)?0:tmpg;
//                      B_temp[x][y] = (tmpb > 255)?255:(tmpb < 0)?0:tmpb;

                        R_tmp[x][y] = ((tmpr>255)? 255: (tmpr<0)? 0: tmpr);
                        G_tmp[x][y] = ((tmpg>255)? 255: (tmpg<0)? 0: tmpg);                     //checking temp values if they exceed 255 or are lower than 0
                        B_tmp[x][y] = ((tmpb>255)? 255: (tmpb<0)? 0: tmpb);

                        tmpr = tmpg = tmpb = 0;
                }
        }

        for(x = 0; x < image->W; x++)
        {
                for(y = 0; y < image->H; y++)
                {
                        SetPixelR(image, x , y, R_tmp[x][y]);                   //setting temp values to new image
                        SetPixelG(image, x , y, G_tmp[x][y]);
                        SetPixelB(image, x , y, B_tmp[x][y]);
                }
        }

        return image;
}

// Hue function
IMAGE *Hue(IMAGE *image, int degree)
{
    int x, y;
    double a, b, r;
    double d = degree * PI / 180.0;                                     //declarations
    double tmp_r, tmp_g, tmp_b;

    a = (2 * cos(d) + 1.0) / 3.0;
    b = (1.0 - cos(d)) / 3.0 - sin(d) / sqrt(3.0);
    r = (1.0 - cos(d)) / 3.0 + sin(d) / sqrt(3.0);

    for (x = 0; x <  image->W; x++)                                     //for loops to access the image pixels
    {   for (y = 0; y <  image->H; y++)
        {
//              tmp_r = R[x][y] * a + G[x][y] * b + B[x][y] * r;
//              tmp_g = R[x][y] * r + G[x][y] * a + B[x][y] * b;
//              tmp_b = R[x][y] * b + G[x][y] * r + B[x][y] * a;

                tmp_r = a * GetPixelR(image, x, y) + b * GetPixelG(image, x, y) + r * GetPixelB(image, x, y);
                tmp_g = r * GetPixelR(image, x, y) + a * GetPixelG(image, x, y) + b * GetPixelB(image, x, y);           //formula used to calculate new values to be set into temporary variables
                tmp_b = b * GetPixelR(image, x, y) + r * GetPixelG(image, x, y) + a * GetPixelB(image, x, y);


//              R[x][y] = (tmp_r > 255)?255:(tmp_r < 0)?0:tmp_r;
//              G[x][y] = (tmp_g > 255)?255:(tmp_g < 0)?0:tmp_g;
//              B[x][y] = (tmp_b > 255)?255:(tmp_b < 0)?0:tmp_b;

                SetPixelR(image, x, y, (tmp_r > 255)? 255: (tmp_r < 0)? 0: tmp_r);
                SetPixelG(image, x, y, (tmp_g > 255)? 255: (tmp_g < 0)? 0: tmp_g);              //used to check the tmp values and setting them to be 0 or 255 in the case they exceed the max pixel value
                SetPixelB(image, x, y, (tmp_b > 255)? 255: (tmp_b < 0)? 0: tmp_b);
        }
    }

        return image;
}

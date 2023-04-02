#ifndef DIPS_H_INCLUDED_
#define DIPS_H_INCLUDED_

#include "Constants.h"
#include "Image.h"

/* DIPs.h */
IMAGE *BlackNWhite(IMAGE *image);

IMAGE *Sharpen(IMAGE *image);

IMAGE *Hue(IMAGE *image, int degree);

#endif /* DIPS_H_INCLUDED_ */

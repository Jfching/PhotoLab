#ifndef ADVANCED_H_INCLUDED_
#define ADVANCED_H_INCLUDED_

#include "Constants.h"
#include "Image.h"

/* Advanced.h */
IMAGE *Noise(IMAGE *image, int n);

IMAGE *Posterize(IMAGE *image, int rbits, int gbits, int bbits);

IMAGE *MotionBlur(IMAGE *image, unsigned char BlurAmount);

IMAGE *Square(IMAGE *image, int x, int y, int L);

IMAGE *Enlarge(IMAGE *image, int percentage);

IMAGE *BrightnessandContrast(IMAGE *image, int brightness, int contrast);

#endif /* ADVANCED_H_INCLUDED_ */

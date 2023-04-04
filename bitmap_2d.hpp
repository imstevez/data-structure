#ifndef bitmap_2d_hpp
#define bitmap_2d_hpp

#include <stdlib.h>
#include "status.hpp"

#define BIT_ON 1
#define BIT_OFF 0
#define BIT_MASK uint8_t(1) << 7

typedef struct {
    int w;
    int h;
    uint8_t *bits;
} Bitmap2D;

typedef struct {
    int x;
    int y;
} Pos;

Status PosEqual(Pos a, Pos b);
Status InitBitmap2D(Bitmap2D &map, int w, int h);
Status Bitmap2DSet(Bitmap2D &map, Pos p, int b);
Status Bitmap2DGet(Bitmap2D &map, Pos p, int &b);
void DestroyBitmap2D(Bitmap2D &map);

#endif
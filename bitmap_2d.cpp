#include <stdio.h>
#include "bitmap_2d.hpp"

Status get_pos(int w, int h, Pos p, int &m, int &n) {
    if (p.x < 0 || p.y < 0 || p.x >= w || p.y >= h) return ERROR;
    int i = p.y * w + p.x;
    m = i / 8;
    n = i % 8;
    return OK;
}

Status PosEqual(Pos a, Pos b) {
    if (a.x == b.x && a.y == b.y) return TRUE;
    return FALSE;
}

Status InitBitmap2D(Bitmap2D &m, int w, int h) {
    int rows = w / 8;
    int n = rows * h;
    if (n <= 0) return ERROR;
    m.bits = (uint8_t *)malloc(n * sizeof(uint8_t));
    if (!m.bits) exit(OVERFLOW);
    m.w = (w / 8) * 8;
    m.h = h;
    return OK;
}

Status Bitmap2DSet(Bitmap2D &map, Pos p, int b) {
    if (b != BIT_ON && b != BIT_OFF) return ERROR;
    int m, n;
    if (!get_pos(map.w, map.h, p, m, n)) return ERROR;
    if (b) map.bits[m] |=  BIT_MASK >> n;
    else map.bits[m] &= ~(BIT_MASK >> n);
    return OK;
} 

Status Bitmap2DGet(Bitmap2D &map, Pos p, int &b) {
    int m, n;
    if (!get_pos(map.w, map.h, p, m, n)) return ERROR;
    if (map.bits[m] & BIT_MASK >> n) b = BIT_ON;
    else b = BIT_OFF;
    return OK;
}

void DestroyBitmap2D(Bitmap2D &map) {
    free(map.bits);
    map.w = 0;
    map.h = 0;
}
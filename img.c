#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "img.h"

static unsigned char buf[HEIGHT][WIDTH][3];
static int filecnt = 0;
static char fname[100];

void img_clear(void) {
  int i, j;
  for(j = 0; j < HEIGHT; ++j) {
    for(i = 0; i < WIDTH; ++i) {
      buf[j][i][0] = buf[j][i][1] = buf[j][i][2] = 255;
    }
  }
}

void img_write(void) {
  sprintf(fname, "img%04d.ppm", ++filecnt);
  FILE *f = fopen(fname, "wb");
  if(f == NULL) { fprintf(stderr, "can't open %s\n", fname); exit(1); }
  fprintf(f, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
  fwrite(buf, sizeof(buf), 1, f);
  fclose(f);
}

void img_putpixel(struct color c, int x, int y) {
  if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) { return; }
  buf[HEIGHT-y-1][x][0] = c.r;
  buf[HEIGHT-y-1][x][1] = c.g;
  buf[HEIGHT-y-1][x][2] = c.b;
}

void img_fillcircle(struct color c, double x, double y, double r) {
  int imin = (int)(x - r - 1), imax = (int)(x + r + 1);
  int jmin = (int)(y - r - 1), jmax = (int)(y + r + 1);
  int i, j;
  for(j = jmin; j <= jmax; ++j) {
    for(i = imin; i <= imax; ++i) {
      if((x-i)*(x-i) + (y-j)*(y-j) <= r*r) { img_putpixel(c, i, j); }
    }
  }
}

void img_fillrect(struct color c, double x, double y, double w, double h) {
  int imin = (int)(x - w/2), imax = (int)(x + w/2);
  int jmin = (int)(y - h/2), jmax = (int)(y + h/2);
  int i, j;
  for(j = jmin; j <= jmax; ++j) {
    for(i = imin; i <= imax; ++i) { img_putpixel(c, i, j); }
  }
}

struct color mixcolor(struct color c, struct color d) {
    struct color ret = { (c.r+d.r), (c.g+d.g), (c.b+d.b) };
  if(c.r + d.r > 255) {
    struct color ret = {255, (c.g + d.g),(c.b+d.b)};
  } else if(c.g+d.g > 255) {
    struct color ret = {(c.r+d.r), 255, (c.b+d.b)};
  } else if(c.b+d.b > 255) {
    struct color ret = {(c.r+d.r), (c.g+d.g), 255};
  }
  return ret;
}
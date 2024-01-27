#include "img.h"
#include "math.h"
#define PI 3.14159265358979

int main(void) {
  struct color c1 = { 0, 205, 255 };
  struct color c2 = {245, 198, 95};
  struct color c3 = {51, 255, 204};
  struct color c4 = {152, 235, 207};
  struct color c5 = {181, 237, 107};
  int i; 
    for(i = 0; i < 40; ++i) {
    double sx = sin(2*PI*i/40), cx = cos(2*PI*i/40);
    double rad = 20 - 10*sx;
    double x = 150 + 100*cx, y = 100 + 50*sx; 
    img_clear();img_fillcircle(c1, 30, 20, 15); img_fillrect(c2,40+x/100,30+y/20,8,40);
    img_fillcircle(c1, 65, 20, 15); img_fillrect(c3,75+y/25,30+x/20,8,40);
    img_fillcircle(c1, 225, 20, 15); img_fillrect(c4,215+y/100,30+x/40,8,40);
    img_fillcircle(c1, 275, 20, 15); img_fillrect(c5,265+x/70,30+y/35,8,40);
     img_write();
  }
  return 0;
}
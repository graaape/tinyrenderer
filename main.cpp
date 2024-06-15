#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

//draw a line from P0(x0,y0) to P1(x1,y1)
void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) { 
    // hard to decide how many pixels to be drawn
	/*
	for (float t=0.; t<1.; t+=.01) { 
        int x = x0 + (x1-x0)*t; 
        int y = y0 + (y1-y0)*t; 
        image.set(x, y, color); 
    } 
	*/
   // simple version with problems: 
   // 1.if x1<x0 then there is no line
   // 2.if height is greater than width then the blank is obvious
   /*
   for (int x=x0; x<=x1; x++) { 
        float t = (x-x0)/(float)(x1-x0); 
        int y = y0*(1.-t) + y1*t; 
        image.set(x, y, color); 
    } 
   */
  bool steep=false;
  if(std::abs(x0-x1)<std::abs(y0-y1)){
	// swap x y
	std::swap(x0,y0);
	std::swap(x1,y1);
	steep=true;
  }
  if(x1<x0){
	std::swap(x0,x1);
	std::swap(y0,y1);
  }
  for (int x=x0; x<=x1; x++) { 
        float t = (x-x0)/(float)(x1-x0); 
        int y = y0*(1.-t) + y1*t;
		if(steep){
			// swap x y again
			image.set(y,x,color);
		} else{
			image.set(x, y, color); 
		}
    } 
}

int main(int argc, char** argv) {
	TGAImage image(100, 100, TGAImage::RGB);
	// image.set(52, 41, red);
	line(13, 20, 80, 40, image, white); 
	line(20, 13, 40, 80, image, red); 
	line(80, 40, 13, 20, image, red);
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}


#include <vector>
#include <cmath>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
Model *model = NULL;
const int width  = 800;
const int height = 800;

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
			image.set(y,x,color);
		}else{
			image.set(x, y, color); 
		}
    } 
  /*
  int dx=x1-x0;
  int dy=y1-y0;
  // original derror is abs(dy/(float)dx)
  // for getting rid of floating point
  // need to multify 0.5 and 1 with 2*dx
  float derror=std::abs(dy)*2;
  float error=0;
  int y=y0;
  for (int x=x0; x<=x1; x++) { 
		if(steep){
			// swap x y again
			image.set(y,x,color);
		} else{
			image.set(x, y, color); 
		}
		error+=derror;
		if(error>dx){
			y+=(y1>y0?1:-1);
			error-=dx*2;
		}
    } 
	*/
}

int main(int argc, char** argv) {
	TGAImage image(width, height, TGAImage::RGB);
	// image.set(52, 41, red);
	// line(13, 20, 80, 40, image, white); 
	// line(20, 13, 40, 80, image, white); 
	// line(80, 40, 13, 20, image, white);

	//draw a head
	model = new Model("obj/african_head.obj");
	for (int i=0; i<model->nfaces(); i++) { 
		std::vector<int> face = model->face(i); 
		// draw a triangle
		for (int j=0; j<3; j++) { 
			Vec3f v0 = model->vert(face[j]); 
			Vec3f v1 = model->vert(face[(j+1)%3]); 
			int x0 = (v0.x+1.)*width/2.; 
			int y0 = (v0.y+1.)*height/2.; 
			int x1 = (v1.x+1.)*width/2.; 
			int y1 = (v1.y+1.)*height/2.; 
			line(x0, y0, x1, y1, image, white); 
		} 
	}
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	delete model;
	return 0;
}


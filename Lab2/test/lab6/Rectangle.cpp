#include <iostream>
#include <cmath>
#include "easygl.h"
#include "Rectangle.h"
using namespace std;


// Constructor. First set up base class (Shape), then store the 
// vertices, which are 3 (x,y) points giving offsets from the Shape center 
// to each triangle vertex.
Rectangle::Rectangle (string _name, string _colour, float _xcen, float _ycen,
            float _width,float _height) : 
            Shape (_name, _colour, _xcen, _ycen) {
    
    width=_width;
    height=_height;
}


Rectangle::~Rectangle () {
   // No dynamic memory to delete
}


void Rectangle::print () const {
   Shape::print();
   cout << "rectangle width: "<<width<<" ";
   cout<<"height: "<<height<<endl;
}


void Rectangle::scale (float scaleFac) {
    width*=scaleFac;
    height*=scaleFac;
}
   

float Rectangle::computeArea () const {
   // 1/2 * base * height
   // The height requires some trigonometry to compute, for an arbitrary triangle.
   // Some manipulation gives a simpler formula to use in this case, which I use below.
   // Compute two vectors, from one vertex to each of the other two.
   // Then use the formula below to get area.
   float area;
   area =width*height;
   return area;
}


float Rectangle::computePerimeter () const {
   float perimeter = 0;
   perimeter = 2*(width+height);
   return perimeter;
}


void Rectangle::draw (easygl* window) const {
   // Load up the data structure needed by easygl, and draw the triangle
   // using the easygl::draw_polygon call.
   
   window->gl_setcolor(getColour());
   window->gl_fillrect(getXcen()-0.5*width,getYcen()-0.5*height,getXcen()+0.5*width,getYcen()+0.5*height);
}


bool Rectangle::pointInside (float x, float y) const {
   // Make a point that corresponds to where you clicked. Since all my
   // vertices are relative to the triangle center, it is more convenient
   // to also shift the click point so it is an offset from the triangle 
   // center.
   t_point click;
   click.x = x - getXcen();
   click.y = y - getYcen();
   
   // The test is that a horizontal line (ray) from x = -infinity to the click point
   // will cross (intersect) only one side of triangle to the left of the 
   // click point.  If the point is above or below the triangle, the ray will not
   // intersect any triangle sides. If the point is to the left of the triangle
   // the ray will also not intersect any sides to the left of the point.
   // If the point is to the right of the triangle, the ray will intersect
   // two sides of the triangle to its left. Only if the point is inside the 
   // triangle will the ray intersect exactly one side to the left of the point.
   float disX,disY;
   disX=abs(click.x-getXcen());
   disY=abs(click.y-getYcen());
   if(disX>0.5*width||disY>0.5*height)
       return false;
   else
       return true;
}


// Private helper functions below.  Working out triangle area etc. 
// requires some vector math, so these helper functions are useful.

// Return the (x,y) vector between start and end points.
t_point Rectangle::getVecBetweenPoints (t_point start, t_point end) const {
   t_point vec;
   vec.x = end.x - start.x;
   vec.y = end.y - start.y;
   return (vec);
}


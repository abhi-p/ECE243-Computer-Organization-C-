#include <iostream>
#include <cmath>
#include "easygl.h"
#include "Circle.h"
using namespace std;


// Constructor. First set up base class (Shape), then store the 
// vertices, which are 3 (x,y) points giving offsets from the Shape center 
// to each triangle vertex.
Circle::Circle (string _name, string _colour, float _xcen, float _ycen,
            float _radius) : 
            Shape (_name, _colour, _xcen, _ycen) {
   
    radius=_radius;
}


Circle::~Circle () {
   // No dynamic memory to delete
}


void Circle::print () const {
   Shape::print();
   cout << "circle radius: ";
   cout << radius;
   cout << endl;
}


void Circle::scale (float scaleFac) {
    radius*=scaleFac;
}
   

float Circle::computeArea () const {
   // 1/2 * base * height
   // The height requires some trigonometry to compute, for an arbitrary triangle.
   // Some manipulation gives a simpler formula to use in this case, which I use below.
   // Compute two vectors, from one vertex to each of the other two.
   // Then use the formula below to get area.
   float area;
   
   
   area = radius*radius*PI;
   return area;
}


float Circle::computePerimeter () const {
   float perimeter = 0;
   perimeter = 2*PI*radius;
   return perimeter;
}


void Circle::draw (easygl* window) const {
   // Load up the data structure needed by easygl, and draw the triangle
   // using the easygl::draw_polygon call.
   
   window->gl_setcolor(getColour());
   window->gl_fillarc(centerP.x,centerP.y,radius,0,360);
}


bool Circle::pointInside (float x, float y) const {
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
   t_point distanceVector=getVecBetweenPoints(click,centerP);
   float distanceSquar=(distanceVector.x*distanceVector.x)+(distanceVector.y*distanceVector.y);
   if(distanceSquar<=radius*radius)
       return true;
   else
       return false;
}


// Private helper functions below.  Working out triangle area etc. 
// requires some vector math, so these helper functions are useful.

// Return the (x,y) vector between start and end points.
t_point Circle::getVecBetweenPoints (t_point start, t_point end) const {
   t_point vec;
   vec.x = end.x - start.x;
   vec.y = end.y - start.y;
   return (vec);
}


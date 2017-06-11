#include <iostream>
#include <cmath>
#include "easygl.h"
#include "Ploygon.h"
using namespace std;


// Constructor. First set up base class (Shape), then store the
// vertices, which are 3 (x,y) points giving offsets from the Shape center
// to each triangle vertex.
Ploygon::Ploygon (string _name, string _colour, float _xcen, float _ycen,
            int _nPoint,t_point _vertices[100]) :
            Shape (_name, _colour, _xcen, _ycen) {

    nPoint=_nPoint;
    for(int i=0;i<nPoint;i++){
      vertices[i].x=_vertices[i].x;
      vertices[i].y=_vertices[i].y;
    }
}


Ploygon::~Ploygon () {
   // No dynamic memory to delete
}


void Ploygon::print () const {
   Shape::print();
   cout << "Ploygon ";
   for (int i=0;i<nPoint;i++) {
     cout<<"("<<vertices[nPoint].x<<","<<vertices[nPoint].y<<") ";
   }
}


void Ploygon::scale (float scaleFac) {
     t_point center;
     center.x=getXcen();
     center.y=getYcen();
    for (size_t i = 0; i < nPoint; i++) {
      t_point a=getVecBetweenPoints(vertices[i],center);
      a*=scaleFac;
      vertices[i].x=center.x-a.x;
      vertices[i].y=center.y-a.y;
    }
}


float Ploygon::computeArea () const {
   // 1/2 * base * height
   // The height requires some trigonometry to compute, for an arbitrary triangle.
   // Some manipulation gives a simpler formula to use in this case, which I use below.
   // Compute two vectors, from one vertex to each of the other two.
   // Then use the formula below to get area.
   float area;
   int j = numPoints-1;  // The last vertex is the 'previous' one to the first

  for (i=0; i<numPoints; i++)
    { area = area +  (vertices[j].x+vertices[i].x) * (vertices[j].y-vertices[i].y);
      j = i;  //j is previous vertex to i
    }
  return area/2;
}


float Ploygon::computePerimeter () const {
   float perimeter = 0;
   for(int i=0;i<nPoint-1;i++){
     t_point distance=getVecBetweenPoints(vertices[i],vertices[i+1]);
     perimeter+=sqar(distance.x*distance.x+distance.y*distance.y);
   }
    t_point distance=getVecBetweenPoints(vertices[nPoint],vertices[0]);
    perimeter+=sqar(distance.x*distance.x+distance.y*distance.y);
    return perimeter;
}


void Ploygon::draw (easygl* window) const {
   // Load up the data structure needed by easygl, and draw the triangle
   // using the easygl::draw_polygon call.

   window->gl_setcolor(getColour());
   window->gl_fillpoly(vertices, nPoint);


bool Ploygon::pointInside (float x, float y) const {
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
   t_point vecOfSide;
   float distanceAlongVector, yDistance;
   int endIndex;
   int sidesToLeft = 0;

   for (int istart = 0; istart < nPoint; istart++) {
      endIndex = (istart + 1) % nPoint; // Next vertex after istart
      vecOfSide = getVecBetweenPoints (vertices[istart], vertices[endIndex]);
      yDistance = (click.y - vertices[istart].y);
      if (vecOfSide.y != 0) {
          distanceAlongVector = yDistance / vecOfSide.y;
      }
      else if (yDistance == 0) {
          distanceAlongVector = 0;
      }
      else {
          distanceAlongVector = 1e10; // Really infinity, but this is big enough
      }

      // We intersect this side if the distance (scaling) along the side vector to
      // get to our "click" y point is between 0 and 1.  Count the first
      // endpoint of the side as being part of the line (distanceAlongVector = 0)
      // but don't count the second endPoint; we'll intersect that point later
      // when we check the next side.
      if (distanceAlongVector >= 0 && distanceAlongVector < 1) {
         float xIntersection = vertices[istart].x + vecOfSide.x * distanceAlongVector;
         if (xIntersection <= click.x )
             sidesToLeft++;
      }
   }

   return (sidesToLeft == 1);
}


// Private helper functions below.  Working out triangle area etc.
// requires some vector math, so these helper functions are useful.

// Return the (x,y) vector between start and end points.
t_point Ploygon::getVecBetweenPoints (t_point start, t_point end) const {
   t_point vec;
   vec.x = end.x - start.x;
   vec.y = end.y - start.y;
   return (vec);
}

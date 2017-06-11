/* 
 * File:   Circle.h
 * 
 */

#ifndef RECTANGLE_H
#define	RECTANGLE_H

#include "Shape.h"
#include "easygl.h"

class Rectangle : public Shape {
private:
   // t_point is a structure defined in easygl.h.  It has two members,
   // .x and .y, storing a 2D point. 
    float width;
    float height;
    
   // Private helper functions.
   t_point getVecBetweenPoints (t_point start, t_point end) const;
   
public:
   Rectangle (string _name, string _colour, float _xcen, float _ycen,float width, float height);
   
   // virtual keyword is optional in all the function declarations below, since
   // the base class Shape already declared them virtucal. But it is good 
   // practice to repeat it again here, for clarity.
   virtual ~Rectangle();
   
   
   virtual void print () const;
   virtual void scale (float scaleFac);
   virtual float computeArea () const;
   virtual float computePerimeter () const;
   virtual void draw (easygl* window) const;
   virtual bool pointInside (float x, float y) const;
};

#endif	/*RECTANGLE_H */

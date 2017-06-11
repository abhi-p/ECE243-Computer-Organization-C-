
#ifndef PLOYGON_H
#define	PLOYGON_H

#include "Shape.h"
#include "easygl.h"

class Polygon : public Shape {
private:
   // t_point is a structure defined in easygl.h.  It has two members,
   // .x and .y, storing a 2D point.
  int nPoint;
  t_point *vertices;

   // Private helper functions.
   t_point getVecBetweenPoints (t_point start, t_point end) const;

public:
   Polygon (string _name, string _colour, float _xcen, float _ycen,int nPoint, t_point *vertices);

   // virtual keyword is optional in all the function declarations below, since
   // the base class Shape already declared them virtucal. But it is good
   // practice to repeat it again here, for clarity.
   virtual ~Polygon();


   virtual void print () const;
   virtual void scale (float scaleFac);
   virtual float computeArea () const;
   virtual float computePerimeter () const;
   virtual void draw (easygl* window) const;
   virtual bool pointInside (float x, float y) const;
};

#endif	/*PLOGON_H */

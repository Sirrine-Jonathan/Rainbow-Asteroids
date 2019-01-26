#include "point.h"
#include "velocity.h"
#include "uiDraw.h"

#ifndef flyingObject_h
#define flyingObject_h

class FlyingObject 
{
  public:
   FlyingObject() : alive(true), lifetime(0), radius(0) {
	   clockwise = (bool)random(0,2); //random 0 or 1 cast to a bool
   }

  private:
   Point p;
   Velocity v;
   bool alive;
   int lifetime;
   int radius;
   int angle;
   bool clockwise;

  public:
   //getters & setters
   Point    getPoint()              { return p;     }
   Velocity getVelocity()           { return v;     }
   void     setPoint(Point p)       { this->p = p;  }
   void     setVelocity(Velocity v) { this->v = v;  }   
   bool     isAlive()               { return alive; }
   virtual int getRadius()           { return radius;         }
   virtual int setRadius(int radius) { this->radius = radius; }
   
   //other member functions
   void     checkWarp(float maxx, float maxy);
   void     kill()                       { this->alive = false;         }
   void     ressurrect()                 { this->alive = true;          }
   void     setLifetime(int life)        { lifetime = life;             }
   int      getLifetime()                { return lifetime;             }
   int      addLifetime()                { lifetime++;                  }
   bool     getClockwise()               { return clockwise;            }
   void     setClockwise(bool clockwise) { this->clockwise = clockwise; }
   int      getAngle()                   { return angle;                }
   void     setAngle(int angle)          { this->angle = angle;         }
   
   void spin(int spin);
   
   //virtual functions
   virtual void advance(){
	  Point p = getPoint();
	  Velocity v = getVelocity();
      setPoint(p + v);
   }
   virtual void draw(){}
};

#endif /* flyingObject_h */

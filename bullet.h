#include "flyingObject.h"
#include "uiDraw.h"
#include <iostream>

#ifndef bullet_h
#define bullet_h

#define BULLET_SPEED 5
#define BULLET_LIFE 40
#define BULLET_LENGTH 5

class Bullet : public FlyingObject
{
  private:
   int life;
   int length;
   
  public:
   //constructor which calls the base class constructor
   Bullet() : FlyingObject() { setLength(0); }
   
   //fire sets the position, velocity, and life to each bullet
   void fire(Point shipP, Velocity shipV, float angle);
   
   //setter and getter for life
   void setLife(int life)     { this->life = life;    }
   int  getLife()             { return life;          }
   
   void setLength(int length) { this->length = length; }
   int  getLength()           { return length;        }
   
   //depends on uiDraw.h methods to draw the bullet   
   virtual void draw()
   {
	   if(getLifetime() < 40)
	   {
	      if (getLength() < BULLET_LENGTH)
			  setLength(getLength() + (BULLET_SPEED / 2));
          drawAsteroidBullet(getPoint(), getAngle(), getLength());
		  setLife(getLife() - 1);
	   }
	   else
		  kill();
   }
};




#endif /* bullet_h */

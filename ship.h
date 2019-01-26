#include "flyingObject.h"
#include "uiDraw.h"

#ifndef ship_h
#define ship_h

#define SHIP_SIZE 10
#define SHIELD_RADIUS 14
#define SHIELD_BUFFER 2

#define ROTATE_AMOUNT 8
#define THRUST_AMOUNT 0.5



// Put your Ship class here
class Ship : public FlyingObject
{
  public:
    Ship();
	Ship(Point p);
	~Ship(){}
	
  private:
   float angle;
   float forwardSpeed;
   bool thrust;
   int shieldRadius;
   void calculateNewVelocity();

  public:
   void  setAngle(float angle)               { this->angle = angle;               }
   float getAngle()                          { return angle;                      }
   float getForwardSpeed()                   { return forwardSpeed;               }
   void  setForwardSpeed(float forwardSpeed) { this->forwardSpeed = forwardSpeed; } 
   bool  getThrust()                         { return thrust;                     }
   void  setThrust(bool thrust)              { this->thrust = thrust;             }
   int   getShieldRadius()                   { return shieldRadius;               }
   void  setShieldRadius(int shieldRadius)   { this->shieldRadius = shieldRadius; }

   //ship movement
   void rotateClockwise();
   void rotateCounterClockwise();
   void moveForward();
   void applyBrakes();
   
   
   //draw
   virtual void draw()
   {
      drawShip(getPoint(), getAngle() - 90, getThrust());
   }   
   
   void drawShipShield(int powers);
   
   void reset();
};


#endif /* ship_h */

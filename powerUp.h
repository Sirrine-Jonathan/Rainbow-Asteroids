#include "flyingObject.h"
#include "uiDraw.h"

#ifndef POWERUP_H
#define POWERUP_H

#define POWERUP_SIZE 6
#define POWERUP_LIFE 250

class PowerUp : public FlyingObject
{
  public:
   PowerUp();
   PowerUp(Point tl, Point br);
   
  private:
  
  public:
   virtual void advance(){
	  
	  //add the velocity points to
	  //the current position point
	  Point p = getPoint();
      float dx = getVelocity().getDx();
      float dy = getVelocity().getDy();
      p.addX(dx);
      p.addY(dy);
      setPoint(p);
	  
	  if (getLifetime() > POWERUP_LIFE)
	  {
         kill();
	  }
   }
   virtual void draw(){	
	  drawShield(getPoint(), POWERUP_SIZE, 0, 3, 3);	 
   }
   virtual void hit(){}
   virtual void initVelocity(){}
   virtual void spin(){}
   virtual int  identify(){}
};

#endif
#include "ship.h"
#include <iostream>

// Put your ship methods here
Ship :: Ship() 
{
   setRadius(SHIP_SIZE);
   setShieldRadius(SHIELD_RADIUS);
   setAngle(90);
   setForwardSpeed(0);
}

Ship :: Ship(Point p)
{
   Ship();
   setPoint(p);
}

void Ship :: rotateClockwise()
{
   float rotation = getAngle() + ROTATE_AMOUNT;
   if (rotation >= 360)
   {
       rotation -= 360;
   }	   
   setAngle(rotation);
}

void Ship :: rotateCounterClockwise()
{
   float rotation = getAngle() - ROTATE_AMOUNT;
   if (rotation < 0)
   {
	   rotation += 360;
   }
   setAngle(rotation);
}

void Ship :: moveForward()
{
   if (getForwardSpeed() < 2)
      setForwardSpeed(getForwardSpeed() + THRUST_AMOUNT);
   float newdx = getForwardSpeed() * (cos(M_PI / 180.0 * angle));
   float newdy = getForwardSpeed() * (sin(M_PI / 180.0 * angle));
   float olddx = getVelocity().getDx();
   float olddy = getVelocity().getDy();
   float dx = newdx + olddx;
   float dy = newdy + olddy;
   
   Velocity v;
   v.setDx(dx);
   v.setDy(dy);   
   setVelocity(v);
}

void Ship :: applyBrakes()
{
   if (getForwardSpeed() > 2.5)
      setForwardSpeed(getForwardSpeed() - 2);
   else if (getForwardSpeed() > 1.5)
	  setForwardSpeed(getForwardSpeed() - 1);
   else if (getForwardSpeed() > 1)
	  setForwardSpeed(getForwardSpeed() - THRUST_AMOUNT);
  
   float newdx = -getForwardSpeed() * (cos(M_PI / 180.0 * angle));
   float newdy = -getForwardSpeed() * (sin(M_PI / 180.0 * angle));
   float olddx = getVelocity().getDx();
   float olddy = getVelocity().getDy();
   float dx = newdx + olddx;
   float dy = newdy + olddy;
   
   Velocity v(olddx, olddy);
   
   if (dx != 0)
   {
      if (dx > olddx)
      {
	     //rising to 0
	     if (dx < 0)
		    v.setDx(dx);
      }
      else if (dx < olddx)
      {
	     //lowering to 0
	     if (dx > 0)
			 v.setDx(dx);
      }
   }
   if (dy != 0)
   {
      if (dy > olddy)
      {
	     //rising to 0
	     if (dy < 0)
			 v.setDy(dy);
      }
      else if (dy < olddy)
      {
	     //lowering to 0
		 if (dy > 0)
			 v.setDy(dy);
      }  
   }
   
   setVelocity(v);
}

void Ship :: reset()
{
   ressurrect();
   setAngle(90);
   setForwardSpeed(0);
   Velocity v;
   Point p;
   setVelocity(v);
   setPoint(p);   
}

void Ship :: drawShipShield(int powers)
{
   int level = powers / 5;
   level++;
   
   int radius;
   for (int i = 0; i < level; i++)
   {
	  radius = SHIELD_RADIUS + (SHIELD_BUFFER * i);
	  
	  //blue shield
	  float red = 0.0;
	  float green = 0.0;
	  float blue = 1.0;
	  
	  if (i <= 2) 
	  {
		 //red shield
         blue = 0.0;
         red = 1.0;		 
	  }
	  else if (i <= 4)
	  {
		 //yellow shield
		 blue = 0.0;
		 red = 1.0;
		 green = 1.0;
	  }
	  else if (i <= 6)
	  {
		 //green shield
         blue = 0.0;
         green = 1.0;		 
	  }
	  
		  
      drawShield(getPoint(), radius, getAngle() - 90, 6, red, green, blue); 
   }
   setShieldRadius(radius);
}


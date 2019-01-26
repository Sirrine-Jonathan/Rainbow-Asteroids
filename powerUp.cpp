#include "powerUp.h"

PowerUp :: PowerUp(Point tl, Point br)
{
   setRadius(POWERUP_SIZE);
   
   //set the point to a random location outside the screen
   float x;
   float y;
   float dx;
   float dy;
   float buffer = 20;
   int deciderOne = random(0, 2);
   int deciderTwo = random(0, 2);
   if(deciderOne)
   {
	   x = random(tl.getX(), br.getX());
	   dx = random(-1, 2);
	   
	   //rock will come in from top or bottom
	   if (deciderTwo)
	   {
		  //rock will come down from top
	      y = tl.getY() + buffer;
		  dy = 2;
	   }
	   else
	   {
		   //rock will come up from bottom
	 	  y = br.getY() - buffer;
		  dy = -2;
	   }
   }
   else
   {
	   y = random(br.getY(), tl.getY());
	   dy = random(-1, 2);
	   
	   //rock will come in from left or right
	   if (deciderTwo)
	   {
		   //rock will come in from right
		   x = br.getX() + buffer;
		   dx = 1;
	   }
	   else
	   {
		   //rock will come in from left
		   x = tl.getX() - buffer;
		   dx = -2;
	   }
   }
   Point p(x, y);
   setPoint(p);
   
   //set velocity so that the rocks travel towards center
   Velocity v = getVelocity();
   v.setDx(dx);
   v.setDy(dy);
   setVelocity(v);
}
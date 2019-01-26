#include "flyingObject.h"
#include "velocity.h"
#include "point.h"
#include "cmath"

/**************************************************
 * FlyingObject :: checkWarp
 * checks if there is a need to 
 * swap x  or  y 
 **************************************************/
void FlyingObject :: checkWarp(float maxx, float maxy)
{ 

   //declare a point with objects point's x & y
   Point changePoint(this->getPoint().getX(), this->getPoint().getY());
   int buffer = getRadius();
   
   //check for horizontal warp
   if (this->getPoint().getX() > maxx + buffer)
      changePoint.setX(-maxx - buffer);
   else if (this->getPoint().getX() < -maxx - buffer)
	  changePoint.setX(maxx + buffer);		

   //check for vertical warp
   if(this->getPoint().getY() > maxy + buffer)
	  changePoint.setY(-maxy - buffer);
   else if (this->getPoint().getY() < -maxy - buffer)
   	  changePoint.setY(maxy + buffer);
  
   //set the point to changePoint which may or may not have changes
   this->setPoint(changePoint);
}   

void FlyingObject :: spin(int spin)
{
  if (clockwise)
	 setAngle(getAngle() + spin);  
  else
	 setAngle(getAngle() - spin);
}

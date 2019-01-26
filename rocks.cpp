#include "rocks.h"
#include "uiDraw.h"
#include <cmath>

// Put your Rock methods here
Rock :: Rock()
{
	FlyingObject();
	setAngle(random(0, 360));
}

Rock :: Rock(Rock & rhs)
{
   setMass(rhs.getMass());
   setVelocity(rhs.getVelocity());
}

/*********************************************************
* Non Default Constructor
* starts a big rock somewhere outside the viewport with
* a velocity that heads towards the center
*********************************************************/
BigRock :: BigRock(Point tl, Point br)
{
   //initialize common properties of all rocks
   Rock();
   setRadius(BIG_ROCK_SIZE);
   setMass(BIG_ROCK_MASS);
   
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
		  dy = 1;
	   }
	   else
	   {
		   //rock will come up from bottom
	 	  y = br.getY() - buffer;
		  dy = -1;
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
		   dx = -1;
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

BigRock :: BigRock(float x, float y)
{
   //initialize common properties of all rocks
   Rock();
   setRadius(BIG_ROCK_SIZE);
   setMass(BIG_ROCK_MASS);
   
   //set private member variables with public member functions
   Point p(x, y);
   setPoint(p);
   initVelocity();
}

MediumRock :: MediumRock(Point p, Velocity v)
{
   //initialize common properties of all rocks
   Rock();
   setRadius(MEDIUM_ROCK_SIZE);
   setMass(MEDIUM_ROCK_MASS);
   
   //set private member variables with public member functions
   setPoint(p);
   setVelocity(v);
}

SmallRock :: SmallRock(Point p, Velocity v)
{
   //initialize common properties of all rocks
   Rock();
   setRadius(SMALL_ROCK_SIZE);
   setMass(SMALL_ROCK_MASS);
   
   //set private member variables with public member functions
   setPoint(p);
   setVelocity(v);
}

void Rock :: updateVelocity(Rock & otherRock)
{
	
   //rock1 variables
   int r1Mass = getMass();
   int r1Vx = getVelocity().getDx();
   int r1Vy = getVelocity().getDy();

   //rock2 variables
   int r2Mass = otherRock.getMass();
   int r2Vx = otherRock.getVelocity().getDx();
   int r2Vy = otherRock.getVelocity().getDy();

   int finalR1Vx = 1;
   int finalR1Vy = 1;
   /*
   int finalR1Vx = r1Vx * (r1Mass - r2Mass) + 2 * r2Mass * r2Vx * r1Mass + r2Mass;
   int finalR1Vy = r1Vy * (r1Mass - r2Mass) + 2 * r2Mass * r2Vy * r1Mass + r2Mass; 
   
   std::cout << "r1Vx * (r1Mass - r2Mass) + 2 * r2Mass * r2Vx * r1Mass + r2Mass;" << std::endl;
   std::cout << finalR1Vx << std::endl << std::endl;
   
   std::cout << "r1Vy * (r1Mass - r2Mass) + 2 * r2Mass * r2Vy * r1Mass + r2Mass;" << std::endl;
   std::cout << finalR1Vy << std:: endl << std:: endl;
   std::cout << std::endl << std::endl;
   */
   
   Velocity newV(finalR1Vx, finalR1Vy);
   setVelocity(newV);
}

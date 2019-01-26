#include "flyingObject.h"
#include "uiDraw.h"
#include <iostream>

#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_MASS 1
#define MEDIUM_ROCK_MASS 1
#define SMALL_ROCK_MASS 1

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10


// Define the following classes here:
//   Rock
class Rock : public FlyingObject
{	
  public:
   Rock();
   Rock(Rock & rhs);
  ~Rock(){}
   
  private:
   int radius;
   float mass;
   
  public: 
   void setMass (float mass) { this->mass = mass; }
   float  getMass ()         { return mass;       }
   
   //flying object virtual functions
   virtual void advance(){}
   virtual void draw(){}
   virtual void hit(){}
   
   //rock virtual functions
   virtual void initVelocity(){}
   virtual int  identify(){}
   
   void updateVelocity(Rock & otherRock);
};





//   BigRock
class BigRock : public Rock
{
  public:
   BigRock() : Rock() {}
   BigRock(Point tl, Point br);
   BigRock(float x, float y);
   
   virtual void advance(){
	  spin(BIG_ROCK_SPIN);
	  FlyingObject :: advance();
   }
   
   virtual void initVelocity(){
      float dx = 1 * (-cos(M_PI / 180.0 * getAngle()));
      float dy = 1 * (sin(M_PI / 180.0 * getAngle()));
      
	  Velocity v = getVelocity();
	  
	  v.setDx(dx);
      v.setDy(dy);
	  
	  setVelocity(v);
   }
   virtual void draw(){
	   drawLargeAsteroid(getPoint(), getAngle());
   }   
   virtual void hit(){}
   virtual int  identify(){ return 2; }
};





//   MediumRock
class MediumRock : public Rock
{
   public:
   MediumRock();
   MediumRock(Point p, Velocity v);
   
   virtual void advance(){
	  spin(MEDIUM_ROCK_SPIN);
	  FlyingObject :: advance();
	  /*	  
	  //add the velocity points to
	  //the current position point
	  Point p = getPoint();
      float dx = getVelocity().getDx();
      float dy = getVelocity().getDy();
      p.addX(dx);
      p.addY(dy);
      setPoint(p);	   
	  */
   }
   virtual void draw(){
      drawMediumAsteroid(getPoint(), getAngle());	   
   }
   virtual void hit(){}
   virtual int  identify(){ return 1; }
   virtual void initVelocity(){}
};





//   SmallRock
class SmallRock : public Rock
{
   public:
   SmallRock();
   SmallRock(Point p, Velocity v);
   
   virtual void advance(){
	  spin(SMALL_ROCK_SPIN);
	  FlyingObject :: advance();
	  /*
	  //add the velocity points to
	  //the current position point
	  Point p = getPoint();
      float dx = getVelocity().getDx();
      float dy = getVelocity().getDy();
      p.addX(dx);
      p.addY(dy);
      setPoint(p);	
	  */	  
   }
   virtual void draw(){
      drawSmallAsteroid(getPoint(), getAngle());
   }
   virtual void hit(){}
   virtual int  identify(){ return 0; }
   virtual void initVelocity(){}
};


#endif /* rocks_h */

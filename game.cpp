
/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

// things to include
#include "game.h"
#include <iostream>

// These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>
using namespace std;

/***************************************
 * GAME CONSTRUCTOR
 ***************************************/
Game :: Game(Point tl, Point br)  : topLeft(tl), bottomRight(br), time(0), powers(STARTING_SHIELD_TIME)
{
   
   //initialize win flag to false
   setWinFlag(false);
   setLoseFlag(false);
   setScore(0);
   setShowInfo(true);
   setAsteroidWait(75);
   
   //setup big rocks
   generateBigRocks();
}

/****************************************
 * GAME DESTRUCTOR
 ****************************************/
Game :: ~Game()
{
   //clean up rocks
   if (rocks.size() > 0)
   {
      for(vector <Rock*> :: iterator it = rocks.begin(); it != rocks.end();)
	  {
		 delete *it;
         rocks.erase(it);
	  }
   }
   
   //clean up bullets
   if (bullets.size() > 0)
   {
      for(vector <Bullet> :: iterator it = bullets.begin(); it != bullets.end();)
	  {	
    	 bullets.erase(it);
      }
   }
   
   //clean up powerups
   if (powerups.size() > 0)
   {
	  for (vector <PowerUp> :: iterator it = powerups.begin(); it != powerups.end();)
	  {
		 powerups.erase(it);
	  }
   }
}

/*********************************************
* Function: resetWin
* Description: Resets game after a win
*********************************************/
void Game :: resetWin()
{
   //make rocks start entering from outside
   //add five new rocks
   BigRock * pBigRock = new BigRock(topLeft, bottomRight);

   //push the pointer to the vector
   rocks.push_back(pBigRock);
}

/*********************************************
* Function: resetLose
* Description: Resets game after a lose
*********************************************/
void Game :: resetLose()
{
	ship.reset();
	setWinFlag(false);
	setLoseFlag(false);
	setTime(0);
	setPowers(STARTING_SHIELD_TIME);
	setScore(0);
	
   //clean up rocks
   if (rocks.size() > 0)
   {
      for(vector <Rock*> :: iterator it = rocks.begin(); it != rocks.end(); ++it)
	  {
		(*it)->kill();
	  }
   }
   
   //clean up bullets
   if (bullets.size() > 0)
   {
      for(vector <Bullet> :: iterator it = bullets.begin(); it != bullets.end(); ++it)
	  {	
    	 (*it).kill();
      }
   }
   
   //clean up powerups
   if (powerups.size() > 0)
   {
	  for (vector <PowerUp> :: iterator it = powerups.begin(); it != powerups.end(); ++it)
	  {
		 (*it).kill();
	  }
   }
   
   generateBigRocks();
}

/*********************************************
* Function: release power up
* Description: release a power up
*********************************************/
void Game :: releasePowerUp()
{
   	PowerUp newPowerup(topLeft, bottomRight);
	powerups.push_back(newPowerup);
}


/***************************************
 * GAME :: ADVANCE
 * advance the game one unit of time
 ***************************************/
void Game :: advance()
{
   advanceShip();
   advanceBullets();
   advanceRocks();
   advancePowerups();
   
   handleCollisions();
   cleanUpZombies();
   
   //check lose state
   if(getLoseFlag())
   {   
	  if(getLoseFlag() && getTime() - getLoseFlagTime() >= NEW_GAME_RELOAD_TIME)
      {
	     resetLose();
      }
	  else
	  {
         Point p(-15,0);
         drawText(p, "Game Over");
		 drawInfo();
	  }
   }
   
   //handle game time
   setTime(getTime() + 1);
   
   //time the release of shield power ups
   if (getTime() % 100 == 0)
      releasePowerUp();
 
	
}

void Game :: advanceShip()
{
   if(ship.isAlive())
   {
		ship.advance();
		ship.addLifetime();
   }
}

void Game :: advanceRocks()
{
   if(rocks.size() > 0)
   {
      for(vector <Rock*> :: iterator it = rocks.begin(); it != rocks.end(); ++it)
	  {
		 if((*it)->isAlive())
		 {
            (*it)->advance();
            (*it)->addLifetime();		
         }			
	  }
	  if (getWinFlag() && rocks.size() < 5 && getTime() > getLastAsteroidAdd() + getAsteroidWait())
	  {
		 resetWin();
		 setLastAsteroidAdd(getTime());
	  }
   }	
   else{
	   setLastAsteroidAdd(getTime() + getAsteroidWait());
	   setWinFlag(true);
	   resetWin();
   }
}

void Game :: advanceBullets()
{
   if (bullets.size() > 0)
   {
      for(vector <Bullet> :: iterator it = bullets.begin(); it != bullets.end(); ++it)
	  {	
    	(*it).advance();
		(*it).addLifetime();
      }
   }
}

void Game :: advancePowerups()
{
   if (powerups.size() > 0)
   {
	  for (vector <PowerUp> :: iterator it = powerups.begin(); it != powerups.end(); ++it)
	  {
		 (*it).advance();
		 (*it).addLifetime();
	  }
   }
}

/***************************************
 * GAME :: HANDLE INPUT
 * accept input from the user
 ***************************************/
void Game :: handleInput(const Interface & ui)
{
   // Change the direction of the ship
   if (ui.isLeft())
   {
      ship.rotateClockwise();
   }
   
   if (ui.isRight())
   {
      ship.rotateCounterClockwise();   
   }
   
   if (ui.isUp())
   {
	  ship.setThrust(true);
	  ship.moveForward();
   }
   else
   {
	  ship.setThrust(false);
   }
   
   if (ui.isDown())
   {
	  ship.applyBrakes();
   }
   
   // Check for "Spacebar
   if (ui.isSpace())
   {
      Bullet newBullet;
	  newBullet.fire(ship.getPoint(), ship.getVelocity(), ship.getAngle());
	  bullets.push_back(newBullet);
   }
   
   //check for function One Key
   if (ui.isFunctionOne())
   {
	   setShowInfo(!getShowInfo());
   }
}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game :: draw(const Interface & ui)
{
   if(ship.isAlive())
   {
		ship.draw();
		
	    if( getPowers() > 0)
		   ship.drawShipShield(getPowers());
		
		ship.checkWarp(getMaxx(), getMaxy());
   }
   
   if(rocks.size() > 0)
   {
      for(vector <Rock*> :: iterator it = rocks.begin(); it != rocks.end(); ++it)
	  {
		 if ( (*it)->isAlive() )
		 {
            (*it)->draw();
            (*it)->checkWarp(getMaxx(), getMaxy());
		 }
	  }
   }
   
   if(bullets.size() > 0)
   {
      for(vector <Bullet> :: iterator it = bullets.begin(); it != bullets.end(); ++it)
	  {	
        if ( (*it).isAlive() )
		{
    	   (*it).draw();
		   (*it).checkWarp(getMaxx(), getMaxy());
		}
      }
   }
   
   if(powerups.size() > 0)
   {
	  for (vector <PowerUp> :: iterator it = powerups.begin(); it != powerups.end(); ++it)
	  {
	    if ( (*it).isAlive() )
		{
		   (*it).draw();
		   (*it).checkWarp(getMaxx(), getMaxy());
		}
	  }
   }
   
   //reduce shield time
   if (getPowers() > 0)
	   setPowers(getPowers() - 1);
   
   if (getShowInfo())
   {
      drawInfo();
   }
   
}

void Game :: drawInfo()
{
   //display shield time
   int centerOffset = 90;
   int labelWidth = 80;   

   //LABEL   
   Point p1(centerOffset, topLeft.getY() - 15);
   drawText(p1, "Shield Time: ");	

   //VALUE
   Point p2(centerOffset + labelWidth, topLeft.getY() - 5);
   drawNumber(p2, getPowers());

   //display score

   //LABEL
   Point p3(-35, topLeft.getY() - 15);
   drawText(p3, "Score: ");

   Point p4(10, topLeft.getY() - 5);
   drawNumber(p4, getScore());

   //display time

   Point p(topLeft.getX() + 10, topLeft.getY() - 5);
   drawNumber(p, getTime());
}

/*********************************************
 * GAME :: HANDLE COLLISIONS
 * Handle different collisions
 *********************************************/
void Game :: handleCollisions()
{
   rockBulletCollision();
   shipPowerCollision();
   rockShipCollision();
   bulletPowerCollision();
   rockRockCollision();
}

/*
*      Handle Rock and Bullet Collisions
*/
void Game :: rockBulletCollision()
{
   //loop through bullets
   for (vector <Bullet> :: iterator itB = bullets.begin(); itB != bullets.end(); ++itB)
   {
	  //if bullet is alive
      if ((*itB).isAlive())
      {
		 //loop through rocks to handle rock collsions
         for (vector <Rock*> :: iterator itR = rocks.begin(); itR != rocks.end();)
         {
			//if rock is alive
		    if((*itR)->isAlive())
		    {
			   
			   //the rock radius is the distance threshold here
			   int distanceThreshold = (*itR)->getRadius();
			   
			   //check collisionDistance
			   if (getClosestDistance((**itR), (*itB)) <= distanceThreshold)
			   {
				  //store point and velocity of the breaking rock
			      Point rockP = (*itR)->getPoint();
                  Velocity rockV = (*itR)->getVelocity();		

				  (*itR)->kill();
				  (*itB).kill();

                  createNewRocks(rockP, rockV, (*itR)->identify());

                  break;				  
			   }
			   else
				  ++itR;
			}
			else 
			   ++itR;
		 }
	  }
   }
}

/*
*      Handle Ship and PowerUp Collisions
*/
void Game :: shipPowerCollision()
{
   for (vector <PowerUp> :: iterator itP = powerups.begin(); itP != powerups.end(); ++itP)
   {
	  if ((*itP).isAlive())
	  {
		 //here the minimum distance that the two objects must acheive is both objects radiuses
		 int distanceThreshold = (*itP).getRadius() + ship.getRadius();
		 
		 if (getClosestDistance((*itP), ship) <= distanceThreshold)
		 {
		    (*itP).kill();
			setPowers(getPowers() + STARTING_SHIELD_TIME);
		 }
	  }
   }
}

/*
*      Handle Rock and Ship Collisions
*/
void Game :: rockShipCollision()
{
   for (vector <Rock*> :: iterator itR = rocks.begin(); itR != rocks.end(); ++ itR)
   {
	  if((*itR)->isAlive())
	  {
		 
		 if (getPowers() <= 0)
		 {  
			//the rock and ship radius is the distance threshold for this collision
	        int distanceThreshold = (*itR)->getRadius() + ship.getRadius();
			
            if (getClosestDistance((**itR), ship) <= distanceThreshold)
		    {
			   ship.kill();
			   			
			   setLoseFlag(true);
               setLoseFlagTime(getTime());			   
		    }
	     }
		 else
		 {
			//the rock and shield radius is the distance threshold for this collision
			int distanceThreshold = ship.getShieldRadius() + (*itR)->getRadius(); 
			
			if (getClosestDistance((**itR), ship) <= distanceThreshold)
			{
			   //store point and velocity of the breaking rock
			   Point rockP = (*itR)->getPoint();
			   Velocity rockV = (*itR)->getVelocity();		

			   (*itR)->kill();

			   createNewRocks(rockP, rockV, (*itR)->identify());

			   break;	
			}
	     }
      }
   }	
}

/*
*      Handle Powerup and Bullet Collisions
*/
void Game :: bulletPowerCollision()
{
   for (vector <Bullet> :: iterator itB = bullets.begin(); itB != bullets.end(); ++itB)
   {
      if ((*itB).isAlive())
	  {
		 //loop through powerups to handle powerup collisions
	     for (vector <PowerUp> :: iterator itP = powerups.begin(); itP != powerups.end(); ++itP)
     	 {
            if ((*itP).isAlive())
			{
			   int distanceThreshold = (*itP).getRadius();
			   
			   if (getClosestDistance((*itP), (*itB)) <= distanceThreshold)
			   {
				  (*itB).kill();
		          (*itP).kill();
			      setPowers(getPowers() + 89);  
				  
			   }
			}
	     }
      }
   }	
}

/*
*      Handle Rock and Rock Collisions
*/
void Game :: rockRockCollision()
{
   for (vector <Rock*> :: iterator itR1 = rocks.begin(); itR1 != rocks.end(); ++ itR1)
   {
      if((*itR1)->isAlive())
	  {
	     for (vector <Rock*> :: iterator itR2 = rocks.begin(); itR2 != rocks.end(); ++ itR2)
		 {
		    if((*itR2)->isAlive() && (*itR1) != (*itR2))
		    {
			   int distanceThreshold = (*itR1)->getRadius() + (*itR2)->getRadius();
			   if (getClosestDistance((**itR1), (**itR2)) <= distanceThreshold)
			   {
                  //handleRockCollision(**itR1, **itR2);
			   }
			}
		 }
	  }
   }	   
}

void Game :: handleRockCollision(Rock & rock1, Rock & rock2)
{
   if(rock1.getLifetime() > 20 && rock2.getLifetime() > 20)
   {
	  /*
	  * TODO
      * get the new velocity for each object 
      * with respect to their current velocities
      * and the laws of elasctic collisions
      */
	  Rock rock1clone(rock1);
	  Rock rock2clone(rock2);
	  rock1.updateVelocity(rock2clone);
	  rock2.updateVelocity(rock1clone);
   }
}

/***************************************************************
* Create New Rocks
* Handles the break down of each rock
***************************************************************/
void Game :: createNewRocks(Point p, Velocity v, int rockSize)
{
   if (rockSize == 2)
      breakBigRock(p, v);
   else if (rockSize == 1)
      breakMediumRock(p, v);
   else 
   {
	  //small rock is destroyed
      setScore(getScore() + 1);	  
   }
}

/*********************************************
* Function: Generate Medium Rocks
* Description: Spawns Medium Rocks 
*********************************************/
void Game :: breakBigRock(Point p, Velocity v)
{
  
  Velocity v1;
  v1.setDx(v.getDx() + 1);
  v1.setDy(v.getDy());
  MediumRock * pMediumRock1 = new MediumRock(p, v1);
  rocks.push_back(pMediumRock1);
  
  //second medium rock
  Velocity v2;
  v2.setDx(v.getDx() - 1);
  v2.setDy(v.getDy());
  MediumRock * pMediumRock2 = new MediumRock(p, v2);
  rocks.push_back(pMediumRock2);
  
  //small rock
  Velocity v3;
  v3.setDx(v.getDx());
  v3.setDy(v.getDy() - 3);
  SmallRock * pSmallRock = new SmallRock(p, v3);
  rocks.push_back(pSmallRock); 
}

/*********************************************
* Function: Generate Small Rocks
* Description: Spawns Small Rocks 
*********************************************/
void Game :: breakMediumRock(Point p, Velocity v)
{
  //first small rock
  Velocity v1;
  v1.setDx(v.getDx() + 3);
  v1.setDy(v.getDy());
  SmallRock * pSmallRock1 = new SmallRock(p, v1);
  rocks.push_back(pSmallRock1); 

  //second small rock
  Velocity v2;
  v2.setDx(v.getDx() - 3);
  v2.setDy(v.getDy());
  SmallRock * pSmallRock2 = new SmallRock(p, v2);
  rocks.push_back(pSmallRock2);   
}

/*********************************************
* Function: Generate Small Rocks
* Description: Spawns Small Rocks 
*********************************************/
void Game :: generateBigRocks()
{
   //initialize 5 BigRocks
   //Struct for a starting point
   struct PT
   {
      int x;
      int y;
   };
   
   //Inital Big Rock Points
   PT startingPoints[5] =
   {
      {70, 100}, {-70,  100}, {0,  -100}, {-120, -100}, {120, -100}
   };

   //Loop five times to set Big Rock Pointers
   for (int i = 0; i < 5; i++)
   {
	  //initalize the next big rock pointer
      BigRock * pBigRock = new BigRock(startingPoints[i].x, startingPoints[i].y);
	  
	  //push the pointer to the vector
      rocks.push_back(pBigRock);
   }	
}


 
// You may find this function helpful...

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/

float Game :: getClosestDistance(FlyingObject &obj1, FlyingObject &obj2) const
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}

void Game :: cleanUpZombies()
{
   //check for dead rocks
   if(rocks.size() > 0)
   {
	  
      for(vector <Rock*> :: iterator it = rocks.begin(); it != rocks.end();)
	  {
		 if(!(*it)->isAlive())
         {
			delete *it;
	        it = rocks.erase(it);
		 }	 
		 else
		    ++it;
	  }
   }
   
   //check for dead bullets
   if(bullets.size() > 0)
   {
      for(vector <Bullet> :: iterator it = bullets.begin(); it != bullets.end();)
	  {	
        if (! (*it).isAlive())
		{
    	   it = bullets.erase(it);
		}
		else
		   ++it;
      }
   }
}


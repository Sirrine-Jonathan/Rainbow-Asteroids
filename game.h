/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/
#include <vector>

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "velocity.h"
#include "flyingObject.h"
#include "bullet.h"
#include "ship.h"
#include "rocks.h"
#include "powerUp.h"
 
 
#ifndef GAME_H
#define GAME_H

#define STARTING_SHIELD_TIME 49
#define CLOSE_ENOUGH 15
#define NEW_GAME_RELOAD_TIME 12

/*****************************************
 * GAME
 * The main game class containing all the state
 *****************************************/
class Game
{
public:
   /*********************************************
    * Constructor
    * Initializes the game
    *********************************************/
   Game(Point tl, Point br);
   ~Game();
   
   /*********************************************
    * Function: resetWin
    * Description: Resets game after a win
    *********************************************/
   void resetWin();
   
   /*********************************************
    * Function: resetLose
    * Description: Resets game after a lose
    *********************************************/
   void resetLose();
   
   /*********************************************
    * Function: handleInput
    * Description: Takes actions according to whatever
    *  keys the user has pressed.
    *********************************************/
   void handleInput(const Interface & ui);
   
   /*********************************************
    * Function: advance
    * Description: Move everything forward one
    *  step in time.
    *********************************************/
   void advance();
   void advanceShip();
   void advanceRocks();
   void advanceBullets();
   void advancePowerups();

   /*********************************************
    * Function: Handle Collisions
    * Description: handles all collisions of objects
    *********************************************/
   void handleCollisions();  
   void rockBulletCollision();
   void shipPowerCollision();
   void rockShipCollision();
   void bulletPowerCollision();
   void rockRockCollision();
   void handleRockCollision(Rock & rock1, Rock & rock2);
  
   /*********************************************
    * Function: draw
    * Description: draws everything for the game.
    *********************************************/
   void draw(const Interface & ui);
  
   
   /*********************************************
    * Function: Create New Rocks
    * Description: will call one of the next 
	* three functions based on the rock size
    *********************************************/
   void createNewRocks(Point p, Velocity V, int rockSize);
   
   /*********************************************
    * Function: Generate Big Rocks
    * Description: Spawns Big Rocks at start
	* and restart of game
    *********************************************/
   void generateBigRocks();
   
   /*********************************************
    * Function: Break Big Rock
    * Description: Spawns 2 Medium Rocks and one
    * small rock while suppying thier velocities	
    *********************************************/
   void breakBigRock(Point p, Velocity v);
   
   /*********************************************
    * Function: Break Medium Rock
    * Description: Spawns 2 Small Rocks while
	* supplying their velocities
    *********************************************/
   void breakMediumRock(Point p, Velocity v);
   
   /*********************************************
    * Function: Clean Up Zombies
    * Description: cleans up memory used for
    * destroyed bullets and rocks	
    *********************************************/
   void cleanUpZombies();
   
   /*********************************************
    * Function: release power up
    * Description: release a power up
    *********************************************/
   void releasePowerUp();
   
   /*********************************************
    * Function: draw info
    * Description: draws game info at the top of
	* the screen
    *********************************************/
   void drawInfo();

   //get maxX and maxY
   float getMaxx()                               { return bottomRight.getX();               }
   float getMaxy()                               { return topLeft.getY();                   }
   
   //get and set winFlag
   void  setWinFlag(bool flag)                   { winFlag = flag;                          }
   bool  getWinFlag()                            { return winFlag;                          }  

   //get and set loseFlag
   void  setLoseFlag(bool loseFlag)              { this->loseFlag = loseFlag;               }
   bool  getLoseFlag()                           { return loseFlag;                         }   
   
   //get and set loseFlagTime
   void  setLoseFlagTime(int loseFlagTime)       { this->loseFlagTime = loseFlagTime;       }
   int   getLoseFlagTime()                       { return loseFlagTime;                     }   
   
   //get and set time
   void  setTime(int time)                       { this->time = time;                       }
   int   getTime()                               { return time;                             }
   
   //get and set lastAsteroidAdd
   void  setLastAsteroidAdd(int lastAsteroidAdd) { this->lastAsteroidAdd = lastAsteroidAdd; }
   int   getLastAsteroidAdd()                    { return lastAsteroidAdd;                  }
   
   //get and set asteroidWait
   void  setAsteroidWait(int asteroidWait)       { this->asteroidWait = asteroidWait;       }
   int   getAsteroidWait()                       { return asteroidWait;                     }
   
   //get and set powers
   void  setPowers(int powers)                   { this->powers = powers;                   }
   int   getPowers()                             { return powers;                           }
   
   //get and set score
   void  setScore(int score)                     { this->score = score;                     }
   int   getScore()                              { return score;                            }
   
   void  setShowInfo(bool showInfo)              { this->showInfo = showInfo;               }
   bool  getShowInfo()                           { return showInfo;                         }

   
private:
   // The coordinates of the screen
   Point topLeft;
   Point bottomRight;
   
   //integer properties
   int time;                 //how long the game has been going without a lose
   int lastAsteroidAdd;      //time since the last large asteroid was added
   int asteroidWait;         //time that the game will wait before adding a new asteroid
   int powers;               //how long the shield will be up for
   int loseFlagTime;         //timestamp of when the ship was destroyed
   int score;                //the number of small asteroids destroyed
   
   //win & lose flags
   bool winFlag;
   bool loseFlag;
   bool showInfo;
   
   
   //function used to handle collisions
   float getClosestDistance(FlyingObject &obj1, FlyingObject &obj2) const;
   
   //objects in game
   Ship ship;
   std::vector<Bullet> bullets;
   std::vector<Rock*> rocks;
   std::vector<PowerUp> powerups;
	
};



#endif /* GAME_H */

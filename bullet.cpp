#include "bullet.h"
#include "cmath"

void Bullet :: fire(Point shipP, Velocity shipV, float angle)
{
   //set life and initial position of the bullet
   setLife(40);
   setAngle(angle);
   setPoint(shipP);
   
   //configure the velocity of the bullet
   //start with the ships velocity
   float shipDx = shipV.getDx();
   float shipDy = shipV.getDy();
   float dx = BULLET_SPEED * (cos(M_PI / 180.0 * angle));
   float dy = BULLET_SPEED * (sin(M_PI / 180.0 * angle));
   Velocity v;
   v.setDx(dx + shipDx);
   v.setDy(dy + shipDy);
   setVelocity(v);
}
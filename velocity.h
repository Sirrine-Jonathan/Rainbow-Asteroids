#ifndef VELOCITY_H
#define VELOCITY_H


// Put your velocity class here, or overwrite this file with your own
// velocity class from the previous project
class Velocity 
{
   private:
    float dx;
	float dy;
	
   public:
   Velocity();
   Velocity(int Dx, int Dy);
   float getDx() { return dx; } const
   float getDy() { return dy; } const
   void  setDx(float dx) { this->dx = dx;  }
   void  setDy(float dy) { this->dy = dy;  }
   void  addDx(float dx) { this->dx += dx; }
   void  addDy(float dy) { this->dy += dy; }

   inline friend Velocity operator + (Velocity & lhs, Velocity & rhs)
   {
      Velocity v;
      v.setDx(lhs.getDx() + rhs.getDx());
      v.setDy(lhs.getDy() + rhs.getDy());
      return v;
   }   
};

#endif /* velocity_h */

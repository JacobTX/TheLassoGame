#ifndef __COIN_H__
#define __COIN_H__

#include "MovingObject.h"


class Coin : public MovingObject {
  
  double release_speed;
  double release_angle_deg;
  double coin_ax;
  double coin_ay;
   

  /*  Moving parts */
  Circle coin_circle;

 public:

 double coin_start_x;
 double coin_start_y;
 char cat;  /* Type of coin - normal, bomb, magnet, etc */

 
 Coin(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta,char c,double sx, double sy) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta)
 {
    release_speed = speed;
    release_angle_deg = angle_deg;
    coin_ax = argax;
    coin_ay = argay;
    cat=c;
    coin_start_x=sx;
    coin_start_y=sy;
    initCoin();
 }
 
  void initCoin();
  void resetCoin(int v0,int v,int d0,int d);
  void dynamics(double sT,double cT,double lcje, double CG, bool* g, double lx, double ly, int v0, int v, int d0, int d);
  
  

}; // End class Coin

#endif

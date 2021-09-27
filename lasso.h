#ifndef __LASSO_H__
#define __LASSO_H__

#include "MovingObject.h"
#include "coin.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>


#define WINDOW_X 1000
#define WINDOW_Y 800
#define BASE 650  /*To control the y-coordinate of the horizontal line independent of WINDOW_Y*/

#define STEP_TIME 0.1

#define PLAY_X_START 100
#define PLAY_Y_START 0
#define PLAY_X_WIDTH (WINDOW_X-PLAY_X_START)
#define PLAY_Y_HEIGHT BASE




#define LASSO_X_OFFSET 100
#define LASSO_Y_HEIGHT 100
#define LASSO_BAND_LENGTH LASSO_X_OFFSET
#define LASSO_THICKNESS 5

#define COIN_GAP 1

#define RELEASE_ANGLE_STEP_DEG 5
#define MIN_RELEASE_ANGLE_DEG 0
#define MAX_RELEASE_ANGLE_DEG (360-RELEASE_ANGLE_STEP_DEG)
#define INIT_RELEASE_ANGLE_DEG 45

#define RELEASE_SPEED_STEP 20
#define MIN_RELEASE_SPEED 0
#define MAX_RELEASE_SPEED 200
#define INIT_RELEASE_SPEED 100

#define COIN_SPEED 75
#define COIN_ANGLE_DEG 90 
#define COIN_COLOR_R rand()%255
#define COIN_COLOR_G rand()%255
#define COIN_COLOR_B rand()%255
#define LASSO_G 30
#define COIN_G 30

#define LASSO_SIZE 10
#define LASSO_RADIUS 50
#define COIN_SIZE 5

class Lasso : public MovingObject {
  double lasso_start_x;
  double lasso_start_y;
  double release_speed;
  double release_angle_deg;
  double lasso_ax;
  double lasso_ay;
  double lasso_radius=LASSO_RADIUS;

  // Moving parts
  Circle lasso_circle;
  Circle lasso_loop;

  // Non-moving parts

  Line lasso_line;
  Line lasso_band;

  // State info

  bool lasso_looped;
  Coin *the_coin;
  int num_coins;
  int yank_freq; /* Number of times lasso has been yanked */
  int loop_freq; /* Number of times loop has been released */


  void initLasso();
 public:

 Lasso(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta): MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    lasso_ax = argax;
    lasso_ay = argay;
    
    initLasso();
  }

  void draw_lasso_band();
  void yank();
  void loopit();
  void addAngle(double angle_deg);
  void addSpeed(double speed);

  void nextStep(double t);
  void check_for_coin(Coin *coin, double* cT, bool *g, int v0, int v, int d0, int d);
  int getNumCoins() { return num_coins; }
  int getYankFreq()
  {
    return yank_freq;
  }
  int getLoopFreq()
  {
    return loop_freq;
  }


 /* To store score and other details */
  void store_score(string name)
{
    ofstream fout("records.dat",ios::app|ios::binary); /*To append relevant info to score.dat*/
    time_t now=time(0);
    char* dt=ctime(&now);
    fout<<name<<" "<<dt<<" "<<num_coins<<endl;
    fout.close();
    
}



  

}; // End class Lasso

#endif

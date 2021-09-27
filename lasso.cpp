#include <simplecpp>
#include <string>
#include "MovingObject.h"
#include "lasso.h"
#include "coin.h"
#include <ctime>
#include <cstdlib>



using namespace simplecpp;

void Lasso::draw_lasso_band() {
  double len = (release_speed/MAX_RELEASE_SPEED)*LASSO_BAND_LENGTH;
  double arad = release_angle_deg*PI/180.0;
  double xlen = len*cos(arad);
  double ylen = len*sin(arad);
  lasso_band.reset(lasso_start_x, lasso_start_y, (lasso_start_x-xlen), (lasso_start_y+ylen));
  lasso_band.setThickness(LASSO_THICKNESS);
} // End Lasso::draw_lasso_band()

void Lasso::initLasso() {
  lasso_start_x = (PLAY_X_START+LASSO_X_OFFSET);
  lasso_start_y = (PLAY_Y_HEIGHT-LASSO_Y_HEIGHT);
  lasso_circle.reset(lasso_start_x, lasso_start_y, LASSO_SIZE);
  lasso_circle.setColor(COLOR("red"));
  lasso_circle.setFill(true);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE/2);
  lasso_loop.setColor(COLOR("brown"));
  lasso_loop.setFill(true);
  addPart(&lasso_circle);
  addPart(&lasso_loop);
  lasso_looped = false;
  the_coin = NULL;
  num_coins = 0;
  yank_freq = 0;
  loop_freq = 0;
  lasso_radius=LASSO_RADIUS;

  lasso_line.reset(lasso_start_x, lasso_start_y, lasso_start_x, lasso_start_y);
  lasso_line.setColor(COLOR("brown"));

  lasso_band.setColor(COLOR("BlueViolet"));
  draw_lasso_band();

} // End Lasso::initLasso()

void Lasso::yank()
{
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE/2);
  lasso_loop.setFill(true);
  lasso_looped = false;
  yank_freq +=1 ;
  lasso_radius=LASSO_RADIUS;
} // End Lasso::yank()

void Lasso::loopit() {
  loop_freq +=1;
  if(lasso_looped) { return; } /* Already looped */
  lasso_loop.reset(getXPos(), getYPos(), lasso_radius);
  lasso_loop.setFill(false);
  lasso_looped = true;  
} // End Lasso::loopit()

void Lasso::addAngle(double angle_deg) {
  release_angle_deg += angle_deg;
  if(release_angle_deg < MIN_RELEASE_ANGLE_DEG) { release_angle_deg = MIN_RELEASE_ANGLE_DEG; }
  if(release_angle_deg > MAX_RELEASE_ANGLE_DEG) { release_angle_deg = MAX_RELEASE_ANGLE_DEG; }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addAngle()

void Lasso::addSpeed(double speed) {
  release_speed += speed;
  if(release_speed < MIN_RELEASE_SPEED) { release_speed = MIN_RELEASE_SPEED; }
  if(release_speed > MAX_RELEASE_SPEED) { release_speed = MAX_RELEASE_SPEED; }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addSpeed()

void Lasso::nextStep(double stepTime) {
  draw_lasso_band();
  MovingObject::nextStep(stepTime);
  if(getYPos() > PLAY_Y_HEIGHT) { yank(); }
  lasso_line.reset(lasso_start_x, lasso_start_y, getXPos(), getYPos());
} // End Lasso::nextStep()


void Lasso::check_for_coin(Coin *coinPtr, double* cT, bool *g, int v0, int v, int d0, int d) {
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double coin_x = coinPtr->getXPos();
  double coin_y = coinPtr->getYPos();
  double xdiff = (lasso_x - coin_x);
  double ydiff = (lasso_y - coin_y);
  double distance = sqrt((xdiff*xdiff)+(ydiff*ydiff));
  if(distance <= lasso_radius) {
    the_coin = coinPtr;
    the_coin->getAttachedTo(this);
  }
  if(the_coin != NULL) {
    if((the_coin->cat)=='c'){
        num_coins++;
        Text Catch(lasso_x+20,lasso_y-20,"+1"); /* To denote that the coin(s) have been captured */
        Catch.setColor(COLOR(0,255,0));
    }
    else if((the_coin->cat)=='b'){
        num_coins-=1;
        Text Catch(lasso_x+20,lasso_y-20,"-1"); /* To denote that a bomb has been captured */
        Catch.setColor(COLOR(255,0,0));
    }
    else if((the_coin->cat)=='s'){
        MovingObject::add_vx(75);
        MovingObject::add_vy(-200);
        Text Catch(lasso_x+20,lasso_y-20,"+v"); /* To denote that a speed up coin has been captured  */  
    }
    else if((the_coin->cat)=='t'){
        (*cT)-=15;
        Text Catch(lasso_x+20,lasso_y-20,"+t"); /* To denote that a time coin has been captured */
        Catch.setColor(COLOR(0,0,255));
        
    }
    else if((the_coin->cat)=='m'){ 
        (*g)=1;
        Text Catch(lasso_x+20,lasso_y-20,"+M"); /* To denote that a magnet coin has been captured*/
    }
    else if((the_coin->cat)=='f'){
        MovingObject::set_vx(0);
        MovingObject::set_vy(0);
        MovingObject::set_ax(0);
        MovingObject::set_ay(0);
        Text Catch(lasso_x+20,lasso_y-20,"F"); /* To denote that a freeze coin has been captured */
    }
    else if((the_coin->cat)=='y'){
        yank_freq-=1;
        Text Catch(lasso_x+20,lasso_y-20,"Y");/* To denote that a yank coin has been captured */
    }
    else if((the_coin->cat)=='l'){
        loop_freq-=1;
        Text Catch(lasso_x+20,lasso_y-20,"L");/* To denote that a loop coin has been captured */
       
    }
    else if((the_coin->cat)=='e'){
        Text Catch(lasso_x+20,lasso_y-20,"E");/* To denote that an enlarge coin has been captured */
        lasso_radius *=2;
        lasso_loop.reset(getXPos(), getYPos(), lasso_radius);
    }
    else if((the_coin->cat)=='r'){        /* The random coin */
        srand(time(0));
        int x=rand()%9;
        if(x==0)
        {
            num_coins++;
            Text Catch(lasso_x+20,lasso_y-20,"+1"); 
            Catch.setColor(COLOR(0,255,0));
        }
        else if(x==1)
        {
            num_coins-=1;
            Text Catch(lasso_x+20,lasso_y-20,"-1");
            Catch.setColor(COLOR(255,0,0));
        }
        else if(x==2)
        {
            MovingObject::add_vx(75);
            MovingObject::add_vy(-200);
            Text Catch(lasso_x+20,lasso_y-20,"+v"); 
        }
        else if(x==3)
        {
            (*cT)-=15;
            Text Catch(lasso_x+20,lasso_y-20,"+t"); 
            Catch.setColor(COLOR(0,0,255));
        }
        else if(x==4)
        {
            (*g)=1;
            Text Catch(lasso_x+20,lasso_y-20,"+M");
        }
        else if(x==5)
        {
            MovingObject::set_vx(0);
            MovingObject::set_vy(0);
            MovingObject::set_ax(0);
            MovingObject::set_ay(0);    
        }
        else if(x==6)
        {
            Text Catch(lasso_x+20,lasso_y-20,"E");
            (lasso_radius)*=2;
            lasso_loop.reset(getXPos(), getYPos(), lasso_radius);       
        }
        else if(x==7)
        {
            yank_freq-=1;
            Text Catch(lasso_x+20,lasso_y-20,"Y");
            
        }
        else if(x==8)
        {
            loop_freq-=1;
            Text Catch(lasso_x+20,lasso_y-20,"L");
        }
    } 
    
    the_coin->resetCoin(v0,v,d0,d);
  }
  
  the_coin=NULL; /*Important to refresh or else the counting will be incorrect after the first time a coin is captured*/
}



#include "coin.h"
#include "lasso.h"
#include "MovingObject.h"
#include <simplecpp>
#include <cstdlib>
#include <ctime>

void Coin::initCoin() {
  coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);
  if(cat=='c'){
    coin_circle.setColor(COLOR("gold"));
  }
  else if(cat=='b'){
    coin_circle.setColor(COLOR("black"));
  }
  else if(cat=='m'){
    coin_circle.setColor(COLOR("silver"));
  }
  else if(cat=='s'){
    coin_circle.setColor(COLOR("red"));
  }
  else if(cat=='t'){
    coin_circle.setColor(COLOR("blue"));
  }
  else if(cat=='f'){
    coin_circle.setColor(COLOR("cyan"));
  }
  else if(cat=='e'){
    coin_circle.setColor(COLOR("green"));
  }
  else if(cat=='y'){
    coin_circle.setColor(COLOR("magenta"));
  }
  else if(cat=='l'){
    coin_circle.setColor(COLOR("brown"));
  }
  else if(cat=='r'){
    coin_circle.setColor(COLOR("purple"));
  }
  
  coin_circle.setFill(true);
  addPart(&coin_circle);
}

void Coin::resetCoin(int v0,int v,int d0,int d) {
  srand(time(0));
  double coin_speed = double(v0+rand()%v);
  double coin_angle_deg = (d0+rand()%d);
  coin_ax = 0;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
}

void Coin::dynamics(double sT,double cT,double lcje, double CG, bool* g, double lx, double ly, int v0, int v, int d0, int d)
{ 
    /* lcje is last_coin_jump_end , sT is stepTime , cT is currTime*/

    if((!isPaused())&&(*g==1))
    {
        
           double cx=getXPos();
           double cy=getYPos();
           double r=sqrt(pow((lx-cx),2)+pow((ly-cy),2));
    
           MovingObject::set_vx(1000*(lx-cx)/r);
           MovingObject::set_vy(1000*(ly-cy)/r);
        
        
    }
    
    if(isPaused())
    {
      if((cT) >= CG)
      {
	        unpause();
            
      }
    }

    

    nextStep(sT);
    
    if(getYPos() > PLAY_Y_HEIGHT) /* To make sure that coin doesnt go beyond the ground level and that coin is reset */
    {
      resetCoin(v0,v,d0,d);
      lcje = cT;
    }
}



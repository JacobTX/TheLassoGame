#include <simplecpp>
#include <string>
#include "MovingObject.h"
#include "lasso.h"
#include "coin.h"
#include "Control.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include "Levels.h"

using namespace simplecpp;

void maindish(string name, int v0, int v, int d0, int d)
{
  /* New window for game */
  initCanvas("Lasso", WINDOW_X, WINDOW_Y);

  Rectangle RW(500,400,1000,800); /*Refresh window*/
  RW.setColor(COLOR(255,255,255));
  RW.setFill(True);

  /* Game clock */
  float runTime = 60; /* if -ve then it means infinite */ /* Total game duration */
  float stepTime=STEP_TIME;
  double currTime = 0;
  int stepCount = 0;
  
  /* After every COIN_GAP sec, make the coin jump */
  double last_coin_jump_end = 0;



  /* Game settings and framework*/

  /* Lasso */
  double release_speed = INIT_RELEASE_SPEED; // m/s

  double release_angle_deg = INIT_RELEASE_ANGLE_DEG;   // degrees
  double lasso_ax = 0;
  double lasso_ay = LASSO_G;
  bool paused = true;
  bool rtheta = true;
  /*bool g=0;*//* If 1, then coins start gravitating towards it */

  Lasso lasso(release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);



  /* Fixed lines, info text */

  int x=BASE; /* Variable to control the relative orientation of the text wrt horizontal line */
  Line b1(0, x, 1000, x);          
  b1.setColor(COLOR("blue"));
  Line b2(100, 0, 100, 1000);
  b2.setColor(COLOR("blue"));
  string msg("Cmd: _");
  Text charPressed(150, x+80, msg);
  char coinScoreStr[256];
  sprintf(coinScoreStr, "Score: %d", lasso.getNumCoins());
  
  Text coinScore(150, x+110, coinScoreStr);
  Text name_hold(150,x+20,"Name: "); /* The word Name */
  Text player_name(150+textWidth("Name: ")+textWidth(name)/2,x+20,name); /* The player username beside Name */

  Rectangle LY(300,100,300,textHeight());
  Text LYank(300,100,"Remaining lasso yanks: ");
  Rectangle LL(300,200,300,textHeight());
  Text LLoop(300,200,"Remaining lasso loops: ");
   


 
  /* Coin(s) */
  
  paused = true; rtheta = true;
  double coin_ax = 0;
  double coin_ay = COIN_G;


  char cat_list[]={'c','b','s','t','m','f','e','y','l','r'}; /* Array of coin types */

  srand(time(0));

   Coin coin[9]={{double(v0+rand()%v),double(d0+rand()%d), coin_ax, coin_ay, paused, rtheta,'c',(500.0+rand()%400),650},
         {double(v0+rand()%v),double(d0+rand()%d), coin_ax, coin_ay, paused, rtheta,cat_list[rand()%10],(500.0+rand()%400),650},
         {double(v0+rand()%v),double(d0+rand()%d), coin_ax, coin_ay, paused, rtheta,cat_list[rand()%10],(500.0+rand()%400),650},
         {double(v0+rand()%v),double(d0+rand()%d), coin_ax, coin_ay, paused, rtheta,cat_list[rand()%10],(500.0+rand()%400),650},
         {double(v0+rand()%v),double(d0+rand()%d), coin_ax, coin_ay, paused, rtheta,cat_list[rand()%10],(500.0+rand()%400),650},
         {double(v0+rand()%v),double(d0+rand()%d), coin_ax, coin_ay, paused, rtheta,cat_list[rand()%10],(500.0+rand()%400),650},
         {double(v0+rand()%v),double(d0+rand()%d), coin_ax, coin_ay, paused, rtheta,cat_list[rand()%10],(500.0+rand()%400),650},
         {double(v0+rand()%v),double(d0+rand()%d), coin_ax, coin_ay, paused, rtheta,cat_list[rand()%10],(500.0+rand()%400),650},
         {double(v0+rand()%v),double(d0+rand()%d), coin_ax, coin_ay, paused, rtheta,cat_list[rand()%10],(500.0+rand()%400),650}};

  /* Action */

   for(;;)
   {
    bool g=0;
    int yf=lasso.getYankFreq();
    int lf=lasso.getLoopFreq();

    /* Display remaining number of lasso yanks and lasso loops */
    
    
    Text numLYank(500,100,10-yf);
    Text numLLoop(500,200,20-lf);

    /* Display remaining time */
    Circle Clock(900,100,20);
    Text Ticking_Clock(900,100,int(runTime-currTime));
    if((runTime-currTime)<=4)
    {
        Ticking_Clock.setColor(COLOR(255,0,0));
    }


    /* If game duration ends */
    if(((runTime > 0) && (currTime > runTime))||(yf>=10)||(lf>=20))
    {
        Text Game_End(500,400,"Game Over");
        Text Coins_Cap(450,400+textHeight(),"Score: ");
        Text End_Score(460+textWidth("Score: ")/2,400+textHeight(),lasso.getNumCoins());
        Game_End.setColor(COLOR(255,0,0));
        End_Score.setColor(COLOR(0,0,255));
        lasso.store_score(name);
        wait(5);
        break;
    }

    /* Keyboard Commands from user */
    
    // When t is pressed, throw lasso
    // If lasso within range, make coin stick
    // When y is pressed, yank lasso
    // When l is pressed, loop lasso
    // When q is pressed, quit
    // When [ is pressed, release angle decreases
    // When ] is pressed, release angle increases
    // When - is pressed, release speed decreases
    // When = is pressed, release speed increases

    

    XEvent e;
    bool pendingEv = checkEvent(e);
    if(pendingEv)
    {
      
     
     /* Response when a certain key is pressed */     
          
              char c = charFromEvent(e);
              msg[msg.length()-1] = c;
              charPressed.setMessage(msg);
      
                if(c=='t'){
                    lasso.unpause();
                }
                else if(c=='y'){
                    lasso.yank();
                }
                else if(c=='l'){
                    lasso.loopit();
                    for(int i=0;i<9;i++)
                    {
	                    lasso.check_for_coin(&coin[i],&currTime,&g,v0,v,d0,d);
                    }
                }
                else if(c=='['){
                    if(lasso.isPaused()) { lasso.addAngle(-RELEASE_ANGLE_STEP_DEG);	}
                }
                else if(c==']'){
                    if(lasso.isPaused()) { lasso.addAngle(+RELEASE_ANGLE_STEP_DEG); }
                }
                else if(c=='-'){
                    if(lasso.isPaused()) { lasso.addSpeed(-RELEASE_SPEED_STEP); }
                }
                else if(c=='='){
                    if(lasso.isPaused()) { lasso.addSpeed(+RELEASE_SPEED_STEP); }    
                }
                else if(c=='q'){
                        lasso.store_score(name);
                        break;
                }
        
     
      

    }
    
    
    lasso.nextStep(stepTime);

    /* Object dynamics */
    srand(time(0));
    for(int i=0;i<9;i++)
    {
        coin[i].dynamics(stepTime,currTime,last_coin_jump_end,rand()%15,&g,lasso.getXPos(),lasso.getYPos(),v0,v,d0,d);
    }


    
    /* Coins collected and time passed */

    sprintf(coinScoreStr, "Score: %d", lasso.getNumCoins());
    
    coinScore.setMessage(coinScoreStr);
    
    stepCount++;
    currTime+=stepTime;
    wait(stepTime);
    
    

   } // End for(;;)

   
        

} // End maindish












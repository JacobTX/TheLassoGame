#include <simplecpp>
#include "Control.h"



void help_sec(){
        /*For refreshment of the window*/
        
        Rectangle RW(500,400,1000,800);
        RW.setColor(COLOR(255,255,255));
        RW.setFill(True);

        Text In[50]; /* Array to store the text */
        double H=textHeight();

        
        In[0].reset(500,20,"Instructions"); /*Title*/

        In[1].reset(500,50,"Main controls");
        In[2].reset(500,100+0*H,"t :- throw lasso");
        In[3].reset(500,100+1*H,"y :- yank lasso");
        In[4].reset(500,100+2*H,"l :- loop it");
        In[5].reset(500,100+3*H,"q :- quit game");
        In[6].reset(500,100+4*H,"[ :- decrease release angle");
        In[7].reset(500,100+5*H,"] :- increase release angle");
        In[8].reset(500,100+6*H,"- :- decrease release speed");
        In[9].reset(500,100+7*H,"= :- increase release speed");

        In[10].reset(500,330,"Coin types");

        In[11].reset(200,370+0*H,"Normal coin");In[21].reset(600,370+0*H,"Adds one point to the score (+1)");
        In[12].reset(200,370+1*H,"Bomb coin");In[22].reset(600,370+1*H,"Deducts one point from the score (-1)");
        In[13].reset(200,370+2*H,"Speed coin");In[23].reset(600,370+2*H,"Provides speed boost in x and y direction (+v)");
        In[14].reset(200,370+3*H,"Time coin");In[24].reset(600,370+3*H,"Adds 15 time units to the remaining time (+t)");
        In[15].reset(200,370+4*H,"Magnet coin");In[25].reset(600,370+4*H,"Makes the lasso draw the surrounding coins (+M)");
        In[16].reset(200,370+5*H,"Freeze coin");In[26].reset(600,370+5*H," Freezes the lasso (F)");
        In[17].reset(200,370+6*H,"Enlarge coin");In[27].reset(600,370+6*H,"Increases the radius of the lasso loop (E)");
        In[18].reset(200,370+7*H,"Yank coin");In[28].reset(600,370+7*H,"Increases the remaining lasso yanks by one (Y)");
        In[19].reset(200,370+8*H,"Loop coin");In[29].reset(600,370+8*H,"Increases the remaining lasso loops by one (L)");
        In[20].reset(200,370+9*H,"Random coin");In[30].reset(600,370+9*H,"Randomly acts like  one of the other coin types.");

        In[11].setColor(COLOR("gold"));
        In[12].setColor(COLOR("black"));
        In[13].setColor(COLOR("red"));
        In[14].setColor(COLOR("blue"));
        In[15].setColor(COLOR("silver"));
        In[16].setColor(COLOR("cyan"));
        In[17].setColor(COLOR("green"));
        In[18].setColor(COLOR("magenta"));
        In[19].setColor(COLOR("brown"));
        In[20].setColor(COLOR("purple"));                    
                     

                          
                          

                          
                          
       
        Rectangle Quit_help(500,700,200,100); /*Quit button*/
        Text Quit_h(500,700,"Quit");

        /* To exit the help section */
        while (true){
            int t=getClick();
            if (Click(Quit_help,t)){
                break;
            }
        }
        
    
}
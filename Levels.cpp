#include <simplecpp>
#include "Control.h"
#include "main.h"


void levels(string name){
    /*For refreshment of the window*/
        
    Rectangle RW(500,400,1000,800);
    RW.setColor(COLOR(255,255,255));
    RW.setFill(True);

    Circle L(500,200,400);
    L.setColor(COLOR("red"));
    L.setFill(true);
    Circle L2(500,200,200);
    L2.setColor(COLOR("brown"));
    L2.setFill(true);

    Rectangle Quit_help(500,700,200,100); /*Quit button*/
    Text Quit_h(500,700,"Quit");

    
    Rectangle Bu[7];
    double H=2*textHeight();

    Bu[1].reset(500,150,200,H);
    Bu[1].setColor(COLOR(255,255,0));
    Bu[1].setFill(true);

    Bu[2].reset(300,400+1*H,200,H);
    Bu[2].setColor(COLOR(0,255,255));
    Bu[2].setFill(true);

    Bu[3].reset(700,400+1*H,200,H);
    Bu[3].setColor(COLOR(255,0,255));
    Bu[3].setFill(true);

    Text Lvl[7];
       
    Lvl[0].reset(500,20,"Modes"); /* Title */
    Lvl[1].reset(500,150,"Cluster");
    Lvl[2].reset(300,400+1*H,"Scatter");
    Lvl[3].reset(700,400+1*H,"Explode");
    
    
   
    

        
    /* To exit the help section */
    while (true)
    {
       int t=getClick();
       if (Click(Bu[1],t))
       {
            
            maindish(name,50,50,80,10);  
       }
       if (Click(Bu[2],t))
       {
            
            maindish(name,50,100,80,50);  
       }
       if (Click(Bu[3],t))
       {
            
            maindish(name,50,200,80,90);  
       }
       if (Click(Quit_help,t))
       {
                break;
       }

    }

}
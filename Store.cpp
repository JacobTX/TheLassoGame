#include <simplecpp>
#include <fstream>
#include "Control.h"
#include <string>
#include <cstdlib>
#include <ctime>

void view(string name)
{
    /*For refreshment of the window*/
    Rectangle RW(500,400,1000,800);
    RW.setColor(COLOR(255,255,255));
    RW.setFill(True);
    Circle L(500,200,400);
    L.setColor(COLOR("gold"));
    L.setFill(true);
    Circle L2(500,200,200);
    L2.setColor(COLOR("silver"));
    L2.setFill(true);

    Text Ach(400,50,"Statistics:"); /*Title*/
    Text User(400+textWidth("Statistics")+textWidth(name)/2,50,name);/*Username*/

    Rectangle Quit_help(500,700,200,100); /*Quit button*/
    Text Quit_h(500,700,"Quit");

    Text l[50]; /*Labels*/
    

    Text n[50]; /*Actual data*/
    int H=textHeight();

    /* Code to read the stored data regarding score,etc */

    ifstream fin("records.dat"); 
    if (!fin.is_open()){
            exit(EXIT_FAILURE);
    }

    string word; /*To store the currently read data*/
    string day,month,date,timeinst,year; /* To read the date and time */
    string timeinfo[10]; /* Array store the currently read date and time */

    long int Max=0,Min=pow(2,31)-1,score=0,total=0,freq=0;
   

    /* For extracting total score and highest score of the current user*/
   
    while(!fin.eof())
    {
        fin>>word>>day>>month>>date>>timeinst>>year>>score;
        if(word==name)
        {
            total+=score;
            freq+=1;
            if(score>Max)
            {
                Max=score;
                timeinfo[0]=day;
                timeinfo[1]=month;
                timeinfo[2]=date;
                timeinfo[3]=timeinst;
                timeinfo[4]=year;
            }
            if(score<Min)
            {
                Min=score;
                timeinfo[5]=day;
                timeinfo[6]=month;
                timeinfo[7]=date;
                timeinfo[8]=timeinst;
                timeinfo[9]=year;
            }
        }
    }

    fin.close();

    
    /* Display total score */
    l[0].reset(200,100,"Total score: ");
    if(freq>1)
    {
        n[0].reset(350,100,total-score);
    }
    else
    {
        n[0].reset(350,100,"NA");    
    }

    /* Display average score */
    l[1].reset(200,150,"Average score: ");
    if(freq>1)
    {
        n[1].reset(350,150,float(total-score)/(freq-1));
    }
    else
    {
        n[1].reset(350,150,"NA");        
    }

    /* Display maximum score and time of scoring */
    l[2].reset(200,200,"Maximum Score: ");
    if(freq>1)
    {
        n[2].reset(350,200+0*H,Max);
    }
    else
    {
        n[2].reset(350,200+0*H,"NA");
    }
    n[3].reset(400,200,"("+timeinfo[0]);
    n[4].reset(450,200,timeinfo[1]);
    n[5].reset(490,200,timeinfo[2]);
    n[6].reset(550,200,timeinfo[4]);
    n[7].reset(650,200,timeinfo[3]+")");

    /* Display minimum score and time of scoring */
    l[3].reset(200,250,"Minimum score: ");
    if(freq>1)
    {
        n[8].reset(350,250,Min);
    }
    else
    {
        n[8].reset(350,250,"NA");        
    }
    n[9].reset(400,250,"("+timeinfo[5]);
    n[10].reset(450,250,timeinfo[6]);
    n[11].reset(490,250,timeinfo[7]);
    n[12].reset(550,250,timeinfo[9]);
    n[13].reset(650,250,timeinfo[8]+")");

    
    

    /* To exit the help section */
    while (true)
    {
       int t=getClick();
       if (Click(Quit_help,t)){
                break;
            }
    }

   



    
      
}


  

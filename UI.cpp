# include <simplecpp>
# include <string>
# include "Help.h"
# include "Control.h"
# include "main.h"
# include "lasso.h"
# include "Store.h"
# include "Levels.h"


main_program{

    /* Graphical components of the interface */
    initCanvas("Interface",1000,800);
    Circle L(500,200,400);
    L.setColor(COLOR("red"));
    L.setFill(true);
    Circle L2(500,200,200);
    L2.setColor(COLOR("brown"));
    L2.setFill(true);
    Text Intro(500,200,"Welcome to The Lasso Game!");
    Intro.setColor(COLOR("yellow"));
    Text Name(500,250,"Enter username in terminal to initiate: ");

    /* Coins on the sides of the home interface */

    Circle NCoin(100,100,50);
    NCoin.setColor(COLOR("gold"));
    NCoin.setFill(true);

    Circle BCoin(900,100,50);
    BCoin.setColor(COLOR("black"));
    BCoin.setFill(true);

    Circle MCoin(100,250,50);
    MCoin.setColor(COLOR("silver"));
    MCoin.setFill(true);

    Circle TCoin(900,250,50);
    TCoin.setColor(COLOR("blue"));
    TCoin.setFill(true);

    Circle FCoin(100,400,50);
    FCoin.setColor(COLOR("cyan"));
    FCoin.setFill(true);

    Circle RCoin(900,400,50);
    RCoin.setColor(COLOR("purple"));
    RCoin.setFill(true);

    Circle SCoin(100,550,50);
    SCoin.setColor(COLOR("red"));
    SCoin.setFill(true);

    Circle ECoin(900,550,50);
    ECoin.setColor(COLOR("green"));
    ECoin.setFill(true);

    Circle YCoin(100,700,50);
    YCoin.setColor(COLOR("magenta"));
    YCoin.setFill(true);

    Circle LCoin(900,700,50);
    LCoin.setColor(COLOR("brown"));
    LCoin.setFill(true);

    /*Play button */
    Rectangle Rp(300,500,200,100);
    Rp.setColor(COLOR("yellow"));
    Rp.setFill(true);
    Text Play(300,500,"Play game");

    /* Info button*/
    Rectangle Ri(700,500,200,100);
    Ri.setColor(COLOR("yellow"));
    Ri.setFill(true);
    Text Help(700,500,"Help");
   
     /* Quit button */
    Rectangle Rq(300,700,200,100);
    Rq.setColor(COLOR("yellow"));
    Rq.setFill(true);
    Text Quit(300,700,"Quit");

     /* Achievements button */
    Rectangle Ra(700,700,200,100);
    Ra.setColor(COLOR("yellow"));
    Ra.setFill(true);
    Text Stats(700,700,"Statistics");

    /* Enter username and display it on log in interface*/
    string name;
    cout<<"Enter username in terminal to initiate: ";
    getline(cin,name);
    while(true){
        if(name.find(" ")!=-1){
            cout<<"Username must be a single word without any spaces"<<endl;
            cout<<"Enter username in terminal to initiate: ";
            getline(cin,name);       
        }
        else{
            break;
        }
    }
    
    Rectangle Rt(500,250,textWidth("Enter username(single word) in terminal to initiate: "),textHeight());
    Rt.setColor(COLOR(255,255,255));
    Rt.setFill(true);
    Text Name1(500,250,name); //Username


    //Different options like help, play, quit

    while(true)
    {
        int s=getClick();
        if (Click(Rp,s))
        {
            levels(name); /*To play the game*/
        }
        else if (Click(Ri,s))
        {
            help_sec();    /*For help and instructions*/
        }
        else if (Click(Rq,s)) /* To quit the application only after logging in */
        {   
            exit(0);
        }
        else if (Click(Ra,s))
        {
            view(name);  /* To view the performance statistics */              
        }
        

    }

    
}

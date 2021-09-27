#include <simplecpp>

bool Click(Rectangle r,int s){
    /* To simplify the process of checking whether a button has been clicked */

    float xc=r.getX();
    float yc=r.getY(); 
    float l=r.getWidth();
    float b=r.getHeight();

    
    float x=s/65536, y=s%65536;
    if((x>(xc-l/2))&&(x<(xc+l/2))&&(y>(yc-b/2))&&(y<(yc+b/2))) /*Condition whether click within button*/
    {
        return true;
    }
    else{
        return false;
    }
}
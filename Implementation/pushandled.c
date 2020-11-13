#include "pushandled.h"

int pushbutton()
{
    FILE *p=NULL;
    int pushvalue=0;
    //Connect led to pin 23 of P9 expansion
    p = fopen("/sys/class/gpio/gpio49/direction","w"); 
    fprintf(p,"in"); //Setting the direction of the pin as input
    fclose(p); 
    p = fopen("/sys/class/gpio/gpio49/value","r"); 
    fscanf(p,"%d",&pushvalue);
    return pushvalue;
}
void ledon()
{
    FILE *p=NULL;
    //Connect led to pin 30 of P9 expansion
    p = fopen("/sys/class/gpio/gpio112/direction","w"); 
    fprintf(p,"out"); //Setting the direction of the pin as output
    fclose(p); 
    p = fopen("/sys/class/gpio/gpio112/value","w"); 
    fprintf(p,"%d",1); //Setting the value of the pin as 1
    fclose(p);
}

void ledoff()
{
    FILE *p=NULL;
    //Connect led to pin 30 of P9 expansion
    p = fopen("/sys/class/gpio/gpio112/direction","w"); 
    fprintf(p,"out"); //Setting the direction of the pin as output
    fclose(p); 
    p = fopen("/sys/class/gpio/gpio112/value","w"); 
    fprintf(p,"%d",0); //Setting the value of the pin as 0
    fclose(p);
}

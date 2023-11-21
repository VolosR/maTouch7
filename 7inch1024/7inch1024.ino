#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "Matouch7.h"
#include "midleFont.h"
#include "smallFont.h"

 #define SCREEN_HD
//#define SCREEN_NORMAL

#ifdef SCREEN_HD
#define SCREEN_W 1024
#define SCREEN_H 600
#endif

#ifdef SCREEN_NORMAL
#define SCREEN_W 800
#define SCREEN_H 480
#endif

unsigned short taskCls[4]={0x2DD3,0x2D17,0xA157,0xB945};
unsigned short blockColor[2]={0x2945,0x8C71};
unsigned short grays[13];

LGFX lcd;
LGFX_Sprite sprite(&lcd);

float fps=0;
unsigned long st=0;
unsigned long en=0;

int32_t x, y;
int32_t xp, yp;
int32_t xs, ys;

int ballX=30;
int ballY=100;

int sW=282;
int sY=500;

int iX=4;
int iY=4;

String tasks[10]={"TRASH","DISHES","VACUMING","DUSTING","FLORS","GROCERIES","BATHROOM","LOUNDRY","IRONING","WINDOWS/MIRRORS"};
String days[8]={"MON","TUE","WED","THU","FRI","SAT","SUN","OTH"};
bool taskFinished[10][7]={0};
int scoreDays[8];
int segmentDays[8];
int mmax=0;
int other[3]={0};
bool press=0;
int deb=0;
int score=0;
int scoreW=0;
int scoreO=0;
int brightnes[5]={40,80,100,120,140};
int b=1;

void setup(void)
{
   
    lcd.init();
    lcd.setRotation(1);
    lcd.setBrightness(brightnes[b]);
    lcd.setSwapBytes(1);
    lcd.fillScreen(TFT_BLACK);
    sprite.createSprite(282,500);
   
     int co=220;
     for(int i=0;i<13;i++)
     {
     grays[i]=lcd.color565(co, co, co);
     co=co-20;
     }

  
    draw(1);
    draw(2);
    draw(0);
}



void draw(int s)

{ 
  sprite.fillSprite(TFT_BLACK);

if(s==0){

  sprite.fillRoundRect(0,20,70,70,4,taskCls[0]);
  sprite.fillRoundRect(0,100,70,70,4,taskCls[0]);
  sprite.fillRoundRect(0,180,70,70,4,taskCls[1]);
  sprite.fillRoundRect(0,260,70,70,4,taskCls[1]);
  sprite.fillRoundRect(0,340,70,70,4,taskCls[2]);
  sprite.fillRoundRect(0,420,70,70,4,taskCls[2]);
  
  sprite.fillRect(0,0,282,4,grays[9]);
  sprite.fillRect(270,80,8,86,taskCls[0]);
  sprite.fillRect(270,172,8,132,taskCls[1]);
  sprite.fillRect(270,309,8,86,taskCls[2]);
  sprite.fillRect(270,401,8,86,taskCls[3]);

  sprite.loadFont(smallFont);
  sprite.setTextDatum(textdatum_t::middle_right); 
  sprite.setTextColor(grays[1],TFT_BLACK);
  sprite.drawString("OTHER TASKS",170,30);
  sprite.setTextColor(grays[3],TFT_BLACK);
  for(int i=0;i<9;i++)
  sprite.drawString(tasks[i],264,100+(i*46));
    
    sprite.setTextColor(grays[10],taskCls[0]);
    sprite.setTextDatum(textdatum_t::middle_center); 
    sprite.drawString("EASY",35,32);
    sprite.setTextColor(grays[9],taskCls[2]);
    sprite.drawString("HARD",35,352);
    sprite.setTextColor(grays[9],taskCls[1]);
     sprite.drawString("NORMAL",35,192);
    sprite.unloadFont();


  sprite.loadFont(midleFont);
  sprite.setTextColor(grays[1],TFT_BLACK);
  for(int i=0;i<3;i++)
  sprite.drawString(String(other[i]),120,96+(i*160));
  sprite.unloadFont();

   
  for(int i=0;i<6;i++){
  sprite.fillRect(70,55+(i*80),50,2,grays[4]);
  sprite.fillRect(25,55+(i*80),20,3,grays[10]);
  if(i%2==0){
  sprite.drawLine(120,55+(i*80),120,75+(i*80),grays[4]);
  sprite.fillRect(34,47+(i*80),3,20,grays[10]);
  }
  else
  sprite.drawLine(120,55+(i*80),120,35+(i*80),grays[4]);}

  
  sprite.pushSprite(10,10);}

if(s==1)
  {
  sprite.loadFont(midleFont);
  sprite.setTextDatum(textdatum_t::middle_center);
  sprite.setTextColor(grays[0],TFT_BLACK);
  sprite.drawString("Household tasks",110,20);
  sprite.unloadFont();

  sprite.loadFont(smallFont);
  
  sprite.setTextColor(grays[4],TFT_BLACK);
  for(int i=0;i<7;i++){
  sprite.drawString(days[i],20+(i*40),56);
  sprite.fillRect(6+(i*40),70,28,4,grays[3]);
  }

 for(int i=0;i<9;i++)
  {
    sprite.drawLine(0,80+(i*40)+(i*6),280,80+(i*40)+(i*6),grays[3]);
    sprite.drawLine(0,120+(i*40)+(i*6),280,120+(i*40)+(i*6),grays[3]);
 for(int j=0;j<7;j++)
 {
   sprite.drawLine(j*40,80+(i*40)+(i*6),j*40,120+(i*40)+(i*6),grays[3]);
   sprite.drawLine(j*40+40,80+(i*40)+(i*6),j*40+40,120+(i*40)+(i*6),grays[3]);
   sprite.fillRect((j*40)+6,80+(i*40)+6+(i*6),28,28,blockColor[taskFinished[i][j]]);
 }
  }
  
  sprite.unloadFont();
  sprite.pushSprite(300,10);
  }   

  if(s==2)
  {
 
  sprite.loadFont(midleFont);
  sprite.setTextColor(grays[0],TFT_BLACK);
  sprite.setTextDatum(textdatum_t::middle_left);
  sprite.drawString("SCORE: "+String(score),0,18);
  sprite.drawString("AVERAGE: "+String(score/7),0,292);
  sprite.unloadFont();
    
    sprite.loadFont(smallFont);
    sprite.setTextColor(grays[2],TFT_BLACK);
    sprite.drawString("HOUSEHOLD TASKS: "+String(scoreW),0,50);
    sprite.drawString("OTHER TASKS: "+String(scoreO),0,256);

    sprite.setTextColor(grays[4],TFT_BLACK);
    sprite.setTextDatum(textdatum_t::middle_center);

  for(int i=0;i<6;i++)
  sprite.drawLine(0,80+(i*20),280,80+(i*20),grays[8]);
  for(int i=0;i<14;i++)
  sprite.drawLine(20+(i*20),80,20+(i*20),200,grays[8]);

  for(int i=0;i<7;i++){
  sprite.drawString(days[i],20+(i*40),220);
  sprite.fillRect(10+(i*40),200-segmentDays[i],20,segmentDays[i],grays[4]);
  }

  sprite.drawLine(0,80,0,200,grays[2]);
  sprite.drawLine(0,200,280,200,grays[2]);

  for(int i=0;i<4;i++)
  {
    sprite.fillRoundRect(0,320+(i*30),20,20,1,taskCls[i]);
    sprite.drawString("X"+String(i+1),34,330+(i*30));
  }



  sprite.fillRoundRect(0,440,135,40,4,taskCls[2]);
  sprite.fillRoundRect(145,440,135,40,4,taskCls[3]);
 

  sprite.setTextColor(grays[12],taskCls[2]);
  sprite.drawString("SAVE",67,460);
  sprite.setTextColor(grays[12],taskCls[3]);
  sprite.drawString("RESET",212,460);
  sprite.unloadFont();

  sprite.pushSprite(10,520);
  }  
    if(s==3)
  {
    sprite.fillCircle(ballX,ballY,5,taskCls[1]);
    sprite.drawBezier(0,150,ballX,ballY-20,280,150,grays[7]);
    sprite.drawBezier(0,200,ballX,ballY-20,280,200,taskCls[1]);
    sprite.drawBezier(0,250,ballX,ballY,280,250,taskCls[2]);
    sprite.drawBezier(0,300,ballX,ballY+20,280,300,taskCls[1]);
    sprite.drawBezier(0,350,ballX,ballY+20,280,350,grays[7]);

    sprite.drawBezier(80,0,ballX,ballY,80,500,taskCls[1]);
    sprite.drawBezier(120,0,ballX,ballY,120,500,taskCls[0]);
    sprite.drawBezier(160,0,ballX,ballY,160,500,taskCls[1]);

    sprite.setTextColor(grays[3],TFT_BLACK);
    sprite.drawString("VOLOS PROJECTS 2023",200,490,2);
 
  sprite.pushSprite(310,520);
  } 
 
}

void reset()
{
  mmax=0;
  other[0]=0;
  other[1]=0;
  other[2]=0;
for(int i=0;i<9;i++)
for(int j=0;j<7;j++)
taskFinished[i][j]=0;
}

void checkScore()
{
 int value=0;
 score=0;
 scoreW=0;
 scoreO=0;;

 for(int i=0;i<8;i++)
 scoreDays[i]=0;
  
  for(int i=0;i<9;i++){
    if(i==0 || i==1) value=1;
    if(i==2 || i==3 || i==4) value=2;
    if(i==5 || i==6) value=3;
    if(i==7 || i==8) value=4;
      for(int j=0;j<7;j++)
      if(taskFinished[i][j])
      {
      scoreW=scoreW+value;
      scoreDays[j]=scoreDays[j]+value;
      }
  
      }
scoreO=other[0]+(other[1]*2)+(other[2]*3);      
score=scoreW+scoreO;


for(int i=0;i<7;i++)
if(scoreDays[i]>mmax) mmax=scoreDays[i];

for(int i=0;i<7;i++)
segmentDays[i]=map(scoreDays[i],0,mmax,0,120);
}


void loop(void)
{
   ballX=ballX+iX;
   ballY=ballY+iY;

   if(ballX<0 || ballX>280)
   iX=iX*-1;

    if(ballY<0-20|| ballY>500+20)
   iY=iY*-1;




if (lcd.getTouch(&x, &y)) {
xp=map(x,6,464,0,600);
yp=map(y,5,1020,0,1024);
if(xp>299 && yp>89 && yp<490 && xp<581)
{
  if(deb==0)
  {
    deb=1;
   xs=(xp-300)/40;
   ys=(yp-90)/46;
   taskFinished[ys][xs]=!taskFinished[ys][xs];
    press=1;
  }
}

 

  if(xp>10 && xp<80 && yp>30 && yp<80)
    {if(deb==0){deb=1; other[0]++; press=1;}}

  if(xp>10 && xp<80 && yp>110 && yp<180)
    {if(deb==0){deb=1; other[0]--; press=1;}}  

     if(xp>10 && xp<80 && yp>190 && yp<260)
    {if(deb==0){deb=1; other[1]++; press=1;}}

    if(xp>10 && xp<80 && yp>270 && yp<340)
    {if(deb==0){deb=1; other[1]--;press=1;}}  

     if(xp>10 && xp<80 && yp>350 && yp<420)
    {if(deb==0){deb=1; other[2]++; press=1;}}

    if(xp>10 && xp<80 && yp>430 && yp<500)
    {if(deb==0){deb=1; other[2]--;press=1;}}  

    if(xp>155 && xp<290 && yp>974 && yp<1024)
    {if(deb==0){deb=1; reset(); press=1;}} 

    if(xp>550 && xp<600 && yp>0 && yp<50)
    {if(deb==0){deb=1; b++; if(b==5) b=0;  lcd.setBrightness(brightnes[b]);}} 




}else deb=0;

 
 if(press){
 checkScore();
 draw(0);  
 draw(1);
 draw(2);
 }
 draw(3);

press=0;
}

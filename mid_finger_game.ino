#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);
#define sag_buton 8
#define ates_buton 9
#define sol_buton 10
int x_silah=10,x_ates=0,y_ates=0,x_orta_parmak=0;
int y_orta_parmak=0,orta_parmak_yon=1;
float orta_parmak_hiz=1;
int orta_parmak_sure=7,yon=44;
int hak=5,puan=0;
boolean basla=false;
void (* resetFunc) (void)=0;
static unsigned char PROGMEM orta_parmak[]= {
  B00010000,
  B00010000,
  B00010000,
  B00011000,
  B01111110,
  B01111111,
  B11111111,
  B11111111};
static unsigned char PROGMEM ates[]={
  B00000000,
  B00010000,
  B00111000,
  B01010100,
  B10010010,
  B00010000,
  B00010000,
  B00010000};
static unsigned char PROGMEM silah[]={
  B10000001,
  B01000010,
  B00100100,
  B01011010,
  B01011010,
  B00100100,
  B01000010,
  B10000001};
void setup()
{
  pinMode(sag_buton,INPUT);
  pinMode(sol_buton,INPUT);
  pinMode(ates_buton,INPUT);
  display.begin();
  display.setContrast(20);
  display.setTextSize(1);
  display.display();
  
}
void loop()
{
  display.clearDisplay();
  if(!basla)
  {
    
    for(int y=10; y<40; y+=10)
    {
    for(int i=10; i<80; i+=10) {
    display.drawBitmap(i,y,orta_parmak,8,8,1);
    display.display();
    delay(100);
    
  }
    }
    display.clearDisplay();
    display.setCursor(10,10);
    display.println("ORTA PARMAK");
    display.print("YAKALAR MISIN?");
    display.print("  *Atese Bas!*");
    display.display();
    delay(2000);
    while(digitalRead(ates_buton)==0);
    basla=true;
  }
  display.setCursor(0,0);
  display.println(puan);
  if(digitalRead(sol_buton)==1 && x_silah>0)  x_silah--;
  if(digitalRead(sag_buton)==1 && x_silah<76) x_silah++;
  if(digitalRead(ates_buton)==1 && y_ates==0)
  {
    x_ates=x_silah;
    y_ates=32;
    
  }
  if(y_ates>0)
  {
    display.drawBitmap(x_ates,y_ates,ates,8,8,1);
    y_ates--;
  }
  if(y_ates>0 && (y_orta_parmak >=y_ates && y_orta_parmak <=(y_ates+8))
  && (x_orta_parmak >= x_ates && x_orta_parmak <= (x_ates+4)))
  {
    puan += 50-y_ates;
    randomSeed(y_ates);
    x_orta_parmak=random(76);
    y_orta_parmak=0;
    y_ates=0;
    orta_parmak_hiz +=0.1;
    if(yon>2) yon -=1;
 }
x_orta_parmak += int(orta_parmak_hiz)*orta_parmak_yon;
 
 if(x_orta_parmak  >76  || x_orta_parmak <0 || random(yon)==1) orta_parmak_yon =orta_parmak_yon*-1;
 orta_parmak_sure--;
 if(orta_parmak_sure<1){y_orta_parmak++; orta_parmak_sure=8;}
 if(y_orta_parmak>48)  y_orta_parmak=0;
 if((y_orta_parmak >32 && (x_orta_parmak >=x_silah && x_orta_parmak <x_silah+8)) 
 || (y_orta_parmak >40)) { 
   hak--;
   if(hak==0)
   {
     display.clearDisplay();
     display.setCursor(10,10);
     display.println("   GIRDI MI ?");
     display.println(puan);
     display.display();
     delay(1500);
     while(digitalRead(ates_buton)==0);
      resetFunc();
   }
      y_orta_parmak=0;
      display.clearDisplay();
      display.setCursor(10,10);
      display.print("  Girenler:");
      display.println(hak);
      display.display();
      delay(1500);
}
  
  display.drawBitmap(x_orta_parmak,y_orta_parmak,orta_parmak,8,8,1);
  display.drawBitmap(x_silah,40,silah,8,8,1);
  display.display();
}






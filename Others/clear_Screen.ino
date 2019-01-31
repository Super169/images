// IMPORTANT: LCDWIKI_SPI LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.

//This program is a demo of clearing screen to display black,white,red,green,blue.

//when using the BREAKOUT BOARD only and using these hardware spi lines to the LCD,
//the SDA pin and SCK pin is defined by the system and can't be modified.
//if you don't need to control the LED pin,you can set it to 3.3V and set the pin definition to -1.
//other pins can be defined by youself,for example
//pin usage as follow:
//                 CS  DC/RS  RESET  SDI  SCK  LED    VCC     GND    
//ESP8266 D1 nimi  D1   D3     D2    D7   D5   D4   5V/3.3V   GND

//Remember to set the pins to suit your display module!
/********************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE 
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**********************************************************************************/
#include <SPI.h>

#define X_MAX_PIXEL 320
#define Y_MAX_PIXEL 480

#define LCD_CS  D1
#define LCD_RST D2
#define LCD_RS  D3


#define LCD_CS_SET (digitalWrite(LCD_CS,HIGH))
#define LCD_RST_SET (digitalWrite(LCD_RST,HIGH))
#define LCD_RS_SET (digitalWrite(LCD_RS,HIGH))


#define LCD_CS_CLR (digitalWrite(LCD_CS,LOW))
#define LCD_RST_CLR (digitalWrite(LCD_RST,LOW))
#define LCD_RS_CLR (digitalWrite(LCD_RS,LOW))


#define BLACK 0x0000
#define WHITE 0xFFFF
#define RED 0xF800
#define GREEN 0x07E0
#define BLUE  0x001F

void spi_init(void)
{
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV2); // 4 MHz (half speed)
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0); 
}

void spi_write(unsigned char data)
{  
  SPI.transfer(data);
}

void Lcd_WriteIndex(unsigned char index)
{
   LCD_CS_CLR;
   LCD_RS_CLR;
   spi_write(index);
   LCD_CS_SET;
}

void Lcd_WriteData(unsigned char data)
{
   LCD_CS_CLR;
   LCD_RS_SET;
   spi_write(data);
   LCD_CS_SET; 
}

void Lcd_SetRegion(unsigned int x_start,unsigned int y_start,unsigned int x_end,unsigned int y_end)
{    
  Lcd_WriteIndex(0x2a);
  Lcd_WriteData(x_start>>8);
  Lcd_WriteData(0x00FF&x_start);
  Lcd_WriteData(x_end>>8);
  Lcd_WriteData(0x00FF&x_end);

  Lcd_WriteIndex(0x2b);
  Lcd_WriteData(y_start>>8);
  Lcd_WriteData(0x00FF&y_start);
  Lcd_WriteData(y_end>>8);
  Lcd_WriteData(0x00FF&y_end);
  Lcd_WriteIndex(0x2c);
}

void Lcd_Reset(void)
{
  LCD_RST_CLR;
  delay(100);
  LCD_RST_SET;
  delay(50);
}

void Lcd_WriteReg(unsigned char index,unsigned char data)
{
  Lcd_WriteIndex(index);
  Lcd_WriteData(data);
}

void LCD_WriteData_16Bit(unsigned int data)
{
  Lcd_WriteData((data>>8)&0xF8);//RED
  Lcd_WriteData((data>>3)&0xFC);//GREEN
  Lcd_WriteData(data<<3);//BLUE
}

void Lcd_Clear(unsigned int color)               
{  
   unsigned int i,m;
   Lcd_SetRegion(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
   for(i=0;i<Y_MAX_PIXEL;i++)
   {
    delay(0); //must be set
    for(m=0;m<X_MAX_PIXEL;m++)
    { 
      LCD_WriteData_16Bit(color);      
    }   
   }
}

void Lcd_Init(void)
{  
  Lcd_Reset(); //Reset before LCD Init.
  Lcd_WriteIndex(0XF7);
  Lcd_WriteData(0xA9);
  Lcd_WriteData(0x51);
  Lcd_WriteData(0x2C);
  Lcd_WriteData(0x82);
  Lcd_WriteIndex(0xC0);
  Lcd_WriteData(0x11);
  Lcd_WriteData(0x09);
  Lcd_WriteIndex(0xC1);
  Lcd_WriteData(0x41);
  Lcd_WriteIndex(0XC5);
  Lcd_WriteData(0x00);
  Lcd_WriteData(0x0A);
  Lcd_WriteData(0x80);
  Lcd_WriteIndex(0xB1);
  Lcd_WriteData(0xB0);
  Lcd_WriteData(0x11);
  Lcd_WriteIndex(0xB4);
  Lcd_WriteData(0x02);
  Lcd_WriteIndex(0xB6);
  Lcd_WriteData(0x02);
  Lcd_WriteData(0x42);
  Lcd_WriteIndex(0xB7);
  Lcd_WriteData(0xc6);
  Lcd_WriteIndex(0xBE);
  Lcd_WriteData(0x00);
  Lcd_WriteData(0x04);
  Lcd_WriteIndex(0xE9);
  Lcd_WriteData(0x00);
  Lcd_WriteIndex(0x36);
  Lcd_WriteData((1<<3)|(0<<6)|(0<<7));
  Lcd_WriteIndex(0x3A);
  Lcd_WriteData(0x66);
  Lcd_WriteIndex(0xE0);
  Lcd_WriteData(0x00);
  Lcd_WriteData(0x07);
  Lcd_WriteData(0x10);
  Lcd_WriteData(0x09);
  Lcd_WriteData(0x17);
  Lcd_WriteData(0x0B);
  Lcd_WriteData(0x41);
  Lcd_WriteData(0x89);
  Lcd_WriteData(0x4B);
  Lcd_WriteData(0x0A);
  Lcd_WriteData(0x0C);
  Lcd_WriteData(0x0E);
  Lcd_WriteData(0x18);
  Lcd_WriteData(0x1B);
  Lcd_WriteData(0x0F);
  Lcd_WriteIndex(0XE1);
  Lcd_WriteData(0x00);
  Lcd_WriteData(0x17);
  Lcd_WriteData(0x1A);
  Lcd_WriteData(0x04);
  Lcd_WriteData(0x0E);
  Lcd_WriteData(0x06);
  Lcd_WriteData(0x2F);
  Lcd_WriteData(0x45);
  Lcd_WriteData(0x43);
  Lcd_WriteData(0x02);
  Lcd_WriteData(0x0A);
  Lcd_WriteData(0x09);
  Lcd_WriteData(0x32);
  Lcd_WriteData(0x36);
  Lcd_WriteData(0x0F);
  Lcd_WriteIndex(0x11);
  delay(120);
  Lcd_WriteIndex(0x29); 
}

void pin_init(void)
{
    pinMode(LCD_CS, OUTPUT);
    pinMode(LCD_RST, OUTPUT);
    pinMode(LCD_RS, OUTPUT); 
    LCD_CS_SET;
    LCD_RST_SET;
    LCD_RS_SET;
}

void setup() 
{
    spi_init();
    pin_init();
    Lcd_Init();
}

void loop() 
{   
   Lcd_Clear(RED); 
 // delay(0); 
  Lcd_Clear(GREEN);
 // delay(0);  
   Lcd_Clear(BLUE); 
 // delay(100); 
  // }
}

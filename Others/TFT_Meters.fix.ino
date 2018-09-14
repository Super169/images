/*
 Example animated analogue meters using a TFT LCD screen

 Originanally written for a 320 x 240 display, so only occupies half
 of a 480 x 320 display.

 Needs Font 2 (also Font 4 if using large centered scale label)

  #########################################################################
  ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
  #########################################################################
 */

#include <SPI.h>

#include <TFT_eSPI.h> // Hardware-specific library



/*********************************/
// Start - script for the initila code from D1 mini sample

#define TFT_RS   27  // DC / RS is the same


#define LCD_CS_SET (digitalWrite(TFT_CS,HIGH))
#define LCD_RST_SET (digitalWrite(TFT_RST,HIGH))
#define LCD_RS_SET (digitalWrite(TFT_RS,HIGH))

#define LCD_CS_CLR (digitalWrite(TFT_CS,LOW))
#define LCD_RST_CLR (digitalWrite(TFT_RST,LOW))
#define LCD_RS_CLR (digitalWrite(TFT_RS,LOW))

#define LCD_CS_SET (digitalWrite(TFT_CS,HIGH))
#define LCD_RST_SET (digitalWrite(TFT_RST,HIGH))
#define LCD_RS_SET (digitalWrite(TFT_RS,HIGH))

#define LCD_CS_CLR (digitalWrite(TFT_CS,LOW))
#define LCD_RST_CLR (digitalWrite(TFT_RST,LOW))
#define LCD_RS_CLR (digitalWrite(TFT_RS,LOW))

void GPIO_Init() {
    pinMode(TFT_CS, OUTPUT);
    digitalWrite(TFT_CS, HIGH);

    pinMode(TFT_DC, OUTPUT);
    digitalWrite(TFT_DC, HIGH);

    pinMode(TFT_RST, OUTPUT);
    digitalWrite(TFT_RST, HIGH);

    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
}

void TFT_Init() {
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV2);
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
}

void spi_write(unsigned char data) {
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
    pinMode(TFT_CS, OUTPUT);
    pinMode(TFT_RST, OUTPUT);
    pinMode(TFT_RS, OUTPUT); 
    LCD_CS_SET;
    LCD_RST_SET;
    LCD_RS_SET;
}

// End - Script for the initila code from D1 mini sample
/*************************************/


TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

#define TFT_GREY 0x5AEB

float ltx = 0;    // Saved x coord of bottom of needle
uint16_t osx = 120, osy = 120; // Saved x & y coords
uint32_t updateTime = 0;       // time for next update

int old_analog =  -999; // Value last displayed
int old_digital = -999; // Value last displayed

int value[6] = {0, 0, 0, 0, 0, 0};
int old_value[6] = { -1, -1, -1, -1, -1, -1};
int d = 0;

void setup(void) {
  // tft.init();
  // tft.setRotation(1);
    GPIO_Init();
    TFT_Init();
    pin_init();
    Lcd_Init();
    tft.setRotation(5);

  Serial.begin(57600); // For debug
  tft.fillScreen(TFT_BLACK);

  analogMeter(); // Draw analogue meter

  // Draw 6 linear meters
  byte d = 40;
  plotLinear("A0", 0, 160);
  plotLinear("A1", 1 * d, 160);
  plotLinear("A2", 2 * d, 160);
  plotLinear("A3", 3 * d, 160);
  plotLinear("A4", 4 * d, 160);
  plotLinear("A5", 5 * d, 160);

  updateTime = millis(); // Next update time
}


void loop() {
  if (updateTime <= millis()) {
    updateTime = millis() + 25; // Delay to limit speed of update
 
    d += 4; if (d >= 360) d = 0;

    //value[0] = map(analogRead(A0), 0, 1023, 0, 100); // Test with value form Analogue 0
    //value[1] = map(analogRead(A1), 0, 1023, 0, 100); // Test with value form Analogue 1
    //value[2] = map(analogRead(A2), 0, 1023, 0, 100); // Test with value form Analogue 2
    //value[3] = map(analogRead(A3), 0, 1023, 0, 100); // Test with value form Analogue 3
    //value[4] = map(analogRead(A4), 0, 1023, 0, 100); // Test with value form Analogue 4
    //value[5] = map(analogRead(A5), 0, 1023, 0, 100); // Test with value form Analogue 5

    // Create a Sine wave for testing
    value[0] = 50 + 50 * sin((d + 0) * 0.0174532925);
    value[1] = 50 + 50 * sin((d + 60) * 0.0174532925);
    value[2] = 50 + 50 * sin((d + 120) * 0.0174532925);
    value[3] = 50 + 50 * sin((d + 180) * 0.0174532925);
    value[4] = 50 + 50 * sin((d + 240) * 0.0174532925);
    value[5] = 50 + 50 * sin((d + 300) * 0.0174532925);
    
    //unsigned long t = millis(); 
    plotPointer(); // It takes aout 3.5ms to plot each gauge for a 1 pixel move, 21ms for 6 gauges
     
    plotNeedle(value[0], 0); // It takes between 2 and 12ms to replot the needle with zero delay
    //Serial.println(millis()-t); // Print time taken for meter update
  }
}


// #########################################################################
//  Draw the analogue meter on the screen
// #########################################################################
void analogMeter()
{
  // Meter outline
  tft.fillRect(0, 0, 239, 126, TFT_GREY);
  tft.fillRect(5, 3, 230, 119, TFT_WHITE);

  tft.setTextColor(TFT_BLACK);  // Text colour

  // Draw ticks every 5 degrees from -50 to +50 degrees (100 deg. FSD swing)
  for (int i = -50; i < 51; i += 5) {
    // Long scale tick length
    int tl = 15;

    // Coodinates of tick to draw
    float sx = cos((i - 90) * 0.0174532925);
    float sy = sin((i - 90) * 0.0174532925);
    uint16_t x0 = sx * (100 + tl) + 120;
    uint16_t y0 = sy * (100 + tl) + 140;
    uint16_t x1 = sx * 100 + 120;
    uint16_t y1 = sy * 100 + 140;

    // Coordinates of next tick for zone fill
    float sx2 = cos((i + 5 - 90) * 0.0174532925);
    float sy2 = sin((i + 5 - 90) * 0.0174532925);
    int x2 = sx2 * (100 + tl) + 120;
    int y2 = sy2 * (100 + tl) + 140;
    int x3 = sx2 * 100 + 120;
    int y3 = sy2 * 100 + 140;

    // Yellow zone limits
    //if (i >= -50 && i < 0) {
    //  tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_YELLOW);
    //  tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_YELLOW);
    //}

    // Green zone limits
    if (i >= 0 && i < 25) {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_GREEN);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_GREEN);
    }

    // Orange zone limits
    if (i >= 25 && i < 50) {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_ORANGE);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_ORANGE);
    }

    // Short scale tick length
    if (i % 25 != 0) tl = 8;

    // Recalculate coords incase tick lenght changed
    x0 = sx * (100 + tl) + 120;
    y0 = sy * (100 + tl) + 140;
    x1 = sx * 100 + 120;
    y1 = sy * 100 + 140;

    // Draw tick
    tft.drawLine(x0, y0, x1, y1, TFT_BLACK);

    // Check if labels should be drawn, with position tweaks
    if (i % 25 == 0) {
      // Calculate label positions
      x0 = sx * (100 + tl + 10) + 120;
      y0 = sy * (100 + tl + 10) + 140;
      switch (i / 25) {
        case -2: tft.drawCentreString("0", x0, y0 - 12, 2); break;
        case -1: tft.drawCentreString("25", x0, y0 - 9, 2); break;
        case 0: tft.drawCentreString("50", x0, y0 - 6, 2); break;
        case 1: tft.drawCentreString("75", x0, y0 - 9, 2); break;
        case 2: tft.drawCentreString("100", x0, y0 - 12, 2); break;
      }
    }

    // Now draw the arc of the scale
    sx = cos((i + 5 - 90) * 0.0174532925);
    sy = sin((i + 5 - 90) * 0.0174532925);
    x0 = sx * 100 + 120;
    y0 = sy * 100 + 140;
    // Draw scale arc, don't draw the last part
    if (i < 50) tft.drawLine(x0, y0, x1, y1, TFT_BLACK);
  }

  tft.drawString("%RH", 5 + 230 - 40, 119 - 20, 2); // Units at bottom right
  tft.drawCentreString("%RH", 120, 70, 4); // Comment out to avoid font 4
  tft.drawRect(5, 3, 230, 119, TFT_BLACK); // Draw bezel line

  plotNeedle(0, 0); // Put meter needle at 0
}

// #########################################################################
// Update needle position
// This function is blocking while needle moves, time depends on ms_delay
// 10ms minimises needle flicker if text is drawn within needle sweep area
// Smaller values OK if text not in sweep area, zero for instant movement but
// does not look realistic... (note: 100 increments for full scale deflection)
// #########################################################################
void plotNeedle(int value, byte ms_delay)
{
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  char buf[8]; dtostrf(value, 4, 0, buf);
  tft.drawRightString(buf, 40, 119 - 20, 2);

  if (value < -10) value = -10; // Limit value to emulate needle end stops
  if (value > 110) value = 110;

  // Move the needle util new value reached
  while (!(value == old_analog)) {
    if (old_analog < value) old_analog++;
    else old_analog--;

    if (ms_delay == 0) old_analog = value; // Update immediately id delay is 0

    float sdeg = map(old_analog, -10, 110, -150, -30); // Map value to angle
    // Calcualte tip of needle coords
    float sx = cos(sdeg * 0.0174532925);
    float sy = sin(sdeg * 0.0174532925);

    // Calculate x delta of needle start (does not start at pivot point)
    float tx = tan((sdeg + 90) * 0.0174532925);

    // Erase old needle image
    tft.drawLine(120 + 20 * ltx - 1, 140 - 20, osx - 1, osy, TFT_WHITE);
    tft.drawLine(120 + 20 * ltx, 140 - 20, osx, osy, TFT_WHITE);
    tft.drawLine(120 + 20 * ltx + 1, 140 - 20, osx + 1, osy, TFT_WHITE);

    // Re-plot text under needle
    tft.setTextColor(TFT_BLACK);
    tft.drawCentreString("%RH", 120, 70, 4); // // Comment out to avoid font 4

    // Store new needle end coords for next erase
    ltx = tx;
    osx = sx * 98 + 120;
    osy = sy * 98 + 140;

    // Draw the needle in the new postion, magenta makes needle a bit bolder
    // draws 3 lines to thicken needle
    tft.drawLine(120 + 20 * ltx - 1, 140 - 20, osx - 1, osy, TFT_RED);
    tft.drawLine(120 + 20 * ltx, 140 - 20, osx, osy, TFT_MAGENTA);
    tft.drawLine(120 + 20 * ltx + 1, 140 - 20, osx + 1, osy, TFT_RED);

    // Slow needle down slightly as it approaches new postion
    if (abs(old_analog - value) < 10) ms_delay += ms_delay / 5;

    // Wait before next update
    delay(ms_delay);
  }
}

// #########################################################################
//  Draw a linear meter on the screen
// #########################################################################
void plotLinear(char *label, int x, int y)
{
  int w = 36;
  tft.drawRect(x, y, w, 155, TFT_GREY);
  tft.fillRect(x+2, y + 19, w-3, 155 - 38, TFT_WHITE);
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.drawCentreString(label, x + w / 2, y + 2, 2);

  for (int i = 0; i < 110; i += 10)
  {
    tft.drawFastHLine(x + 20, y + 27 + i, 6, TFT_BLACK);
  }

  for (int i = 0; i < 110; i += 50)
  {
    tft.drawFastHLine(x + 20, y + 27 + i, 9, TFT_BLACK);
  }
  
  tft.fillTriangle(x+3, y + 127, x+3+16, y+127, x + 3, y + 127 - 5, TFT_RED);
  tft.fillTriangle(x+3, y + 127, x+3+16, y+127, x + 3, y + 127 + 5, TFT_RED);
  
  tft.drawCentreString("---", x + w / 2, y + 155 - 18, 2);
}

// #########################################################################
//  Adjust 6 linear meter pointer positions
// #########################################################################
void plotPointer(void)
{
  int dy = 187;
  byte pw = 16;

  tft.setTextColor(TFT_GREEN, TFT_BLACK);

  // Move the 6 pointers one pixel towards new value
  for (int i = 0; i < 6; i++)
  {
    char buf[8]; dtostrf(value[i], 4, 0, buf);
    tft.drawRightString(buf, i * 40 + 36 - 5, 187 - 27 + 155 - 18, 2);

    int dx = 3 + 40 * i;
    if (value[i] < 0) value[i] = 0; // Limit value to emulate needle end stops
    if (value[i] > 100) value[i] = 100;

    while (!(value[i] == old_value[i])) {
      dy = 187 + 100 - old_value[i];
      if (old_value[i] > value[i])
      {
        tft.drawLine(dx, dy - 5, dx + pw, dy, TFT_WHITE);
        old_value[i]--;
        tft.drawLine(dx, dy + 6, dx + pw, dy + 1, TFT_RED);
      }
      else
      {
        tft.drawLine(dx, dy + 5, dx + pw, dy, TFT_WHITE);
        old_value[i]++;
        tft.drawLine(dx, dy - 6, dx + pw, dy - 1, TFT_RED);
      }
    }
  }
}


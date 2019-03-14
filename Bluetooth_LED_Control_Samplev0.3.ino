#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <Adafruit_NeoMatrix.h>
#include <gamma.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN         5
#define NUM_PIXELS      10
#define DELAY_MS        5
#define NUM_COLORS      8
#define MATRIX_SIZE_X   5
#define MATRIX_SIZE_Y   2
#define BIG_X           32
#define BIG_Y           8

Adafruit_NeoPixel pix = Adafruit_NeoPixel(NUM_PIXELS, LED_PIN, NEO_RGB + NEO_KHZ800);
//Adafruit_NeoMatrix mat = Adafruit_NeoMatrix(MATRIX_SIZE_X, MATRIX_SIZE_Y, LED_PIN,
//  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
//  NEO_MATRIX_ROWS    + NEO_MATRIX_ZIGZAG,
//  NEO_RGB            + NEO_KHZ800);

//8x32 Matrix Practice
Adafruit_NeoMatrix mat = Adafruit_NeoMatrix(BIG_X, BIG_Y, LED_PIN,
                         NEO_MATRIX_BOTTOM   +  NEO_MATRIX_RIGHT +
                         NEO_MATRIX_COLUMNS  +  NEO_MATRIX_ZIGZAG,
                         NEO_GRB             +  NEO_KHZ800);

unsigned long prev_ms = 0;
bool shimmerMode = false;
bool fillMode = false;
bool textMode = false;
bool blankMode = false;
bool customTextMode = false;

String customText = "";

//orange = 255,60,0
const uint16_t colors[NUM_COLORS] = {mat.Color(0, 0, 0), mat.Color(100, 0, 0), mat.Color(100, 100, 0), mat.Color(100, 40, 0), mat.Color(0, 100, 0), mat.Color(0, 0, 100), mat.Color(100, 0, 100),mat.Color(100,100,100)};
/*
  Arduino Turn LED On/Off using Serial Commands
  Created April 22, 2015
  Hammad Tariq, Incubator (Pakistan)
  It's a simple sketch which waits for a character on serial
  and in case of a desirable character, it turns an LED on/off.
  Possible string values:
  a (to turn the LED on)
  b (tor turn the LED off)
*/

char junk;
String inputString = "";

void setup()                    // run once, when the sketch starts
{
  Serial.begin(9600);            // set the baud rate to 9600, same should be of your Serial Monitor
  pinMode(13, OUTPUT);
  
  mat.begin();
  mat.fillScreen(colors[0]);
  mat.setTextWrap(false);
  mat.setBrightness(20);
  mat.setTextColor(colors[1]);
  mat.show();
}

void loop()
{
  listenForCommands();
  if (shimmerMode == true)
  {
    shimmer();
  }
  else if (fillMode == true)
  {
    for (int i = 0; i < NUM_COLORS; i++)
    {
      colorFill(colors[i]);
      delay(1000);
    }
  }
  else if(textMode == true)
  {
    text("Project Lumen"); //"Project Lumen"
  }
  else if(customTextMode == true)
  {
    text(customText);
  }
  else if (blankMode == true)
  {
    mat.fillScreen(colors[0]);
  }
}

void listenForCommands()
{
  if (Serial.available()) {
    while (Serial.available())
    {
      char inChar = (char)Serial.read(); //read the input
      inputString += inChar;        //make a string of the characters coming on serial
    }
    Serial.println(inputString);
    while (Serial.available() > 0)
    {
      junk = Serial.read() ;  // clear the serial buffer
    }
    if (inputString == "a")
    { //in case of 'a' switch to shimmer

      //shimmer();
      shimmerMode = true;
      fillMode = false;
      textMode = false;
      blankMode = false;
      customTextMode = false;
      mat.fillScreen(0);
    }
    else if (inputString == "b")
    { //incase of 'b' switch to color fill
      shimmerMode = false;
      fillMode = true;
      textMode = false;
      blankMode = false;
      customTextMode = false;
    }
    else if (inputString == "c")
    {
      //switch to text mode
      shimmerMode = false;
      fillMode = false;
      textMode = true;
      blankMode = false;
      customTextMode = false;
      mat.fillScreen(0);
    }
    else if (inputString == "d")
    {
      //shut off lights
      shimmerMode = false;
      fillMode = false;
      textMode = false;
      blankMode = true;
      customTextMode = false;
      mat.fillScreen(0);
    }
    else
    { //custom text mode
      customText = inputString;
      shimmerMode = false;
      fillMode = false;
      textMode = false;
      blankMode = false;
      customTextMode = true;
      mat.fillScreen(0);
    }
    

    inputString = "";
  }
}

void drawMatPix(int x, int y, uint16_t color)
{
  mat.drawPixel(x, y, color);
  mat.show();
}

void setPixelOff(int pixIndex)
{
  setPixelColor(pixIndex, 0, 0, 0);
}

void setPixelColor(int pixIndex, int red, int green, int blue)
{
  pix.setPixelColor(pixIndex, pix.Color(red, green, blue));
  pix.show();
}



void setAllPixelColor(int red, int green, int blue)
{
  for (int i = 0; i < NUM_PIXELS; i++)
  {
    setPixelColor(i, red, green, blue);
  }
}

void colorScroll(int delay_ms, int red, int green, int blue)
{
  setAllPixelColor(0, 0, 0);
  for (int i = 0; i < NUM_PIXELS; i++)
  {
    setPixelColor(i, red, green, blue);
    delay(delay_ms);
    setPixelOff(i);
  }
}

bool timer(long time_ms)
{
  if (millis() >= prev_ms + time_ms)
  {
    //prev_ms = millis();
    return true;
  }
  else
    return false;
}

void shimmer()
{

  for (int i = 0; i < NUM_COLORS; i++)
  {
    int rand_x = random(0, BIG_X);
    int rand_y = random(0, BIG_Y);
    drawMatPix(rand_x, rand_y, colors[i]);
    delay(50);
  }
}

void colorFill(uint16_t color)
{
  for (int i = 0; i < BIG_X; i++)
  {
    for (int j = 0; j < BIG_Y; j++)
    {
      mat.drawPixel(i, j, color);
    }
    delay(50);
    mat.show();
  }
}
  
  int x    = mat.width();
  int pass = 1;
  
void text(String textInput)
{
  mat.fillScreen(0);
  mat.setCursor(x, 0);
  mat.print(textInput);
  //mat.print(F("Project Lumen"));
  //if(--x < -60) 

  int scroll = (textInput.length()*(-6));
  
  if(--x < scroll) 
  {
    x = mat.width();

    if(++pass >= 8) pass = 1;
    mat.setTextColor(colors[pass]);
  }
  mat.show();
  delay(40);
}

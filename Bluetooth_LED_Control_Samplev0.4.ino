#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <Adafruit_NeoMatrix.h>
#include <gamma.h>
#include <Adafruit_NeoPixel.h>
//#include <Snake.ino>

#define LED_PIN         5
#define NUM_PIXELS      10
#define DELAY_MS        5
#define NUM_COLORS      8
#define MATRIX_SIZE_X   5
#define MATRIX_SIZE_Y   2
#define BIG_X           32
#define BIG_Y           8
#define  IN_NONE   0
#define  IN_UP     1
#define  IN_DOWN   2
#define  IN_LEFT   3
#define  IN_RIGHT  4
#define  IN_STOP   5

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
int mode = 0;

uint8_t controlInput = IN_NONE;
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

  //Snake snake = new Snake();
}

void loop()
{
  listenForCommands();
  switch(mode)
  {
    case 0: //off
    mat.fillScreen(colors[0]);
    mat.show();
    break;
    
    case 1: //shimmer
    shimmer();
    break;

    case 2: //fill
    for (int i = 0; i < NUM_COLORS; i++)
    {
      colorFill(colors[i]);
      delay(1000);
    }
    break;

    case 3: //Lumen
    text("Project Lumen");
    break;
    
    

    case 4: //Custom Text
    text(customText);
    break;

    case 5: //Play Snake
    playSnake();
    break;

    default:
    mat.fillScreen(colors[0]);
    break;
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
      mode = 1;
      mat.fillScreen(0);
    }
    else if (inputString == "b")
    { //incase of 'b' switch to color fill
      mode = 2;
    }
    else if (inputString == "c")
    {
      //switch to text mode
      mode = 3;
      mat.fillScreen(0);
    }
    else if (inputString == "off")
    {
      //shut off lights
      mode = 0;
    }
    else if(inputString == "psnek")
    {
      mode = 5; //play snake
    }
    else if(inputString == "u")
    {
      controlInput = IN_UP;
    }
    else if(inputString == "d")
    {
      controlInput = IN_DOWN;
    }
    else if(inputString == "l")
    {
      controlInput = IN_LEFT;
    }
    else if(inputString == "r")
    {
      controlInput = IN_RIGHT;
    }
    else if(inputString == "s")
    {
      controlInput = IN_STOP;
    }
    else
    { //custom text mode
      mode = 4;
      customText = inputString;
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
  pix.setPixelColor(pixIndex, 0, 0, 0);
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

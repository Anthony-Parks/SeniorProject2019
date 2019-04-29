//OPTIMIZED FOR FULL SIZE TAIL LIGHTS
//OPTIMIZED FOR FULL SIZE TAIL LIGHTS
//OPTIMIZED FOR FULL SIZE TAIL LIGHTS
// COMPLETE, NOT TESTED, TEXT MAY BE SKETCHY

#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <Adafruit_NeoMatrix.h>
#include <gamma.h>
#include <Adafruit_NeoPixel.h>
//#include <Snake.ino>

#define LED_PIN         5
#define LED_PINL        4
#define LED_PINR        5
#define NUM_PIXELS      10
#define DELAY_MS        5
#define NUM_COLORS      8
#define MATRIX_SIZE_X   5
#define MATRIX_SIZE_Y   2
#define BIG_X           32
#define BIG_Y           8
#define FULL_X          28
#define FULL_Y          10
//#define REG_X
//#define REG_Y
#define  IN_NONE   0
#define  IN_UP     1
#define  IN_DOWN   2
#define  IN_LEFT   3
#define  IN_RIGHT  4
#define  IN_STOP   5
#define  BRIGHT    20

#define TAIL_PIN     6
#define BRAKE_PIN    7
#define LBLINKER_PIN 8
#define RBLINKER_PIN 9
#define REVERSE_PIN  10

Adafruit_NeoPixel pix = Adafruit_NeoPixel(NUM_PIXELS, LED_PIN, NEO_RGB + NEO_KHZ800);

//matrix for right taillight 
Adafruit_NeoMatrix matR = Adafruit_NeoMatrix(FULL_X, FULL_Y, LED_PINR,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS    + NEO_MATRIX_ZIGZAG,
  NEO_RGB            + NEO_KHZ800);

//matrix for left taillight 
Adafruit_NeoMatrix matL = Adafruit_NeoMatrix(FULL_X, FULL_Y, LED_PINL,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_ROWS    + NEO_MATRIX_ZIGZAG,
  NEO_RGB            + NEO_KHZ800);

//8x32 Matrix Practice
Adafruit_NeoMatrix mat = Adafruit_NeoMatrix(BIG_X, BIG_Y, LED_PIN,
                         NEO_MATRIX_BOTTOM   +  NEO_MATRIX_RIGHT +
                         NEO_MATRIX_COLUMNS  +  NEO_MATRIX_ZIGZAG,
                         NEO_GRB             +  NEO_KHZ800);

unsigned long prev_ms = 0;

String customText = "";
int mode = 4;

uint8_t controlInput = IN_NONE;
//orange = 255,60,0
const uint16_t colors[NUM_COLORS+1] = {mat.Color(0, 0, 0), mat.Color(150, 0, 0), mat.Color(150, 150, 0), mat.Color(150, 90, 0), mat.Color(0, 150, 0), mat.Color(0, 0, 150), mat.Color(150, 0, 150),mat.Color(125,125,125),mat.Color(225, 0, 0)};


char junk;
String inputString = "";


//this needs to be adjusted for two taillights
void setup()                    // run once, when the sketch starts
{
  Serial.begin(9600);            // set the baud rate to 9600, same should be of your Serial Monitor
  pinMode(13, OUTPUT);
  
  matR.begin();
  matR.fillScreen(colors[0]);
  matR.setTextWrap(false);
  matR.setBrightness(20);
  matR.setTextColor(colors[1]);
  matR.show();

  matL.begin();
  matL.fillScreen(colors[0]);
  matL.setTextWrap(false);
  matL.setBrightness(20);
  matL.setTextColor(colors[1]);
  matL.show();

  pinMode(TAIL_PIN ,    INPUT);    
  pinMode(BRAKE_PIN,    INPUT);
  pinMode(LBLINKER_PIN, INPUT);
  pinMode(RBLINKER_PIN, INPUT);
  pinMode(REVERSE_PIN,  INPUT);
}

void loop()
{
  listenForCommands();
  switch(mode)
  {
    case 0: //off
    matL.fillScreen(colors[0]);
    matR.fillScreen(colors[0]);
    matL.show();
    matR.show();
    break;
    
    case 1: //shimmer
    shimmer();
    break;

    case 2: //fill
    colorFill();
    break;

    case 3:  //zig-zag
    zigZag();
    break;    

    case 4: //driving mode
    drivingMode();
    break;

    case 5: //Lumen
    text("Project Lumen");
    break;

    case 6: //t2
    text("Get off my tail!");
    break;

    case 7: //t3
    text("Wanna Race?");
    break;

    case 8: //t4
    text("Thanks!!!");
    break;

    case 9: //t5
    text("Sorry!!!");
    break;

    case 10: //Snake
    playSnake();
    break;

    case 11: //Pong
    playPong();
    break;

    case 12: //custom text
    text(customText);
    break;

    default:
    drivingMode();
    break;
  }
}

void listenForCommands()
{
  if (Serial.available()) {
    while (Serial.available())
    {
      char inChar = (char)Serial.read();
      inputString += inChar;        
    }
    Serial.println(inputString);
    while (Serial.available() > 0)
    {
      junk = Serial.read() ; 
    }
    if (inputString == "?o") // "?o" case 0
    {
      //shut off lights
      mode = 0;
    }
    else if (inputString == "?s1") // "?s1" case 1
    { //in case of 'a' switch to shimmer
      //shimmer();
      mode = 1;
      mat.fillScreen(0);
    }
    else if (inputString == "?s2") // "?s2" case 2
    { //incase of 'b' switch to color fill
      mode = 2;
    }
    else if (inputString == "?s3") //case 3
    {
      mode = 3;
    }
    else if (inputString == "?d") //case 4
    {
      mode = 4; //drivingMode();
    }
    else if (inputString == "?t1") // "?t1" case 5
    {
      //switch to "Lumen"
      mode = 5;
      //mat.fillScreen(0);
    }
    else if (inputString == "?t2") // preset sentence case 6
    {
      mode = 6;
    }
    else if (inputString == "?t3") // preset sentence case 7
    {
      mode = 7;
    }
    else if (inputString == "?t4") // preset sentence case 8
    {
      mode = 8;
    }
    else if (inputString == "?t5") // preset sentence case 9
    {
      mode = 9;
    }
    else if(inputString == "s") // "?g1" case 10
    {
      matL.fillScreen(0);
      matL.show();
      mode = 10; //play snake
    }
    else if (inputString == "p") // case 11
    {
      matL.fillScreen(0);
      matL.show();
      mode = 11; //play pong
    }
    else if(inputString == "u") // "?up" 
    {
      controlInput = IN_UP;
    }
    else if(inputString == "d") // "?down"
    {
      controlInput = IN_DOWN;
    }
    else if(inputString == "l") // "?left"
    {
      controlInput = IN_LEFT;
    }
    else if(inputString == "r") // "?right"
    {
      controlInput = IN_RIGHT;
    }
    else if(inputString == "q") // "?stop"
    {
      controlInput = IN_STOP;
    }
    else
    { //custom text mode           case 12
      mode = 12;
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
  
  matL.setBrightness(BRIGHT);
  matR.setBrightness(BRIGHT);
  for (int i = 0; i < NUM_COLORS; i++)
  {
    int rand_x = random(0, FULL_X);
    int rand_y = random(0, FULL_Y);
    matL.drawPixel(rand_x, rand_y, colors[i]);
    matL.show();
    delay(25);
    rand_x = random(0, FULL_X);
    rand_y = random(0, FULL_Y);
    matR.drawPixel(rand_x, rand_y, colors[i]);
    matR.show();
    delay(25);
  }
}


int fillColor = 0;

void colorFill()
{
  matL.setBrightness(BRIGHT);
  matR.setBrightness(BRIGHT);
  
  for (int i = 0; i < FULL_X; i++)
  {
    fillRow(i, colors[fillColor]);

    matL.show();
    matR.show();
    delay(50);
  }
  ++fillColor;
  if(fillColor==7)
    fillColor = 0;
}

void fillRow(int row, uint16_t color)
{
  matL.setBrightness(BRIGHT);
  matR.setBrightness(BRIGHT);
  for (int j = 0; j < FULL_Y; j++)
    {
      matL.drawPixel(row, j, color);
      matR.drawPixel(row, j, color);
    }
}

int xz = 0;
int yz = 0;
int colorZ = 1;
  
void zigZag()
{
  matL.fillScreen(colors[0]);
  matR.fillScreen(colors[0]);
  matL.setBrightness(BRIGHT);
  matR.setBrightness(BRIGHT);
  if(colorZ == 8)
  {
    colorZ = 1;
  }
  if(xz%2==0 || xz==0)
  {
    //even
    matL.drawPixel(xz, yz-1, colors[colorZ]);  
    matR.drawPixel(xz, yz-1, colors[colorZ]);
    matL.drawPixel(xz, yz, colors[colorZ]);  
    matR.drawPixel(xz, yz, colors[colorZ]);
    matL.drawPixel(xz, yz+1, colors[colorZ]);  
    matR.drawPixel(xz, yz+1, colors[colorZ]);
    matL.show();
    matR.show();
    ++yz;
  }
  else
  {
    //odd
    matL.drawPixel(xz, yz-1, colors[colorZ]);  
    matR.drawPixel(xz, yz-1, colors[colorZ]);
    matL.drawPixel(xz, yz, colors[colorZ]);  
    matR.drawPixel(xz, yz, colors[colorZ]);
    matL.drawPixel(xz, yz+1, colors[colorZ]);
    matR.drawPixel(xz, yz+1, colors[colorZ]);
    matL.show();
    matR.show();
    --yz;
  }
  if(yz>FULL_Y)
  {
    ++xz;
  }
  if(yz<0)
  {
    ++xz;
  }
  if(xz>=FULL_X)
  {
    xz=0;
    ++colorZ;
  }
  
}
  
  int x = matL.width();

  int pass = 1;
  
void text(String textInput)
{
  matL.setBrightness(BRIGHT);
  matR.setBrightness(BRIGHT);
  
  matL.fillScreen(0);
  matR.fillScreen(0);
  matL.setCursor(x, 1);
  matR.setCursor(x, 1);
  matL.print(textInput);
  matR.print(textInput);
  //mat.print(F("Project Lumen"));
  //if(--x < -60) 

  int scroll = (textInput.length()*(-6));
  
  if(--x < scroll) 
  {
    x = matL.width();

    if(++pass >= 8) pass = 1;
    matL.setTextColor(colors[pass]);
    matR.setTextColor(colors[pass]);
  }
  matL.show();
  matR.show();
  delay(40);
}

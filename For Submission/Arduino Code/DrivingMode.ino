
#define TAIL_BRIGHT      20
#define BRAKE_BRIGHT     60
#define REVERSE_BRIGHT   40

//OPTIMIZED FOR FULL SIZE TAIL LIGHTS
//TESTED, WORKING

bool tail;
bool brake;
bool lblinker;
bool rblinker;
bool reverse;

int pattern = 0;

void drivingMode()
{
  //startDrivingMode();
  matL.fillScreen(colors[0]);
  matR.fillScreen(colors[0]);
  
  tail = digitalRead(TAIL_PIN);
  brake = digitalRead(BRAKE_PIN);
  lblinker = digitalRead(LBLINKER_PIN);
  rblinker = digitalRead(RBLINKER_PIN);
  reverse = digitalRead(REVERSE_PIN);
  
  //0000
  if(!lblinker && !tail && !brake && !rblinker && !reverse)
  {
    //nothing
  }
  //0001
  else if(!lblinker && !tail && !brake && !rblinker && reverse)
  {
    Reverse();
  }
  //0010
  else if(!lblinker &&!tail && !brake && rblinker && !reverse)
  {
    RBlinker();
  }
  //0011
  else if(!lblinker &&!tail && !brake && rblinker && reverse)
  {
    RBlinker();
    Reverse();
  }
  //0100
  else if(!lblinker &&!tail && brake && !rblinker && !reverse)
  {
    Brake();
  }
  //0101
  else if(!lblinker &&!tail && brake && !rblinker && reverse)
  {
    Brake();
    Reverse();

  }
  //0110
  else if(!lblinker &&!tail && brake && rblinker && !reverse)
  {
    Brake();
    RBlinker();
  }
  //0111
  else if(!lblinker &&!tail && brake && rblinker && reverse)
  {
    Brake();
    RBlinker();
    Reverse();
  }
  //1000
  else if(!lblinker &&tail && !brake && !rblinker && !reverse)
  {
    Tail();
  }
  //1001
  else if(!lblinker &&tail && !brake && !rblinker && reverse)
  {
    Tail();
    Reverse();
  }
  //1010
  else if(!lblinker &&tail && !brake && rblinker && !reverse)
  {
    Tail();
    RBlinker();
  }
  //1011
  else if(!lblinker &&tail && !brake && rblinker && reverse)
  {
    Tail();
    RBlinker();
    Reverse();
  }
  //1100
  else if(!lblinker &&tail && brake && !rblinker && !reverse)
  {
    Brake();
  }
  //1101
  else if(!lblinker &&tail && brake && !rblinker && reverse)
  {
    Brake();
    Reverse();
  }
  //1110
  else if(!lblinker &&tail && brake && rblinker && !reverse)
  {
    Brake();
    RBlinker();
  }
  //1111
  else if(!lblinker && tail && brake && rblinker && reverse)
  {
    Brake();
    RBlinker();
    Reverse();
  }

  //above has left blinker off  
  //below is left blinker on

  //10000
  else if(lblinker && !tail && !brake && !rblinker && !reverse)
  {
    LBlinker();
  }
  //10001
  else if(lblinker && !tail && !brake && !rblinker && reverse)
  {
    LBlinker();
    Reverse();
  }
  
  //10010
  else if(lblinker &&!tail && !brake && rblinker && !reverse)
  {
    LBlinker();
    RBlinker();
  }

  //10011
  else if(lblinker &&!tail && !brake && rblinker && reverse)
  {
    LBlinker();
    RBlinker();
    Reverse();
  }
  
  //10100
  else if(lblinker &&!tail && brake && !rblinker && !reverse)
  {
    Brake();
    LBlinker();
  }
  //10101
  else if(lblinker &&!tail && brake && !rblinker && reverse)
  {
    Brake();
    LBlinker();
    Reverse();
  }
  
  //10110
  else if(lblinker &&!tail && brake && rblinker && !reverse)
  {
    Brake();
    LBlinker();
    RBlinker();
  }

  //10111
  else if(lblinker &&!tail && brake && rblinker && reverse)
  {
    Brake();
    LBlinker();
    RBlinker();
    Reverse();
  }

  //11000
  else if(lblinker &&tail && !brake && !rblinker && !reverse)
  {
    Tail();
    LBlinker();
  }
  //11001
  else if(lblinker &&tail && !brake && !rblinker && reverse)
  {
    Tail();
    LBlinker;
    Reverse();
  }
  //11010
  else if(lblinker &&tail && !brake && rblinker && !reverse)
  {
    Tail();
    LBlinker();
    RBlinker();
  }

  //11011
  else if(lblinker &&tail && !brake && rblinker && reverse)
  {
    Tail();
    LBlinker();
    RBlinker();
    Reverse();
  }

  //11100
  else if(lblinker &&tail && brake && !rblinker && !reverse)
  {
    Brake();
    LBlinker();
  }
  //11101
  else if(lblinker &&tail && brake && !rblinker && reverse)
  {
    Brake();
    LBlinker();
    Reverse();
  }
  //11110
  else if(lblinker &&tail && brake && rblinker && !reverse)
  {
    Brake();
    LBlinker();
    RBlinker();
  }

  //11111
  else if(lblinker && tail && brake && rblinker && reverse)
  {
    Brake();
    LBlinker();
    RBlinker();
    Reverse();
  }

  matL.show();
  matR.show();
  
  //24 total possible states
}

void Tail()
{
  //brightness 20% light all red
  
  matL.fillScreen(colors[1]);
  matR.fillScreen(colors[1]);
}

void Brake()
{
  //brightness 60% light all red
  
  matL.fillScreen(colors[8]);
  matR.fillScreen(colors[8]);
}

//blinkers must be placed under brake
void RBlinker()
{
  //turn off right side lights
  if(tail || brake)
    matR.fillScreen(colors[0]);
  //turn on
  else
  {
    matR.fillScreen(colors[8]);
  }
}

void LBlinker()
{
  //turn off right side lights
  if(tail || brake)
    matL.fillScreen(colors[0]);
  //turn on
  else
  {
    matL.fillScreen(colors[8]);
  }
}

//in 16 if statements above blinker must be placed above reverse, so reverse will shine above blinker turning 
void Reverse()
{
  //illuminate all top and bottom row white
  for(int i = 0; i < FULL_X; i++)
  {
    //top
    matL.drawPixel(i, FULL_Y-1, colors[7]);
    matR.drawPixel(i, FULL_Y-1, colors[7]);
    //bottom
    matL.drawPixel(i, 0, colors[7]);
    matR.drawPixel(i, 0, colors[7]);
  }
}

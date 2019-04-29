#define  WIDTH            1 //Snake width
#define  DIR_UP           1
#define  DIR_DOWN         2
#define  DIR_LEFT         3
#define  DIR_RIGHT        4
#define  SNAKE_MAX_LENGTH 25


//OPTIMIZED FOR FULL SIZE TAIL LIGHTS
//***COMPLETE FOR RIGHT TAILLIGHT, TESTED***


  int Length;
  int X[SNAKE_MAX_LENGTH];
  int Y[SNAKE_MAX_LENGTH];
  int currentDir; //current input direction
  int score;

  boolean GameOver;

  int appleX;
  int appleY;
  uint16_t appleColor;
  String output = "";


  
  
  void startSnake()
  {
    //Starting position and direction for Snake
    Length = 2;
    X[0] = 2; X[1] = 1;
    Y[0]=FULL_Y/2; Y[1]=FULL_Y/2;
    currentDir = DIR_RIGHT;
    score = 0;
    
    //random first apple coordinates
    appleX = random(3, FULL_X - 6-1);
    appleY = random(FULL_Y);
    
    GameOver = false;
  }

  void playSnake()
  {
    startSnake();
    unsigned long previousTime = 0;
    boolean runSnake = true;
    while(runSnake)
    {
      //this code checks for the snake colliding with itself
      int i = Length - 1;
      while(i>=2)
      {
        if(checkCollision(X[0],X[i],Y[0],Y[i],WIDTH,WIDTH,WIDTH,WIDTH))
        {
          gameOver();
        }
        i = i-1;
      }

      if(GameOver)
      {
        runSnake = false;
        break;
      }

      //check if eat apple
      if (checkCollision(X[0], appleX, Y[0], appleY, WIDTH, WIDTH, WIDTH, WIDTH))
      {
        //Increase score and snake lenghth by one
        score = score + 1;
        Length = Length + 1;
        //new segment has temporary position
        X[Length-1] = 255;
        Y[Length-1] = 255;
      
        //Randomize new apple position
        appleX = random(2, FULL_X - 6-1);
        appleY = random(FULL_Y);


        int i= Length-1;
        for(int i=0; i<Length; i++) 
        {
          if (checkCollision(appleX, X[i], appleY, Y[i], WIDTH, WIDTH, WIDTH, WIDTH))
          {
           appleX = random(2, FULL_X - 6-1);
           appleY = random(FULL_Y-1);
           i=0;
          }
        }
      }
      
      //move one pixel
      i = Length-1;
      while(i>=1)
      {
        X[i] = X[i-1];
        Y[i] = Y[i-1];
        i = i-1;
      }
      //new position for snake's head
      if (currentDir == DIR_RIGHT)
      {
        X[0] = X[0] + WIDTH;
      } 
      else if (currentDir == DIR_LEFT)
      {
        X[0] = X[0] - WIDTH;
      } 
      else if (currentDir == DIR_UP) 
      {
        Y[0] = Y[0] - WIDTH;
      } 
      else if (currentDir == DIR_DOWN)
      {//DOWN
        Y[0] = Y[0] + WIDTH;
      }
      //If you slither off screen you return on the other side
      //These paths could be changed to game over for a more hardcore game mode
      if ((X[0]<2) || (X[0]>=FULL_X - 6) || (Y[0]<0) || (Y[0]>=FULL_Y))
      {
        if (X[0]<2) 
        {
           X[0] =FULL_X - 6 -1;
        }
        else if (X[0]>=FULL_X - 6) 
        {
           X[0] = 2;
        }      
        else if (Y[0]<0) 
        {
          Y[0] = FULL_Y - 1;
        }
        else if (Y[0]>=FULL_Y) 
        {
          Y[0] = 0;
        }    
      }

      //clear all pixels 
      matR.fillScreen(colors[0]);

      //draw pixel representing apple
      matR.drawPixel(appleX,appleY,colors[7]); 

      for (int i=0; i<Length; i++)
      {
        //draw pixels representing snake
        matR.drawPixel(X[i],Y[i],colors[1]); //red
      }
      //show pixels
      matR.show();

      unsigned long currentTime;
      bool directionChange = false;
      do
      {
        //look for BT input
        //reset to none
        controlInput = IN_NONE;
        listenForCommands();
        if(controlInput == IN_STOP)
        {
          runSnake = false;
          gameOver();
          break;
        }
        if(controlInput != IN_NONE && !directionChange)
        {
          directionChange = true;
          changeDirection();
        }
        currentTime = millis();
      }
      while((currentTime - previousTime)<250);
        previousTime = currentTime;
    }
  }

  void changeDirection()
  {
    switch(controlInput)
    {
      case IN_NONE:
        break;
      case IN_UP:
        currentDir = DIR_UP;
        break;
      case IN_DOWN:
        currentDir = DIR_DOWN;
        break;
      case IN_LEFT:
        currentDir = DIR_LEFT;
        break;
      case IN_RIGHT:
        currentDir = DIR_RIGHT;
        break;
    }
  }
  
  void gameOver()
  {
    GameOver = true;
    for(int i = 0; i < 200; i++)
    {
      text("Score: " + String(score));
    }
    mode = 0;
    
  }
  
  boolean checkCollision(int x1, int x2, int y1, int y2, int w1, int w2, int h1, int h2)
  {
    if ((x1+w1>x2) && (x1<x2+w2) && (y1+h1>y2) && (y1<y2+h2))
    {
      return true;
    } 
    else 
    {
      return false;
    }
  };

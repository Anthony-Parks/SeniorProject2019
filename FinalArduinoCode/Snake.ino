#define  WIDTH            1 //Snake width
#define  DIR_UP           1
#define  DIR_DOWN         2
#define  DIR_LEFT         3
#define  DIR_RIGHT        4
#define  SNAKE_MAX_LENGTH 25


//OPTIMIZED FOR FULL SIZE TAIL LIGHTS
//***COMPLETE FOR RIGHT TAILLIGHT, NOT YET TESTED***


  int Length;//Curren length of snake
  int X[SNAKE_MAX_LENGTH];//Array containing all snake segments,
  int Y[SNAKE_MAX_LENGTH];// max snake length is array length
  int currentDir; //Current Direction of snake
  int score;

  boolean GameOver;

  int appleX;//Apple x position
  int appleY;//Apple y position
  uint16_t appleColor;
  String output = "";


  
  
  void startSnake()
  {
    //Snake start position, direction & initialise variables
    Length = 2;
    X[0] = 2; X[1] = 1;
    Y[0]=FULL_Y/2; Y[1]=FULL_Y/2;
    currentDir = DIR_RIGHT;
    score = 0;
    //random apple coordinates
    //random color
    //appleColor = colors[7];
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
      //check for self-collision
      int i = Length - 1;
      while(i>=2)
      {
        if(collide(X[0],X[i],Y[0],Y[i],WIDTH,WIDTH,WIDTH,WIDTH))
        {
          output = "Self Collision";
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
      if (collide(X[0], appleX, Y[0], appleY, WIDTH, WIDTH, WIDTH, WIDTH))
      {
        //Increment score and snake length;
        score = score + 1;
        Length = Length + 1;
        //Add snake segment with temporary position of new segments
        X[Length-1] = 255;
        Y[Length-1] = 255;
      
        //Generate new apple position
        appleX = random(2, FULL_X - 6-1);
        appleY = random(FULL_Y);
        //Generate apple color
        //int color = random(1,NUM_COLORS);
        //appleColor = colors[7];

        int i= Length-1;
        for(int i=0; i<Length; i++) 
        {
          if (collide(appleX, X[i], appleY, Y[i], WIDTH, WIDTH, WIDTH, WIDTH))
          {
           appleX = random(2, FULL_X - 6-1);
           appleY = random(FULL_Y-1);
           i=0;
          }
        }
      }
      
      //Shift snake position by one
      i = Length-1;
      while(i>=1)
      {
        X[i] = X[i-1];
        Y[i] = Y[i-1];
        i = i-1;
      }
      //Determine new position of head of snake
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
      //Check if outside playing field
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

      //clear pixels
      matR.fillScreen(colors[0]);

      //draw apple
      matR.drawPixel(appleX,appleY,colors[7]); 

      for (int i=0; i<Length; i++)
      {
        //setTablePixel(xs[i], ys[i], WHITE); draw snake
        matR.drawPixel(X[i],Y[i],colors[1]); //red
      }
      //show
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
    for(int i = 0; i < 300; i++)
    {
      text("Score: " + String(score));
    }
    mode = 0;
    
  }
  
  boolean collide(int x1, int x2, int y1, int y2, int w1, int w2, int h1, int h2)
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

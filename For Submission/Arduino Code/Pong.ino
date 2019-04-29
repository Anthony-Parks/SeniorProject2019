#define PLAYER_HEIGHT 4
#define MAX_SCORE 10
#define PLAYER_SPEED 200

//OPTIMIZED FOR FULL SIZE TAIL LIGHTS
//***COMPLETE*** FOR RIGHT TAILLIGHT, TESTED

int scoreLeft;
int scoreRight;

int posLeft;
int posRight;

int ballx;
int prevBallx;

int bally;
int prevBally;

int velYX;
int velYY;

int ballBounce;

int gameSpeed;

unsigned long lastAutoPlayerMoveTime;
unsigned long rumbleUntil;
unsigned long waitUntil;
unsigned long currentTime;
unsigned long preTime = 0;

void startPong() {

  scoreLeft = 0;
  scoreRight = 0;
  FULL_Y * FULL_X;

  posLeft = FULL_Y/2;
  posRight = FULL_Y/2;

  ballx = FULL_X/2;
  bally = FULL_Y/2;

  velYX = 1;
  velYY = 0;

  ballBounce = 0;
  gameSpeed = 180;
  lastAutoPlayerMoveTime = 0;
  rumbleUntil = 0;
  waitUntil =0;
  
}

void playPong() {

  startPong();

  boolean gameRunning = true;

  while (gameRunning) {

    if (scoreLeft == MAX_SCORE || scoreRight == MAX_SCORE) {

      gameRunning = false;
      gameOverPong();
      break;  
    }

    ballHit();

    if((currentTime - lastAutoPlayerMoveTime) > PLAYER_SPEED) {
      if(moveAutoPlayer()) {
        lastAutoPlayerMoveTime = currentTime;
      }
    }

    ballx += velYX;
    bally += velYY;

    checkBallBounds();
    matR.fillScreen(colors[0]);

    //Draw ball
    //WHITE
    matR.drawPixel(ballx,bally, colors[7]);
    //Draw player left
    for (int y = posLeft - PLAYER_HEIGHT/2; y<= posLeft + PLAYER_HEIGHT/2; ++y) {
      //BLUE
      matR.drawPixel(2, y, colors[5]);
    }
    //Draw player Right
        for (int y = posRight - PLAYER_HEIGHT/2; y<= posRight + PLAYER_HEIGHT/2; ++y) {
      //YELLOW
      matR.drawPixel(FULL_X-6 -1, y, colors[2]);
    }
    matR.show();
    
    boolean directionChange = false;
    do {
      //look for BT input
      //reset to none
      controlInput = IN_NONE;
      listenForCommands();

      if(controlInput == IN_STOP) {
        gameRunning = false;
        gameOverPong();
        break;
      }

      if (controlInput != IN_NONE && !directionChange) {
        directionChange = true;
        setPos();
      }

      currentTime = millis();      
    }

    while((currentTime - preTime) < 250);
    preTime = currentTime;
  }
  
}

void setPos(){
  switch(controlInput){
    case IN_NONE:
      break;
    case IN_DOWN: 
    if (posLeft + (PLAYER_HEIGHT-1) / 2 < FULL_Y -1) {
      ++posLeft;
    }
      break;
    case IN_UP:
    if(posLeft - PLAYER_HEIGHT/ 2 > 0) {
      --posLeft;
    }
    break;
    
  }
}

void ballHit() {
  if(ballx == 3){
    if(bally == posLeft){
      velYX = 1;
      ballx = 3;
      ++ballBounce;
      rumbleUntil = currentTime + 200;
    }
    else if(bally < posLeft && bally >= posLeft - (PLAYER_HEIGHT) / 2)  {
      velYX = 1;
      velYY = max(-1,velYY-1);
      ballx = 3;
      bally = posLeft - PLAYER_HEIGHT/2-1;
      ++ballBounce;
      rumbleUntil = currentTime + 200;
    }
    else if(bally > posLeft && bally <= posLeft + (PLAYER_HEIGHT) / 2) {
      velYX = 1;
      velYY = min(1,velYY+1);
      ballx = 3;
      bally = posLeft + (PLAYER_HEIGHT-1) / 2+1;
      ++ballBounce;
      rumbleUntil = currentTime + 200;
    }
  }

  else if(ballx == FULL_X-6 - 2) {
    if(bally = posRight) {
      velYX = -1;
      ballx = FULL_X-6 - 2;
      ++ballBounce;
    }
  

  else if(bally < posRight && bally >= posRight - PLAYER_HEIGHT/2) {
    velYX = - 1;
    velYY = max(-1, velYY -1);
    ballx = FULL_X-6 -2;
    bally = posRight - PLAYER_HEIGHT / 2-1;
    ++ballBounce;
  }

  else if(bally > posRight && bally <= posRight + (PLAYER_HEIGHT-1) /2) {
    velYX = -1; 
    velYY = min(1, velYY +1);
    ballx = FULL_X-6 -2;
    bally = posRight +(PLAYER_HEIGHT -1) / 2+1;
    ++ballBounce;
  }
 }
}

void checkBallBounds() {
  if(bally <0) {
    velYY = -velYY;
    bally =1;
    
  }
  else if (bally > FULL_Y -1) {
    velYY = -velYY;
    bally = FULL_Y -2;
    
  }
  if(ballx < 1){
    velYX = -velYX;
    velYY = 0;
    ballx = FULL_X/2;
    bally = FULL_Y/2;
    ++scoreRight;
    ballBounce = 0;
    waitUntil = currentTime + 2000;
  }
  //if(ballx > FULL_X){
  //  velYX = -velYX;
  //  velYY = 0;
  //  ballx = (FULL_X-6)/2;
  //  bally = FULL_Y/2;
  //  ++scoreLeft;
  //  ballBounce = 0;
  //  waitUntil = currentTime + 2000;
  //}
}

boolean moveAutoPlayer() {
  if(bally < posRight) {
    if(posRight - PLAYER_HEIGHT / 2 > 0) {
      --posRight;
      return true;
    }
  }

  else if (bally > posRight){
    if(posRight+ (PLAYER_HEIGHT -1) /2 < FULL_Y -1) {
      ++posRight;
      return true;
    }
  }
  return false;
}

void gameOverPong()
  {
    //GameOver = true;
    //output = "Game over. Score: " + score;
    for(int i = 0; i < 200; i++)
    {
      text("Left: " + String(scoreLeft) + " Right: " + String(scoreRight));
    }
    mode = 0;
  }

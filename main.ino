#include <TM1637Display.h>

#define PINDTWENTY 7
#define PINDTWELVE 6
#define PINDTEN 5
#define PINDEIGHT 4
#define PINDSIX 3
#define PINDTFOUR 2

#define PINCLK 9
#define PINDIO 8

#define NO_SELECTION 0
#define SWITCH_DEFAULT -1

TM1637Display Display;
int Selected;

const uint8_t LetterD[] = {
  0b01011110
};
const uint8_t LoadingFrames[] = {
   SEG_F,
   SEG_A,
   SEG_B,
   SEG_C,
   SEG_D,
   SEG_E
};
const uint8_t BlankScreen[] = { 
  0x00, 
  0x00, 
  0x00, 
  0x00 
};

void setup() 
{
  Display = new TM1637Display(PINCLK, PINDIO)
  Display.setBrightness(0x0f);
  clearScreen();
  
  Selected = NO_SELECTION;

  randomSeed(analogRead(0));
}

void loop() 
{
  requestAnimationFrame(millis());
}
void requestAnimationFrame(long mtime)
{
  int currentDice = getSelectedDice();
  
  //Switch status same as last frame
  if (currentDice == Selected)
  {
    Display.setSegments(LetterD + 0, 1, 0);
    Display.showNumberDec(Selected, false, (Selected > 9) ? 2 : 1, 1);
    loadingIndicator(mtime);
  }   
  //Switch status changed
  else if (currentDice != SWITCH_DEFAULT)
  {
    clearScreen();    
    Selected = currentDice;
  }
  //Switch released and selection was made
  else if (Selected > NO_SELECTION)
  {
    Display.showNumberDec(random(Selected) + 1, false, 4);
    Selected = NO_SELECTION;     
  }
}
int getSelectedDice()
{
  int dice = checkDice(PINDTWENTY, 20);
  dice = dice == SWITCH_DEFAULT ? checkDice(PINDTWELVE, 12) : dice;
  dice = dice == SWITCH_DEFAULT ? checkDice(PINDTEN, 10) : dice;
  dice = dice == SWITCH_DEFAULT ? checkDice(PINDEIGHT, 8) : dice;
  dice = dice == SWITCH_DEFAULT ? checkDice(PINDSIX, 6) : dice;
  dice = dice == SWITCH_DEFAULT ? checkDice(PINDFOUR, 4) : dice;

  return dice;
}
int checkDice(int pin, int range)
{
  int switchState = digitalRead(pin); 
  if (switchState == HIGH)
  {
    return range;
  }

  return SWITCH_DEFAULT;
}

void clearScreen()
{
  Display.setSegments(BlankScreen + 0);
}
void loadingIndicator(long mtime)
{
  int frame = (mtime / (1000 / 30)) % 6;
  Display.setSegments(LoadingFrames + frame, 1, 3);
}




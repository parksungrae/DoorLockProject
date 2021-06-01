#include <wiringPi.h>
#include <stdio.h>
 
//Pin 11 on Raspberry Pi corresponds to BCM GPIO 17 and wiringPi pin 0
#define BeepPin 0

//Frequency
#define cH 523
#define fH 698
#define bH 933
 
//This function generates the square wave that makes the piezo speaker sound at a determinated frequency.
void beep(unsigned int note, unsigned int duration)
{
  //This is the semiperiod of each note.
  long beepDelay = (long)(1000000/note);
  //This is how much time we need to spend on the note.
  long time = (long)((duration*1000)/(beepDelay*2));
  int i;
  for(i=0;i<time;i++)
  {
    //1st semiperiod
    digitalWrite(BeepPin, HIGH);
    delayMicroseconds(beepDelay);
    //2nd semiperiod
    digitalWrite(BeepPin, LOW);
    delayMicroseconds(beepDelay);
  }
 
  //Add a little delay to separate the single notes
  digitalWrite(BeepPin, LOW);
  delay(20);
}
 
//The source code of the Imperial March from Star Wars
void errorBuzzer()	//fail
{
  beep( bH, 250);
  beep( bH, 250);
  beep( bH, 250);
  
}
 
 void openBuzzer()	//success
{
  beep( fH, 250);
  beep( cH, 250);
  beep( bH, 250);
  
}
int main(void)
{
  //Check wiringPi setup
  if(-1 == wiringPiSetup())
  {
    printf("setup wiringPi failed!");
    return 1;
  }
 
  //Prepare GPIO0
  pinMode(BeepPin, OUTPUT);

  
  //Play the Imperial March
  openBuzzer();
  errorBuzzer();
 
  return 0;
}



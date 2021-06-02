#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <softPwm.h>
#include <wiringShift.h> // shift funciton

#define P_MAX_CLK 0 // BCM_GPIO #17
#define P_MAX_CS 2 // BCM_GPIO #27
#define P_MAX_DIN 3 // BCM_GPIO #22

//Servo Function
#define Servo 26
#define BeepPin 25

//Frequency
#define cH 523
#define fH 698
#define bH 933



#define ROWS 4
#define COLS 3

const uint8_t allOff[] = {
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const uint8_t zero[] = {
    0x3C, 0x7E, 0xC3, 0xC3, 0xC3, 0xC3, 0x7E, 0x3C // 0
};
const uint8_t one[] = {
    0x00, 0x18, 0x38, 0x18, 0x18, 0x18, 0x3C, 0x00 // 1
};
const uint8_t two[] = {
    0x7E, 0x7E, 0x06, 0x7E, 0x7E, 0x60, 0x7E, 0x7E // 2
};
const uint8_t three[] = {
    0x00, 0x7E, 0x02, 0x7E, 0x7E, 0x02, 0x7E, 0x00 // 3
};
const uint8_t four[] = {
    0x0C, 0x3C, 0x6C, 0xCC, 0xFF, 0xFF, 0x0C, 0x0C // 4
};
const uint8_t five[] = {
    0x7E, 0x7E, 0x60, 0x7E, 0x7E, 0x06, 0x7E, 0x7E // 5
};
const uint8_t six[] = {
    0x7E, 0x7E, 0x60, 0x7E, 0x66, 0x66, 0x7E, 0x7E // 6
};
const uint8_t seven[] = {
    0x7E, 0x7E, 0x66, 0x66, 0x06, 0x06, 0x06, 0x06 // 7
};
const uint8_t eight[] = {
    0xFF, 0xFF, 0xC3, 0xFF, 0xFF, 0xC3, 0xFF, 0xFF // 8
};
const uint8_t nine[] = {
    0xFF, 0xFF, 0xC3, 0xFF, 0xFF, 0x03, 0xFF, 0xFF // 9
};
const uint8_t success[] = {
    0x7E, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x7E // O
};
const uint8_t fail[] = {
    0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81 // X
};

char pressedKey = '\0';
int rowPins[ROWS] = {1, 4, 5, 6};
int colPins[COLS] = {27, 28, 29};


uint8_t buf[8];
void MAX7219_WRITE(uint8_t address, uint8_t data) {
 digitalWrite(P_MAX_CS, LOW);
 shiftOut(P_MAX_DIN, P_MAX_CLK, MSBFIRST, address);
 shiftOut(P_MAX_DIN, P_MAX_CLK, MSBFIRST, data);
 digitalWrite(P_MAX_CS, HIGH);
}
void MAX7219_INIT(void) {
MAX7219_WRITE(0x09, 0x00);
// Decode Mode : no decode all digits(0x00)
MAX7219_WRITE(0x0A, 0x0F); // Intensity : max(0x0F)
MAX7219_WRITE(0x0B, 0x07);
// Scan Limit : Digit 0 ~ Digit 7, (0x07)
MAX7219_WRITE(0x0C, 0x01); // Shutdown : Normal(0x01)
}
void setup(void) {
 pinMode(P_MAX_DIN, OUTPUT);
 pinMode(P_MAX_CS, OUTPUT);
 pinMode(P_MAX_CLK, OUTPUT);
 digitalWrite(P_MAX_CS, HIGH);
 MAX7219_INIT();
}

void write_num(char number){
  int i;
  int num = (int)number;
  printf("%d", num);
  switch (num){
    case 1:
    for(i=0; i<8; i++){
      MAX7219_WRITE(i+1, one[i]);
    }
    break;
    case 2:
    for(i=0; i<8; i++){
      MAX7219_WRITE(i+1, two[i]);
    }
    break;
    case 3:
    for(i=0; i<8; i++){
      MAX7219_WRITE(i+1, three[i]);
    }
    break;
    case 4:
    for(i=0; i<8; i++){
      MAX7219_WRITE(i+1, four[i]);
    }
    break;
    case 5:
    for(i=0; i<8; i++){
      MAX7219_WRITE(i+1, five[i]);
    }
    break;
    case 6:
    for(i=0; i<8; i++){
      MAX7219_WRITE(i+1, six[i]);
    }
    break;
    case 7:
    for(i=0; i<8; i++){
      MAX7219_WRITE(i+1, seven[i]);
    }
    break;
    case 8:
    for(i=0; i<8; i++){
      MAX7219_WRITE(i+1, eight[i]);
    }
    break;
    case 9:
    for(i=0; i<8; i++){
      MAX7219_WRITE(i+1, nine[i]);
    }
    break;
    case 0:
    for(i=0; i<8; i++){
      MAX7219_WRITE(i+1, zero[i]);
    }
    break;
    default:
    break;
  }
}
void openServo(void) {
    int pos = 10 ;
  int dir = 1 ;
  while(pos < 20) {
    pos += dir ;
    if (pos < 10) dir *= -1 ;
    softPwmWrite(Servo, pos) ;
    delay(100) ;
  }
}
void closeServo(void) {
  int pos = 20 ;
  int dir = 1 ;
  while(pos > 10) {
    pos += dir ;
    if (pos > 20) dir *= -1 ;
    softPwmWrite(Servo, pos) ;
    delay(100) ;
  }
}
void setupServo(void) {
    pinMode(Servo, OUTPUT) ;  // 0번핀을 OUTPUT으로 설정. WiringPi의 0번핀은 BCM GPIO 17번핀에 해당한다
  digitalWrite(Servo, LOW) ;  // 0 pin output LOW voltage
  softPwmCreate(Servo, 0, 200) ;  // 0번 핀의 초기 pwm 값을 LOW로 하고 PWM주기는 20ms 로 설정한다
}
//Servo Function



//Buzzer Function
 
void beep(unsigned int note, unsigned int duration)
{
  long beepDelay = (long)(1000000/note);
  long time = (long)((duration*1000)/(beepDelay*2));
  int i;
  for(i=0;i<time;i++)
  {
    digitalWrite(BeepPin, HIGH);
    delayMicroseconds(beepDelay);
    digitalWrite(BeepPin, LOW);
    delayMicroseconds(beepDelay);
  }
 
  digitalWrite(BeepPin, LOW);
  delay(20);
}
 
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
//Buzzer Function



int findLowRow()
{
   for (int r = 0; r < ROWS; r++)
   {
      if (digitalRead(rowPins[r]) == LOW)
         return r;
   }

   return -1;
}

char keys[ROWS][COLS] = {
   {'1', '2', '3'},
   {'4', '5', '6'},
   {'7', '8', '9'},
   {'*', '0', '#'},
};
char get_key()
{
   int rowIndex;
   for (int c = 0; c < COLS; c++)
   {
      digitalWrite(colPins[c], LOW);
      rowIndex = findLowRow();
      if (rowIndex > -1)
      {
         if (!pressedKey)
            pressedKey = keys[rowIndex][c];
         return pressedKey;
      }
      digitalWrite(colPins[c], HIGH);
   }
   pressedKey = '\0';
   return pressedKey;
}
void init_keypad()
{
   for (int c = 0; c < COLS; c++)
   {
      pinMode(colPins[c], OUTPUT);   
      digitalWrite(colPins[c], HIGH);
   }

   for (int r = 0; r < ROWS; r++)
   {
      pinMode(rowPins[0], INPUT);   
      pullUpDnControl(rowPins[r], PUD_UP);
   }
}



int main ()
{
  int i;
  
  if (wiringPiSetup() == -1) exit(1) ;  //init wiringPi
  pinMode(BeepPin, OUTPUT);
  setupServo();
  // 10은 1ms, 15는 1.5ms(1500마이크로 초), 20은 2.0ms 이므로, HS-311기종의 경우, 10은 최저각, 15는 중립, 20은 최고각을 가리킨다.  
  init_keypad();
  setup();
  
  for(i=0;i<8;i++){
    MAX7219_WRITE(i+1, allOff[i]);
  }
  
   while(1)
   {
    char x[4] = {};
    int cnt = 0;
    while(cnt < 4){
      x[cnt] = get_key();
      if(x[cnt]) {
          delay(100);
          printf("pressed: %c %c %c %c\n", x[0],x[1],x[2],x[3]);
          
          char c = 'a';
          while(c) {
            c = get_key();
            printf("Wait");
            delay(50);
          }
          write_num(x[cnt]);
          cnt++;
      }
    }
    if(cnt >=4) {
      if (x[0] == '1' && x[1] == '2' && x[2] == '3' && x[3] == '4') {
         printf("pressed: %c\n", x[0]);
         for(i=0; i<8; i++){
            MAX7219_WRITE(i+1, success[i]);
        }
         openServo();
         openBuzzer();
         delay(1000);
         closeServo();
        for(i=0;i<8;i++){
        MAX7219_WRITE(i+1, allOff[i]);
      }
      }
      else if (x[0] == '*' && x[1] == '*' && x[2] == '*' && x[3] == '*') return 0;
      else {
        for(i=0; i<8; i++){
            MAX7219_WRITE(i+1, fail[i]);
        }
        errorBuzzer();
        delay(1000);
          for(i=0;i<8;i++){
            MAX7219_WRITE(i+1, allOff[i]);
          }
      }
      cnt = 0;
      delay(250);
    }
    }
  return 0;
}



#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <softPwm.h>
 
#define Servo 26
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
int main ()
{
  if (wiringPiSetup() == -1) exit(1) ;  //init wiringPi
 
  
 setupServo()
  // 10은 1ms, 15는 1.5ms(1500마이크로 초), 20은 2.0ms 이므로, HS-311기종의 경우, 10은 최저각, 15는 중립, 20은 최고각을 가리킨다
  openServo();
  closeServo();
  return 0;
}

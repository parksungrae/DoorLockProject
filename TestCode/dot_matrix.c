//=======================================
// dotMtx_01.c
// using shift functions
//=======================================
#include <stdio.h>
#include <wiringPi.h>
#include <wiringShift.h> // shift funciton
#define P_MAX_CLK 0 // BCM_GPIO #17
#define P_MAX_CS 2 // BCM_GPIO #27
#define P_MAX_DIN 3 // BCM_GPIO #22
const uint8_t image[] = { // 5x8 font
 0x1E, 0x12, 0x1E, 0x00, 0x04, 0x07, 0x04, 0x04, // 마
};
const uint8_t allOff[] = {
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
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
int main(void) {
 int i, j;
 int k;
 printf("[Dot Matrix testing....]\n");
 if(wiringPiSetup() == -1)
 return 1;
 setup();
 for(i=0; i<8; i++){
 MAX7219_WRITE(i+1, image[i]);
 delay(1000);
 }
 for(i=0; i<8; i++){
 MAX7219_WRITE(i+1, allOff[i]);
 }
 delay(1000);
 return 0;
}

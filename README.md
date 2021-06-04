# DoorLockProject

## Materials

Board : RaspberryPi 4

Module : Buzzer, LedDotMatrix, KeyPad, ServoMotor

other.. : register, jumper Cable, bread board

*Using Wiring Pi*

## Function

1. get 1 value(0~9) from keyPad 
2. print input value on DotMatrix 
<br> X 4
3. if 4 value == password, 
    * Control Servo motor(open Door)
    * LedMatrix emoticon (Good) 
    * Buzzer on 1000ms(good)
4. else,
    * reset input value to 0
    * LedMatrix(Bad)
    * Buzzer on 1000ms(bad)


[![Video Label](http://img.youtube.com/rglUoGtRLoI/2.jpg)](https://youtu.be/rglUoGtRLoI)
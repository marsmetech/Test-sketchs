//основу взял здесь https://create.arduino.cc/projecthub/eliott3005/pwm-and-direction-control-of-a-dc-motor-via-bluetooth-ced466
#include<SoftwareSerial.h>
SoftwareSerial bt_ser(4,5); //connected to RX and TX pins for serial data communication
char c[6];
int i=0,speed_value=0,send_value;

#define pwm1     9   //input 2
#define pwm2    10   //input 1

// const int BTState = 13; //Bluetooth (HC-05) State pin on pin 13of Arduino купить этот модуль 


void setup()
{
  Serial.begin(9600);
  bt_ser.begin(9600);
  pinMode(pwm1,   OUTPUT);
  pinMode(pwm2,   OUTPUT);
}

void loop()
{
   
  
   while(bt_ser.available())   //when data is transmitted
     {
       if(bt_ser.available()>0)
       {
         c[i] = bt_ser.read();   //reading the string sent from master device
         Serial.print(c[i]); 
         i++;  
       }
       
      }
       
       speed_value = (c[1]-48)*100+(c[2]-48)*10+(c[3]-48)*1;  //interpreting speed from string
       
       //Stop car when connection lost or bluetooth disconnected
    // if(digitalRead(BTState)==LOW) {c[i-1]=='s';}
       
            if(c[i-1]=='#')   //прямо 
              {analogWrite(pwm1, speed_value-100);  //-100 so that when slider is on "0" speed is 0
              analogWrite(pwm2, speed_value-100);
              i=0;}
         
            else if(c[i-1]=='l')  //налево 
                {analogWrite(pwm1, speed_value-100);
                analogWrite(pwm2, 0);
                i=0;}
              

          else if(c[i-1]=='r')   //направо
                {analogWrite(pwm1, 0);
                analogWrite(pwm2, speed_value-100);
                i=0;}
                
        
          else if(c[i-1]=='s')   //стоп
          {analogWrite(pwm1, 0);
           analogWrite(pwm2, 0);
           i=0;}
                 
            
}   

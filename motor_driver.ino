#include "HCPCA9685.h"
#define I2CAdd 0x40
int Servo0Position; 
int Servo1Position;     
HCPCA9685 HCPCA9685(I2CAdd);
 
void setup() {
 
  HCPCA9685.Init(SERVO_MODE);
  HCPCA9685.Sleep(false);
  Servo0Position = 155;                  // 위치값의 초기값을 400으로 설정합니다.
  HCPCA9685.Servo(0, Servo0Position);    // 서보모터를 서보모터 드라이버 0번에 연결합니다.
  Servo1Position = 160;                  // 위치값의 초기값을 400으로 설정합니다.
  HCPCA9685.Servo(1, Servo1Position);    // 서보모터를 서보모터 드라이버 1번에 연결합니다.

}
 
void loop() {
 

    delay(1000);                         // 1초간 지속
    
    Servo0Position = 345;                // 위치값 155의 위치로 이동
    HCPCA9685.Servo(0, Servo0Position);  
    delay(2000);                         // 1초간 지속
      
    Servo1Position = 110;                // 위치값 400 (초기 위치) 으로 이동
    HCPCA9685.Servo(1, Servo1Position);
    delay(2000);       
    Servo1Position = 160;                // 위치값 400 (초기 위치) 으로 이동
    HCPCA9685.Servo(1, Servo1Position);
    delay(2000);       
    
    Servo1Position = 210;                // 위치값 400 (초기 위치) 으로 이동
    HCPCA9685.Servo(1, Servo1Position);
    delay(2000);       
    Servo1Position = 160;                // 위치값 400 (초기 위치) 으로 이동
    HCPCA9685.Servo(1, Servo1Position);
    
    
    
    delay(2000); 
    
    Servo0Position = 155;                // 위치값 155의 위치로 이동
    HCPCA9685.Servo(0, Servo0Position);  
    delay(2000);     

    Servo1Position = 110;                // 위치값 400 (초기 위치) 으로 이동
    HCPCA9685.Servo(1, Servo1Position);
    delay(2000);       
    Servo1Position = 160;                // 위치값 400 (초기 위치) 으로 이동
    HCPCA9685.Servo(1, Servo1Position);
    delay(2000);       
    
    Servo1Position = 210;                // 위치값 400 (초기 위치) 으로 이동
    HCPCA9685.Servo(1, Servo1Position);
    delay(2000);       
    Servo1Position = 160;                // 위치값 400 (초기 위치) 으로 이동
    HCPCA9685.Servo(1, Servo1Position);

    

    
  
}

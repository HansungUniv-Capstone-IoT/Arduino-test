/*
* 엘레파츠 전자저울 예제 프로그램 - loadcell + HX711
* 사용 라이브러리 : https://github.com/bogde/HX711
* 
* 아두이노 GPIO 연결
* loadcell / HX711 board
* Dout PIN : D2
* SCK PIN  : D3
*/

#include "HX711.h"
#include "HCPCA9685.h"
#define I2CAdd 0x40
int Servo0Position; 
int Servo1Position;     
HCPCA9685 HCPCA9685(I2CAdd);

int distance1 = 0; // 거리값을 저장할 변수
int distance2 = 0;
int distance3 = 0;
int distance4 = 0;

// HX711 circuit wiring
#define LOADCELL_DOUT_PIN         2
#define LOADCELL_SCK_PIN          3
// scale - 10Kg loadcell : 226 / 5kg loadcell : 372
// ADC 모듈에서 측정된 결과값을 (loadcellValue)값 당 1g으로 변환해 줌
float loadcellValue = 226.0;
HX711 scale;

void setup() {
  HCPCA9685.Init(SERVO_MODE);
  HCPCA9685.Sleep(false);
  Servo0Position = 155;                  // 위치값의 초기값을 400으로 설정합니다.
  HCPCA9685.Servo(0, Servo0Position);    // 서보모터를 서보모터 드라이버 0번에 연결합니다.
  Servo1Position = 155;                  // 위치값의 초기값을 400으로 설정합니다.
  HCPCA9685.Servo(1, Servo1Position);    // 서보모터를 서보모터 드라이버 1번에 연결합니다.

	// put your setup code here, to run once:
	Serial.begin(115200);
	// 로드셀 HX711 보드 pin 설정
	scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
	// 부팅 후 잠시 대기 (2초)
	delay(2000);

	// 측정값 1회 읽어오기
	Serial.print("read: \t\t\t");
	Serial.println(scale.read());
	delay(1000);

	// 스케일 설정
	scale.set_scale(loadcellValue);
	
	// 오프셋 설정(10회 측정 후 평균값 적용) - 저울 위에 아무것도 없는 상태를 0g으로 정하는 기준점 설정(저울 위에 아무것도 올려두지 않은 상태여야 합니다.)   
	scale.tare(10);    

	// 설정된 오프셋 및 스케일 값 확인
	Serial.print("Offset value :\t\t");
	Serial.println(scale.get_offset());
	Serial.print("Scale value :\t\t");
	Serial.println(scale.get_scale());

	// (read - offset) 값 확인 (scale 미적용)
	Serial.print("(read - offset) value: \t");  
	Serial.println(scale.get_value());
	delay(2000);
}


void loop() {
	// put your main code here, to run repeatedly:

	// 오프셋 및 스케일이 적용된 측정값 출력 (5회 측정 평균값) 
	Serial.print("value :\t");
  float scaleResult = scale.get_units(5);
	Serial.print(scaleResult, 2);    // 5회 측정 평균값, 소수점 아래 2자리 출력
	Serial.println(" g");
	delay(1000);  // 1초 대기

  int volt1 = map(analogRead(A0), 0, 1023, 0, 5000); // 0~1023 사이 값을 갖는 아날로그 신호값을  //  0~5000 (5V) 사이 값으로 변환
  int volt2 = map(analogRead(A1), 0, 1023, 0, 5000);
  int volt3 = map(analogRead(A2), 0, 1023, 0, 5000);
  int volt4 = map(analogRead(A3), 0, 1023, 0, 5000);
  
  distance1 = (27.61 / (volt1 - 0.1696)) * 1000; // 읽어들인 Voltage 값을 거리값(단위: cm)로 변환하는 공
  distance2 = (27.61 / (volt2 - 0.1696)) * 1000;
  distance3 = (27.61 / (volt3 - 0.1696)) * 1000;
  distance4 = (27.61 / (volt4 - 0.1696)) * 1000;
  
  Serial.print(distance1);  //거리값을 시리얼모니터로 출력해줍니다.
  Serial.print(" cm \n");
  Serial.print(distance2);
  Serial.print(" cm \n");
  Serial.print(distance3);
  Serial.print(" cm \n");
  Serial.print(distance4);
  Serial.print(" cm \n \n");
  delay(1000);

  
    if(scaleResult < 40 && scaleResult > 20)
    {
      delay(1000);                         // 1초간 지속
      Servo0Position = 400;                // 위치값 155의 위치로 이동
      HCPCA9685.Servo(0, Servo0Position);  
      delay(2000);                         // 2초간 지속
      Servo0Position = 155;                // 위치값 400 (초기 위치) 으로 이동
      HCPCA9685.Servo(0, Servo0Position);
      Serial.println("can");
      delay(2000);
    }
    
    
    else if( scaleResult > 40){
      delay(1000);                         // 1초간 지속
      Servo1Position = 400;                // 위치값 155의 위치로 이동
      HCPCA9685.Servo(1, Servo1Position);  
      delay(2000);                         // 2초간 지속
      Servo1Position = 155;                // 위치값 400 (초기 위치) 으로 이동
      HCPCA9685.Servo(1, Servo1Position);
      Serial.println("plastic");
      delay(2000);
    }

    else if( scaleResult < 20){
      Servo0Position = 155;                // 위치값 155의 위치로 이동
      HCPCA9685.Servo(0, Servo0Position);  
      Servo1Position = 155;                // 위치값 400 (초기 위치) 으로 이동
      HCPCA9685.Servo(1, Servo1Position);
      delay(100);
    }

   	
}

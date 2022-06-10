int distance1 = 0; // 거리값을 저장할 변수
int distance2 = 0;
int distance3 = 0;
int distance4 = 0;

void setup(){
  Serial.begin(9600); // PC와의 시리얼 통신속도를 9600bps로 설정
}
 
 
void loop(){
 
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
  Serial.print(" cm \n");
  delay(3000);

}

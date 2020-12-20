#include <Keyboard.h>
#include <SPI.h>    // RFID를 위한 SPI 라이브러
#include <MFRC522.h>// RFID 라이브러
 
#define SS_PIN 10   //RFID SS(SDA:ChipSelect) PIN
#define RST_PIN 9   //RFID Reset PIN
MFRC522 rfid(SS_PIN, RST_PIN); //RFID 라이브러리
  
void setup() { 
  //시리얼 모니터 시작
  Serial.begin(9600);
  SPI.begin(); // SPI 시작
  rfid.PCD_Init(); // RF 모듈 시작 
}
 
void loop() {
  //카드가 인식 안되었다면 더이상 진행하지 말고 빠져나감
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
 
  //RF카드의 ID가 인식 안되었다면 더이상 진행하지 말고 빠져나감
  if ( ! rfid.PICC_ReadCardSerial())
    return;
 
 
  Serial.print(F("PICC type: "));
  //PICC 타입 읽어오기
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));
 
 
  //MIFARE 방식이 아니라면 더이상 진행하지 말고 빠져나감
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }
 
  //RFID UID를 Keyboard Input으로 전달
  delay(100);
  printHex(rfid.uid.uidByte, rfid.uid.size);  
  delay(100);
  Keyboard.write (KEY_RETURN);
  delay(100);
  
  //종료
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
 
  //다시 시작
}
 
//16진수 to 10진수
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    //Keyboard.print(buffer[i] < 0x10 ? " 0" : " ");
    Keyboard.print(buffer[i]);
  }
}

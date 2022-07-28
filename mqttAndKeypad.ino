#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
 
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {10, 9, 8, 7};
byte colPins[COLS] = {6, 5, 4};
 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LiquidCrystal_I2C lcd(0x3F, 16, 2);//coba juga 0x27
 
char stringAngka[17];
int indexKeypad = 0;
String data = "";
void setup() {
  Serial.begin(9600);
  Serial3.begin(115200);
  Serial.println();
        for(int i = 0; i< sizeof(stringAngka); i++){
            stringAngka[i] = '0';
          }
  Wire.begin();
  Wire.beginTransmission(0x3F);
  if (Wire.endTransmission())
  {
    lcd = LiquidCrystal_I2C(0x27, 16, 2);
  }
  lcd.init();
  lcd.backlight();
  lcd.print("Hallo");
  delay(3000);
  lcd.clear();
}

void loop() {
  getNumber();
  
}

void sendData(int number){
    
    data += "Tebakan :";
    data += number;
    Serial3.println(data);
  }

void getNumber(){
  int nilaiAngka;
  
  char key = keypad.getKey();
  lcd.setCursor(0, 0);
  lcd.print("Input Angka:");
  lcd.print(stringAngka);
  if (key) {
    
    //Serial.println(key);
    switch (key)
    {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        if (!indexKeypad)
        {
          lcd.clear();
        }
        stringAngka[indexKeypad++] = key;
        //lcd.print(key);
        break;
      case '*'://reset
        for(int i = 0; i< sizeof(stringAngka); i++){
            stringAngka[i] = '0';
          }
        lcd.clear();
        indexKeypad = 0;
        break;
      case '#':
        
        stringAngka[indexKeypad] = 0;
        lcd.setCursor(0, 1);
 
        nilaiAngka = atoi(stringAngka);
        lcd.print(nilaiAngka);
        lcd.print(" DIKIRIM");
        sendData(nilaiAngka);
        for(int i = 0; i< sizeof(stringAngka); i++){
            stringAngka[i] = '0';
          }
        indexKeypad = 0;
        break;
    }
    
  }
  }

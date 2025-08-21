#include <Wire.h>
//#include <I2Cdev.h>
//#include <MPU6050.h>
#include <Mouse.h>
#include <Keyboard.h>
#include <SoftwareSerial.h>

// Definicje pinów dla modułu Bluetooth
const int bluetoothTx = 2; // Pin TX modułu Bluetooth, podłączony do pinu RX Arduino
const int bluetoothRx = 3; // Pin RX modułu Bluetooth, podłączony do pinu TX Arduino

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

const int button[6] = {A0, A1, A2, A3, A4, A5}; // Button numbers in table

bool button_state[6] = {false, false, false, false, false, false}; // Button states in a table

int number_of_combination = 0;

char chosen_letter;

bool input_done = false;

float czytaj_rezystancje(int sensorValue)
{
  float referenceResistance = 10000.0; // przykładowa wartość
  
  // Napięcie referencyjne (w tym przypadku 3V)
  float referenceVoltage = 3.0;
  
  // Obliczenie napięcia na tensometrze
  float voltage = (sensorValue / 1023.0) * referenceVoltage;
  
  // Obliczenie rezystancji tensometru za pomocą prawa dzielników napięcia
  float resistance = referenceResistance * (referenceVoltage / voltage - 1);

  return resistance;
}

//Function for updating button states
void check_button_states(int how_much_buttons)
{
  for(int i = 0; i < how_much_buttons; i++)
  {
    if (czytaj_rezystancje(analogRead(button[i]))<6500) button_state[i] = true;
    else button_state[i] = false;
  }
}

char button_translation(int number)
{
  char letter;
  switch (number){
    case 1:
      letter = 'a';
      break;
  }
  return letter;
}

int boolToInt(bool b1, bool b2, bool b3, bool b4, bool b5, bool b6) {
  int result = 0;

  // Ustawianie kolejnych bitów na podstawie wartości boolowskich
  result |= b1 << 5;
  result |= b2 << 4;
  result |= b3 << 3;
  result |= b4 << 2;
  result |= b5 << 1;
  result |= b6;

  return result;
}

bool checkAllFalse(bool tablica[][numCols]) {
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {
      if (tablica[i][j]) {
        return false; // Zwraca false, jeśli znaleziono true
      }
    }
  }
  return true; // Zwraca true, jeśli wszystkie wartości są false
}










void setup() {
  Serial.begin(9600); // Inicjalizacja komunikacji szeregowej
  Keyboard.begin(KeyboardLayout_en_US);
  Wire.begin();
  bluetooth.begin(9600);
  Serial.write("AT+NAMEYourDeviceName\r\n");
  //bluetooth.print("AT+ROLE1\r\n");
  //delay(500);
  //bluetooth.print("AT+NAMEYourDeviceName\r\n");
  //delay(500);
  //bluetooth.print("AT+PSWD1234\r\n");
  //delay(500);
}

//void button_state(number) {
//  print();
//}



void loop() {
  check_button_states(6);

  number_of_combination = boolToInt(button_state[0], button_state[1], button_state[2], button_state[3], button_state[4], button_state[5]);

  Serial.print(number_of_combination); 

  chosen_letter = button_translation(number_of_combination);
  
  if (!input_done)
  {
    //Keyboard.write(chosen_letter);
    input_done = true;
  }
  if(input_done && checkAllFalse(button_state))
  {

  }

  if (bluetooth.available()) {
    //char receivedChar = bluetooth.read(); // Odczyt pojedynczego znaku
    Serial.print("BT available"); // Wyświetlenie otrzymanego znaku w monitorze szeregowym
  }

  delay(1000); // Pauza na sekundę
}

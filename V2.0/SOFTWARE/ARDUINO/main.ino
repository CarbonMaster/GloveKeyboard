const int tensometerPins[] = {A0, A1, A2, A3, A4}; // Piny analogowe
const int tensometer_number = 5;
const int digitalPins[] = {0,2,4,7,8}; // Piny cyfrowe do sterowania stanem
// const int numSamples = 10; // Liczba próbek do średniej

int tensometerValues[tensometer_number];
int tensometer_off_Values[tensometer_number];
int tensometer_on_Values[tensometer_number];
bool tensometer_bool_Values[tensometer_number];
bool allSensorsAboveThreshold = true;

void setup() {
  // pinMode(DOUT, OUTPUT);
  for(int pin = 0; pin < tensometer_number; pin++)
  {
    pinMode(digitalPins[pin], OUTPUT);
  }
  Serial.begin(9600);
  setup_tensometers();
}

void loop() {

  // Odczyt z każdego tensometru (średnia z kilku próbek)
  read_temsometer_values();
  update_digital_ports();
  print_bool_states();

  delay(1000); // Opóźnienie, aby zmniejszyć obciążenie procesora
}

void setup_tensometers()
{
  for (int i = 0; i < tensometer_number; i++) 
  {
    Serial.println("Release previous tensometer");
    delay(5000);
    tensometer_off_Values[i] = readTensometer(tensometerPins[i], 1000);
    Serial.println("Press ");
    Serial.print("tensometer ");
    Serial.print(i);
    Serial.println("");
    int tries = 0;
    int tries_max = 5;
    while(true)
    {
      tries++;
      delay(1000);
      Serial.println("Waiting...");
      if(readTensometer(tensometerPins[i], 10) > tensometer_off_Values[i] + 100) break;
      else if (tries>tries_max) break;
    }
    Serial.println("Recording...");
    tensometer_on_Values[i] = readTensometer(tensometerPins[i],1000);
    Serial.println("Tensometer calibrated. Next step.");
  }

  Serial.println("Off values");
  for (int i = 0; i < tensometer_number; i++) 
  {
    Serial.print(tensometer_off_Values[i]);
    Serial.print("\t");
    Serial.println("");
  }
  
  Serial.println("On values");
  for (int i = 0; i < tensometer_number; i++) 
  {
    Serial.print(tensometer_on_Values[i]);
    Serial.print("\t");
    Serial.println("");
  }

  Serial.println("Tensometers are CALIBRATED. Proceed.");
}

// Funkcja odczytująca średnią z 10 próbek
int readTensometer(int pin, int numSamples) {
  long sum = 0;
  for (int i = 0; i < numSamples; i++) {
    sum += analogRead(pin);
    //delay(10); // Krótkie opóźnienie między próbkami
  }
  return sum / numSamples; // Zwraca średnią wartość
}

void read_temsometer_values()
{
  for (int pin = 0; pin < tensometer_number; pin++) 
  {
    // Serial.print("Tensometer ");
    // Serial.print(i);
    // Serial.print(": ");
    tensometerValues[pin] = readTensometer(tensometerPins[pin], 10);
    tensometer_bool_Values[pin] = ( (tensometer_on_Values[pin]-20 < tensometerValues[pin]) ? true : false);
    // Serial.print(tensometerValues[pin]);
    // Serial.print("\t");

    // Sprawdzanie, czy wartość jest poniżej progu (przykład: 500)
  }
  // Serial.println("");
}

void print_bool_states()
{
  Serial.println("Bools");
  for (int pin = 0; pin < tensometer_number; pin++) 
  {
    Serial.print(tensometer_bool_Values[pin]);
    Serial.print("\t");
  }
  Serial.println("");
  for (int pin = 0; pin < tensometer_number; pin++) 
  {
    Serial.print(tensometerValues[pin]);
    Serial.print("\t");
  }
  Serial.println("");
  Serial.println("DOUTS");
  for (int pin = 0; pin < tensometer_number; pin++) 
  {
    bool value = digitalRead(digitalPins[pin]);
    Serial.print(value);
    Serial.print("\t");
  }
  Serial.println("");
}

void update_digital_ports()
{
  for (int pin = 0; pin < tensometer_number; pin++) 
  {
    switch(tensometer_bool_Values[pin])
    {
      case true:
        digitalWrite(digitalPins[pin], HIGH);
        // Serial.print(digitalPins[pin]);
        break;
      case false:
        digitalWrite(digitalPins[pin], LOW);
        break;
    }
  }
}

const int how_much_buttons = 6;

const int button[how_much_buttons] = {A0, A1, A2, A3, A4, A5}; // Button numbers in table
int out_digital_port[how_much_buttons] = {2, 3, 4, 5, 6, 7}; // Button numbers in table
bool button_state[how_much_buttons] = {false, false, false, false, false, false}; // Button states in a table


float czytaj_rezystancje(int sensorValue)
{
  long sum = 0;
  for (int i = 0; i < numSamples; i++) {
    sum += analogRead(pin);
    //delay(10); // Krótkie opóźnienie między próbkami
  }
  return sum / numSamples; // Zwraca średnią wartość
}

void check_button_states()
{
  for(int i = 0; i < how_much_buttons; i++)
  {
    if (czytaj_rezystancje(analogRead(button[i])) > 10000)
    //6500
    {
      button_state[i] = true;
    }
    else 
    {
      button_state[i] = false;
    }
  }
}

void set_digital_outputs()
{
  for(int i = 0; i < how_much_buttons; i++)
  {
    out_digital_port[i] = button_state[i];
    Serial.print(button_state[i]); 
  }
  Serial.println("");
}

void setup() {
  for(int i = 0; i < how_much_buttons; i++)
  {
    pinMode(button[i], INPUT);
    pinMode(out_digital_port[i], OUTPUT);
  }
}

void loop() {
  check_button_states();
  set_digital_outputs();
  delay(100);
}

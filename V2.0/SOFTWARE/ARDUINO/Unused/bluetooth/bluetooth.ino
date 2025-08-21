
#include <SoftwareSerial.h>  //Usaremos el puerto serial personalizado
char rec;
SoftwareSerial blue(4,5); //Rx,Tx

const int PinDatos = 3;  // Verde
const int PinReloj =  2;  // Blanco

void setup() 

{
  delay(1000);
  blue.begin(9600);
}

void loop() 
{
      
}

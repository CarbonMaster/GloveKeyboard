#include <PS2Keyboard.h>
#include <SoftwareSerial.h>  //Usaremos el puerto serial personalizado
char rec;
SoftwareSerial blue(4,5); //Rx,Tx

const int PinDatos = 3;  // Verde
const int PinReloj =  2;  // Blanco

PS2Keyboard teclado;

void setup() 

{

  delay(1000);

  teclado.begin(PinDatos, PinReloj);

  blue.begin(9600);

}

void loop() 
{
  // Si el teclado está disponible
  if (teclado.available()) {
    
    // Lee la tecla presionada
    char c = teclado.read();
    
    // Revisa algunas teclas especiales
    if (c == PS2_ENTER) {
      blue.println("ent");
    } else if (c == PS2_TAB) {
      blue.println("tab");
    } else if (c == PS2_ESC) {
      blue.println("esc");
    } else if (c == PS2_BACKSPACE) {
      blue.println("bsp");
    } else if (c == PS2_PAGEDOWN) {
      blue.println("pgd");
    } else if (c == PS2_PAGEUP) {
      blue.println("pgu");
    } else if (c == PS2_LEFTARROW) {
      blue.println("lft");
    } else if (c == PS2_RIGHTARROW) {
      blue.println("rgt");
    } else if (c == PS2_UPARROW) {
      blue.println("upk]");
    } else if (c == PS2_DOWNARROW) {
      blue.println("dwn");
    } else if (c == PS2_DELETE) {
      blue.println("del");
    } else {
      
      // Si no, imprime los caracteres normales
     
      blue.println(c);
      
      
    }
  }
}


/*
 Name:    geekino.ino
 Created: 9/28/2016 8:59:38 AM
 Author:  kharl
*/

#include <MFRC522.h>
#include <SPI.h>

#define RST_PIN 9                                // Pin 9 para el reset del RC522
#define SS_PIN 10                                // Pin 10 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN);                 // Creamos el objeto para el RC522
// Configuramos los pines para el color del LED y el Buzzer
int red = 2;                          
int green = 3;                        
int blue = 4;
int buzz = 5;


void setup() {
  Serial.begin(9600);                 //Iniciamos la comunicaciÃƒÂ³n serial
  SPI.begin();                        // Iniciamos el Bus SPI
  mfrc522.PCD_Init();                 // Iniciar el objeto mrfc522
  // Activamos los pines como salida
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(buzz, OUTPUT);


}

void loop() {

/*
 * Esta sección se encarga de escuchar el perto serial (COM),
 * si hay un flujo de datos entrante se activan diferentes c
 * colores en el led.
 * Se activara el Azul cuando se inicia la aplicación
 * y el rojo cuando se esta cerrando.
 */
  if(Serial.available())
  {
    int val = Serial.read() -'0';
    if(val == 1)
    {
      led(red, 0, 0);
      led(green, 0, 0);   
      led(blue, 1, 1000);
      led(blue, 0, 0);
    }
    else if(val == 0)
    {
      led(blue, 0, 0);
      led(green, 0, 0);
      led(red, 1, 1000);
      led(red, 0, 0);
    }
    
  }
  
  MFRC522::MIFARE_Key key;
  for(byte i = 0; i < 6; i++) 
  {
    key.keyByte[i] = 0xFF;
  }

  if(! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  //Select one of th cards
  if( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  Serial.print(F("\nCard UID"));
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? "0" : " ");
    Serial.print(mfrc522.uid.uidByte[i] , HEX);
  }
  Serial.print(F(" PICC_Type: "));
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.println(mfrc522.PICC_GetTypeName(piccType));
  

  
}

//Controlar el apagado o encendido del LED de estatus.
void led(int color, char estado, int tme)
{
  if (estado == 0)
  {
    digitalWrite(color, LOW);
    delay(tme);
    
    return;
  }
  else if (estado == 1)
  {
    digitalWrite(color, HIGH);
    delay(tme);
    return;
  }

}
// Funcion para emitir sonido(beep)
void beep(int frec, int duration)
{
  tone(buzz, frec, duration);
  return;
}

/* Interaccion con la tarjeta RFID
 * y poder modificar u operar con los
 * demas registros del chip
 */


















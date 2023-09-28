/**
 * MCU: ATtiny2313 - 1MHz
 * 
 * Com base na leitura do horário a partir do DS1307, ativa o rele no PD6 no momento estipulado.
 * A cada leitura do horário, o LED em PB2 pisca, ao acionar o rele, o LED permanesse aceso.
 */

#include <TinyWireM.h>

#define DS1307_ADDR 0x68
#define RELE_PIN    8     //PD6
#define LED_PIN     11    //PB2

#define HORA_ON   0x06
#define MINUTO_ON 0x46

bool passou = 0;

byte minuto = 0;
byte hora = 0;

void setup() {
  TinyWireM.begin();

  pinMode(RELE_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  
  digitalWrite(RELE_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  delay(1000);
}

void loop() {
  if(!passou) {
    getHorario();

    digitalWrite(LED_PIN, HIGH);

    if(hora == HORA_ON && minuto >= MINUTO_ON) {
      passou = 1;
      digitalWrite(RELE_PIN, HIGH);
    } else {
      delay(100);
      digitalWrite(LED_PIN, LOW);
    }
    
  }

  delay(1000);

}

void getHorario() {

  //Define o registrador do DS1307 para recuperar o horário a pardir dos minutos  
  TinyWireM.beginTransmission(DS1307_ADDR);
  TinyWireM.send(1);
  TinyWireM.endTransmission(); //TODO: Check error

  //Recupera minuto e hora  
  TinyWireM.requestFrom(DS1307_ADDR, 2); //TODO: Check error
  delay(10);
  minuto = TinyWireM.receive();
  hora = TinyWireM.receive();  
}

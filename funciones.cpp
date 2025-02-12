#include "HardwareSerial.h"

#include "funciones.h"
#include "Arduino.h"
const float referencia=(5.0/1023.0);
int lectura1= 0;
int lectura2= 0;
float voltaje1=0;
float voltaje2=0;

bool determinarConfiguracion(int pinReferencia,int pin1in, int pin2in, int pin3in, int pin1, int pin2, int pin3) {
    // Activamos los pines de salida
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, HIGH);
    digitalWrite(pin3, LOW);

    // Leer las entradas analógicas
    int lectura1 = analogRead(pin2in);  // Leer el valor del ADC (0 - 1023)
    int lectura2 = analogRead(pin3in);  // Leer el valor del ADC (0 - 1023)
    int lectura3 = analogRead(pinReferencia);  // Leer el valor del ADC (0 - 1023)

    // Convertir a voltaje
    float voltaje = (lectura3 / 1023.0) * 5.0;  // Voltaje en el pin de referencia

    // Caso 1: Si la diferencia entre lectura3 y lectura1 es significativa
    if (abs(lectura3 - lectura1) > 0.7) {
        // Asignamos la base según el pinReferencia
               configuracion_pines = pinReferencia==pin1?"BEC":pinReferencia==pin2?"BBB":"BBB";
     
        // Determinamos si es NPN o PNP
       
        configuracion = (lectura3 - lectura1 > 0.7) ? "NPN" : "PNP";
        return true;
    }

    // Caso 2: Si la diferencia entre lectura3 y lectura2 es significativa
    if (abs(lectura3 - lectura2) > 0.7) {
 // Asignamos la base según el pinReferencia
        if (pinReferencia == pin1) {
            configuracion_pines = "BEC";
        } else if (pinReferencia == pin2) {
          configuracion_pines = "CEB";
           } else if (pinReferencia == pin3) {
          configuracion_pines = "ECB";
    
        }

        // Determinamos si es NPN o PNP
        configuracion = (lectura3 - lectura2 > 0.7) ? "NPN" : "PNP";
        return true;
    }

    return false;  // Si no se cumplen las condiciones anteriores
}

bool probador_diodo(int pin1out,int pin2out, int pin1in,int pin2in){
  digitalWrite(pin1out, HIGH);
  digitalWrite(pin2out, LOW);
  delay(5);
  lectura1= analogRead(pin1in);
  lectura2= analogRead(pin2in);
  voltaje1=lectura1*referencia;
  voltaje2=lectura2*referencia;
  float voltaje_diodo=abs(-voltaje1+voltaje2);
 
  //Probar si es un diodo ZENER
  if(voltaje_diodo>2.5&&voltaje_diodo<4.7){
    Serial.println("Es un diodo zener");
    Serial.print("A:" );
    Serial.println(pin1in);
    Serial.print("C:");
    Serial.println(pin2in);
    return true;
  }
 digitalWrite(pin1out, LOW);
  digitalWrite(pin2out, HIGH);
  delay(5);
  lectura1= analogRead(pin1in);
  lectura2= analogRead(pin2in);
  voltaje1=lectura1*referencia;
  voltaje2=lectura2*referencia;
  voltaje_diodo=abs(voltaje1-voltaje2);
  
   if(voltaje_diodo>2.5&&voltaje_diodo<4.7){
    Serial.println("Es un diodo zener");
    Serial.print("A:" );
    Serial.println(pin2in);
    Serial.print("C:");
    Serial.println(pin1in);
    return true;
  }
 
 delay(1000);
   
   if(0.6<voltaje_diodo &&  voltaje_diodo <0.8) {
      Serial.print("A:" );
      Serial.println(pin1in);
     
     Serial.print("C:");
      Serial.println(pin2in);
      return true;
     } 
      digitalWrite(pin1out, HIGH);
     digitalWrite(pin2out, LOW);
     delay(5);
     lectura1= analogRead(pin1in);
     lectura2= analogRead(pin2in);
    voltaje1=lectura1*referencia;
    voltaje2=lectura2*referencia;
     voltaje_diodo=-voltaje1+voltaje2;
    Serial.println(voltaje_diodo);
     if(0.6<voltaje_diodo &&  voltaje_diodo <0.8 ) {
      Serial.print("C:" );
      Serial.println(pin1in);
       Serial.print("A:");
      Serial.println(pin2in);
      return true;
     } 
     Serial.println("No es un diodo");
     digitalWrite(pin1out, LOW);
  digitalWrite(pin2out, LOW);
     return false;

}
void medir_resistencia(int pin1out,int pin2out, int pin1in){
  digitalWrite(pin1out, LOW);
  digitalWrite(pin2out, HIGH);
  delay(5);
  lectura1= analogRead(pin1in);
  voltaje1=lectura1*referencia;
  Serial.println(voltaje1);
  float resistencia=(5000-2000*voltaje1)/(voltaje1-5);
  Serial.print("Resistencia medida: ");
  Serial.print(resistencia);
  Serial.println("Ω");
  digitalWrite(pin1out, LOW);
  digitalWrite(pin2out, LOW);  
}
void medir_voltaje(int pin1out,int pin2out, int pin1in,int pin2in){
  pinMode(pin1out, INPUT);
  pinMode(pin2out, INPUT);
  pinMode(pin1in, OUTPUT);
  digitalWrite(pin1in, LOW);
  delay(5);
  lectura1=analogRead(pin2in);
  voltaje1=lectura1*referencia;
  Serial.print(" Voltaje medido: ");
  Serial.println(voltaje1);
  pinMode(pin1out, OUTPUT);
  pinMode(pin1out, OUTPUT);
  pinMode(pin1in, INPUT);
}
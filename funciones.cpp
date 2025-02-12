#include "HardwareSerial.h"

#include "funciones.h"
#include "Arduino.h"
const float referencia=(5.0/1024.0);
float lectura1= 0;
float lectura2= 0;
float lectura3= 0;
float voltaje1=0;
float voltaje2=0;
float voltaje3=0;
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
  if(voltaje_diodo>2&&voltaje_diodo<4.7){
    Serial.println("Es un diodo zener");
    Serial.print("A:" );
    Serial.println(pin1in);
    Serial.print("C:");
    Serial.println(pin2in);
    Serial.print("Voltaje zener: ");
    Serial.println(voltaje_diodo);
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
  
   if(voltaje_diodo>2&&voltaje_diodo<4.7){
    Serial.println("Es un diodo zener");
    Serial.print("A:" );
    Serial.println(pin2in);
    Serial.print("C:");
    Serial.println(pin1in);
    Serial.print("Voltaje zener: ");
    Serial.println(voltaje_diodo);
    return true;
  }
 
  
   if(0.6<voltaje_diodo &&  voltaje_diodo <0.8) {
      Serial.print("C:" );
      Serial.println(pin1in);
     
     Serial.print("A:");
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
      Serial.print("A:" );
      Serial.println(pin1in);
       Serial.print("C:");
      Serial.println(pin2in);
      return true;
     } 
     Serial.println("No es un diodo");
     digitalWrite(pin1out, LOW);
  digitalWrite(pin2out, LOW);
     return false;

}
void medir_resistencia(int pin1out,int pin2out, int pin1in){
  digitalWrite(pin1out, HIGH);
  digitalWrite(pin2out, LOW);
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
  pinMode(pin2in, OUTPUT);
  digitalWrite(pin2in, LOW);
  delay(5);
  lectura1=analogRead(pin1in);
  voltaje1=lectura1*referencia;
  Serial.print(" Voltaje medido: ");
  Serial.println(voltaje1);
  pinMode(pin1out, OUTPUT);
  pinMode(pin1out, OUTPUT);
  pinMode(pin2in, INPUT);
}



void determinar_bjt(int pin1out, int pin2out, int pin3out, int pin1in, int pin2in, int pin3in) {
    Serial.println("Determinar BJT");
    float beta=0;
    float voltaje_prueba = 0;
    float voltaje_prueba1 = 0;

    for (int i = 0; i < 3; i++) {
        switch (i) {
            case 0:
                Serial.println("Primer caso");

                digitalWrite(pin1out, HIGH);
                pinMode(pin2out, LOW);
                digitalWrite(pin3out, LOW);

                lectura1 = analogRead(pin1in);
                voltaje1 = lectura1 * referencia;
                lectura2 = analogRead(pin2in);
                voltaje2 = lectura2 * referencia;
                lectura3 = analogRead(pin3in);
                voltaje3 = lectura3 * referencia;

                voltaje_prueba = voltaje1 - voltaje2;
                voltaje_prueba1 = voltaje1 - voltaje3;
                

               

                if (0.6 < voltaje_prueba && voltaje_prueba < 0.9) {
                   
                    Serial.println("Es un NPN con la siguiente configuración:");
                    if (abs(voltaje_prueba) > abs(voltaje_prueba1)) {
                        Serial.println("BEC");
                        beta=(5-voltaje3)/(5-voltaje1);
                         Serial.print("Beta: ");
                         Serial.print(beta);
                    } else {
                        Serial.println("BCE");
                        beta=(5-voltaje2)/(5-voltaje1);
                         Serial.print("Beta: ");
                         Serial.print(beta);
                    }
                                        return;

                } else if (-0.9 < voltaje_prueba && voltaje_prueba < -0.6) {
                    Serial.println("Es un PNP con la siguiente configuración:");
                    if (abs(voltaje_prueba) > abs(voltaje_prueba1)) {
                        Serial.println("BEC");
                        beta=(5+voltaje3)/(5-voltaje1);
                         Serial.print("Beta: ");
                         Serial.print(beta);
                    } else {
                        Serial.println("BCE");
                         beta=(5+voltaje1)/(5-voltaje1);
                         Serial.print("Beta: ");
                         Serial.print(beta);
                    }
                    return;
                }
                break;

            case 1:
                Serial.println("Segundo caso");

                digitalWrite(pin1out, LOW);
                digitalWrite(pin2out, HIGH);
                digitalWrite(pin3out, LOW);

                lectura1 = analogRead(pin2in);
                voltaje1 = lectura1 * referencia;
                lectura2 = analogRead(pin1in);
                voltaje2 = lectura2 * referencia;
                lectura3 = analogRead(pin3in);
                voltaje3 = lectura3 * referencia;

                voltaje_prueba = voltaje1 - voltaje2;
                voltaje_prueba1 = voltaje1 - voltaje3;

                Serial.println(voltaje1);
                Serial.println(voltaje2);
                Serial.println(voltaje3);
                Serial.println(voltaje_prueba1);
                Serial.println(voltaje_prueba);

                if (0.6 < voltaje_prueba && voltaje_prueba < 0.9) {
                    Serial.println("Es un NPN con la siguiente configuración:");
                    if (abs(voltaje_prueba) > abs(voltaje_prueba1)) {
                        Serial.println("CBE");
                         beta=(5-voltaje3)/(5-voltaje1);
                         Serial.print("Beta: ");
                         Serial.print(beta);
                    } else {
                        Serial.println("EBC");
                         beta=(5-voltaje2)/(5-voltaje1);
                         Serial.print("Beta: ");
                         Serial.print(beta);
                    }
                    return;
                } else if (-0.9 < voltaje_prueba1 && voltaje_prueba1 < -0.6) {
                    Serial.println("Es un PNP con la siguiente configuración:");
                    if (abs(voltaje_prueba) > abs(voltaje_prueba1)) {
                        Serial.println("CBE");
                         beta=(5+voltaje3)/(5-voltaje1);
                         Serial.print("Beta: ");
                         Serial.print(beta);
                    } else {
                        Serial.println("EBC");
                         beta=(5+voltaje2)/(5-voltaje1);
                         Serial.print("Beta: ");
                         Serial.print(beta);
                    }
                    return;
                }
                break;

            case 2:
                Serial.println("Tercer caso");

                digitalWrite(pin1out, LOW);
                digitalWrite(pin2out, LOW);
                digitalWrite(pin3out, HIGH);

                lectura1 = analogRead(pin3in);
                voltaje1 = lectura1 * referencia;
                lectura2 = analogRead(pin1in);
                voltaje2 = lectura2 * referencia;
                lectura3 = analogRead(pin2in);
                voltaje3 = lectura3 * referencia;

                voltaje_prueba = voltaje1 - voltaje2;
                voltaje_prueba1 = voltaje1 - voltaje3;

                Serial.println(voltaje1);
                Serial.println(voltaje2);
                Serial.println(voltaje3);
                Serial.println(voltaje_prueba1);
                Serial.println(voltaje_prueba);

                if (0.6 < voltaje_prueba && voltaje_prueba < 0.9) {
                    Serial.println("Es un NPN con la siguiente configuración:");
                    if (abs(voltaje_prueba) > abs(voltaje_prueba1)) {
                        Serial.println("CEB");
                         beta=(5-voltaje3)/(5-voltaje1);
                         Serial.print("Beta: ");
                         Serial.print(beta);
                    } else {
                        Serial.println("ECB");
                         beta=(5-voltaje2)/(5-voltaje1);
                         Serial.print("Beta: ");
                         Serial.print(beta);
                    }
                                        return;

                } else if (-0.9 < voltaje_prueba1 && voltaje_prueba1 < -0.6) {
                    Serial.println("Es un PNP con la siguiente configuración:");
                    if (abs(voltaje_prueba) > abs(voltaje_prueba1)) {
                        Serial.println("CEB");
                         beta=(5+voltaje3)/(5-voltaje1);
                         Serial.print("Beta: ");
                         Serial.print(beta);
                    } else {
                        Serial.println("ECB");
                         beta=(5+voltaje2)/(5-voltaje1);
                         Serial.print("Beta: ");
                         Serial.print(beta);
                    }
                    return;
                }
                break;

            default:
                Serial.println("No se pudo determinar si es un BJT");
                break;
        }
    }
    delay(1000);
}


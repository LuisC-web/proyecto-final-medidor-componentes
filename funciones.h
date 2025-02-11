// funciones.h

#ifndef FUNCIONES_H   // Esto evita que se incluya varias veces
#define FUNCIONES_H
#include <Arduino.h>  // Esto es esencial para las funciones de Arduino, como digitalWrite, analogRead, etc.

extern String configuracion_pines;
extern String configuracion;  // Crea un String con el valor "ABC"

bool determinarConfiguracion(int pinReferencia,int pin1in,int pin2in, int pin3in,int pin1, int pin2,int pin3);
bool probador_diodo(int pin1out,int pin2out, int pin1in,int pin2in);



#endif

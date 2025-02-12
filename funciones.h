// funciones.h

#ifndef FUNCIONES_H   // Esto evita que se incluya varias veces
#define FUNCIONES_H
#include <Arduino.h>  // Esto es esencial para las funciones de Arduino, como digitalWrite, analogRead, etc.
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
extern String configuracion_pines;
extern String configuracion;  // Crea un String con el valor "ABC"
extern LiquidCrystal_I2C lcd;  // Crea un String con el valor "ABC"

bool determinarConfiguracion(int pinReferencia,int pin1in,int pin2in, int pin3in,int pin1, int pin2,int pin3);
bool probador_diodo(int pin1out,int pin2out, int pin1in,int pin2in);
void medir_resistencia(int pin1out,int pin2out, int pin1in);
void medir_voltaje(int pin1out,int pin2out, int pin1in,int pin2in);
void determinar_bjt(int pin1out,int pin2out,int pin3out, int pin1in,int pin2in,int pin3in);
float leerAnalogPin(int pin);
#endif

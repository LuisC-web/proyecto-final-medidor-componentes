#include"funciones.h"
//Pines para medicion
const int pinMedir1=A0;
const int pinMedir2=A1;
const int pinMedir3=A2;
//Pines entrada
const int pinOut1=7;
const int pinOut2=6;
const int pinOut3=5;
void setup() {
inicializar();
Serial.begin(9600);
}

void loop() {
probarComponentes();
Serial.println("Realizando mediciones");

delay(1000);
}

void inicializar(){
  pinMode(pinMedir1, INPUT); 
  pinMode(pinMedir2, INPUT); 
  pinMode(pinMedir3,INPUT);
  pinMode(pinOut1, OUTPUT); 
  pinMode(pinOut2, OUTPUT); 
  pinMode(pinOut3,OUTPUT);
}

void probarComponentes(){
  if(probador_diodo(pinOut1,pinOut2,pinMedir1,pinMedir2)){
    Serial.println("Es un diodo");
    return;
  }
  if(medir_resistencia(pinOut1,pinOut2,pinMedir1)){
    Serial.println("Es un diodo");
    return;
  }
}
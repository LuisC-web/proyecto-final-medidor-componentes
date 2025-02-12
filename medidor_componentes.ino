#include"funciones.h"
//Pines para medicion
const int pinMedir1=A0;
const int pinMedir2=A1;
const int pinMedir3=A2;
//Pines salidas 
const int pinOut1=7;
const int pinOut2=6;
const int pinOut3=5;
//Pin modo
const int modo=4;
//contador_modo
int contador=0;
void setup() {
inicializar();
Serial.begin(9600);
}

void loop() {
int estado = digitalRead(modo);
Serial.println(estado);
if(estado==HIGH)
{
 if(contador==5){
  contador=0;
   } else{

contador+=1;
   }
}
Serial.println(contador);
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
   pinMode(modo, INPUT); 
}

void probarComponentes(){
 
 switch (contador) {
  case 0:
    // Código a ejecutar cuando variable es igual a valor1
    probador_diodo(pinOut1,pinOut2,pinMedir1,pinMedir2);
    break;
  case 1:
    // Código a ejecutar cuando variable es igual a valor2
    medir_resistencia(pinOut1,pinOut2,pinMedir1);
    break;
  // Puedes tener tantos casos como necesites.
  default:
    // Código a ejecutar si ninguno de los casos anteriores coincide.
    break;
}

  
  
}
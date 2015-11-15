#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Addr, En, Rw, Rs, d4, d5, d6, d7, backlighpin, polarity

#include "Ultrasonic.h"
#define echoPin 13 //Pino 13 recebe o pulso do echo
#define trigPin 12 //Pino 12 envia o pulso para gerar o echo
//iniciando a função e passando os pinos
Ultrasonic ultrasonic(12,13);
 
const int buzzer = 10; 
void setup()
{
   Serial.begin(9600); //inicia a porta serial
   pinMode(echoPin, INPUT); // define o pino 13 como entrada (recebe)
   pinMode(trigPin, OUTPUT); // define o pino 12 como saida (envia)
   //Definindo o pino buzzer como de saída.
  pinMode(buzzer,OUTPUT);
  
  //Liga LCD
   lcd.begin(16,2);
   lcd.backlight();
}

void loop()
{
  //Hertz
  int frequencia=3000;
  //seta o pino 12 com um pulso baixo "LOW" ou desligado ou ainda 0
    digitalWrite(trigPin, LOW);
  // delay de 2 microssegundos
    delayMicroseconds(2);
  //seta o pino 12 com pulso alto "HIGH" ou ligado ou ainda 1
    digitalWrite(trigPin, HIGH);
  //delay de 10 microssegundos
    delayMicroseconds(10);
  //seta o pino 12 com pulso baixo novamente
    digitalWrite(trigPin, LOW);
  // função Ranging, faz a conversão do tempo de
  //resposta do echo em centimetros, e armazena
  //na variavel distancia
  
    double distancia = (ultrasonic.Ranging(CM));
   if(distancia >40){
       //Ligando o buzzer com uma frequencia de 1500 hz.
      tone(buzzer,frequencia);   
      delay(500);
       
      //Desligando o buzzer.
      noTone(buzzer);
      delay(500);
   }
   
   if(distancia <=40 && distancia >30){
          //Ligando o buzzer com uma frequencia de 1500 hz.
        tone(buzzer,frequencia);   
        delay(100);
         
        //Desligando o buzzer.
        noTone(buzzer);
        delay(100); 
   }
   
   if(distancia <=30 && distancia >20){
         //Ligando o buzzer com uma frequencia de 1500 hz.
      tone(buzzer,frequencia);   
      delay(50);
       
      //Desligando o buzzer.
      noTone(buzzer);
      delay(50);
   }
   
   if(distancia <=20 && distancia >10){
         //Ligando o buzzer com uma frequencia de 1500 hz.
      tone(buzzer,frequencia);   
      delay(25);
       
      //Desligando o buzzer.
      noTone(buzzer);
      delay(25);
   }
  
  if(distancia <=10){
        //Ligando o buzzer com uma frequencia de 1500 hz.
      tone(buzzer,frequencia);  
  }

//Serial.print("Distancia em CM: ");
//Serial.println(distancia);
    lcd.setCursor(0, 0);
    lcd.print("Distancia CM:");
    lcd.setCursor(5, 1);
    lcd.print(distancia);
    lcd.setCursor(8, 1);
    lcd.print("cm"); 
delay(100); //espera 1 segundo para fazer a leitura novamente
}

#include <Arduino.h>
float cm,duracao,mcub; 

byte pinoTransmissor=11; // trig
byte pinoReceptor=10; //echo

//LED RGB
const int ledg=4;
const int ledy=7;
const int ledr=2;

void setup()
{
  // LED
  pinMode(ledr, OUTPUT);
  pinMode(ledg, OUTPUT);
  pinMode(ledy, OUTPUT);
  // Sensor
  pinMode(pinoTransmissor, OUTPUT); 
  pinMode(pinoReceptor, INPUT);     
  
  Serial.begin(9600);
}

float distancia()
{  
  // apenas para limpar o pino transmissor, cortar o sinal e aguardar 5us segundos  
  // (recomendado p/ melhor funcionamento) 
  digitalWrite(pinoTransmissor, LOW);
  delayMicroseconds(5); 
  // envio do pulso de ultrassom 
  digitalWrite(pinoTransmissor, HIGH); 
  // aguarda 10 microsegundos / tempo para o pulso ir e voltar para a leitura
  delayMicroseconds(10);
  // desliga o pino que envia para habiliar o pino que recebe
  digitalWrite(pinoTransmissor, LOW);
  // calcula a duracao em microsegundos do pulso para ir e voltar 
  duracao = pulseIn(pinoReceptor, HIGH);
  // velocidade do som 343 m/s -> 34300 cm / 1000000 us -> 0.00343
  float calcDistancia= (duracao/2) * 0.0343; // em centímetro
  if (calcDistancia>=331){ // fora do limite do sensor
      calcDistancia=0;
    }
  float cmcub = map(calcDistancia,0,31,31,0);
  //return calcDistancia;
  return cmcub;
} 
  
  
// funcoes de cores do led
void red(){
    digitalWrite(ledr,HIGH);
    delay(200);
    digitalWrite(ledr,LOW);
  }
void green(){
    digitalWrite(ledg,HIGH);
    delay(200);
    digitalWrite(ledg,LOW);
  }  
void yellow(){
    digitalWrite(ledy,HIGH);
    delay(200);
    digitalWrite(ledy,LOW);
  }
void apaga(){
    digitalWrite(ledy,LOW);
    digitalWrite(ledr,LOW);
    digitalWrite(ledg,LOW);
  } 

void loop()
{
  cm =  distancia();
  //Serial.println(cm);
  mcub = 20 * (cm * 11.5)  ;

  if(mcub < 4500){
    green();
    Serial.println("Green");
  }
  else if ((mcub >= 4500) && mcub <= 5250){
    yellow();
    Serial.println("YEllOW");
  }
  else if (mcub >= 5250){
    red();
    }
    
  
  // Impressão Dados
  Serial.print(mcub);
  Serial.println(" cm3");
  delay(500);
}

float cm,duracao; 

byte pinoTransmissor=11; // trig
byte pinoReceptor=10; //echo

//LED RGB
const byte G=3;
const byte B=4;
const byte R=5;

void setup()
{
  // LED
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  // sensor
  pinMode(pinoTransmissor, OUTPUT); 
  pinMode(pinoReceptor, INPUT);     
  //porta serial
  Serial.begin(9600);
}

void loop()
{
  cm =  distancia();  
  // Impressão Dados
  Serial.print(cm);
  Serial.println(" cm");
  delay(500);
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
  float mcub= map(calcDistancia,3,310,0,16);
  return calcDistancia;  
}
// funcoes de cores do led
void red(){
    digitalWrite(ledr,HIGH);
    delay(500);
  }
void green(){
    digitalWrite(ledg,HIGH);
    delay(500);
  }  
void blue(){
    digitalWrite(ledy,HIGH);
    delay(500);
  }
void apaga(){
    digitalWrite(ledy,LOW);
    digitalWrite(ledr,LOW);
    digitalWrite(ledg,LOW);
  } 

#include <Servo.h>
#include <AFMotor.h>
#include <HCSR04.h>
//Rodas:
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

//Sensor ultrassonico
#define TRIGGER   A1
#define ECHO      A0
//Inicializa o sensor
UltraSonicDistanceSensor distanceSensor(TRIGGER, ECHO); 
float dist;

int E = 0, Le = 0, D = 0, Ld =0;
int F = 0;
//Servo Motor
int SM = 10; 
int posicao = 90;

// Variaveis Tempos
int tempinho = 0;
int T1 = 0;
int T2 =0;
bool sentido=LOW;
int sentiv = 0;
Servo servo;

int db = 40;
int acho = 0;
int Tempopravirar = 780; //tempo do delay para virar
int ini = 0;
int Sf = A5; //sensor linha da frente
int St = A3; //sensor linha de trás

//Inicio codigo
void Movimentacao (){
  //define todos os motores para irem pra frente
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  
if (F == 1){
//Serial.println ("andando para frente"); 
    motor1.setSpeed(120);  
    motor2.setSpeed(120);
    motor3.setSpeed(120);
    motor4.setSpeed(120);

    delay (Tempopravirar);
}
   if (E == 1){
    //Serial.println ("andando para esquerda"); 

  motor2.run(BACKWARD);
  motor4.run(BACKWARD);

    motor1.setSpeed(120);  
    motor2.setSpeed(50);
    motor3.setSpeed(120);
    motor4.setSpeed(50);

    delay (Tempopravirar);
   }

    if (D == 1){
      //Serial.println ("andando para direita");
 
  motor1.run(BACKWARD);
  motor4.run(BACKWARD);
  
    motor1.setSpeed(50);  
    motor2.setSpeed(120);
    motor3.setSpeed(120);
    motor4.setSpeed(50);

    delay (Tempopravirar);
    }
 

  dist = distanceSensor.measureDistanceCm();
F = 0;
 delay(10);
}


void Localizacao (){
    posicao = 90;
    servo.write(posicao);
    delay (100);
  //Le as informacoes do sensor em cm 
  dist = distanceSensor.measureDistanceCm();
  delay (400);
//detecta oponente a frente:
  if (dist <= db && posicao == 90 ){//verifica a frente
    F = 1;
    D = 0, E = 0;
     Serial.println ("Frente");
     Serial.print ("Distancia:");
     Serial.println (dist);
     
  } 
  if (dist > db ){ //verifica a esquerda
     posicao = 45;
    servo.write(posicao);
        delay (500);
    dist = distanceSensor.measureDistanceCm();
            delay (100);
            Serial.println ("entrou passo direita");


 if (dist <= db && posicao == 45){
      D = 1; //D
      F = 0, D = 0;
      Serial.println ("Esquerda");
       Serial.print ("Distancia:");
     Serial.println (dist);
        //dist = distanceSensor.measureDistanceCm();

  } 
  }
  
//Detecta oponente a esquerda
 
   if (dist > db && F != 1 && D != 1){
     posicao = 140;
    servo.write(posicao);
            delay (500);
      dist = distanceSensor.measureDistanceCm();
              delay (100);
              Serial.println ("entrou passo esquerda");

    if(dist <= db && posicao == 140){
    E = 1; //E
    F = 0, E = 0;
    Serial.println ("Direita");
     Serial.print ("Distancia:");
     Serial.println (dist);
  }

  }
  
//Detecta oponente a direita
 
  
  
}

void recuo(){
    F= 1; D =0; E =0;
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
    motor1.setSpeed(120);  
    motor2.setSpeed(120);
    motor3.setSpeed(120);
    motor4.setSpeed(120);
    delay(10);
    if(analogRead(A5)>650){
      motor2.run(BACKWARD);
      motor4.run(BACKWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);
      motor2.setSpeed(120);
      motor4.setSpeed(120);
      delay(500);
    }
}

void recuo(){
    F= 1; D =0; E =0;
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
    motor1.setSpeed(220);  
    motor2.setSpeed(220);
    motor3.setSpeed(220);
    motor4.setSpeed(220);
    delay(50);
    if(analogRead(A5)>650){
      motor2.run(BACKWARD);
      motor4.run(BACKWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);
      motor2.setSpeed(120);
      motor4.setSpeed(220);
      delay(500);
    }
}
void setup(){

  Serial.begin(9600);
  //Define rodas como saida
  motor1.setSpeed(0);
  motor1.run(RELEASE);
    motor2.setSpeed(0);
  motor2.run(RELEASE);
    motor3.setSpeed(0);
  motor3.run(RELEASE);
    motor4.setSpeed(0);
  motor4.run(RELEASE);
  servo.write(0);//INICIA O MOTOR NA POSIÇÃO 0º
  delay(1000);
  servo.attach(10); // servo ligado ao 6
  servo.write(posicao);//INICIA O MOTOR NA POSIÇÃO 90º
  delay (250);
  F = 0, D = 0, E = 0;
  Serial.println ("iniciou");
  attachInterrupt(digitalPinToInterrupt(A3), recuo, RISING );

}

void loop(){

 
  dist = distanceSensor.measureDistanceCm();

     
  if (dist > db || ini == 0){
  ini = 1;
  Localizacao();}
  
  if(F == 1 || E == 1|| D == 1){
    //Serial.println ("achou um oponente");
   Movimentacao();
   Serial.print ("Distancia:");
     Serial.println (dist);
  }
  //Serial.println(posicao);
   

}

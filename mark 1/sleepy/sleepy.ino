
// include the Adafruit motor v1 library
#include <AFMotor.h>        // INCLUI BIBLIOTECA MOTOR SHIELD
#include <SoftwareSerial.h> // INCLUI SERIAL DO BLUETOOTH
#include <HCSR04.h>         // INCLUI BIBLIOTECA HCSR04 
SoftwareSerial bluetooth(A1, A0 ); // RX(TX DO MÓDULO BT), TX(RX DO MÓDULO BT)

AF_DCMotor MotorBR(1);   // M1 DA MOTOR SHIELD
AF_DCMotor MotorFR(2);   // M2 DA MOTOR SHIELD
AF_DCMotor MotorFL(3);   // M3 DA MOTOR SHIELD
AF_DCMotor MotorBL(4);   // M4 DA MOTOR SHIELD

HCSR04 sensorDistancia( A2, A3 ); //PINO TRIGGER, PINO ECHO
int velocidade = 255; // INICIALIZA A VARIAVEL VELOCIDADE DO SLEEPY

// VARIÁVEL PARA ARMAZENAR DISTANCIA MEDIDA NO SENSOR
float distancia;

String readString;  // DECLARA STRING PARA O BLUETOOTH ################################


void setup(){
  bluetooth.begin(9600);    // DECLARA O BAUD RATE DO BLUETOOTH
  
  // DEFINE A VELOCIDADE INICIAL DOS MOTORES
  MotorBR.setSpeed(velocidade);
  MotorFR.setSpeed(velocidade);
  MotorFL.setSpeed(velocidade);
  MotorBL.setSpeed(velocidade);
  // DEFINE QUE OS MOTORES IRAM COMEÇAR DESLIGADOS
  MotorBR.run(RELEASE);
  MotorFR.run(RELEASE);
  MotorFL.run(RELEASE);
  MotorBL.run(RELEASE);

}

void loop() {

  while (bluetooth.available() > 0) {    // ENQUANTO TIVER UM BYTE NO BLUETOOTH
     char command = bluetooth.read();    // PEGA O PRIMEIRO BYTE ENVIADO PELO APP
     bluetooth.println(command);         // EXECUTA O BITE LIDO ACIMA
     distancia = sensorDistancia.dist(); // DEFINE A VARIAVEL QUE VAI LER A DISTANCIA LIDA PELO SENSOR ULTRASONICO
    switch(command){
    case 'F':   // AO APERTAR O BOTAO ANDA PRA FRENTE
    if (distancia >= 15){
        SetSpeed(velocidade);
        MotorBR.run(FORWARD);
        MotorFR.run(FORWARD);
        MotorFL.run(FORWARD);
        MotorBL.run(FORWARD);
    }
        break;
    case 'f':   // AO SOLTAR O BOTAO CANCELA O ANDAR PRA FRENTE
        MotorBR.run(RELEASE);
        MotorFR.run(RELEASE);
        MotorFL.run(RELEASE);
        MotorBL.run(RELEASE);
        break;    
    case 'B':   // AO APERTAR O BOTAO ANDA PRA TRAS
        SetSpeed(velocidade);
        MotorBR.run(BACKWARD);
        MotorFR.run(BACKWARD);
        MotorFL.run(BACKWARD);
        MotorBL.run(BACKWARD);
        break;
    case 'b':   // AO SOLTAR O BOTAO CANCELAR O ANDAR PRA TRAS
        MotorBR.run(RELEASE);
        MotorFR.run(RELEASE);
        MotorFL.run(RELEASE);
        MotorBL.run(RELEASE);
        break;    
    case 'R':   // VIRAR DIREITA
        SetSpeed(velocidade);
        MotorBR.run(BACKWARD);
        MotorFR.run(BACKWARD);
        MotorFL.run(FORWARD);
        MotorBL.run(FORWARD);
        break;
    case 'r':   // CANCELAR VIRAR DIREITA
        MotorBR.run(RELEASE);
        MotorFR.run(RELEASE);
        MotorFL.run(RELEASE);
        MotorBL.run(RELEASE);
        break;    
    case 'L':   // VIRAR ESQUERDA 
        SetSpeed(velocidade);
        MotorBR.run(FORWARD);
        MotorFR.run(FORWARD);
        MotorFL.run(BACKWARD);
        MotorBL.run(BACKWARD);
        break;
    case 'l':   // CANCELAR VIRAR ESQUERDA
        SetSpeed(velocidade);
        MotorBR.run(RELEASE);
        MotorFR.run(RELEASE);
        MotorFL.run(RELEASE);
        MotorBL.run(RELEASE);
        break;    
    case 'Q':   // FRENTE ESQUERDA
        MotorFR.setSpeed(velocidade/4);
        MotorBL.setSpeed(velocidade/4);
        MotorBR.run(FORWARD);
        MotorFR.run(FORWARD);
        MotorFL.run(FORWARD);
        MotorBL.run(FORWARD);
        break;
    case 'q':   // CANCELAR FRENTE ESQUERDA
        MotorBR.run(RELEASE);
        MotorFR.run(RELEASE);
        MotorFL.run(RELEASE);
        MotorBL.run(RELEASE);
        break;    
    case 'A':   // TRAS ESQUERDA
        MotorFL.setSpeed(velocidade/4);
        MotorBR.setSpeed(velocidade/4);
        MotorBR.run(BACKWARD);
        MotorFR.run(BACKWARD);
        MotorFL.run(BACKWARD);
        MotorBL.run(BACKWARD);
        break;
    case 'a':   // CANCELAR TRAS ESQUERDA
        SetSpeed(velocidade);
        MotorBR.run(RELEASE);
        MotorFR.run(RELEASE);
        MotorFL.run(RELEASE);
        MotorBL.run(RELEASE);
        break;    
    case 'E':   // FRENTE DIREITA
        MotorFL.setSpeed(velocidade/4);
        MotorBR.setSpeed(velocidade/4);
        MotorBR.run(FORWARD);
        MotorFR.run(FORWARD);
        MotorFL.run(FORWARD);
        MotorBL.run(FORWARD);
        break;
    case 'e':   // CANCELAR FRENTE DIREITA
        SetSpeed(velocidade);
        MotorBR.run(RELEASE);
        MotorFR.run(RELEASE);
        MotorFL.run(RELEASE);
        MotorBL.run(RELEASE);
        break;    
    case 'D':   // TRAS DIREITA
        MotorFR.setSpeed(velocidade/4);
        MotorBL.setSpeed(velocidade/4);
        MotorBR.run(BACKWARD);
        MotorFR.run(BACKWARD);
        MotorFL.run(BACKWARD);
        MotorBL.run(BACKWARD);
        break;
    case 'd':   // CANCELAR TRAS DIREITA
        SetSpeed(velocidade);
        MotorBR.run(RELEASE);
        MotorFR.run(RELEASE);
        MotorFL.run(RELEASE);
        MotorBL.run(RELEASE);
        break;    
    case 'S':   // PARAR
        MotorBR.run(RELEASE);
        MotorFR.run(RELEASE);
        MotorFL.run(RELEASE);
        MotorBL.run(RELEASE);
        break;
    
     case '0':   // DEFINE A VELOCIDADE DO MOTOR PARA 30
        SetSpeed(30);
        break;
    case '1':   // DEFINE A VELOCIDADE DO MOTOR PARA 55
        SetSpeed(55);
        break;
    case '2':   // DEFINE A VELOCIDADE DO MOTOR PARA 80
        SetSpeed(80);
        break;
    case '3':   // DEFINE A VELOCIDADE DO MOTOR PARA 105
        SetSpeed(105);
        break;
    case '4':   // DEFINE A VELOCIDADE DO MOTOR PARA 130
        SetSpeed(130);
        break;
    case '5':   // DEFINE A VELOCIDADE DO MOTOR PARA 155
        SetSpeed(155);
        break;
    case '6':   // DEFINE A VELOCIDADE DO MOTOR PARA 180
        SetSpeed(180);
        break;
    case '7':   // DEFINE A VELOCIDADE DO MOTOR PARA 205
        SetSpeed(205);
        break;
    case '8':   // DEFINE A VELOCIDADE DO MOTOR PARA 230
        SetSpeed(230);
        break;
    case '9':   // DEFINE A VELOCIDADE DO MOTOR PARA 255 (MAXIMO)
        SetSpeed(255);
        break;
   
    } 
  }

  }


// FUNÇAO QUE DEFINE A VELOCIDADE DOS MOTORES
void SetSpeed(int val){
  velocidade = val;
  MotorBR.setSpeed(val);
  MotorFR.setSpeed(val);
  MotorFL.setSpeed(val);
  MotorBL.setSpeed(val);
}

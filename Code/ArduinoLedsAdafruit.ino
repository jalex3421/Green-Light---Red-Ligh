#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define NUMPIXELS 2 //NUMERO PIXELS
#define PIN        12 


Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


#define NOTE_C4  262 //do
#define NOTE_D 146//re
#define NOTE_E 164//mi
#define NOTE_F 174//fa
#define NOTE_G3  196 //sol
#define NOTE_A3  220 //la
#define NOTE_B3  123 //si
#define NOTE_C4  262 //do

Servo servoMotor;

int Buzz1= 8; // Define Bizzer pin
int Buzz2= 7;
int PIR= 6; // Define PIR pin
int val= 0; // Initializing the value as zero at the beginning
int calibrationTime = 15;//30
// notes in the melody:
int melody[] = {
    NOTE_B3,NOTE_B3,NOTE_E,NOTE_E,NOTE_D,NOTE_D,NOTE_E,NOTE_E,NOTE_B3,NOTE_D,0
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
      4,4,2,2,4,4,4,4,2,2
};
void setup() {
  // Iniciamos el servo para que empiece a trabajar con el pin 10
  servoMotor.attach(10);
  pinMode(Buzz1, OUTPUT);
  pinMode(Buzz2, OUTPUT);
  pinMode(PIR, INPUT);
  Serial.begin(9600);
  pixels.begin();
  for(int i=1;i<=calibrationTime;i++){
    //Serial.print("calibrando...");
    //Serial.println(i);
    delay(1000);
  }
  tone(Buzz2, 1047, 2000);
  do{}while(!comienzoPartida());
 
}

void loop() {
  pixels.clear();
  
  for (int i=0;i<5;i++){//este for se cambiara por un while--> mientras el cronometro no este en 0
     Serial.println(i);
     pixels.setPixelColor(0, pixels.Color(0, 0, 0)); 
     pixels.setPixelColor(1, pixels.Color(0, 0, 0));
     pixels.show();

    
    servoMotor.write(180);
    delay(1500);//delay de espera entre que el servo se gira y cominenzo de musica
    
    //int rand = random(100,1000);
    int numeroIteraciones = random(4,8);
    //mientras suena la musica los leds estan apagados
   

    //suena la musica
    for (int thisNote = 0; thisNote < 10; thisNote++) {
      //Serial.println("musica");
      noTone(Buzz1);

      int noteDuration = 1000 / noteDurations[thisNote];
      tone(Buzz2, melody[thisNote], noteDuration);//_------------------->

       int pauseBetweenNotes = noteDuration * 1.30;
       delay(pauseBetweenNotes);

        // stop the tone playing:
        noTone(Buzz2);
    }
    //Serial.println("no musica");
    servoMotor.write(0);
    delay(1000);
    
    //Serial.println(numeroIteraciones);
    //DETECCION DE MOVIMIENTO
    
    for(int i=0;i<numeroIteraciones;i++){
      val = digitalRead(PIR); // The value read from PIR pin 3 will be assigned to 'val'
      if(val == HIGH){
        //Serial.println("movimiento");
        //led rojo
        pixels.setPixelColor(0, pixels.Color(255, 0, 0));
        pixels.setPixelColor(1, pixels.Color(255, 0, 0));
        pixels.show();
        for(int i=0;i<4;i++){
          tone(Buzz1, 1047, 300); // play tone 72 (C6 = 1047 Hz)
          delay(100);
        }
        delay(1000);
        //led verde
        pixels.setPixelColor(0, pixels.Color(0,255,0));
        pixels.setPixelColor(1, pixels.Color(0, 255, 0));
        pixels.show();
        //delay(100);
       
       //digitalWrite(Buzz, HIGH); // Turn Buzzer ON
        //noTone(Buzz1);
        /*for(int i=0;i<4;i++){
          tone(Buzz1, 1047, 300); // play tone 72 (C6 = 1047 Hz)
          delay(100);
        }*/

          //Serial.println("Movement Detected"); // Print this text in Serial Monitor
      }
      else
      {
        //Serial.println("no movimiento");
        //led verde
        pixels.setPixelColor(0, pixels.Color(0, 255, 0)); 
        pixels.setPixelColor(1, pixels.Color(0, 255, 0));
        pixels.show();
        delay(100);
        //digitalWrite(Buzz1, LOW);
        noTone(Buzz1);
        //Serial.println("Movement not Detected");
      }

      delay(1500);
    }
    
  }
  //SONIDO DE FIN DEL JUEGO
  pixels.setPixelColor(0, pixels.Color(0, 255, 255)); 
  pixels.setPixelColor(1, pixels.Color(0, 255, 255));
  pixels.show();
  tone(Buzz2, 1047, 2000);
  delay(2000);
  pixels.setPixelColor(0, pixels.Color(0, 0, 0)); 
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.show();
  exit(0);
}

bool comienzoPartida(){
  //Serial.println("estoy al principio funcion");
  boolean receiveData = false;
  if (Serial.available()>0){
    tone(Buzz2, 1047, 1000);
    receiveData = true;
    return receiveData;
  }else{
    receiveData = false;
    return receiveData;
  }
}

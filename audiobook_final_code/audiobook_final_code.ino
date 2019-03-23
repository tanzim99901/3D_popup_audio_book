#include <SD.h>                      // need to include the SD library
#define SD_ChipSelectPin 10  //using digital pin 10 on arduino nano 328, can use other pins

// REED SWITCH PINS
#define switch1 A0
#define switch2 A1
#define switch3 A2
#define switch4 A3
#define switch5 A4

#include <TMRpcm.h>           //  audio playback library
#include <SPI.h>              // SPI Communication library

TMRpcm tmrpcm;                // create an object for use in this sketch

char c;

// internal switch state variables
boolean p1 = 1;
boolean p2 = 1;
boolean p3 = 1;
boolean p4 = 1;
boolean p5 = 1;

boolean s1, s2, s3, s4, s5;     // switch state variables

unsigned long time = 0;

void setup() {
  Serial.begin(9600);
  pinMode(switch1, INPUT);
  pinMode(switch2, INPUT);
  pinMode(switch3, INPUT);
  pinMode(switch4, INPUT);
  pinMode(switch5, INPUT);

  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);

  tmrpcm.speakerPin = 9; // single-channel audio output; speaker connected to digital pin 9
  //For Complimentary Output or Dual Speakers:
  //Pin pairs: 9,10 Mega: 5-2,6-7,11-12,46-45

  Serial.begin(9600);
  delay(1000);
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("SD fail");
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    return;
  }
  else {
    Serial.println("SD ok");
    digitalWrite(8, HIGH);
    digitalWrite(7, LOW);
  }
  tmrpcm.setVolume(6);    // modify volume
  tmrpcm.quality(1);      // modify quality
}

void loop() {
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);
  digitalWrite(2, LOW);

  switch_state();   // read switch states
  run_music();      // play music accordingly
}

// READ STATE OF THE REED SWITCHES
void switch_state()
{
  s1 = digitalRead(switch1);
  s2 = digitalRead(switch2);
  s3 = digitalRead(switch3);
  s4 = digitalRead(switch4);
  s5 = digitalRead(switch5);

  // serial debugging
  Serial.print(s1);
  Serial.print(" ");
  Serial.print(s2);
  Serial.print(" ");
  Serial.print(s3);
  Serial.print(" ");
  Serial.print(s4);
  Serial.print(" ");
  Serial.print(s5);
  Serial.println(" ");

  digitalWrite(6, s1);
  digitalWrite(5, s2);
  digitalWrite(4, s3);
  digitalWrite(3, s4);
  digitalWrite(2, s5);

}

void stop_play()
{
  tmrpcm.setVolume(0);
  tmrpcm.stopPlayback();
  tmrpcm.disable();
  digitalWrite(9, LOW);
  Serial.println("STOP PLAY");
}

void run_music()
{
  if (s1 && s2 && s3 && s4 && s5) // STOP EVERYTHING
  {
    stop_play();
  }

  else if (!s1 && s2 && s3 && s4 && s5 && p1) // PAGE 1
  {
    tmrpcm.setVolume(6);
    tmrpcm.quality(1);
    tmrpcm.play("one.wav");   // .wav file to be played for page 1
    p1 = 0;
    p2 = 1;
    p3 = 1;
    p4 = 1;
    p5 = 1;
    delay(200);
  }

  else if (s1 && !s2 && s3 && s4 && s5 && p2) // PAGE 2
  {
    tmrpcm.setVolume(6);
    tmrpcm.quality(1);
    tmrpcm.play("two.wav");   // .wav file to be played for page 2
    p2 = 0;
    p1 = 1;
    p3 = 1;
    p4 = 1;
    p5 = 1;
    delay(200);
  }

  else if (s1 && s2 && !s3 && s4 && s5 && p3) // PAGE 3
  {
    tmrpcm.setVolume(6);
    tmrpcm.quality(1);
    tmrpcm.play("three.wav");   // .wav file to be played for page 3
    p3 = 0;
    p2 = 1;
    p1 = 1;
    p4 = 1;
    p5 = 1;
    delay(200);
  }

  else if (s1 && s2 && s3 && !s4 && s5 && p4) // PAGE 4
  {
    tmrpcm.setVolume(6);
    tmrpcm.quality(1);
    tmrpcm.play("four.wav");   // .wav file to be played for page 4
    p4 = 0;
    p2 = 1;
    p1 = 1;
    p3 = 1;
    p5 = 1;
    delay(200);
  }

  else if (s1 && s2 && s3 && s4 && !s5 && p5) // PAGE 5
  {
    tmrpcm.setVolume(6);
    tmrpcm.quality(1);
    tmrpcm.play("five.wav");   // .wav file to be played for page 5
    p5 = 0;
    p2 = 1;
    p1 = 1;
    p4 = 1;
    p3 = 1;
    delay(200);
  }
}


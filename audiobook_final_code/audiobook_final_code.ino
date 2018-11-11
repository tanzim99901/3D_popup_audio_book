#include <SD.h>                      // need to include the SD library
#define SD_ChipSelectPin 10  //using digital pin 10 on arduino nano 328, can use other pins

// REED SWITCH PINS
#define switch1 A0
#define switch2 A1
#define switch3 A2
#define switch4 A3
#define switch5 A4

#include <TMRpcm.h>           //  also need to include this library...
#include <SPI.h>

TMRpcm tmrpcm;   // create an object for use in this sketch

char c;

// internal switch state variables
boolean p1 = 1;
boolean p2 = 1;
boolean p3 = 1;
boolean p4 = 1;
boolean p5 = 1;

boolean s1, s2, s3, s4, s5; // switch state variables

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
  //pinMode(7, OUTPUT);

  tmrpcm.speakerPin = 9; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc
  //Complimentary Output or Dual Speakers:
  //pinMode(10,OUTPUT); Pin pairs: 9,10 Mega: 5-2,6-7,11-12,46-45

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
  tmrpcm.setVolume(6);
  tmrpcm.quality(1);
  //tmrpcm.play("ek.wav");
  //tmrpcm.play("raat.wav");
  //tmrpcm.play("cricat.wav");
  //tmrpcm.loop(1);
  /*if (tmrpcm.isPlaying())
    {
    digitalWrite(7, HIGH);
    //tmrpcm.setVolume(0);
    //tmrpcm.stopPlayback();
    //tmrpcm.disable();
    //digitalWrite(9, LOW);
    //Serial.println("DONE");
    }
    else digitalWrite(7, LOW);*/
  //tmrpcm.play("music"); //the sound file "music" will play each time the arduino powers up, or is reset
}



void loop() {
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);
  digitalWrite(2, LOW);

  switch_state();
  run_music();


  //blink the LED manually to demonstrate music playback is independant of main loop
  /*if(tmrpcm.isPlaying() && millis() - time > 50 ) {
      digitalWrite(13,!digitalRead(13));
      time = millis();
    }else
    if(millis() - time > 500){
    digitalWrite(13,!digitalRead(13));
    time = millis();
    }


    if(Serial.available()){
    switch(Serial.read()){
    case 'd': tmrpcm.play("furk.wav"); Serial.println("Playing FURK"); break;
    case 'r': tmrpcm.play("at.wav"); Serial.println("Playing AT"); break;
    case 'k': tmrpcm.play("ek.wav"); Serial.println("Playing EK"); break;
    case 't': tmrpcm.play("sholo.wav"); Serial.println("Playing SHOLO"); break;
    case 'p': tmrpcm.pause(); Serial.println("PAUSE/PLAY"); break;
    case '?': if(tmrpcm.isPlaying()){ Serial.println("A wav file is being played");} break;
    case 's': tmrpcm.stopPlayback(); Serial.println("STOP"); break;
    case '0': tmrpcm.quality(0); Serial.println("Low Quality"); break;
    case '1': tmrpcm.quality(1); Serial.println("High Quality"); break;
    case '=': tmrpcm.volume(7); Serial.println("High Volume"); break;
    case '-': tmrpcm.volume(6); Serial.println("Low Volume"); break;
    default: break;
    }
    }*/

}

void switch_state()
{
  s1 = digitalRead(switch1);
  s2 = digitalRead(switch2);
  s3 = digitalRead(switch3);
  s4 = digitalRead(switch4);
  s5 = digitalRead(switch5);
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
    tmrpcm.play("ek.wav");
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
    tmrpcm.play("dui.wav");
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
    tmrpcm.play("tin.wav");
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
    tmrpcm.play("car.wav");
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
    tmrpcm.play("pac.wav");
    p5 = 0;
    p2 = 1;
    p1 = 1;
    p4 = 1;
    p3 = 1;
    delay(200);
  }

  //else stop_play();

  /*if (!tmrpcm.isPlaying())
    {
    stop_play();
    }*/
}


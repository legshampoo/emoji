
//------------------------
//
//  setup constants and libs
//  
//------------------------
#include <SoftwareSerial.h>
#define clockRx 7
#define clockTx 6
#define audioRx 10
#define audioTx 11
#define startButtonPin 4
#define stopButtonPin 3

SoftwareSerial clock(clockRx, clockTx);
SoftwareSerial audio(audioRx, audioTx);

//------------------------
//
//  init global variables
//  
//------------------------

int timeLimit = 30;
int counter = timeLimit;
int startButtonPress = 0;
int stopButtonPress = 0;
boolean count = false;

unsigned long previousMillis = 0;
const long interval = 1000;

//------------------------
//
//  INIT
//  
//------------------------

void setup() {  
  pinMode(startButtonPin, INPUT);
  pinMode(stopButtonPin, INPUT);

  clock.begin(9600); 

  clock.println("88:88");
  delay(1000);
  clock.print("00:");
  clock.println(counter);

  audio.begin(38400);  
}


//------------------------
//
//  LOOP
//  
//------------------------

void loop() { 
 
  startButtonListener();
  stopButtonListener();

  if(count){
    countDown();
  }
}






//------------------------
//
//  FUNCTIONS
//  
//------------------------

//on start button press by brand rep
void startButtonListener(){

  startButtonPress = digitalRead(startButtonPin);

  if(startButtonPress){
    count = true;
  }
}


//on stop butotn press by participant
void stopButtonListener(){

  stopButtonPress = digitalRead(stopButtonPin);

  //if SUCCESS
  if(stopButtonPress){
    count = false;
    clock.print("00:");
    clock.println(counter);
    
    //trigger Success sound
    audio.write('T');
    audio.write('1');
    delay(3000);
    resetTimer();
  }
}

//clock countdown
void countDown(){
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis >= interval){
    counter--;
    previousMillis = currentMillis;

    clock.print("00:");
    clock.println(counter);
    
    //if you FAIL
    if(counter < 1){      
      count = false;
      clock.print("00:");
      clock.println(counter);
      
      //trigger FAIL sound
      audio.write('T');
      audio.write('3');
      
      delay(3000);
      resetTimer();
      return;
    }
  }

}

//reset to start time after round is over
void resetTimer(){
  counter = timeLimit;
  clock.print("00:");
  clock.println(counter);
}


#include <IRremote.h>

//the size of each data element, equals to the amount of buttons you will support
const int sizeData = 4;
//record index used when input or output signals are saved
int recordIndex = 0;
//output signal type;
int outputType = -1;
//data input array
unsigned long dataInput[sizeData]; 
//bits input array
int bitsInput[sizeData]; 
//data output array  
unsigned long dataOutput[sizeData]; 
//bits output array
int bitsOutput[sizeData];   
//text's used for each button needed to be recorded
char* serialText[]={"Press the button to increase the channel","Press the button to decrease the channel","Press the button to increase the volumen","Press the button to decrease the volumen"};
//PWN pin where the receiver is connected
int RECV_PIN = 2;

IRrecv irrecv(RECV_PIN);

IRsend irsend;

boolean recordInput = false;

boolean recordOutput = false;

decode_results results;

boolean sentSignal =  false;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (Serial.available())
  {
   char ch = Serial.read();
     if (ch == 'O')
    {
     recordOutput = true;
    Serial.println("Recording Output Signal");
    Serial.println(serialText[recordIndex]); 
    } else if(ch == 'I'){
     recordInput = true; 
    Serial.println("Recording Input Signal");
     Serial.println(serialText[recordIndex]); 
    }
  } 
  if (irrecv.decode(&results)) {
    if(recordInput == true){
       dataInput[recordIndex] = results.value;
       bitsInput[recordIndex] = results.bits;
       Serial.println("Processing...");
       delay(300);
       recordIndex++;
      if(recordIndex<sizeData){
       Serial.println(serialText[recordIndex]);
      }else{
         recordInput = false;
         recordIndex = 0;
         Serial.println("Input Signals Recorded!");
      }
    }else if(recordOutput == true){
       outputType = results.decode_type;
       dataOutput[recordIndex] = results.value;
       bitsOutput[recordIndex] = results.bits;
       Serial.println("Processing...");
       delay(300);
       recordIndex++;
      if(recordIndex<sizeData){
       Serial.println(serialText[recordIndex]);
      }else{
         recordOutput = false;
         recordIndex = 0;
         Serial.println("Output Signals Recorded!:");
      } 
    }else{

      sentSignal = false;
      
       for(int i = 0;i<sizeData;i++){
           if(dataInput[i] == results.value && bitsInput[i] == results.bits){
             switch(outputType){
              case NEC:
              sentSignal = true;
              irsend.sendNEC(dataOutput[i], bitsOutput[i]);
              break; 
              case SONY:
              sentSignal = true;
              irsend.sendSony(dataOutput[i], bitsOutput[i]);               
              break; 
              case RC5:
              sentSignal = true;
              irsend.sendRC5(dataOutput[i], bitsOutput[i]);              
              break; 
              case RC6:
              sentSignal = true;
              irsend.sendRC6(dataOutput[i], bitsOutput[i]);               
              break; 
              case DISH:
              sentSignal = true;
              irsend.sendDISH(dataOutput[i], bitsOutput[i]); 
              break; 
              case SHARP:
              sentSignal = true;
              irsend.sendSharp(dataOutput[i], bitsOutput[i]); 
              break;               
             }
             if(sentSignal == true){
              i = sizeData + 1; 
              irrecv.enableIRIn();
             }
           }
       }
       if(sentSignal == false){
         Serial.println("Signal is not recognized!");
       }else{
         Serial.println("Signal sent!");         
       }
    }
    irrecv.resume(); // Receive the next value
  }
}

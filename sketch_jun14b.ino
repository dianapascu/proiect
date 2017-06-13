int incomingByte;   // for incoming serial data
char dateAndHour[23];
int i = 0;

void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}

void loop() {
  setAlarm();
  //delay(1000);
}

void setAlarm(){


        // send data only when you receive data:
        while (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte = Serial.read();

                dateAndHour[i] = char(incomingByte);
                // say what you got:
                Serial.print("I received: ");
                Serial.println(dateAndHour[i]);

                i++;
        }
  
}
 


struct ButtonCommand{
  unsigned int pre_delay; //Delay in miliseconds before the command is fired
  int button; //Button/Trigger to press
  unsigned int button_delay; //delay in milis during the press, before release
  unsigned int post_delay; //delay in milis after the release
  int32_t trigger_val; //Value to set the trgger
  int32_t joystick_x; //Joystick X
  int32_t joystick_y; //Joystick Y
  String buttonVal; //Value of the button to print in debug logs
};

void setup() {
  Serial1.begin(9600); //Leonardo
  Serial.begin(9600); //PC
}
ButtonCommand bCommand = {0,1,0,0,0,0,0,"A"};
//Based on ButtonCommand
byte bPress[] = {254,1,254,0,0,0,0};
byte aPress[] = {254,2,254,0,0,0,0};
byte yPress[] = {254,3,254,0,0,0,0};
byte xPress[] = {254,4,254,0,0,0,0};

void loop() 
{
  sendStruct(bPress, 7);
  delay(500);
  sendStruct(aPress, 7);
  delay(500);
  sendStruct(yPress, 7);
  delay(500);
  sendStruct(xPress, 7);
  delay(500);
}

//byte_input[] = Bytes to send to the leonardo - to be changed to ButtonCommand
//byteSize = amount of bytes to send (standard is 7)
void sendStruct(byte byte_input[], int byteSize)
{
    Serial1.write('>'); //Write our start char to tell Leonardo this is a new command
    for (int i = 0; i <= byteSize; i++) //Loop the amount of values are in the array
    {
       Serial1.write(byte_input[i]);//Write i byte to serial1
       if(i != byteSize) //If i isnt byteSize, then add a comma
       {
          Serial1.write(",");
       }
    }
    Serial1.write('<'); //Write our ending char
     Serial.print('>'); //Mimmic what we send to leonardo
     for (int i = 0; i <= byteSize; i++)
     {
       Serial.print(byte_input[i]);
       if(i != byteSize)
       {
          Serial.print(",");
       }
    }
    Serial.println('<'); 
}

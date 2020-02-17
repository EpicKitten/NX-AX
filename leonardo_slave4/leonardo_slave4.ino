#include <XInput.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// OLED display TWI address
#define OLED_ADDR   0x3C

Adafruit_SSD1306 display(-1);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

struct ButtonCommand{
  int pre_delay; //Delay in miliseconds before the command is fired
  uint8_t button; //Button/Trigger to press
  unsigned int button_delay; //delay in milis during the press, before release
  unsigned int post_delay; 
  int32_t trigger_val; //Value to set the trgger
  int32_t joystick_x; //Joystick X
  int32_t joystick_y; //Joystick Y
  //missing button name, not used
};

void buttonTest(int bCom, int post_delay, int pre_delay)
{
    delay(pre_delay);
    XInput.press(bCom);
    XInput.send();
    delay(200); //About the speed the Nintendo Switch and reliabily get precise button presses  
    XInput.release(bCom);
    XInput.send();
    delay(post_delay);
}

void setup() {
  XInput.setAutoSend(false);  // Wait for all controls before sending
  XInput.begin(); //Start Xinput
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();
  Serial1.begin(9600);//Start reading from serial pins 1 & 0
}


void loop() 
{
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("LXSC Ready!"); //Leonardo XInput Slave Controller
  while (Serial1.available() > 0) 
  { //Check for data
    if(Serial1.read() == '>')
    {
      display.clearDisplay();
      display.setCursor(70,0);
      display.print("Data in!");
      char serialIn[15];
      Serial1.readBytesUntil('<', serialIn, 16);
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.display();

      display.clearDisplay();
      display.setCursor(0,20);
      display.print("Button: ");
      display.setCursor(70,20);
      display.print((uint8_t)serialIn[2]);
      display.display();

      display.clearDisplay();
      display.setCursor(0,30);
      display.print("post_delay: ");
      display.setCursor(70,30);
      display.print((int)serialIn[3]);
      display.display();
      
      display.clearDisplay();
      display.setCursor(0,40);
      display.print("pre_delay: ");
      display.setCursor(70,40);
      display.print(serialIn[4]);
      display.display();
      display.clearDisplay();
      
      buttonTest((uint8_t)serialIn[2],(uint8_t)serialIn[3],(uint8_t)serialIn[4]);
    }
  }
  display.display();
  display.clearDisplay();
}

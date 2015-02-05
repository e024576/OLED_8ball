/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



char* phrases[] = /* Known phrases */{"    Ask      again     later", "  It is    certain", 
" Without a   doubt", "   Yes    definitely", " As I see   it, yes", "   Most     likely", 
"  Outlook    good", "    Yes", " My reply   is no", "   Very    doubtful", "    No",
 "  Not a     chance", "  No way", "Absolutely   not", "I doubt it", " Ask again",
 "   I'm     uncertain"};
char* output;
int numberofphrases = 17; //Number of phrases known, must be the same as, well, the number of phrases known

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   {  
randomSeed(analogRead(1)); //Seed for random number generation  
  Serial.begin(9600);
  
  pinMode(12, INPUT_PULLUP); // pin for tilt switch
  pinMode(11, OUTPUT); // create new ground pin for tilt switch
  digitalWrite(11, LOW); // ground point for tilt switch

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(20);

  // Clear the buffer.
  display.clearDisplay();
}

void loop() {
  // text display start up message
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,1);
  display.println(" Ask, then  Slowly     Tilt    Side-Side");
  display.display();
  delay(1000);
  display.clearDisplay();
 
 // wait for ball to be shaken side to side 
 // int vibSwitch = digitalRead(12); 
 if (digitalRead(12) == LOW) {
  for(int x=0; x < 50; x++)
  {
  output = phrases[random(numberofphrases)]; //Chooses phrase
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,12);
  display.println(output);
  display.display();
  delay(3);
  display.clearDisplay();
  }
  delay(3000);
 } 
}



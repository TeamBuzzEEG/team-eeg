#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int memory[100];
int memory_lenght;

const int OUT_PIN = 8;
const int SAMPLE_TIME = 50;
unsigned long millisCurrent;
unsigned long millisLast = 0;
unsigned long millisElapsed = 0;

int sampleBufferValue = 0;

void setup() {
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(3);
  display.setTextColor(WHITE);
}

void loop() {




  millisCurrent = millis();
  millisElapsed = millisCurrent - millisLast;

  if (digitalRead(OUT_PIN) == LOW) {
    sampleBufferValue++;
  }

  if (millisElapsed > SAMPLE_TIME) {

    //Display value
    display.setCursor(0,0);
    display.print(sampleBufferValue);    
    display.display(); 
    display.clearDisplay();

    //Print value
    //Serial.println(sampleBufferValue);

    //Shift values
    memcpy(memory, &memory[1], sizeof(memory) - sizeof(sampleBufferValue));
    memory_lenght = sizeof(memory)/sizeof(memory[0]);
    memory[memory_lenght-1] =  sampleBufferValue;

//    for(int i = 0; i < memory_lenght; i++) {
//        Serial.print( memory[i]);
//        Serial.print(',');        
//    }Serial.println("");
    

    //Reset value
    millisLast = millisCurrent;
    sampleBufferValue = 0;
    

    
    
  }

}

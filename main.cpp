#include <Arduino.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN           3
#define NUMPIXELS     35
#define BRIGHT        150
#define trigger_pin   2

uint8_t leer[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t eins[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0};
uint8_t zwei[] = {0,1,1,1,0,0,0,0,0,0,1,1,1,1,1,0,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1};
uint8_t drei[] = {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1};
uint8_t voll[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
static unsigned long last_interrupt_time = 0;
volatile uint8_t state=0;

void print_number_segment (uint8_t [], uint8_t, uint8_t, uint8_t);
void test (void);
void shoot_ISR();
void count_down(void);
/*
        C1
     ----------
    |          |
    |          |
B1  |          | D1
    |          |
    |    G1    |
     ----------
    |          |
    |          |
A1  |          | E1
    |          |
    |    F1    |
     ----------

*/

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 200; // delay for half a second

void setup(){
  pinMode(trigger_pin, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
//  attachInterrupt(2, shoot_ISR, FALLING);
  pixels.begin(); // This initializes the NeoPixel library
  test();
}

void loop(){
  //EICRB &= ~(bit(ISC40) | bit(ISC41));
  state = digitalRead(trigger_pin);

  if(state == 1){
    count_down();
    state = 0;
  }
}


void print_number_segment(uint8_t num[], uint8_t red, uint8_t green, uint8_t blue){
  uint8_t i=0;

  for(i=0; i<=NUMPIXELS; ++i){
    pixels.setPixelColor(i, pixels.Color(num[i]*red, num[i]*green, num[i]*blue));
    pixels.show();
  }
}

void count_down(void){
  digitalWrite(13, LOW);
  print_number_segment(drei, 130, 30, 130);
    delay(1000);
  print_number_segment(zwei, 130, 30, 130);
    delay(1000);
  print_number_segment(eins, 130, 30, 130);
    delay(1000);
  print_number_segment(voll, 200, 200, 200);
  digitalWrite(13, HIGH);
    delay(250);
  digitalWrite(13, LOW);
  print_number_segment(voll, 50, 50, 50);
  delay(2000);
  print_number_segment(voll, 10, 10, 10);
}

void test (void){
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(0,200,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(50); // Delay for a period of time (in milliseconds).
  }

  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(0,0,200)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(50); // Delay for a period of time (in milliseconds).
  }

  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(200,0,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(50); // Delay for a period of time (in milliseconds).
  }
  print_number_segment(voll, 10, 10, 10);
}

#include "GIF.h"
#include "Magic.h"

#define R1_PIN 33
#define G1_PIN 32
#define B1_PIN 25
#define R2_PIN 27
#define G2_PIN 26
#define B2_PIN 21
#define A_PIN 13
#define B_PIN 12
#define C_PIN 2
#define D_PIN 15
#define E_PIN 14 // required for 1/32 scan panels, like 64x64. Any available pin would do, i.e. IO32
#define LAT_PIN 4
#define OE_PIN 17
#define CLK_PIN 16

void displaySetup()
{
  HUB75_I2S_CFG mxconfig;
  mxconfig.mx_width = 64;  // module width
  mxconfig.mx_height = 64;  // module height
  mxconfig.chain_length = 2; // Chain length
  mxconfig.latch_blanking = 4;
  mxconfig.i2sspeed = HUB75_I2S_CFG::HZ_10M;
  mxconfig.clkphase = false;
  mxconfig.gpio.e = 14;
  matrix = new MatrixPanel_I2S_DMA(mxconfig);

  if ( not matrix->begin(R1_PIN, G1_PIN, B1_PIN, R2_PIN, G2_PIN, B2_PIN, A_PIN, B_PIN, C_PIN, D_PIN, E_PIN, LAT_PIN, OE_PIN, CLK_PIN))
    Serial.println("****** !KABOOM! I2S memory allocation failed ***********");
}

void setup()
{
  Serial.begin(115200);
  displaySetup();
  matrix->clearScreen();  
  matrix->setBrightness8(128); //0-255
  gif.begin(LITTLE_ENDIAN_PIXELS);
}

void loop()
{
  if (gif.open((uint8_t *)gifData, sizeof(gifData), GIFDraw))
  {
    Serial.printf("Successfully opened GIF; Canvas size = %d x %d\n", gif.getCanvasWidth(), gif.getCanvasHeight());
    while (gif.playFrame(true, NULL)){}
    gif.close();
  }
}

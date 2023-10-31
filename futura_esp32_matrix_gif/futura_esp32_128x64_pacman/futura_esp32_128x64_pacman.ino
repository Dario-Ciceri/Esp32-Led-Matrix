#include "pacman.h"

#include <AnimatedGIF.h>

#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

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
#define E_PIN 14 // required for 1/32 scan panels, like 64x64
#define LAT_PIN 4
#define OE_PIN 17
#define CLK_PIN 16

MatrixPanel_I2S_DMA *matrix = nullptr;

AnimatedGIF gif;

void GIFDraw(GIFDRAW *pDraw)
{
  uint8_t *s;
  uint16_t *d, *usPalette, usTemp[320];
  int x, y, iWidth;

  usPalette = pDraw->pPalette;
  y = pDraw->iY + pDraw->y; 

  s = pDraw->pPixels;
  if (pDraw->ucDisposalMethod == 2) 
  {
    for (x = 0; x < iWidth; x++)
    {
      if (s[x] == pDraw->ucTransparent)
        s[x] = pDraw->ucBackground;
    }
    pDraw->ucHasTransparency = 0;
  }

  if (pDraw->ucHasTransparency) 
  {
    uint8_t *pEnd, c, ucTransparent = pDraw->ucTransparent;
    int x, iCount;
    pEnd = s + pDraw->iWidth;
    x = 0;
    iCount = 0;
    while (x < pDraw->iWidth)
    {
      c = ucTransparent - 1;
      d = usTemp;
      while (c != ucTransparent && s < pEnd)
      {
        c = *s++;
        if (c == ucTransparent) 
        {
          s--; 
        }
        else 
        {
          *d++ = usPalette[c];
          iCount++;
        }
      }          
      if (iCount) 
      {
        for (int xOffset = 0; xOffset < iCount; xOffset++)
        {
          matrix->drawPixel(x + xOffset, y, usTemp[xOffset]);
        }
        x += iCount;
        iCount = 0;
      }
      
      c = ucTransparent;
      while (c == ucTransparent && s < pEnd)
      {
        c = *s++;
        if (c == ucTransparent)
          iCount++;
        else
          s--;
      }
      if (iCount)
      {
        x += iCount; 
        iCount = 0;
      }
    }
  }
  else
  {
    s = pDraw->pPixels;
    
    for (x = 0; x < pDraw->iWidth; x++)
    {
      matrix->drawPixel(x, y, usPalette[*s++]);
    }
  }
} 

void displaySetup()
{
  HUB75_I2S_CFG mxconfig;
  mxconfig.mx_width = 64;  
  mxconfig.mx_height = 64;  
  mxconfig.chain_length = 2; 
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
  matrix->fillScreen(matrix->color565(0, 0, 0));
  gif.begin(LITTLE_ENDIAN_PIXELS);
}

void loop()
{
  if (gif.open((uint8_t *)pacman, sizeof(pacman), GIFDraw))
  {
    Serial.printf("Successfully opened GIF; Canvas size = %d x %d\n", gif.getCanvasWidth(), gif.getCanvasHeight());
    while (gif.playFrame(true, NULL))
    {
    }
    gif.close();
  }
}

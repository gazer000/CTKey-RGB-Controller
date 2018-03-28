#include <EEPROMex.h>
#include <EEPROMVar.h>
#include <Keyboard.h>
#include <Bounce2.h>
#include <SoftPWM.h>
#define REDUCED_MODES
#include <WS2812FX.h>
#define LED_COUNT 16
#define LED_PIN 4
Bounce b1d = Bounce();
Bounce b2d = Bounce();
WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);
String cmd = "";
boolean cmd_complete = false;
boolean pressed, pressed1, pressed2 = false;
boolean toprb = false;
boolean topfade, topfadereverse, topfaderandom, topstatic, topoff = false;
const int redPin = 6;
const int greenPin = 5;
const int bluePin = 3;
const int redPin2 = 8;
const int bluePin2 = 10;
const int greenPin2 = 9;
long int fade_goTime;
int fade_break = 10;
int R, G, B, R2, G2, B2;
int value1, value2, value3, value4, value5;
long randNumb1, randNumb2, randNumb3, randNumb4, randNumb5, randNumb6;
void setup()
{
  Serial.begin(115200);
  ws2812fx.init();
  ws2812fx.setBrightness(EEPROM.read(3));
  ws2812fx.setSpeed(EEPROM.readLong(4));
  ws2812fx.setMode(EEPROM.read(1));
  ws2812fx.setColor(EEPROM.readLong(2));
  ws2812fx.start();
  toprb = EEPROM.read(5);
  topfade = EEPROM.read(6);
  topfadereverse = EEPROM.read(7);
  topfaderandom = EEPROM.read(8);
  topstatic = EEPROM.read(9);
  R = EEPROM.read(10);
  G = EEPROM.read(11);
  B = EEPROM.read(12);
  R2 = EEPROM.read(13);
  G2 = EEPROM.read(14);
  B2 = EEPROM.read(15);
  pinMode(A0, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  SoftPWMBegin(SOFTPWM_INVERTED);
  SoftPWMSet(3, 0);
  SoftPWMSet(5, 0);
  SoftPWMSet(6, 0);
  SoftPWMSet(8, 0);
  SoftPWMSet(9, 0);
  SoftPWMSet(10, 0);
  fade_goTime = millis();
  b1d.attach(A0);
  b1d.interval(5);
  b2d.attach(7);
  b2d.interval(5);
}
void loop()
{
  b1d.update();
  b2d.update();
  ws2812fx.service();
  serialEvent();
  toprgbcontrol();
  if (cmd_complete) {
    switchModes();
  }
  keyboard();
}
void keyboard()
{
  value1 = b1d.read();
  value2 = b2d.read();
  value3 = digitalRead(A1);
  value4 = digitalRead(A2);
  value5 = digitalRead(A3);
  if (!pressed && value1 == 0)
  {
    pressed = true;
    Keyboard.press('z');
  }
  else if (pressed && value1 == 1)
  {
    pressed = false;
    Keyboard.release('z');
  }
  if (!pressed1 && value2 == 0)
  {
    pressed1 = true;
    Keyboard.press('x');
  }
  else if (pressed1 && value2 == 1)
  {
    pressed1 = false;
    Keyboard.release('x');
  }
  if (value3 == 0)
  {
    Keyboard.press(KEY_ESC);
  }
  else if (value3 == 1)
  {
    Keyboard.release(KEY_ESC);
  }
  if (value4 == 0)
  {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('r');
  }
  else if (value4 == 1)
  {
    Keyboard.release(KEY_LEFT_CTRL);
    Keyboard.release('r');
  }
  if (value5 == 0)
  {
    Keyboard.press(KEY_F8);
  }
  else if (value5 == 1)
  {
    Keyboard.release(KEY_F8);
  }
}
void switchModes()
{
  if (cmd == F("sta")) {
    ws2812fx.setMode(FX_MODE_STATIC);
  }
  if (cmd == F("bli")) {
    ws2812fx.setMode(FX_MODE_BLINK);
  }
  if (cmd == F("bre")) {
    ws2812fx.setMode(FX_MODE_BREATH);
  }
  if (cmd == F("rac")) {
    ws2812fx.setMode(FX_MODE_RANDOM_COLOR);
  }
  if (cmd == F("rai")) {
    ws2812fx.setMode(FX_MODE_RAINBOW);
  }
  if (cmd == F("blr")) {
    ws2812fx.setMode(FX_MODE_BLINK_RAINBOW);
  }
  if (cmd == F("s")) {
    EEPROM.update(1, ws2812fx.getMode());
    EEPROM.update(3, ws2812fx.getBrightness());
    EEPROM.updateLong(4, ws2812fx.getSpeed());
    EEPROM.update(5, toprb);
    EEPROM.update(6, topfade);
    EEPROM.update(7, topfadereverse);
    EEPROM.update(8, topfaderandom);
    EEPROM.update(9, topstatic);
  }
  if (cmd == F("x")) {
    EEPROM.updateLong(2, ws2812fx.getColor());
    EEPROM.update(10, R);
    EEPROM.update(11, G);
    EEPROM.update(12, B);
    EEPROM.update(13, R2);
    EEPROM.update(14, G2);
    EEPROM.update(15, B2);
  }
  if (cmd.startsWith(F("c "))) {
    uint32_t c = (uint32_t) strtol(&cmd.substring(2, cmd.length())[0], NULL, 16);
    ws2812fx.setColor(c);
  }
  if (cmd.startsWith(F("b "))) {
    uint8_t b = (uint8_t) cmd.substring(2, cmd.length()).toInt();
    ws2812fx.setBrightness(b);
  }
  if (cmd.startsWith(F("s "))) {
    uint16_t s = (uint16_t) cmd.substring(2, cmd.length()).toInt();
    ws2812fx.setSpeed(s);
  }
  cmd = "";
  cmd_complete = false;
}
void toprgbcontrol() {
  if (cmd == F("trb") || toprb == true) {
    toprb = true;
    topfade = false;
    topfadereverse = false;
    topfaderandom = false;
    topstatic = false;
    topoff = false;
    SoftPWMSetFadeTime(ALL, 5, 5);
    if (millis() >= fade_goTime)
    {
      fade1();
      fade2();
    }
  }
  if (cmd == F("TOFF") || topoff == true)
  {
    toprb = false;
    topfade = false;
    topfadereverse = false;
    topfaderandom = false;
    topstatic = false;
    topoff = true;
    SoftPWMSet(redPin, 0);
    SoftPWMSet(bluePin, 0);
    SoftPWMSet(greenPin, 0);
    SoftPWMSet(redPin2, 0);
    SoftPWMSet(bluePin2, 0);
    SoftPWMSet(greenPin2, 0);
  }
  if (cmd.startsWith("T1"))
  {
    SoftPWMSetFadeTime(ALL, 5, 5);
    custom_color_t1();
  }
  if (cmd.startsWith("T2"))
  {
    SoftPWMSetFadeTime(ALL, 5, 5);
    custom_color_t2();
  }
  if (topstatic == true)
  {
    toprb = false;
    topfade = false;
    topfadereverse = false;
    topfaderandom = false;
    topstatic = true;
    topoff = false;
    SoftPWMSet(redPin, R);
    SoftPWMSet(bluePin, B);
    SoftPWMSet(greenPin, G);
    SoftPWMSet(redPin2, R2);
    SoftPWMSet(bluePin2, B2);
    SoftPWMSet(greenPin2, G2);
  }
  if (cmd.startsWith("T3"))
  {
    SoftPWMSetFadeTime(ALL, 5, 5);
    custom_color_t();
  }
  if (cmd == F("TF") || topfade == true)
  {
    toprb = false;
    topfade = true;
    topfadereverse = false;
    topfaderandom = false;
    topstatic = false;
    topoff = false;
    top_fade_press();
  }
  if (cmd == F("TFR") || topfadereverse == true)
  {
    toprb = false;
    topfade = false;
    topfadereverse = true;
    topfaderandom = false;
    topstatic = false;
    topoff = false;
    top_fade_reverse();
  }
  if (cmd == F("TRA") || topfaderandom == true)
  {
    toprb = false;
    topfade = false;
    topfadereverse = false;
    topfaderandom = true;
    topstatic = false;
    topoff = false;
    top_fade_random();
  }
}
void top_fade_random()
{
  SoftPWMSetFadeTime(ALL, 5, 400);
  value1 = b1d.read();
  value2 = b2d.read();
  randNumb1 = random(5, 256);
  randNumb2 = random(5, 256);
  randNumb3 = random(5, 256);
  randNumb4 = random(5, 256);
  randNumb5 = random(5, 256);
  randNumb6 = random(5, 256);
  int runtime = 1;
  int runtime2 = 1;
  if (!pressed && value1 == 0)
  {
    pressed = true;
    Keyboard.press('z');
    if (runtime)
    {
      SoftPWMSet(redPin, randNumb1);
      SoftPWMSet(bluePin, randNumb2);
      SoftPWMSet(greenPin, randNumb3);
      runtime--;
    }
  }
  else if (pressed && value1 == 1)
  {
    Keyboard.release('z');
    SoftPWMSet(redPin, 0);
    SoftPWMSet(bluePin, 0);
    SoftPWMSet(greenPin, 0);
    runtime = 1;
  }
  if (!pressed1 && value2 == 0)
  {
    pressed1 = true;
    Keyboard.press('x');
    if (runtime2)
    {
      SoftPWMSet(redPin2, randNumb4);
      SoftPWMSet(bluePin2, randNumb5);
      SoftPWMSet(greenPin2, randNumb6);
      runtime2--;
    }
  }
  else if (pressed1 && value2 == 1)
  {
    Keyboard.release('x');
    SoftPWMSet(redPin2, 0);
    SoftPWMSet(bluePin2, 0);
    SoftPWMSet(greenPin2, 0);
    runtime2 = 1;
  }
}
void top_fade_reverse()
{
  SoftPWMSetFadeTime(ALL, 400, 5);
  value1 = b1d.read();
  value2 = b2d.read();
  if (value1 == 1)
  {
    SoftPWMSet(redPin, R);
    SoftPWMSet(bluePin, B);
    SoftPWMSet(greenPin, G);
  }
  else if (value1 == 0)
  {
    SoftPWMSet(redPin, 0);
    SoftPWMSet(bluePin, 0);
    SoftPWMSet(greenPin, 0);
  }
  if (value2 == 1)
  {
    SoftPWMSet(redPin2, R2);
    SoftPWMSet(bluePin2, B2);
    SoftPWMSet(greenPin2, G2);
  }
  else if (value2 == 0)
  {
    SoftPWMSet(redPin2, 0);
    SoftPWMSet(bluePin2, 0);
    SoftPWMSet(greenPin2, 0);
  }
}
void top_fade_press()
{
  SoftPWMSetFadeTime(ALL, 5, 400);
  value1 = b1d.read();
  value2 = b2d.read();
  if (value1 == 0)
  {
    SoftPWMSet(redPin, R);
    SoftPWMSet(bluePin, B);
    SoftPWMSet(greenPin, G);
  }
  else if (value1 == 1)
  {
    SoftPWMSet(redPin, 0);
    SoftPWMSet(bluePin, 0);
    SoftPWMSet(greenPin, 0);
  }
  if (value2 == 0)
  {
    SoftPWMSet(redPin2, R2);
    SoftPWMSet(bluePin2, B2);
    SoftPWMSet(greenPin2, G2);
  }
  else if (value2 == 1)
  {
    SoftPWMSet(redPin2, 0);
    SoftPWMSet(bluePin2, 0);
    SoftPWMSet(greenPin2, 0);
  }
}
void custom_color_t1()
{
  toprb = false;
  topfade = false;
  topfadereverse = false;
  topfaderandom = false;
  topstatic = true;
  R = (cmd.substring(cmd.indexOf("T1") + 1 , cmd.indexOf("R") )).toInt();
  SoftPWMSet(redPin, R);

  G = (cmd.substring(cmd.indexOf("R") + 1 , cmd.indexOf("G") )).toInt();
  SoftPWMSet(greenPin, G);

  B = (cmd.substring(cmd.indexOf("G") + 1 , cmd.indexOf("B") )).toInt();
  SoftPWMSet(bluePin, B);
}
void custom_color_t2()
{
  toprb = false;
  topfade = false;
  topfadereverse = false;
  topfaderandom = false;
  topstatic = true;
  R2 = (cmd.substring(cmd.indexOf("T2") + 1 , cmd.indexOf("R") )).toInt();
  SoftPWMSet(redPin2, R2);

  G2 = (cmd.substring(cmd.indexOf("R") + 1 , cmd.indexOf("G") )).toInt();
  SoftPWMSet(greenPin2, G2);

  B2 = (cmd.substring(cmd.indexOf("G") + 1 , cmd.indexOf("B") )).toInt();
  SoftPWMSet(bluePin2, B2);
}
void custom_color_t()
{
  toprb = false;
  topfade = false;
  topfadereverse = false;
  topfaderandom = false;
  topstatic = true;
  R = (cmd.substring(cmd.indexOf("T3") + 1 , cmd.indexOf("R") )).toInt();
  R2 = R;
  SoftPWMSet(redPin, R);
  SoftPWMSet(redPin2, R2);

  G = (cmd.substring(cmd.indexOf("R") + 1 , cmd.indexOf("G") )).toInt();
  G2 = G;
  SoftPWMSet(greenPin, G);
  SoftPWMSet(greenPin2, G2);

  B = (cmd.substring(cmd.indexOf("G") + 1 , cmd.indexOf("B") )).toInt();
  B2 = B;
  SoftPWMSet(bluePin, B);
  SoftPWMSet(bluePin2, B2);
}
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char) Serial.read();
    if (inChar == '\n') {
      cmd_complete = true;
    } else {
      cmd += inChar;
    }
  }
}
void fade1()
{
  static unsigned int rgbColour[3] = {255, 0, 0}; //Start on red
  static int incColour = 1;
  static int decColour = 0;
  static int i = -1;

  // cross-fade the two colours.
  i++;
  if (i > 254) {
    i = 0;
    decColour ++;
    if (decColour > 2) decColour = 0;
    if (decColour == 2)  incColour = 0;
    else incColour = decColour + 1;
  }


  rgbColour[decColour] -= 1;
  rgbColour[incColour] += 1;

  setColourRgb(rgbColour[0], rgbColour[1], rgbColour[2]);
  fade_goTime = millis() + fade_break;
}
void fade2()
{
  static unsigned int rgbColour[3] = {255, 0, 0}; //Start on red
  static int incColour = 1;
  static int decColour = 0;
  static int i = -1;

  // cross-fade the two colours.
  i++;
  if (i > 254) {
    i = 0;
    decColour ++;
    if (decColour > 2) decColour = 0;
    if (decColour == 2)  incColour = 0;
    else incColour = decColour + 1;
  }


  rgbColour[decColour] -= 1;
  rgbColour[incColour] += 1;

  setColourRgb2(rgbColour[0], rgbColour[1], rgbColour[2]);
  fade_goTime = millis() + fade_break;
}
void setColourRgb(unsigned int red, unsigned int green, unsigned int blue) {
  SoftPWMSet(redPin, red);
  SoftPWMSet(greenPin, green);
  SoftPWMSet(bluePin, blue);
}
void setColourRgb2(unsigned int red2, unsigned int green2, unsigned int blue2) {
  SoftPWMSet(redPin2, red2);
  SoftPWMSet(greenPin2, green2);
  SoftPWMSet(bluePin2, blue2);
}

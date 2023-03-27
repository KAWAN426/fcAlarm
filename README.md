#if 1

#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <TouchScreen.h>
#define MINPRESSURE 200
#define MAXPRESSURE 1000

// ALL Touch panels and wiring is DIFFERENT
// copy-paste results from TouchScreen_Calibr_native.ino
const int XP = 6, XM = A2, YP = A1, YM = 7; //ID=0x9341
const int TS_LEFT = 907, TS_RT = 136, TS_TOP = 942, TS_BOT = 139;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button btn1, btn2, btn3, btn4, btn5, btn6, btn7, btn8, btn9, btn0;

int pixel_x, pixel_y;     //Touch_getXY() updates global vars
bool Touch_getXY(void)
{
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   //because TFT control pins
    digitalWrite(XM, HIGH);
    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (pressed) {
        pixel_x = map(p.x, TS_LEFT, TS_RT, 0, tft.width() - 55); //.kbv makes sense to me
        pixel_y = map(p.y, TS_TOP, TS_BOT, 0, tft.height() + 100);
    }
    return pressed;
}

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

void showmsgXY(int x, int y, int sz, const GFXfont *f, const char *msg)
{
    int16_t x1, y1;
    uint16_t wid, ht;
    tft.setFont(f);
    tft.setCursor(x, y);
    tft.setTextColor(WHITE);
    tft.setTextSize(sz);
    tft.print(msg);
}

void setup(void)
{
    Serial.begin(9600);
    uint16_t ID = tft.readID();
    Serial.print("TFT ID = 0x");
    Serial.println(ID, HEX);
    Serial.println("Calibrate for your Touch Panel");
    if (ID == 0xD3D3) ID = 0x9486; // write-only shield
    tft.begin(ID);
    tft.setRotation(1);            //PORTRAIT
    tft.fillScreen(BLACK);
    int size = 45;
    int margin = 15;
    btn1.initButton(&tft, size / 2 + margin, size / 2 + margin, size, size, WHITE, CYAN, BLACK, "1", 2);
    btn2.initButton(&tft, size / 2 + margin + (size + margin) * 1, size / 2 + margin, size, size, WHITE, CYAN, BLACK, "2", 2);
    btn3.initButton(&tft, size / 2 + margin + (size + margin) * 2, size / 2 + margin, size, size, WHITE, CYAN, BLACK, "3", 2);
    btn4.initButton(&tft, size / 2 + margin + (size + margin) * 3, size / 2 + margin, size, size, WHITE, CYAN, BLACK, "4", 2);
    btn5.initButton(&tft, size / 2 + margin + (size + margin) * 4, size / 2 + margin, size, size, WHITE, CYAN, BLACK, "5", 2);
    btn6.initButton(&tft, size / 2 + margin, size / 2 + margin + (size + margin) * 1, size, size, WHITE, CYAN, BLACK, "6", 2);
    btn7.initButton(&tft, size / 2 + margin + (size + margin) * 1, size / 2 + margin + (size + margin) * 1, size, size, WHITE, CYAN, BLACK, "7", 2);
    btn8.initButton(&tft, size / 2 + margin + (size + margin) * 2, size / 2 + margin + (size + margin) * 1, size, size, WHITE, CYAN, BLACK, "8", 2);
    btn9.initButton(&tft, size / 2 + margin + (size + margin) * 3, size / 2 + margin + (size + margin) * 1, size, size, WHITE, CYAN, BLACK, "9", 2);
    btn0.initButton(&tft, size / 2 + margin + (size + margin) * 4, size / 2 + margin + (size + margin) * 1, size, size, WHITE, CYAN, BLACK, "0", 2);
    btn1.drawButton(false);
    btn2.drawButton(false);
    btn3.drawButton(false);
    btn4.drawButton(false);
    btn5.drawButton(false);
    btn6.drawButton(false);
    btn7.drawButton(false);
    btn8.drawButton(false);
    btn9.drawButton(false);
    btn0.drawButton(false);

    showmsgXY(size / 2 + margin + (size + margin) * 4 + 400,  size / 2 + margin + (size + margin) * 1, 6, NULL, "12:25");
}

/* two buttons are quite simple
 */
void loop(void)
{
    bool down = Touch_getXY();
    btn1.press(down && btn1.contains(pixel_y, pixel_x));
    btn2.press(down && btn2.contains(pixel_y, pixel_x));
    btn3.press(down && btn3.contains(pixel_y, pixel_x));
    btn4.press(down && btn4.contains(pixel_y, pixel_x));
    btn5.press(down && btn5.contains(pixel_y, pixel_x));
    btn6.press(down && btn6.contains(pixel_y, pixel_x));
    btn7.press(down && btn7.contains(pixel_y, pixel_x));
    btn8.press(down && btn8.contains(pixel_y, pixel_x));
    btn9.press(down && btn9.contains(pixel_y, pixel_x));
    btn0.press(down && btn0.contains(pixel_y, pixel_x));

    Serial.println("justReleased : " + String(btn1.justReleased()) + ", isPressed : " + String(btn1.isPressed()) + ", justPressed : " + String(btn1.justPressed()));

    if (btn1.justPressed()){
      Serial.println(1);
      btn1.drawButton(true);
    }
    if (btn2.isPressed()){
      Serial.println(2);
      btn2.drawButton(true);
    }else if(btn2.justReleased()) {
      btn2.drawButton(false);
    }
    if (btn3.isPressed()){
      Serial.println(3);
      btn3.drawButton(true);
    }else if(btn3.justReleased()) {
      btn3.drawButton(false);
    }
    if (btn4.isPressed()){
      Serial.println(4);
      btn4.drawButton(true);
    }else if(btn4.justReleased()) {
      btn4.drawButton(false);
    }
    if (btn5.isPressed()){
      Serial.println(5);
      btn5.drawButton(true);
    }else if(btn5.justReleased()) {
      btn5.drawButton(false);
    }
    if (btn6.isPressed()){
      Serial.println(6);
      btn6.drawButton(true);
    }else if(btn6.justReleased()) {
      btn6.drawButton(false);
    }
    if (btn7.isPressed()){
      Serial.println(7);
      btn7.drawButton(true);
    }else if(btn7.justReleased()) {
      btn7.drawButton(false);
    }
    if (btn8.isPressed()){
      Serial.println(8);
      btn8.drawButton(true);
    }else if(btn8.justReleased()) {
      btn8.drawButton(false);
    }
    if (btn9.isPressed()){
      Serial.println(9);
      btn9.drawButton(true);
    }else if(btn9.justReleased()) {
      btn9.drawButton(false);
    }
    if (btn0.isPressed()){
      Serial.println(0);
      btn0.drawButton(true);
    }else if(btn0.justReleased()) {
      btn0.drawButton(false);
    }
}
#endif


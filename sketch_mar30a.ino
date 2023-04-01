#if 1

#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <TouchScreen.h>
#define minsPRESSURE 200
#define MAXPRESSURE 1000
#include <string.h>

// ALL Touch panels and wiring is DIFFERENT
// copy-paste results from TouchScreen_Calibr_native.ino
const int XP = 6, XM = A2, YP = A1, YM = 7; //ID=0x9341
const int TS_LEFT = 907, TS_RT = 136, TS_TOP = 942, TS_BOT = 139;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button btn1, btn2, btn3, btn4, btn5, btn6, btn7, btn8, btn9, btn0,
  hourBtn,minsBtn,colBtn,applyBtn,cancelBtn;

char hour[3] = {'0', '0', '\0'};
char mins[3] = {'0', '0', '\0'};
bool isHour = true;
unsigned long time = 0;

int pixel_x, pixel_y;     //Touch_getXY() updates global vars
bool Touch_getXY(void)
{
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   //because TFT control pins
    digitalWrite(XM, HIGH);
    bool pressed = (p.z > minsPRESSURE && p.z < MAXPRESSURE);
    if (pressed) {
        pixel_x = map(p.x, TS_LEFT, TS_RT, 0, tft.height()); //.kbv makes sense to me
        pixel_y = map(p.y, TS_TOP, TS_BOT, 0, tft.width());
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

int width = 38;
int height = 38;
int margin = 10;

int getLeft(int line){
  return width / 2 + margin + (width + margin) * (line - 1);
}
int getTop(int line){
  return height / 2 + margin + (height + margin) * (line - 1);
}

char* changeTime(char time, Adafruit_GFX_Button clickBtn) {
  clickBtn.drawButton(true);
  if(isHour){
    hour[0] = hour[1];
    hour[1] = time;
  } else {
    mins[0] = mins[1];
    mins[1] = time;
    if(atoi(mins) > 60){
      strcpy(mins, "60");
    }
  }
}

void setup(void)
{
    Serial.begin(9600);
    uint16_t ID = tft.readID();
    if (ID == 0xD3D3) ID = 0x9486;
    tft.begin(ID);
    tft.setRotation(1);
    tft.fillScreen(BLACK);

    btn1.initButton(&tft, getLeft(1), getTop(1), width, height, WHITE, WHITE, BLACK, "1", 2);
    btn2.initButton(&tft, getLeft(2), getTop(1), width, height, WHITE, WHITE, BLACK, "2", 2);
    btn3.initButton(&tft, getLeft(3), getTop(1), width, height, WHITE, WHITE, BLACK, "3", 2);
    btn4.initButton(&tft, getLeft(1), getTop(2), width, height, WHITE, WHITE, BLACK, "4", 2);
    btn5.initButton(&tft, getLeft(2), getTop(2), width, height, WHITE, WHITE, BLACK, "5", 2);
    btn6.initButton(&tft, getLeft(3), getTop(2), width, height, WHITE, WHITE, BLACK, "6", 2);
    btn7.initButton(&tft, getLeft(1), getTop(3), width, height, WHITE, WHITE, BLACK, "7", 2);
    btn8.initButton(&tft, getLeft(2), getTop(3), width, height, WHITE, WHITE, BLACK, "8", 2);
    btn9.initButton(&tft, getLeft(3), getTop(3), width, height, WHITE, WHITE, BLACK, "9", 2);
    btn0.initButton(&tft, getLeft(2), getTop(4), width, height, WHITE, WHITE, BLACK, "0", 2);
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

    hourBtn.initButton(&tft, getLeft(4) + 20, getTop(1) + 25, 55, 55, BLACK, WHITE, BLACK, hour, 4);
    hourBtn.drawButton(true);
    colBtn.initButton(&tft, getLeft(5) + 13, getTop(1) + 25, 0, 0, BLACK, WHITE, BLACK, ":", 6);
    colBtn.drawButton(true);
    minsBtn.initButton(&tft, getLeft(6), getTop(1) + 25, 55, 55, BLACK, WHITE, BLACK, mins, 4);
    minsBtn.drawButton(true);

    applyBtn.initButton(&tft, getLeft(5) + 13, getTop(3), 125, 45, WHITE, WHITE, BLACK, "Apply", 2.5);
    applyBtn.drawButton(true);

    cancelBtn.initButton(&tft, getLeft(5) + 13, getTop(4) + 15, 125, 45, WHITE, WHITE, BLACK, "Cancle", 2.5);
    cancelBtn.drawButton(true);
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
    
    hourBtn.press(down && hourBtn.contains(pixel_y, pixel_x));
    minsBtn.press(down && minsBtn.contains(pixel_y, pixel_x));

    delay(50);

//    Serial.println(String(hour) + " " + String(mins));
    
    if (btn1.justPressed()){
      changeTime('1',btn1);
    }else if(!btn1.isPressed() && btn1.justReleased()) {
      btn1.drawButton(false);
    }
    if (btn2.justPressed()){
      changeTime('2',btn2);
    }else if(!btn2.isPressed() && btn2.justReleased()) {
      btn2.drawButton(false);
    }
    if (btn3.justPressed()){
      changeTime('3',btn3);
    }else if(!btn3.isPressed() && btn3.justReleased()) {
      btn3.drawButton(false);
    }
    if (btn4.justPressed()){
      changeTime('4',btn4);
    }else if(!btn4.isPressed() && btn4.justReleased()) {
      btn4.drawButton(false);
    }
    if (btn5.justPressed()){
      changeTime('5',btn5);
    }else if(!btn5.isPressed() && btn5.justReleased()) {
      btn5.drawButton(false);
    }
    if (btn6.justPressed()){
      changeTime('6',btn6);
    }else if(!btn6.isPressed() && btn6.justReleased()) {
      btn6.drawButton(false);
    }
    if (btn7.justPressed()){
      changeTime('7',btn7);
    }else if(!btn7.isPressed() && btn7.justReleased()) {
      btn7.drawButton(false);
    }
    if (btn8.justPressed()){
      changeTime('8',btn8);
    }else if(!btn8.isPressed() && btn8.justReleased()) {
      btn8.drawButton(false);
    }
    if (btn9.justPressed()){
      changeTime('9',btn9);
    }else if(!btn9.isPressed() && btn9.justReleased()) {
      btn9.drawButton(false);
    }
    if (btn0.justPressed()){
      changeTime('0',btn0);
    }else if(!btn0.isPressed() && btn0.justReleased()) {
      btn0.drawButton(false);
    }
    
    if (hourBtn.justPressed()){
      isHour = true;
      minsBtn.initButton(&tft, getLeft(6), getTop(1) + 25, 55, 55, BLACK, WHITE, BLACK, mins, 4);
      minsBtn.drawButton(true);
      hourBtn.initButton(&tft, getLeft(4) + 20, getTop(1) + 25, 55, 55, BLACK, WHITE, BLACK, hour, 4);
      hourBtn.drawButton(true);
    }
    if (minsBtn.justPressed()){
      isHour = false;
      minsBtn.drawButton(true);
      minsBtn.initButton(&tft, getLeft(6), getTop(1) + 25, 55, 55, BLACK, WHITE, BLACK, mins, 4);
      minsBtn.drawButton(true);
      hourBtn.initButton(&tft, getLeft(4) + 20, getTop(1) + 25, 55, 55, BLACK, WHITE, BLACK, hour, 4);
      hourBtn.drawButton(true);
    }

    time += 1;
    
    if(isHour){
      if(time % 20 == 0){
        hourBtn.initButton(&tft, getLeft(4) + 20, getTop(1) + 25, 55, 55, BLACK, WHITE, BLACK, hour, 4);
        hourBtn.drawButton(true);
      }else if(time % 20 == 10) {
        hourBtn.initButton(&tft, getLeft(4) + 20, getTop(1) + 25, 55, 55, BLACK, BLACK, BLACK, hour, 4);
        hourBtn.drawButton(true);
      }
    }else{
      if(time % 20 == 0){
        minsBtn.initButton(&tft, getLeft(6), getTop(1) + 25, 55, 55, BLACK, WHITE, BLACK, mins, 4);
        minsBtn.drawButton(true);
      }else if(time % 20 == 10) {
        minsBtn.initButton(&tft, getLeft(6), getTop(1) + 25, 55, 55, BLACK, BLACK, BLACK, mins, 4);
        minsBtn.drawButton(true);
      } 
    }
}
#endif

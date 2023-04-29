#include <M5Core2.h>

//Button lt(0, 0, 160, 120,false,  "left-top",{BLACK, WHITE, WHITE});
//Button lb(0, 120, 160, 120,false,  "left-bottom",{BLACK, WHITE, WHITE});
//Button rt(160, 0, 160, 120,false,  "right-top",{BLACK, WHITE, WHITE});
//Button rb(160, 120, 160, 120,false,  "right-bottom",{BLACK, WHITE, WHITE});
Button front(110, 0, 100, 75, false,  "FRONT",{GREEN, WHITE, WHITE});
Button stop(110, 80, 100, 75 , false,  "STOP",{RED, WHITE, WHITE});
Button back(110, 165, 100, 75, false,  "BACK",{GREEN, WHITE, WHITE});
Button left(5, 80, 95, 75, false,  "LEFT",{BLUE, WHITE, WHITE});
Button right(215, 80, 95, 75, false,  "RIGHT",{BLUE, WHITE, WHITE});

  void colorButtons(Event& e) {
    Button& b = *e.button;
    M5.Lcd.fillRect(b.x, b.y, b.w, b.h, b.isPressed() ? WHITE : BLACK);
  }

  void rtTapped(Event& e) {
    Serial.println("--- TOP RIGHT BUTTON WAS TAPPED ---");
  }
  void rbTapped(Event& e) {
    Serial.println("--- BOTTOM RIGHT BUTTON WAS TAPPED ---");
  }
  void ltTapped(Event& e) {
    Serial.println("--- TOP LEFT BUTTON WAS TAPPED ---");
  }
  void lbTapped(Event& e) {
    Serial.println("--- BOTTOM LEFT BUTTON WAS TAPPED ---");
  }
  
void setup() {
  M5.begin();
  Serial.begin(115200);
//  M5.Lcd.fillScreen(WHITE);
//    M5.Buttons.addHandler(colorButtons,  E_TOUCH + E_RELEASE);
//    rt.addHandler(rtTapped, E_PRESSED);
//    rb.addHandler(rbTapped, E_PRESSED);
//    lt.addHandler(ltTapped, E_PRESSED);
//    lb.addHandler(lbTapped, E_PRESSED);
  
//   if (rb.isPressed()) Serial.print("Pressed ");
}

  void loop() {
    M5.update();
    if (front.wasPressed()) Serial.print("FRONT");
    if (stop.wasPressed()) Serial.print("STOP");
    if (back.wasPressed()) Serial.print("BACK");
    if (left.wasPressed()) Serial.print("LEFT");
    if (right.wasPressed()) Serial.print("RIGHT");
  }

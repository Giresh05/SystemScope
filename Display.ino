#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String input = "";
String cpu = "", gpu = "", fps = "";

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Waiting for data...");
  display.display();
}

void loop() {
  if (Serial.available()) {
    input = Serial.readStringUntil('\n');

    int cpuIndex = input.indexOf("CPU:");
    int gpuIndex = input.indexOf("GPU:");
    int fpsIndex = input.indexOf("FPS:");

    if (cpuIndex != -1 && gpuIndex != -1 && fpsIndex != -1) {
      cpu = input.substring(cpuIndex + 4, gpuIndex).trim();
      gpu = input.substring(gpuIndex + 4, fpsIndex).trim();
      fps = input.substring(fpsIndex + 4).trim();

      // ✅ Display on OLED
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("System Performance:");
      display.print("CPU: "); display.println(cpu + "%");
      display.print("GPU: "); display.println(gpu + "%");
      display.print("FPS: "); display.println(fps);
      display.display();

      // ✅ Display on Serial Monitor
      Serial.println("=== System Performance ===");
      Serial.println("CPU: " + cpu + "%");
      Serial.println("GPU: " + gpu + "%");
      Serial.println("FPS: " + fps);
      Serial.println("==========================");
    }
  }
}

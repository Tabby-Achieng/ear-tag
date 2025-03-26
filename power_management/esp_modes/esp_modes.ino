#include <Arduino.h>

#include <Arduino.h>

#define WAKEUP_PIN_1 15  // GPIO pin to wake up ESP32 (Pin 15)
#define WAKEUP_PIN_2 16  // GPIO pin to wake up ESP32 (Pin 16)

void setup() {
    Serial.begin(115200);
    delay(1000);  // Allow time for Serial Monitor connection

    // Configure GPIO as input with pull-up resistors
    pinMode(WAKEUP_PIN_1, INPUT_PULLUP);
    pinMode(WAKEUP_PIN_2, INPUT_PULLUP);

    // Enable wake-up on either GPIO 15 or GPIO 16 (wakes when LOW)
    esp_sleep_enable_ext0_wakeup((gpio_num_t)WAKEUP_PIN_1, LOW); // For WAKEUP_PIN_1
    esp_sleep_enable_ext0_wakeup((gpio_num_t)WAKEUP_PIN_2, LOW); // For WAKEUP_PIN_2

    Serial.println("Going to Light Sleep. Press the button on either GPIO 15 or GPIO 16 to wake up...");
}

void loop() {
    Serial.println("Entering Light Sleep Mode...");

    // Enter Light Sleep
    esp_light_sleep_start();

    // When ESP32 wakes up, it resumes here
    Serial.println("Woke up from Light Sleep!");
    delay(2000);  // Simulate processing time before going back to sleep
}

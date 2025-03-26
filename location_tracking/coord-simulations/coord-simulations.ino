#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#define SIMULATE_BUTTON 15  // GPIO for push button

SoftwareSerial ss(16, 17);  // RX, TX for GPS
TinyGPSPlus gps;

bool simulateMode = false;  // Track simulation state
int buttonState = HIGH;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 200;

const float simulatedCoordinates[][2] = {
    { -1.2921, 36.8219 },  // Nairobi
    { -1.3000, 36.8000 },  // Simulated Point 1
    { -1.3100, 36.8100 }   // Simulated Point 2
};

int simIndex = 0;

void setup() {
    Serial.begin(115200);
    ss.begin(9600);

    pinMode(SIMULATE_BUTTON, INPUT_PULLUP);
}

void loop() {
    // Read button state with debounce
    int reading = digitalRead(SIMULATE_BUTTON);
    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }
    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading == LOW && lastButtonState == HIGH) {
            simulateMode = !simulateMode;  // Toggle simulation mode
            Serial.print("Simulation Mode: ");
            Serial.println(simulateMode ? "ON" : "OFF");
        }
    }
    lastButtonState = reading;

    // GPS Data Processing
    if (simulateMode) {
        Serial.print("Simulated Location: ");
        Serial.print(simulatedCoordinates[simIndex][0], 6);
        Serial.print(", ");
        Serial.println(simulatedCoordinates[simIndex][1], 6);

        simIndex = (simIndex + 1) % 3;  // Cycle through locations
        delay(3000);  // Simulate movement every 3 seconds
    } else {
        while (ss.available()) {
            gps.encode(ss.read());
        }

        if (gps.location.isUpdated()) {
            Serial.print("Live GPS Location: ");
            Serial.print(gps.location.lat(), 6);
            Serial.print(", ");
            Serial.println(gps.location.lng(), 6);
        }
    }
}

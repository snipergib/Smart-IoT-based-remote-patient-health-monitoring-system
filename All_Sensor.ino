#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

const int pulseSensorPin = 0;
const int ad8232Pin = A1;
int pulseSignal;
int ad8232Signal;
int ad8232Threshold = 500;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!mlx.begin()) {
    Serial.println("Error connecting to MLX sensor. Check wiring.");
    while (1);
  }
}

void loop() {
  // Read pulse sensor signal
  pulseSignal = analogRead(pulseSensorPin);
  Serial.print("Pulse sensor value: ");
  Serial.println(pulseSignal);

  // Read AD8232 signal
  ad8232Signal = analogRead(ad8232Pin);
  Serial.print("AD8232 sensor value: ");
  Serial.println(ad8232Signal);

  // Check for a heartbeat
  if (pulseSignal > ad8232Threshold) {
    Serial.println("Heartbeat detected");
  }

  // Read temperature sensor
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC());
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF());
  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");

  Serial.println();
  delay(1500);
}

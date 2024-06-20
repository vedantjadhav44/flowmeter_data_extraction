#include <ModbusMaster.h>
// Modbus object
ModbusMaster node;
// Define the DE/RE pin for RS485 control
const int DE_RE_PIN = 3;  // Pin D3 for DE/RE control
void setup() {
  // Initialize Serial for debug prints
  Serial.begin(9600);
  delay(100); // Allow time for serial monitor to initialize

  // Initialize Modbus communication
  node.begin(25, Serial);  // Modbus ID 025, using Serial (TX/RX)

  // Set up RS485 control pin
  pinMode(DE_RE_PIN, OUTPUT);
  digitalWrite(DE_RE_PIN, LOW);  // Set DE/RE pin low initially

  Serial.println("Setup complete.");
}
void loop() {
  uint8_t result;
  uint16_t data[3];  // Array to store multiple register values

  // Example: Read flow rate values from registers 0x4001 to 0x4003 (addresses 16385 to 16387), 3 registers
  result = node.readHoldingRegisters(0x4001, 3);

  if (result == node.ku8MBSuccess) {
    // Print flow rate values
    Serial.print("Flow Rate Values: ");
    for (uint8_t i = 0; i < 3; i++) {
      data[i] = node.getResponseBuffer(i);
      Serial.print(data[i]);
      Serial.print(" ");
    }
    Serial.println();
  } else {
    Serial.print("Error reading flow rate values. Error: ");
    Serial.println(result, HEX); // Print error code in hexadecimal
  }

  // Read flow rate value unit from register 0x4004 (address 16388), 1 register
  result = node.readHoldingRegisters(0x4004, 1);

  if (result == node.ku8MBSuccess) {
    data[0] = node.getResponseBuffer(0);
    Serial.print("Flow Rate Value Unit: ");
    Serial.println(data[0]);
  } else {
    Serial.print("Error reading flow rate value unit. Error: ");
    Serial.println(result, HEX); // Print error code in hexadecimal
  }

  // Example: Read totalizer values from registers 0x4005 to 0x4007 (addresses 16389 to 16391), 3 registers
  result = node.readHoldingRegisters(0x4005, 3);

  if (result == node.ku8MBSuccess) {
    // Print totalizer values
    Serial.print("Totalizer Values: ");
    for (uint8_t i = 0; i < 3; i++) {
      data[i] = node.getResponseBuffer(i);
      Serial.print(data[i]);
      Serial.print(" ");
    }
    Serial.println();
  } else {
    Serial.print("Error reading totalizer values. Error: ");
    Serial.println(result, HEX); // Print error code in hexadecimal
  }

  // Read totalizer value unit from register 0x4008 (address 16392), 1 register
  result = node.readHoldingRegisters(0x4008, 1);

  if (result == node.ku8MBSuccess) {
    data[0] = node.getResponseBuffer(0);
    Serial.print("Totalizer Value Unit: ");
    Serial.println(data[0]);
  } else {
    Serial.print("Error reading totalizer value unit. Error: ");
    Serial.println(result, HEX); // Print error code in hexadecimal
  }

  delay(1000); // Delay between readings'
}

#define PotentiometerPin 33
#define ledPin 27
volatile int inputVoltage;

void Read(void* param){
  while(1){
    inputVoltage = analogRead(PotentiometerPin);
    vTaskDelay(pdMS_TO_TICKS(40));
  }
}

void Indicator(void* param){
  pinMode(ledPin, OUTPUT);
  while(1){
    digitalWrite(ledPin, inputVoltage > 4096*0.7);
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}
void Check(void* param){
  auto prevState = inputVoltage;
  while(1){
    if(inputVoltage != prevState){
    Serial.print("Potentiometer voltage is now:");
    Serial.print(inputVoltage*(3.3/4096));
    Serial.print("\n");
    prevState = inputVoltage; 
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  xTaskCreate(Read, "Input Task", 2048, NULL, 1, NULL);
  xTaskCreate(Indicator, "Led Task", 2048, NULL, 1, NULL);
  xTaskCreate(Check, "Check Task", 2048, NULL, 1, NULL);
  Serial.println("Hello, ESP32!");
}

void loop() {
  // put your main code here, to run repeatedly:
  // this speeds up the simulation
}

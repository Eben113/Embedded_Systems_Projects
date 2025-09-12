#define ledPin 27
#define buttonPin 25

const int delays[] = {0, 150, 250};
const String modes[] = {"Constant\n", "Fast\n", "Slow\n"};
const int num_delays = 3;
int currentIdx = 0;

void blinkTask(void* param){
  pinMode(ledPin, OUTPUT);
  while(1){
    digitalWrite(ledPin, HIGH);
    vTaskDelay(pdMS_TO_TICKS(delays[currentIdx]));
    vTaskDelay(pdMS_TO_TICKS(delays[currentIdx]));
    digitalWrite(ledPin, LOW);
    vTaskDelay(pdMS_TO_TICKS(delays[currentIdx]));
  }
}

void buttonTask(void* params){
  pinMode(buttonPin, INPUT);
  bool prevState = LOW;

  while(1){
    bool currState = digitalRead(buttonPin);
    if(prevState == LOW && currState == HIGH){
      currentIdx = (currentIdx + 1) % 3;
      Serial.print("Mode: ");
      Serial.print(modes[currentIdx]);
      //vTaskDelay(pdMS_TO_TICKS(150));
    }
    prevState = currState;
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  xTaskCreate(blinkTask, "Blink Task", 2048, NULL, 1, NULL);
  xTaskCreate(buttonTask, "Button Task", 2048, NULL, 1, NULL);
  Serial.println("Hello, ESP32!");
}

void loop() {
  // put your main code here, to run repeatedly:
}

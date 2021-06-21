#define IRpin A0
const int feeding_messenger = 2;
const int fill_messenger = 3;
const int change_messenge  = 4;
const int temperture_messenge = 12;
const int relay = 6;
const int bitMessenger = 7;
const int bitMessenger2 = 8;

int feeding = 0;
int fillwater = 0;
int changewater = 0;
int temperture = 0;

int fillwater_time = 60;
int change_time = 10;
int timer = 0;

float sensorValue, IR_distance;
void setup() {
  Serial.begin(9600);

  pinMode(feeding_messenger, INPUT);
  pinMode(fill_messenger, INPUT);
  pinMode(change_messenge, INPUT);
  pinMode(temperture_messenge, INPUT);
  pinMode(IRpin, INPUT);

  pinMode(relay,OUTPUT);
  pinMode(bitMessenger,OUTPUT);
  pinMode(bitMessenger2,OUTPUT);
}

void loop() {
  sensorValue = analogRead(IRpin);//紅外線校正
  sensorValue *= 0.0048828125;
  IR_distance = 65 * pow(sensorValue, -1.10);
  Serial.println(IR_distance);

  feeding = digitalRead(feeding_messenger);
  fillwater = digitalRead(fill_messenger);
  changewater = digitalRead(change_messenge);
  temperture = digitalRead(temperture_messenge);
  
  Serial.print("temperture:  ");
  Serial.println(temperture);
  Serial.println("");
  Serial.print("feeding:  ");
  Serial.println(feeding);
  Serial.println("");
  Serial.print("fillwater:  ");
  Serial.println(fillwater);
  Serial.println("");
  Serial.print("changewater:  ");
  Serial.println(changewater);
  Serial.println("");
  delay(1000);
  if(temperture == 1 and IR_distance <= 57 and fillwater == 1){
    digitalWrite(relay ,HIGH);
    while(timer < fillwater_time){
      sensorValue = analogRead(IRpin);//紅外線校正
      sensorValue *= 0.0048828125;
      IR_distance = 65 * pow(sensorValue, -1.10);
      Serial.println(IR_distance);
      if(IR_distance <=57){
        timer++;
        Serial.print("timer : ");
        Serial.println(timer);
        delay(1000);
      }
      else if(IR_distance >57){
        break;
      }
    }
    Serial.println("turn off");
    digitalWrite(relay, LOW);
    digitalWrite(bitMessenger, HIGH);
    delay(1500);
    digitalWrite(bitMessenger, LOW);
  }
  else if(changewater == 1){
    digitalWrite(relay ,HIGH);
    while(timer < change_time){
      timer++;
      digitalWrite(relay, HIGH);
      Serial.print("timer : ");
      Serial.println(timer);
      delay(1000);
    }
    Serial.println("turn off");
    digitalWrite(relay, LOW);
    digitalWrite(bitMessenger2, HIGH);
    delay(1500);
    digitalWrite(bitMessenger2, LOW);
  }
  timer = 0;
}

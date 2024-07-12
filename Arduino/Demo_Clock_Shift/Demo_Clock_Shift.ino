#define OUTPUT_ENABLE 3
#define LOAD 4
#define CLEAR 5
#define SHIFT_CLK 6
#define DATA 7

void setup() {
  // put your setup code here, to run once:

  pinMode(OUTPUT_ENABLE, OUTPUT);
  pinMode(LOAD, OUTPUT);
  pinMode(CLEAR, OUTPUT);
  pinMode(SHIFT_CLK, OUTPUT);
  pinMode(DATA, OUTPUT);
 digitalWrite(CLEAR, HIGH);
  Serial.begin(9600);

}

int pattern = 0b00000001;
int hour = 0;
int min = 0;

int min_ones = 0;
int min_tens = 0;
int hour_ones = 0;
int hour_tens = 0;
void loop() {
  // put your main code here, to run repeatedly:

  min += 1;

  if(min >= 60){
    hour += 1;
    min = 0;
  }

  if(hour >= 24){
    hour = 0;
  }

  
  min_tens = floor(min/10);
  min_ones = min - min_tens * 10;


  hour_tens = floor(hour/10);
  hour_ones = hour - hour_tens * 10;

  digitalWrite(LOAD, LOW);

  shift_number(min_ones);
  shift_number(min_tens);
  shift_number(hour_ones);
  shift_number(hour_tens);
  digitalWrite(LOAD, HIGH);
    delay(50);
 


}

void shift_number(int number){
  int number2;
  if(number >= 8){
      number2 = number - 8;
  }else{
      number2 = 9;
  }

  shiftOut(DATA, SHIFT_CLK, MSBFIRST, pattern << number2);
  shiftOut(DATA, SHIFT_CLK, MSBFIRST, pattern << number);
  
  
  
}

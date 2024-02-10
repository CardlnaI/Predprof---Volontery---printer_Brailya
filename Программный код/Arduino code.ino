#include <string.h>
#include <Servo.h>


#define UP_BUTT 10
#define LEFT_BUTT 11
#define RIGHT_BUTT 12

#define MOTOR_LINE_DIR 23
#define MOTOR_LINE_STP 9
#define MOTOR_LINE_SLP 24
#define MOTOR_LINE_EN 10

#define MOTOR_NLINE_DIR 26
#define MOTOR_NLINE_STP 10
#define MOTOR_NLINE_SLP 27
#define MOTOR_NLINE_EN 11

#define SERVO_L_U 5
#define SERVO_L_C 2
#define SERVO_L_B 3 

#define SERVO_R_U 6
#define SERVO_R_C 7
#define SERVO_R_B 8

#define SERVO_START_POS 0
#define SERVO_END_POS 30

#define SERVO_TIME 300
#define LINE_TIME 2000
#define NLINE_TIME 3000


Servo servo_l_u;
Servo servo_l_c;
Servo servo_l_b;

Servo servo_r_u;
Servo servo_r_c;
Servo servo_r_b;


int symbols_in_line = 0;
int max_symbols = 5;
int deg_ns = 0;


void setup() {

  pinMode(UP_BUTT, INPUT_PULLUP);
  pinMode(LEFT_BUTT, INPUT_PULLUP);
  pinMode(RIGHT_BUTT, INPUT_PULLUP);


  pinMode(MOTOR_LINE_DIR, OUTPUT);
  pinMode(MOTOR_LINE_STP, OUTPUT);
  pinMode(MOTOR_LINE_SLP, OUTPUT);
  pinMode(MOTOR_LINE_EN, OUTPUT);

  pinMode(MOTOR_NLINE_DIR, OUTPUT);
  pinMode(MOTOR_NLINE_STP, OUTPUT);
  pinMode(MOTOR_NLINE_SLP, OUTPUT);
  pinMode(MOTOR_NLINE_EN, OUTPUT);

  servo_l_u.attach(SERVO_L_U);
  servo_l_c.attach(SERVO_L_C);
  servo_l_b.attach(SERVO_L_B);

  servo_r_u.attach(SERVO_R_U);
  servo_r_c.attach(SERVO_R_C);
  servo_r_b.attach(SERVO_R_B);

  Serial.begin(9600); 

  servo_l_u.write(SERVO_START_POS);
  servo_l_c.write(SERVO_START_POS);
  servo_l_b.write(SERVO_START_POS);

  servo_r_u.write(180 - SERVO_START_POS);
  servo_r_c.write(180 - SERVO_START_POS);
  servo_r_b.write(180 - SERVO_START_POS);
  

}


int start_up = 1;
int start_left = 1;





void loop() {
  if (Serial.available()) {

    long mass1[] = Serial.read()
  

    symbols_in_line = 0;

    delay(15000);
    // delay(15000);


    digitalWrite(MOTOR_LINE_SLP, 1);
    digitalWrite(MOTOR_NLINE_SLP, 1);

    digitalWrite(MOTOR_LINE_DIR, 0);
    digitalWrite(MOTOR_NLINE_DIR, 1);

    int up = digitalRead(UP_BUTT);
    int left = digitalRead(LEFT_BUTT);
    int right = digitalRead(RIGHT_BUTT);

    
    for (long degs : mass1) {

      digitalWrite(MOTOR_LINE_EN, 1);
      digitalWrite(MOTOR_NLINE_EN, 1);

      if (symbols_in_line == 20) {

        analogWrite(MOTOR_NLINE_STP, 250);
        delay(1500);
        analogWrite(MOTOR_NLINE_STP, 0);

        digitalWrite(MOTOR_LINE_DIR, 0);
        analogWrite(MOTOR_LINE_STP, 250);
        delay(14000);
        symbols_in_line = 0;

      } else {
        
        analogWrite(MOTOR_NLINE_STP, 0);
        digitalWrite(MOTOR_LINE_DIR, 1);
        analogWrite(MOTOR_LINE_STP, 250);
        delay(700);
        analogWrite(MOTOR_LINE_STP, 0);

        symbols_in_line += 1;

      }

      digitalWrite(MOTOR_LINE_EN, 0);
      digitalWrite(MOTOR_NLINE_EN, 0);

      delay(1000);
      

      Serial.println(symbols_in_line);

      int deg0 = degs % 10;
      int deg1 = degs % (10 * 10) / 10;
      int deg2 = degs % (10 * 10 * 10) / (10 * 10);
      int deg3 = degs % (10 * 10 * 10 * 10) / (10 * 10 * 10);
      int deg4 = degs % (10 * 10 * 10 * 10 * 10) / (10 * 10 * 10 * 10);

      int degtmp = degs / (10 * 10 * 10 * 10);
      int deg5 = degtmp / 10;

      
      servo_l_u.write(deg0 * SERVO_END_POS);
      servo_l_c.write(deg1 * SERVO_END_POS);
      servo_l_b.write(deg2 * SERVO_END_POS);

      servo_r_u.write(180 - deg3 * SERVO_END_POS);
      servo_r_c.write(180 - deg4 * SERVO_END_POS);
      servo_r_b.write(180 - deg5 * SERVO_END_POS);

      delay(SERVO_TIME);

      servo_l_u.write(SERVO_START_POS);
      servo_l_c.write(SERVO_START_POS);
      servo_l_b.write(SERVO_START_POS);

      servo_r_u.write(180 - SERVO_START_POS);
      servo_r_c.write(180 - SERVO_START_POS);
      servo_r_b.write(180 - SERVO_START_POS);

      delay(SERVO_TIME);

      delay(500);
      
    }


    digitalWrite(MOTOR_LINE_EN, 1);
    digitalWrite(MOTOR_NLINE_EN, 1);

    analogWrite(MOTOR_NLINE_STP, 250);
    delay(1500);
    analogWrite(MOTOR_NLINE_STP, 0);

    digitalWrite(MOTOR_LINE_DIR, 0);
    analogWrite(MOTOR_LINE_STP, 250);
    delay(700 * symbols_in_line);
    analogWrite(MOTOR_LINE_STP, 0);
  }
    

}   

#include "HardwareSerial.h"
#include "Arduino.h"
#include "robot.h"
#include <LiquidCrystal_SoftI2C.h>
SoftwareWire *wire = new SoftwareWire(10, 11);
LiquidCrystal_I2C lcd(0x27, 16, 2, wire);

#define         MASK2_2         0x66    /* xooxxoox   01100110                  */ 
#define         MASK2_0         0xc0    /* ooxxxxxx   01100000                  */
#define         MASK0_2         0x03    /* xxxxxxoo   00000110                  */
#define         MASK3_3         0xe7    /* oooxxooo   11100111                  */
#define         MASK0_3         0x07    /* xxxxxooo   00000111                  */
#define         MASK3_0         0xe0    /* oooxxxxx   11100000                  */
#define         MASK4_0         0xf0    /* ooooxxxx   11110000                  */
#define         MASK0_4         0x0f    /* xxxxoooo   00001111                  */
#define         MASK1_1         0x81    /* oxxxxxxo   01111110                  */
#define			    MASK4_4			    0xff	  /* oooooooo	  11111111					        */


/////-----------Differential -------------------//////
const char coeffR1[50] ={
	100,	98, 	96, 	94, 	93, 	91, 	90, 	88, 	86, 	85,
	83, 	82, 	80, 	79, 	77, 	76, 	74, 	73, 	72, 	70,
	69, 	67, 	66, 	64, 	63, 	62, 	60, 	59, 	58, 	56,
	55, 	53, 	52, 	50, 	49, 	48, 	46, 	45, 	43, 	42,
	40, 	39, 	37, 	36, 	34, 	33, 	31, 	30, 	28, 	27
};

lineFollowerRobot::lineFollowerRobot(Motors &robotMotors,Buzzer &robotBuzzer,Led &robotLed,PushButton &button1,PushButton &button2,PushButton &button3,LineSensor &robotLineSensor)
{
  this -> robotMotors = robotMotors;
  this -> robotBuzzer = robotBuzzer;
  this -> robotLed = robotLed;
  this -> button1 = button1;
  this -> button2 = button2;
  this -> button3 = button3;
  this -> robotLineSensor = robotLineSensor;

}

void lineFollowerRobot::init()
{
  robotBuzzer.init(false);
  robotMotors.init();
  button1.init();
  button2.init();
  button3.init();
  robotLed.init(false);
  robotLineSensor.init();
  myservo.attach(6);
  // robotBuzzer.setBeep(300);
  state = INTRODUCTION_STATE;
  robot_runcase = STOP;
  MenuCount = 0;
  drawMenu = true;
  sensor = 0;
  cnt1 = 0;
  new_time = millis();


  myservo.write(servo_center);
  lcd.begin();
  lcd.backlight();  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("EIU FABLAB - SoE");
  lcd.setCursor(0,1);
  lcd.print("----LF Robot----");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("Press Switch 3    ");
}

void lineFollowerRobot::sensor_calibration()
{
  lcd.setCursor(0, 0);
  lcd.print("Sensor Calibrate");
  lcd.setCursor(0, 1);
  lcd.print("B:S1 W:S2  S:S3 ");
  myservo.write(servo_center);
  if(!button1.isPressed())
   {
    robotBuzzer.setBeep(200);
    unsigned long timeNow = millis();
    while(millis() - timeNow <= 2000){
      lcd.setCursor(0, 0);
      lcd.print("Calib Black Line");
      lcd.setCursor(0, 1);
      lcd.print(".......................");
      robotLineSensor.update_black(); // this is in the lineSensor file
    }
    lcd.setCursor(0, 1);
    lcd.print("Finished Cablib!");
   }

   if(!button2.isPressed())
   {
    robotBuzzer.setBeep(200);
    unsigned long timeNow = millis();
    while(millis() - timeNow <= 2000){
    lcd.setCursor(0, 0);
    lcd.print("Calib White Line");
    lcd.setCursor(0, 1);
    lcd.print(".......................");
    robotLineSensor.update_white(); // this is in the lineSensor file
    }
    lcd.setCursor(0, 1);
    lcd.print("Finished Cablib!");
   }

   if(!button3.isPressed())
   {
    robotBuzzer.setBeep(200);
    lcd.setCursor(0, 0);
    lcd.print("Done Calibration");
    lcd.setCursor(0, 1);
    lcd.print("Return to Main Menu");
    state = MAIN_MENU;
    }

}

void lineFollowerRobot::handle_calibration()
{
    lcd.setCursor(0, 0);
    lcd.print("Handle Calibrate");
    lcd.setCursor(0, 1);
    lcd.print("L:S1 R:S2 S:S3");
     myservo.write(servo_center);
    if(!button1.isPressed())
    {
      servo_center= servo_center + 1;
      delay(300);
    }
    if(!button2.isPressed())
    {
      servo_center = servo_center - 1;
      delay(300);
    }
    
    if(!button3.isPressed())
    {
      robotBuzzer.setBeep(200);
      lcd.setCursor(0, 0);
      lcd.print("Done Calibration");
      lcd.setCursor(0, 1);
      lcd.print("Return to Main Menu");
      state = MAIN_MENU;
    }
   //-----> SW3 save and out this functions.
}

void lineFollowerRobot::motor_check()
{
    lcd.setCursor(0, 0);
    lcd.print("--Check Motors--");
    lcd.setCursor(0, 1);
    lcd.print("F:S1 R:S2  S:S3");
     myservo.write(servo_center);
    if(!button1.isPressed())
    {
      unsigned long timeNow = millis();
      while(millis() - timeNow <= 3000){
      lcd.setCursor(0, 0);
      lcd.print("Running Forward ");
      lcd.setCursor(0, 1);
      lcd.print(".......................");
      robotMotors.setSpeed(100, 100);
      }
    }
    if(!button2.isPressed())
    {
      unsigned long timeNow = millis();
      while(millis() - timeNow <= 3000){
      lcd.setCursor(0, 0);
      lcd.print("Running Backward");
      lcd.setCursor(0, 1);
      lcd.print(".......................");
      robotMotors.setSpeed(-100, -100);
      }
    }
    robotMotors.setSpeed(0, 0);
    
   if(!button3.isPressed())
   {
    robotBuzzer.setBeep(200);
    lcd.setCursor(0, 0);
    lcd.print("Done Checking");
    lcd.setCursor(0, 1);
    lcd.print("Return to Main Menu");
    state = MAIN_MENU;
    }
     //-----> SW3 save and out this functions.
}

void lineFollowerRobot::show_position()
{
  byte curr_pos = 0;
  curr_pos = robotLineSensor.readSensor();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Current Sensors    ");
  lcd.setCursor(0, 1);
  lcd.print(curr_pos , BIN);
  delay(1000);
  if(!button3.isPressed())
  {
  robotBuzzer.setBeep(200);
  lcd.setCursor(0, 0);
  lcd.print("Done Checking     ");
  lcd.setCursor(0, 1);
  lcd.print("Return to Main Menu");
  state = MAIN_MENU;
  }
}

void lineFollowerRobot::menu_control()
{
   if(!button2.isPressed()){MenuCount++;delay(500);if(MenuCount > 5) MenuCount = 0;}
   if(!button1.isPressed()){MenuCount--;delay(500);if(MenuCount < 0) MenuCount = 5;}

      // Serial.println(MenuCount);
      if (MenuCount == 0) // First menu
      {
          lcd.setCursor(0, 0);
          lcd.print("----Main Menu---");
          lcd.setCursor(0, 1);
          lcd.print(" U:S1 D:S2 S:S3 ");
      }
      if (MenuCount== 1) // Sensor calibration menu
      {
        lcd.setCursor(0, 1);
        lcd.print("> 1. Sensor Cal     ");
        if(!button3.isPressed()){state = SENSOR_CALIB; delay(500);}
      }
      if (MenuCount== 2) // Show mask menu
      {
        lcd.setCursor(0, 1);
        lcd.print("> 2. Show Mask       ");
        if(!button3.isPressed()){state = SHOW_MASK_VALUE; delay(500); lcd.clear();}

      }
      if (MenuCount== 3) // Handle calibration
      {
        lcd.setCursor(0, 1);
        lcd.print("> 3. Handle Cal       ");
        if(!button3.isPressed()){state = SERVO_CALIB; delay(500);}

      }
      if (MenuCount== 4) // Motor check 
      {
        lcd.setCursor(0, 1);
        lcd.print("> 4. Motors         ");
        if(!button3.isPressed()){state = MOTOR_CHECK; delay(500);}

      }

      if (MenuCount == 5) // Running mode without PID
      {
        lcd.setCursor(0, 1);
        lcd.print("> 5. Racing        ");
        if(!button3.isPressed()){state = RACING; delay(500);}
      }
}

void lineFollowerRobot::robot_loop()
{
  // button 1, button 2, button 3
 
  switch (state) {
   case INTRODUCTION_STATE:
   {
    if(!button3.isPressed())
    {
      state = MAIN_MENU;
    }
    break;
   }
  case MAIN_MENU:
    { 
      // lcd.clear();
      menu_control();
      break;
    }

  case SENSOR_CALIB:
    { 
      sensor_calibration();
      break;
    }

  case SERVO_CALIB:
    {
      handle_calibration();
      break;
    }

  case MOTOR_CHECK:
    {
      motor_check();
      break;
    }

  case SHOW_MASK_VALUE:
    {
      show_position();
      break;
    }
  case RACING:
  {
    run();
    break;
  }

  default:{
      //to do
      state = MAIN_MENU;
    }

  }
}

void lineFollowerRobot::run()
{
  // Function to run the robot (in while);
  switch (robot_runcase)
    {
      case STOP:
        myservo.write(servo_center);
        robotMotors.setSpeed(0, 0);
        if(!button3.isPressed())
          {
            robotBuzzer.setBeep(300);
            robot_runcase = NORMAL_TRACE; 
          }
        break;

      case NORMAL_TRACE:
      
        sensor = robotLineSensor.readSensor();
        // Check cross line + Check right line + check left line
        if(check_crossline(sensor)==1){robot_runcase = CROSS_LINE_ONE;break;}
        // if(check_leftline(sensor)==1){robot_runcase = LEFT_HALF_LANE_ONE;break;}
        if(check_rightline(sensor)==1){robot_runcase = RIGHT_HALF_LANE_ONE;break;}

        switch(sensorMask(sensor, MASK3_3)) {
          //Car in the center of the line//
          case 0x00: 
          case 0x3c: // 001xx100 ->> This case hardly happens
            /* Center -> straight */
            handle_and_speed(0, speed_run);
            break;

          //Diviate to the Left//
          case 0x04: //0100 ~ x100
            /* Slight amount left of center -> slight turn to right */
            handle_and_speed(-2, speed_run);
            break;

          case 0x06: //0110
            /* Small amount left of center -> small turn to right */
            handle_and_speed(-5, 0.8 * speed_run);
            break;

          case 0x02: //0010
          case 0x07://0111
          case 0x1e:
            /* Medium amount left of center -> medium turn to right */
            handle_and_speed(-10, 0.6 * speed_run);
            break;

          case 0x03://0011
          case 0x01://0001
            /* Large amount left of center -> large turn to right */
            handle_and_speed(-15, 0.5 * speed_run);
            robot_runcase = LARGE_RIGHT_TURN; //--> Change to case 12 for configure the large turn RIGHT
            cnt1 =0;
            new_time = millis();
            break;

          //Diviate to the Right//
          case 0x20://0010 0000
            /* Slight amount right of center -> slight turn to left */
            handle_and_speed(2, speed_run);
            break;

          case 0x60: //0110 0000 
            /* Small amount right of center -> small turn to left */
            handle_and_speed(5, 0.8 * speed_run);
            break;

          case 0xe0://1110 0000
          case 0x40: //0100 0000
            /* Medium amount right of center -> medium turn to left */
            handle_and_speed(10, 0.6 * speed_run);
            break;

          case 0xc0: //1100 0000
          case 0x80: //1000 0000
            /* Large amount right of center -> large turn to left */
            handle_and_speed(15, 0.5 * speed_run);
            robot_runcase = LARGE_LEFT_TURN; //--> Change to case 12 for configure the large turn LEFT
            break;

          default:
            break;

        }
        break;

      case LARGE_LEFT_TURN:
        // Check cross line + Check right line + check left line
        if(check_crossline(sensor)==1){robot_runcase = CROSS_LINE_ONE;break;}
        // if(check_leftline(sensor)==1){robot_runcase = LEFT_HALF_LANE_ONE;break;}
        if(check_rightline(sensor)==1){robot_runcase = RIGHT_HALF_LANE_ONE;break;}
        if(sensorMask(sensor, MASK3_3) == 0x60  ) robot_runcase = NORMAL_TRACE;// 0110 0000 //0100 0000
        
        break;
      
      case LARGE_RIGHT_TURN:
        // Check cross line + Check right line + check left line
        if(check_crossline(sensor) == 1){robot_runcase = CROSS_LINE_ONE;break;}
        // if(check_leftline(sensor) == 1){robot_runcase = LEFT_HALF_LANE_ONE;break;}
        if(check_rightline(sensor) == 1){robot_runcase = RIGHT_HALF_LANE_ONE;break;}
        if(sensorMask(sensor, MASK3_3) == 0x06 ) robot_runcase = NORMAL_TRACE; //0000 0110
        
        break;
    
      case CROSS_LINE_ONE:
        // handle_and_speed(0,-25); // Break --> Check in the hardware for more precise
        robotMotors.setSpeed(-20, -20);
        robot_runcase = CROSS_LINE_TWO;
        cnt1 = 0;
        new_time = millis();
        break;

      case CROSS_LINE_TWO:
          delay(50);
          robot_runcase = TRACE_AFTER_CROSS_LINE;
        break;

      case TRACE_AFTER_CROSS_LINE:
        if(sensorMask(sensor, MASK4_4) == 0xf8 or //11111000
           sensorMask(sensor, MASK4_4) == 0xf0 or //11110000
           sensorMask(sensor, MASK4_4) == 0xfc or //11111100
           sensorMask(sensor, MASK4_4) == 0xfe    //11111110
          ) 
          {
            // left turn determined -> to the left turn clear processing
            handle_and_speed(+25 , 0.5*speed_run); // Max angle for turning right ==> Imidiately turn cause => cannot reach 0x60
            robot_runcase = TURN_LEFT_90;
            break;
          }

        switch(sensorMask(sensor, MASK3_3)){
          case 0x00:
            //Center -> Straight
            handle_and_speed(0, 0.4*speed_run);
            break;

          case 0x04:
          case 0x06:
          case 0x02:
          case 0x07: 
          case 0x03:
            // Divation to the left of the center -> turn right
            handle_and_speed(-5, 0.4*speed_run);
            break;

          case 0x20:
          case 0x40:
          case 0x60:
          case 0xe0:
          case 0xc0:
            // Diviation to the right of the center -> turn left
            handle_and_speed(5, 0.4*speed_run);
            break;

          }

        break;
      
      case TURN_LEFT_90:
        // TURN LEFT 90 -> Wait until stable
          delay(150);
          robot_runcase = END_TURN_LEFT_90;   
          break;
  
      case END_TURN_LEFT_90:
        if(sensorMask(sensor, MASK3_3)== 0x60) //0110 0000 
          {
            robotLed.Off();
            robot_runcase = NORMAL_TRACE;
          }
        break;

      case RIGHT_HALF_LANE_ONE:
        robotMotors.setSpeed(0, 0);
        robot_runcase = RIGHT_HALF_LANE_TWO;
        break;

      case RIGHT_HALF_LANE_TWO:
          robot_runcase = CHANGE_RIGHT_LANE;
        break;

      case CHANGE_RIGHT_LANE:
        // Trace after right half lane
        if(sensorMask(sensor, MASK4_4) == 0x00)
          {
            handle_and_speed(-25, 0.4*speed_run);
            robot_runcase = END_CHANGE_RIGHT_LANE;
            break;
          }

        switch(sensorMask(sensor, MASK3_3)){
          case 0x00:
            // center -> Straight
            handle_and_speed(0, 0.5*speed_run);
            break;
          case 0x04:
          case 0x06:
          case 0x07:
          case 0x03:
            // Diviation to the LEFT of the center -> Turn right
            handle_and_speed(-2, 0.5*speed_run);
            break;

          case 0x20:
          case 0x60:
          case 0xe0:
          case 0xc0:
            // Divaition to the RIGHT of the center -> Turn left
            handle_and_speed(2, 0.4*speed_run);
            break;

          default:
            break;
        }
        break;

      case END_CHANGE_RIGHT_LANE:
        // Right lane end check
        if(sensorMask(sensor, MASK4_4) == 0x3c or // 0011 1100
           sensorMask(sensor, MASK4_4) == 0x3c  or // 1110 0000
           sensorMask(sensor, MASK4_4) == 0x3e   or //00111110
           sensorMask(sensor, MASK4_4) == 0x1e  //00011110
          )

          {
            robotLed.Off();
            robot_runcase = NORMAL_TRACE;
            cnt1 = 0;
          }  
        break;
      default:
        {
          robot_runcase = STOP;
          break;
        }
  }

}

// Masking method
byte lineFollowerRobot::sensorMask (byte sensor,  byte MASK)
{
  sensor = robotLineSensor.readSensor();
  return ( sensor & MASK);
}

// Check cross line
int lineFollowerRobot::check_crossline(byte sensor)
{
  byte b;
  int ret = 0;
  if(sensorMask(sensor, MASK3_3) == 0xe7 or //1110 0111
     sensorMask(sensor, MASK3_3) == 0xc3   //1100 0011
  )
  {
    ret = 1;
  }
  return ret;
}

// Check right line
int lineFollowerRobot::check_rightline(byte sensor)
{
  byte b;
  int ret = 0;
  if(sensorMask(sensor, MASK4_4) == 0x1f or //00011111
    // sensorMask(sensor, MASK4_4) == 0x0f or //00001111
     sensorMask(sensor, MASK4_4) == 0x3f or //00111111
     sensorMask(sensor, MASK4_4) == 0x7f)   //01111111
  {   
    ret = 1;
  }
  return ret;
}

// Check left line
int lineFollowerRobot::check_leftline(byte sensor)
{
  byte b;
  int ret = 0;
  if(sensorMask(sensor, MASK4_4) == 0xf8 or //11111000
     //sensorMask(sensor, MASK4_4) == 0xf0 or //11110000
     sensorMask(sensor, MASK4_4) == 0xfc or //11111100
     sensorMask(sensor, MASK4_4) == 0xfe    //11111110
     )
  {
    ret = 1;
  }
  return ret;
}

// Handle the speed of 2 motors by changing the speed based on the current position corresponding to the road
void lineFollowerRobot::handle_and_speed(int angle, int speed)
{

  int speed1;
  int speed2;
  if (angle > 25) angle = 25;
  if (angle < -25) angle = -25;

  myservo.write(servo_center + angle);

  if(angle < 0) // turn right
  {
    angle = -angle;
    speed2 = speed;
    speed1 = speed*coeffR1[angle]/100;
    robotMotors.setSpeed(speed2,speed1);
  }
  else if (angle == 0)
  {
    robotMotors.setSpeed(speed,speed);
  }
  else if (angle > 0)// turn left
  {
    speed1 = speed;
    speed2 = speed*coeffR1[angle]/100;
    robotMotors.setSpeed(speed2,speed1);
  }
}

/// End of the file///

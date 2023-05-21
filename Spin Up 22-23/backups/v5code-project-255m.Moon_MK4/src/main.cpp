/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Lucas                                                     */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Auton1               limit         A               
// Auton2               limit         B               
// leftFront            motor         13              
// leftBack             motor         2               
// rightFront           motor         12              
// rightBack            motor         1               
// Controller1          controller                    
// Intake               motor_group   11, 20          
// Inertial             inertial      10              
// String               digital_out   G               
// FlyWheel             motor         9               
// Roller               motor         3               
// DiskPush             digital_out   H               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;


// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

// function to calibrate the Inertial sensor which is called in pre auton so during autonomus the PD Loops work 
void calibrateInertial(){
  Inertial.calibrate();

  while (Inertial.isCalibrating()){
    Controller1.Screen.clearLine(3);
    Controller1.Screen.print("Calibrating");
  } 

  Controller1.Screen.clearLine(3);
  Controller1.Screen.print("Done");
  Controller1.rumble("..");
  wait(10, msec);
}

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*---------------------------------------------------------------------------*/

// Callback Boolean Variables

// For Auton Shooting
bool canShoot;
bool canShoot2;

// For Auton Selection
bool switch1=false;
bool switch2=false;

int timetoarm = 2150; // millisecond time to enable firing of the first disk
int timetoarm2 = 4800; // 2nd timing to enable the firing of the second disk

// CallBack Boolean Logic

// 1st disk
void  FireShot(void){
canShoot=true;
}

// 2nd disk
void  Fire2ndShot(void){
canShoot2=true;
}

// Autonomous Selection

// Auton 1 
void AutonButton1(void){
  if (switch1){ 
  switch1= false;
  Brain.Screen.clearLine();
  Brain.Screen.printAt(2, 20, "Close-Side Auton Switch 1 Off");
  } else {
  switch1= true;
  Brain.Screen.clearLine();
  Brain.Screen.printAt(2, 20, "Close-Side Auton Switch 1 On");
  }  
}

// Auton 2
void AutonButton2(void){
  if (switch2){ 
  switch2= false;
  Brain.Screen.clearLine();
  Brain.Screen.printAt(2, 40, "Far-Side Auton Switch 2 Off");
  } else {
  switch2= true;
  Brain.Screen.clearLine();
  Brain.Screen.printAt(2, 40, "Far-Side Auton Switch 2 On");
  } 
  
}


void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  calibrateInertial();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...

 rightBack.setPosition(0,degrees);  
 leftBack.setPosition(0,degrees);
 rightFront.setPosition(0,degrees);
 leftFront.setPosition(0,degrees);
}

// The Following is about PD loops. The form of the loop was developed by
// Conner from Team 1814D: His tutorial video link https://youtu.be/_Itn-0d340g

/////////////////////////
// Lateral PD Function //
/////////////////////////

// Tuned Variables - the kP and kD are fractional for precision. These terms dictate if the robot goes on the right direction (kP) and if the speed is correct (kD)
double kP = 0.38;
double kD = 0.61;


// Stated Variables

int error; // The error term is calculated by subtracting where you want to be from where you are (average)
int prevError; // Previous error (prevError) is the last error term when it cycles
int derivative; // The Derivative term is the future term that negates overshoot
int targetValue; // The target destination :: ~425/ tile

bool resetSens = false; // Rests the motor position to 0 when turned true
bool latDriveON = true; // Determines if the while loop can run


// Delcaration of the function
int latDrive(){

  // Checks if the boolean variable is true and if so it runs the following statements
  while(latDriveON){
    
    // If logic that check if the resetSens boolean is true and if so it sets it to false and sets the 
    // position of the wheel to 0 for when starting a new line of movement
    if(resetSens){
      resetSens = false;
      rightBack.setPosition(0,degrees);
      leftBack.setPosition(0,degrees);
      rightFront.setPosition(0,degrees);
      leftFront.setPosition(0,degrees);
    }

    // Gets the position of where the bot is in degrees
    int leftBackPosition = leftBack.position(degrees);
    int rightBackPosition = rightBack.position(degrees);
    int leftPosition = leftFront.position(degrees);
    int rightPosition = rightFront.position(degrees);

    int avg = (leftBackPosition + rightBackPosition + leftPosition + rightPosition)/4; // Calculates the average of the motor positions

    error = targetValue - avg; // Error term equation to find the difference between where you want to be from where you are

    derivative = error - prevError; // Derivative term equation to get the differenve between the current and previous error to check that you haven't gone past the target 

    double latMotorPower = error * kP + derivative * kD; // The total motor power equation to control the speed

    // application of the speed to the motors
    leftBack.spin(forward, latMotorPower, pct);
    leftFront.spin(forward, latMotorPower, pct);
    rightBack.spin(forward, latMotorPower, pct);
    rightFront.spin(forward, latMotorPower, pct);

    prevError = error; // updating the error term to the previous error
    vex::task::sleep(20); // Cycle of the while loop in milliseconds
  }

  return 1; // because the function is int we have to return a 1 to have the controller work
}

//////////////////////
// Turn PD Function //
//////////////////////

// Tuned Variables - the kP and kD are fractional for precision. These terms dictate if the robot goes on the right direction (kP) and if the speed is correct (kD)
double turnkP = 0.5;
double turnkD = 0.6;

int turnError; // DesiredValue - SensorValue : Position
int turnPrevError; // Position 20 miliseconds ago
int turnDerivative; // error - prevError : Speed
double targetHeading; // The target destination

bool rotDriveON = true; // Determines if the while loop can run

// Delcaration of the function
int rotPD(){

  while (rotDriveON){

    turnError = targetHeading - Inertial.heading(degrees); // Error term equation to find the difference between where you want to be from where you are : Position

    turnDerivative = turnError - turnPrevError; // Derivative term equation to get the differenve between the current and previous error 
                                                // to check that the robot is going the correct speed to not miss the target value

    double turnMotorPower = turnError * turnkP + turnDerivative * turnkD; // The total motor power equation to control the speed

    // application of the speed to the motors
    leftFront.spin(forward, turnMotorPower, pct);
    leftBack.spin(forward, turnMotorPower, pct);
    rightBack.spin(reverse, turnMotorPower, pct); 
    rightFront.spin(reverse, turnMotorPower, pct);

    turnPrevError = turnError; // updating the error term to the previous error
    vex::task::sleep(20); // Cycle of the while loop in milliseconds
  }

  return 1; // because the function is int we have to return a 1 to have the controller work
}

/*---------------------------------------------------------------------------*/
/*                              Autonomous Task                              */
/*---------------------------------------------------------------------------*/

void autonomous(void) {

  //uses the auton number selected to run the auton, and checks if you confirmed


  if (switch1 && switch2){
    // Run Third Auton Program
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(2, 60, "Running Skills Auton...");

  }
  else if  (switch1){
    // Run First Auton Program
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(2, 60, "Running Close-Side Auton...");
    FlyWheel.spin(fwd, 465, rpm);
    DiskPush.set(true);
    wait(1.5,sec);   

    for(int i = 0; i < 1;){
      if (canShoot){
        canShoot = false;
        DiskPush.set(false);
        i++;
        wait(.5, sec);
        DiskPush.set(true);
      } 
    }

    wait(.5,sec);
    DiskPush.set(false);
    wait(1, sec);
    FlyWheel.stop(coast);
    latDriveON = true;
    vex::task DrivePD(latDrive);
    targetValue = -100;
    Roller.spinFor(fwd, .5, sec, 200, rpm);
    targetValue = 50;
     
  }
    else if (switch2) {
    // Run Second Auton Program
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(2, 60, "Running Far-Side Auton...");
    FlyWheel.spin(fwd, 430, rpm);
    //auto starttime = std::chrono::high_resolution_clock::now();

    resetSens = true;
    // demo of both lateral and rotational PD Loops working together
    DiskPush.set(true);
    rotDriveON=true;
    vex::task turnPD(rotPD);
    targetHeading = 30; 
    vex::task::sleep(1000);
    latDriveON = true;
    vex::task DrivePD(latDrive);
    targetValue = 425;
    vex::task::sleep(1000);
    wait(1.5,sec);    

    for(int i = 0; i < 1;){
      if (canShoot){
        canShoot = false;
        DiskPush.set(false);
        i++;
        wait(.5, sec);
        DiskPush.set(true);
      } 
    }

    wait(.5,sec);
    DiskPush.set(false);
    wait(1, sec);
    FlyWheel.stop(coast);
    rotDriveON = false;
    latDriveON = false;
    wait(.5, sec);
    leftBack.spinFor(reverse, 170, deg,false);
    leftFront.spinFor(reverse, 170, deg,false);
    rightFront.spinFor(forward, 190, deg,false);
    rightBack.spinFor(forward, 190, deg,true);
    wait(2, sec);
    leftBack.spinFor(reverse, 720, deg, 200, rpm, false);
    leftFront.spinFor(reverse, 720, deg, 200, rpm, false);
    rightFront.spinFor(reverse, 720, deg, 200, rpm, false);
    rightBack.spinFor(reverse, 720, deg, 200, rpm, false);
    wait(2, sec);
    Roller.spinFor(fwd, 190, degrees, 100, rpm);
    wait(1, sec);
    leftBack.spinFor(forward, 240, deg, 125, rpm, false);
    leftFront.spinFor(forward, 240, deg, 125, rpm, false);
    rightFront.spinFor(forward, 240, deg, 125, rpm, false);
    rightBack.spinFor(forward, 240, deg, 125, rpm, true);
  }
    
}

/*---------------------------------------------------------------------------*/
/*                              User Control Task                            */
/*---------------------------------------------------------------------------*/

int endGameFailSafe = 0; // set index 

// This function is responsible for checking if the end game string can be launched
// it makes sure that the string pistons will only fire when button x is clicked twice
void FailSafe() {
  endGameFailSafe++; // when called by a button press, the index is incremented by one

  // parameter to check if the button has been pressed twice
  if (endGameFailSafe == 2) {
    String.set(true);    
  } else{
    String.set(false);
  }
}


void usercontrol(void) {
  // User control code here, inside the loop

  // The PD booleans are set to false because we don't want the bot to correct itself while the diver in driving 
  rotDriveON = false;
  latDriveON = false;

  bool toggleEnabled = false; // two-choice toggle, so we use bool
  bool buttonPressed = false; // logic variable

  while (1) {

    // A constant setting of velocity for the motors
    FlyWheel.setVelocity(390, rpm);
    Intake.setVelocity(200, rpm); 
    Roller.setVelocity(100, rpm);
    leftBack.setVelocity(225, rpm);
    leftFront.setVelocity(225, rpm);
    rightBack.setVelocity(225, rpm);
    rightFront.setVelocity(225, rpm);


    bool buttonA = Controller1.ButtonA.pressing(); // boolean to get if the button is pressed (true) or it isn't pressed (false)

// These lines set the controllers analog sticks to the left motors nad right motors using the tank drive layout
//This is Left Side AXES 3
    leftFront.spin(vex::directionType::fwd,Controller1.Axis3.position(vex::percentUnits::pct),vex::percentUnits::pct);
    leftBack.spin(vex::directionType::fwd,Controller1.Axis3.position(vex::percentUnits::pct),vex::percentUnits::pct);
    //This is Right Side AXES 2
    rightBack.spin(vex::directionType::fwd,Controller1.Axis2.position(vex::percentUnits::pct),vex::percentUnits::pct);
    rightFront.spin(vex::directionType::fwd,Controller1.Axis2.position(vex::percentUnits::pct),vex::percentUnits::pct);


////////////////////////////////////
// Controller's button assignment //
////////////////////////////////////

  /* conditional statements for a motor toggle output. The first parts are the booleans that where addressed eariler, we put these true or false variabes into the first conditional 
  to figure out if the button was being pressed (the parameter). If it was true then it will assign the buttonPressed value to true  and toggledEnabled to the opposite */

    // Toggle Logic
    if (buttonA && !buttonPressed){
      buttonPressed = true; 
      toggleEnabled = !toggleEnabled;
    }
    else if (!buttonA) buttonPressed = false;
    /* from the logic above we take the output of if the toggledEnabled is true or false and then we use it to spin the fly wheel motor */

    // Code For toggle Enabled or Disabled
    if(toggleEnabled){
      FlyWheel.spin(fwd); // spin the motor
    } else{
     FlyWheel.stop(coast); // stops the motor but keeps the motion die off
    }
    
    /*
     The following are statements that run under conditions/ parameters that check if the button is actively being pressed
     if the case is true then the bot will perform the action/ statement
     if the case is not true, hence false, they will perform the if else statement which is a second option that checks for another input and if that input is true 
     it will work as the same as the if portion if all if/ else parameters are false then it will run the else portion which in majority of the cases will tell 
     the motor to stop running by coast. This will progressively stop the motor: Coast basicly lets the motor carry out and finish the current motion so the motors do not overheat 
    */

    // Intake Control
    if(Controller1.ButtonL2.pressing()){
      Intake.spin(reverse);
    }
    else if (Controller1.ButtonL1.pressing()) {
      Intake.spin(forward);
    }
    else {
      Intake.stop(coast); 
    }

    // Roller Control
    if(Controller1.ButtonR1.pressing()){
      Roller.spin(reverse);
    }
    else {
      Roller.stop(coast);
    }

    // Disk Indexer Control
    if (Controller1.ButtonR2.pressing()){
      DiskPush.set(false);
    }
    else {
      DiskPush.set(true);
    }


    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}



//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.

  // Makes the booleans false to not have a miss fire
  canShoot = false;
  canShoot2=false;

  // When the timer reaches the set millisecond time in the timetoarm variables it will callback to the fireshot functions
  vex::timer::event(FireShot,timetoarm);
  vex::timer::event(Fire2ndShot,timetoarm2);

  // When either of the limit switches are pressed then it calls back to the AutonButton functions
  Auton1.pressed(AutonButton1);
  Auton2.pressed(AutonButton2);

  // When button x is pressed on the controller it callsback to the FailSafe function to reduce the chance of miss firing 
  Controller1.ButtonX.pressed(FailSafe);

  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  
  // Run the pre-autonomous function.
  pre_auton();


  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}

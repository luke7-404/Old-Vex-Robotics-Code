/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Auton1               limit         A               
// Auton2               limit         B               
// Auton3               limit         C               
// Auton4               limit         D               
// leftFront            motor         13              
// leftBack             motor         2               
// rightFront           motor         12              
// rightBack            motor         1               
// Controller1          controller                    
// Intake               motor_group   11, 20          
// Inertial             inertial      10              
// DiskPush             digital_out   E               
// StringP1             digital_out   F               
// StringP2             digital_out   G               
// FlyWheel             motor         9               
// Roller               motor         3               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

// function to calibrate the Inertial sensor which is called in pre auton so during autonomus it works 
void calibrateInertial(){
  Inertial.calibrate();

  while (Inertial.isCalibrating()){
    Controller1.Screen.clearScreen();
    Controller1.Screen.print("Calibrating");
  } 

  Controller1.Screen.clearScreen();
  Controller1.Screen.print("Done");
  Controller1.rumble("...");
  wait(10, msec);
}
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  calibrateInertial();  

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...

  leftBack.setPosition(0, degrees);
  rightBack.setPosition(0, degrees);
  leftFront.setPosition(0, degrees);
  rightFront.setPosition(0, degrees);
}

/////////////////////////
// Lateral PD Function //
/////////////////////////

void resetDriveSensors (){
  leftBack.setPosition(0, degrees);
  rightBack.setPosition(0, degrees);
  leftFront.setPosition(0, degrees);
  rightFront.setPosition(0, degrees);
}

bool latDriveOn = false;

void LatDrive(double targetDistance){

  double Kp = 0.5;

  while(latDriveOn){
    int bakLefPos = leftBack.position(degrees);// gets the position of the left back motor to be used for an average 
    int bakRigtPos = rightBack.position(degrees);// gets the position of the right back motor to be used for an average
    int frntLefPos = leftFront.position(degrees);// gets the position of the left front motor to be used for an average
    int frntRigtPos = rightFront.position(degrees);// gets the position of the right front motor to be used for an average

  
    int avgPos = (bakLefPos + bakRigtPos + frntLefPos + frntRigtPos)/4;
  
    double error = targetDistance - avgPos;

    double latMotorSpeed = error * Kp;

    if (targetDistance < 0){
      leftFront.spin(reverse, latMotorSpeed, pct);
      leftBack.spin(reverse, latMotorSpeed, pct);
      rightFront.spin(reverse, latMotorSpeed, pct);
      rightFront.spin(reverse, latMotorSpeed, pct);
    } else if (targetDistance > 0) {
      leftFront.spin(forward, latMotorSpeed, pct);
      leftBack.spin(forward, latMotorSpeed, pct);
      rightFront.spin(forward, latMotorSpeed, pct);
      rightFront.spin(forward, latMotorSpeed, pct);  
    }
  }
  leftFront.stop(brake);
  leftBack.stop(brake);
  rightFront.stop(brake);
  rightFront.stop(brake);
}

//////////////////////
// Turn PD Function //
//////////////////////

void RotDrive (double targetHeading){

  double turnError = targetHeading - Inertial.heading();
  double TprevError = turnError;
  double turnDerivative = turnError - TprevError; 

  double TKp = 0.5;
  double TKd = 0;

  double rotMotorSpeed;

  while (fabs(turnError) > 4){
    
    rotMotorSpeed = TKp * turnError + TKd * turnDerivative;

    leftFront.spin(fwd, rotMotorSpeed, pct);
    leftBack.spin(fwd, rotMotorSpeed, pct);
    rightFront.spin(reverse, rotMotorSpeed, pct);
    rightFront.spin(reverse, rotMotorSpeed, pct);

    turnError = targetHeading - Inertial.heading();

    vex::task::sleep(20);
    TprevError = turnError;
    turnDerivative = turnError - TprevError;
  }
  leftFront.stop(brake);
  leftBack.stop(brake);
  rightFront.stop(brake);
  rightFront.stop(brake);
}

/*---------------------------------------------------------------------------*/
/*                              Autonomous Task                              */
/*---------------------------------------------------------------------------*/

void autonomous(void) {

  //uses the auton number selected to run the auton, and checks if you confirmed


  if (Auton1.pressing() == 1){
    // Run First Auton Code
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(2, 40, "Runing Red Auton 1...");
    FlyWheel.spin(fwd, 480, rpm);
    leftBack.spinFor(-30, degrees, 175, rpm, false);
    leftFront.spinFor(-30, degrees, 175, rpm, false);
    rightBack.spinFor(10, degrees, 175, rpm, false);
    rightFront.spinFor(10, degrees, 175, rpm, false);
    Roller.spinFor(95, degrees, 50, rpm, true);
    wait(1, sec);
    DiskPush.set(true);
    wait(1,sec);
    DiskPush.set(false);
    wait(2,sec);
    DiskPush.set(true);
    wait(1,sec);
    DiskPush.set(false);

    //RotDrive(270);
  }
  else if (Auton2.pressing() == 1) {
    // Run Second Auton Code
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(2, 40, "Runing Red Auton 2...");
  }
    else if (Auton3.pressing() == 1) {
    // Run Third Auton Code
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(2, 40, "Runing Blue Auton 3...");
  }
    else if (Auton4.pressing() == 1) {
    // Run Forth Auton Code
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(2, 40, "Runing Blue Auton 4...");
  }
  else {
    // Run No Auton
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(2, 40, "No Auton Selected!!!");
  }
}



/*---------------------------------------------------------------------------*/
/*                              User Control Task                            */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop

  latDriveOn = false;

  bool toggleEnabled = false; // two-choice toggle, so we use bool
  bool buttonPressed = false; // logic variable



  while (1) {

    // A constant setting of velocity for the motors
    Intake.setVelocity(190, rpm); 
    Roller.setVelocity(50, rpm);

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
      FlyWheel.spin(fwd, 400, rpm);
    }
    else{
     FlyWheel.stop(coast);
    }

    /* conditional if/ if else/ else statement for the motor group to intake the disks for the fly wheel.
     When L2 is pushed the motors spin to take the disks in, when L1 is pressed it reverses the motors for 
     if there is a disk jam, and lastly the else part is to make sure if both of those actions don't 
     happen then the motors will finish rolling so that they don't heat up */
    if(Controller1.ButtonL2.pressing()){
      Intake.spin(reverse);
    }
    else if (Controller1.ButtonL1.pressing()) {
      Intake.spin(forward);
    }
    else {
      Intake.stop(coast); 
    }

    /* conditional if/ else statements. 1 for the pistion to push the disks into the fly wheel.
     When r2 is pushed the pistion pushes the disk in the fly wheel, when r1 is pressed it retracts for the
     next disk, and lastly the else part is to make sure if both of those actions don't happen then 
     nothing will. 2 for spinning the roller wheels on the back of the robot  */
    if (Controller1.ButtonR2.pressing()){
      DiskPush.set(false);
    }
    else {
      DiskPush.set(true);
    }

    if(Controller1.ButtonR1.pressing()){
      Roller.spin(reverse);
    }
    else {
      Roller.stop(coast);
    }

    /* conditional if/ else statement for when the final string pistions are fired. it 
    makes sure that the string pistons will only fire when x button is clicked but nothing else */
    if (Controller1.ButtonX.pressing()){
      StringP1.set(false);
      StringP2.set(false);
    }
    else {
      StringP1.set(true);
      StringP2.set(true);
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
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  
  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}

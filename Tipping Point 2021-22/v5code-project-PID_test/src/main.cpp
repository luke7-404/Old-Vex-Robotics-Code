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
// Controller1          controller                    
// Controller2          controller                    
// FrontClaw            digital_out   A               
// Arms                 motor_group   11, 20          
// Backpack             motor_group   15, 16          
// LeftSensor           encoder       C, D            
// RightSensor          encoder       E, F            
// LF                   motor         18              
// LB                   motor         19              
// RF                   motor         12              
// RB                   motor         13              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

// Drive PID Functions

// Positional Tuners
double latKp = 0;
double rotKp = 0;

//Integral Tuners
double latKi = 0;
double rotKi = 0;

//Derivative Turners
double latKd = 0;
double rotKd = 0;

//Motor speed
double latSpeed;
double rotSpeed;

//Potential
double latError;
double rotError;

//Previous Potential
double latPrevError = 0;
double rotPrevError = 0;

//Integral
double latIntegral = 0;
double rotIntegral = 0;

//Derivative
double latDerivative;
double rotDerivative;

//Manual Toggle
bool LateralPID_ON = false;
bool RotationalPID_ON = false;

//Reset Rotational Sensors
void resetSensors(){
LeftSensor.setPosition(0, degrees); 
RightSensor.setPosition(0, degrees);
}

//Lateral PID
void LateralPID(int distance_cm){
  resetSensors();
  while (LateralPID_ON){

    //Get Left and Right Values in cm
    double LeftValue = (LeftSensor.position(degrees)/360) * 8.255;
    double RightValue = (RightSensor.position(degrees)/360) * 8.255;

    //Get Error Values
    latError = distance_cm - ((LeftValue - RightValue)/2);
    rotError = LeftValue - RightValue;

    //Get Integtal Value with Boundaries
    if ((sqrt(latError * latError)) < 2 && latError != 0){
      latIntegral = latIntegral + latError;
    }
    else {
      latIntegral = 0;
    }

    //Get Integtal Value with Boundaries
    if ((sqrt(rotError * rotError)) < 2 && rotError != 0){
      rotIntegral = rotIntegral + rotError;
    }
    else {
      rotIntegral = 0;
    }

    //Get Drivetrain Value
    latDerivative = latError - latPrevError;
    rotDerivative = rotError - rotPrevError;

    //Update Previous Error
    latPrevError = latError;
    rotPrevError = rotError;

    //Set Motor Speeds
    latSpeed = (latError * latKp) + (latIntegral * latKi) + (latDerivative * latKd);
    rotSpeed = (rotError * rotKp) + (rotIntegral * rotKi) + (rotDerivative * rotKd);

    //Spin Motor
    LF.spin(forward, (latSpeed - rotSpeed), voltageUnits::volt);
    LB.spin(forward, (latSpeed - rotSpeed), voltageUnits::volt);
    RF.spin(forward, (latSpeed + rotSpeed), voltageUnits::volt);
    RB.spin(forward, (latSpeed + rotSpeed), voltageUnits::volt);

    //Provide Exist Condition
    if (latError < 1 && latError < -1){
      LF.stop();
      LB.stop();
      RF.stop();
      RB.stop();
      break;
    }

    //wait 20 msec
    vex::task::sleep(20);
  }
}

void Rotational_PID (int bot_angle){
  while (RotationalPID_ON){

    //Get Sensors Values
    double LeftValue = LeftSensor.position(degrees);
    double RightValue = RightSensor.position(degrees);

    //Establish Rotational Error
    rotError = bot_angle - (LeftValue - RightValue);

    //Get Rotational Integral with Boundaries
    if ((sqrt(rotError * rotError)) < 60 && rotError != 0){
      rotIntegral = rotIntegral + rotError;
    }
    else{
      rotIntegral = 0;
    }

    //Get Rotational Derivative
    rotDerivative = rotError - rotPrevError;

    //Update Rotational Previous Error
    rotPrevError = rotError;

    //Set Rotational Motor Speed
    rotSpeed = (rotError * rotKp) + (rotIntegral * rotKi) + (rotDerivative * rotKd);

    //Spin Motors
    LF.spin(reverse, (rotSpeed), voltageUnits::volt);
    LB.spin(reverse, (rotSpeed), voltageUnits::volt);
    RF.spin(forward, (rotSpeed), voltageUnits::volt);
    RB.spin(forward, (rotSpeed), voltageUnits::volt);

    //Provide Exist Condition
    if (rotError < 1 && rotError > -1){
      LF.stop();
      LB.stop();
      RF.stop();
      RB.stop();
      break;
    }

    //Wait 20 msec
    vex::task::sleep(20);

  }
}







void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

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

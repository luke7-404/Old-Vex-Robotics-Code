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
// Drivetrain           drivetrain    1, 2, 4, 5      
// LeftArm              motor         20              
// RightArm             motor         11              
// Intake               motor         15              
// Claw                 motor         3               
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

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
Drivetrain.driveFor(forward, 12, inches);
Drivetrain.turnFor(left, 90, degrees);  
Drivetrain.driveFor(forward, 18, inches);
Drivetrain.driveFor(reverse, 4 inches);
Drivetrain.stop();
LeftArm.spinFor(forward, 90, degrees); 
RightArm.spinFor(forward, 90, degrees);  
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
    //This is for the controll, make sure the Cotroller is added
    //Example //motor(PORT#).spin(vex::directionType::fwd,Controller1.Axis3.position(vex::percentUnits::pct),vex::percentUnits::pct);

   //This is Left Side AXES 3 and 4
    motor(PORT1).spin(vex::directionType::fwd,Controller1.Axis3.position(vex::percentUnits::pct),vex::percentUnits::pct);
    motor(PORT2).spin(vex::directionType::fwd,Controller1.Axis3.position(vex::percentUnits::pct),vex::percentUnits::pct);

    //This is Right Side AXES 1 and 2
    motor(PORT4).spin(vex::directionType::fwd,Controller1.Axis2.position(vex::percentUnits::pct),vex::percentUnits::pct);
    motor(PORT5).spin(vex::directionType::fwd,Controller1.Axis2.position(vex::percentUnits::pct),vex::percentUnits::pct);
    

    //Addition of Controller, Doing this you can have more then one motor to a single controller. Using name (buttons) 

     if(Controller2.ButtonL1.pressing())
    {
      motor(LeftArm).spin(vex::directionType::fwd,30,vex::percentUnits::pct);
      motor(RightArm).spin(vex::directionType::fwd,30,vex::percentUnits::pct);
    }
    else if(Controller2.ButtonL2.pressing())
    {
      motor(LeftArm).spin(vex::directionType::fwd,-30,vex::percentUnits::pct);
      motor(RightArm).spin(vex::directionType::fwd,-30,vex::percentUnits::pct);
    }
    else
    {
     motor(LeftArm).stop(vex::brakeType::hold);
      motor(RightArm).stop(vex::brakeType::hold);
    }    
 
    if(Controller2.ButtonUp.pressing())
    {
      motor(Intake).spin(vex::directionType::fwd,30,vex::percentUnits::pct);
    }
    else if(Controller2.ButtonDown.pressing())
    {
      motor(Intake).spin(vex::directionType::fwd,-30,vex::percentUnits::pct);
    }
    else
    {
     motor(Intake).stop(vex::brakeType::hold);
    }    

if(Controller2.ButtonR1.pressing())
    {
      motor(Claw).spin(vex::directionType::fwd,30,vex::percentUnits::pct);
    }
    else if(Controller2.ButtonR2.pressing())
    {
      motor(Claw).spin(vex::directionType::fwd,-30,vex::percentUnits::pct);
    }
    else
    {
     motor(Claw).stop(vex::brakeType::hold);
    } 

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

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
// LeftArm              motor         10              
// RightArm             motor         1               
// Tiller               motor         16              
// Claw                 motor         5               
// ClawPiston           digital_out   A               
// Drivetrain           drivetrain    20, 19, 11, 12  
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
ClawPiston.set(false);
Drivetrain.setDriveVelocity(200, vex::percentUnits::pct);
Drivetrain.setTurnVelocity(100, vex::percentUnits::pct);
Drivetrain.turnFor(right, 14.5, degrees);
Drivetrain.driveFor(forward, 70, inches);
ClawPiston.set(true);
wait(1, sec);
Drivetrain.driveFor(reverse, 60, inches);
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
    
  // bool for the claw toggle
  bool toggleUp = false;
  bool buttonUpPressed = false;
  
  while (1) {

     // Temp display
    Brain.Screen.printAt(0, 20 ,"Claw Motor Temp %f " , Claw.temperature(percentUnits::pct));
    Brain.Screen.printAt(2, 40 ,"Tiller Motor Temp %f " , Tiller.temperature(percentUnits::pct));
    Brain.Screen.printAt(4, 60 ,"LeftArm Motor Temp %f " , LeftArm.temperature(percentUnits::pct));
    Brain.Screen.printAt(6, 80 ,"RightArm Motor Temp %f " , RightArm.temperature(percentUnits::pct));
    Brain.Screen.printAt(8, 100 ,"DriveTrain Left-Side %f " , motor(PORT20).temperature(percentUnits::pct));
    Brain.Screen.printAt(10, 120 ,"DriveTrain Left-Side %f " , motor(PORT19).temperature(percentUnits::pct));
    Brain.Screen.printAt(12, 140 ,"DriveTrain Right-Side %f " , motor(PORT11).temperature(percentUnits::pct));
    Brain.Screen.printAt(14, 160 ,"DriveTrain Right-Side %f " , motor(PORT12).temperature(percentUnits::pct));
   
   // bool for claw
   bool buttonUp = Controller2.ButtonUp.pressing();

    //DiveTrain Velocity
    motor(PORT20).setVelocity(100,vex::percentUnits::pct);
    motor(PORT11).setVelocity(100,vex::percentUnits::pct);

   //This is Left Side AXES 3 and 4
    motor(PORT20).spin(vex::directionType::fwd,Controller1.Axis3.position(vex::percentUnits::pct),vex::percentUnits::pct);
    motor(PORT19).spin(vex::directionType::fwd,Controller1.Axis3.position(vex::percentUnits::pct),vex::percentUnits::pct);
    //This is Right Side AXES 1 and 2
    motor(PORT11).spin(vex::directionType::fwd,Controller1.Axis2.position(vex::percentUnits::pct),vex::percentUnits::pct);
    motor(PORT12).spin(vex::directionType::fwd,Controller1.Axis2.position(vex::percentUnits::pct),vex::percentUnits::pct);

    // Lift Code
     if(Controller2.ButtonR1.pressing())
    {
      motor(LeftArm).spin(vex::directionType::fwd,70,vex::percentUnits::pct);
      motor(RightArm).spin(vex::directionType::fwd,70,vex::percentUnits::pct);
    }
    else if(Controller2.ButtonR2.pressing())
    {
      motor(LeftArm).spin(vex::directionType::rev,70,vex::percentUnits::pct);
      motor(RightArm).spin(vex::directionType::rev,70,vex::percentUnits::pct);
    }
    else
    {
     motor(LeftArm).stop(vex::brakeType::hold);
      motor(RightArm).stop(vex::brakeType::hold);
    }    

    // Tiller Code
    if(Controller2.ButtonL1.pressing())
    {
      motor(Tiller).spin(vex::directionType::fwd,70,vex::percentUnits::pct);
    }
    else if(Controller2.ButtonL2.pressing())
    {
      motor(Tiller).spin(vex::directionType::rev,70,vex::percentUnits::pct);
    }
    else
    {
     motor(Tiller).stop(vex::brakeType::hold);
    } 


    // Claw toggle code
    if (buttonUp && !buttonUpPressed){
      buttonUpPressed = true;
      toggleUp = !toggleUp;
      Brain.Screen.printAt(16, 180 ,"Claw Triggred");
    }
    else if (!buttonUp)
    buttonUpPressed = false;
    if(toggleUp){
      ClawPiston.set(true);
    }
    else {
      ClawPiston.set(false);
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

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
// Drivetrain           drivetrain    20, 11          
// LeftArm              motor         10              
// RightArm             motor         1               
// Tiller               motor         16              
// Claw                 motor         5               
// RightWing            motor         15              
// LeftWing             motor         17              
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
motor(Claw).spin(vex::directionType::fwd,70,vex::percentUnits::pct);
Drivetrain.driveFor(forward, 45.5, inches);
motor(Tiller).spin(vex::directionType::rev,70,vex::percentUnits::pct);
motor(Claw).spin(vex::directionType::rev,70,vex::percentUnits::pct);
wait(3, sec);
motor(LeftArm).spin(vex::directionType::fwd,70,vex::percentUnits::pct);
motor(RightArm).spin(vex::directionType::fwd,70,vex::percentUnits::pct);
wait(2, sec);
Drivetrain.driveFor(reverse, 15.5, inches);
Drivetrain.turnFor(left, 106, degrees);  
Drivetrain.driveFor(reverse, 23.5, inches);
motor(Tiller).spin(vex::directionType::fwd,70,vex::percentUnits::pct);
wait(3, sec);
Drivetrain.driveFor(forward, 4, inches); 
Drivetrain.stop(); 
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
  
  //bool for leftwing toggle
  bool toggleY = false;
  bool buttonYPressed = false;

  //bool for rightwing toggle
  bool toggleA = false;
  bool buttonAPressed = false;
  
  while (1) {
   
     // Temp display
    Brain.Screen.printAt(0, 20 ,"Claw Motor Temp %f " , Claw.temperature(percentUnits::pct));
    Brain.Screen.printAt(2, 40 ,"Tiller Motor Temp %f " , Tiller.temperature(percentUnits::pct));
    Brain.Screen.printAt(4, 60 ,"LeftArm Motor Temp %f " , LeftArm.temperature(percentUnits::pct));
    Brain.Screen.printAt(6, 80 ,"RightArm Motor Temp %f " , RightArm.temperature(percentUnits::pct));
    Brain.Screen.printAt(8, 100 ,"LeftWing Motor Temp %f " , LeftWing.temperature(percentUnits::pct));
    Brain.Screen.printAt(10, 120 ,"RighttWing Motor Temp %f " , RightWing.temperature(percentUnits::pct));


   // bool for claw
   bool buttonUp = Controller2.ButtonUp.pressing();
   
   // bool for leftwing
   bool buttonY = Controller2.ButtonY.pressing();
   
   // bool for rightwing
   bool buttonA = Controller2.ButtonA.pressing();


    //DriveTrain
   //This is Left Side AXES 3 and 4
    motor(PORT20).spin(vex::directionType::fwd,Controller1.Axis3.position(vex::percentUnits::pct),vex::percentUnits::pct);

    //This is Right Side AXES 1 and 2
    motor(PORT11).spin(vex::directionType::fwd,Controller1.Axis2.position(vex::percentUnits::pct),vex::percentUnits::pct);
    

    // Lift Code
     if(Controller2.ButtonL1.pressing())
    {
      motor(LeftArm).spin(vex::directionType::fwd,70,vex::percentUnits::pct);
      motor(RightArm).spin(vex::directionType::fwd,70,vex::percentUnits::pct);
    }
    else if(Controller2.ButtonL2.pressing())
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
    if(Controller2.ButtonR1.pressing())
    {
      motor(Tiller).spin(vex::directionType::fwd,70,vex::percentUnits::pct);
    }
    else if(Controller2.ButtonR2.pressing())
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
      Brain.Screen.printAt(12, 140 ,"Claw Triggred");
    }
    else if (!buttonUp)
    buttonUpPressed = false;
    if(toggleUp){
      motor(Claw).spin(vex::directionType::fwd,70,vex::percentUnits::pct);
    }
    else {
      motor(Claw).spin(vex::directionType::rev,70,vex::percentUnits::pct);
    }

    // LeftWing Toggle Code
     if (buttonY && !buttonYPressed){
      buttonYPressed = true;
      toggleY = !toggleY;
      Brain.Screen.printAt(14, 160 ,"LeftWing Triggred");
    }
    else if (!buttonY)
    buttonYPressed = false;
    if(toggleY){
      motor(LeftWing).spin(vex::directionType::fwd,70,vex::percentUnits::pct);
    }
    else {
      motor(LeftWing).spin(vex::directionType::rev,70,vex::percentUnits::pct);
    }

    // RightWing Toggle Code
     if (buttonA && !buttonAPressed){
      buttonAPressed = true;
      toggleA = !toggleA;
      Brain.Screen.printAt(16, 180,"RightWing Triggred");
    }
    else if (!buttonA)
    buttonAPressed = false;
    if(toggleA){
      motor(RightWing).spin(vex::directionType::fwd,70,vex::percentUnits::pct);
    }
    else {
      motor(RightWing).spin(vex::directionType::rev,70,vex::percentUnits::pct);
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

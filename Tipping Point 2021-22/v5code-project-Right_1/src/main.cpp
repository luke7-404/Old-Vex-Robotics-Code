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
// lift                 motor_group   11, 20          
// BackClaw             digital_out   B               
// GreenLED             led           G               
// RedLED               led           H               
// lf                   motor         19              
// lm                   motor         18              
// lb                   motor         17              
// rf                   motor         12              
// rm                   motor         13              
// rb                   motor         14              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices her

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void autonomous(void) {
    lf.setVelocity(350,vex::percentUnits::pct);
    lm.setVelocity(350,vex::percentUnits::pct);
    lb.setVelocity(350,vex::percentUnits::pct);
    rf.setVelocity(350,vex::percentUnits::pct);
    rm.setVelocity(350,vex::percentUnits::pct);
    rb.setVelocity(350,vex::percentUnits::pct);
  //Drive Forward
  lf.spinFor(forward, 1565, deg, false);
  lm.spinFor(forward, 1565, deg, false);
  lb.spinFor(forward, 1565, deg, false);
  rf.spinFor(reverse, 1565, deg, false);
  rm.spinFor(reverse, 1565, deg, false);
  rb.spinFor(reverse, 1565, deg, true);
  FrontClaw.set(true);
  //Come back
  lf.spinFor(reverse, 1000, deg, false);
  lm.spinFor(reverse, 1000, deg, false);
  lb.spinFor(reverse, 1000, deg, false);
  rf.spinFor(forward, 1000, deg, false);
  rm.spinFor(forward, 1000, deg, false);
  rb.spinFor(forward, 1000, deg, true);
  BackClaw.set(true);
  BackClaw.set(false);
  BackClaw.set(true);
  lift.spin(fwd, 70, pct);
  //rotation
  lf.spinFor(reverse, 430, deg, false);
  lm.spinFor(reverse, 430, deg, false);
  lb.spinFor(reverse, 430, deg, false);
  rf.spinFor(reverse, 430, deg, false);
  rm.spinFor(reverse, 430, deg, false);
  rb.spinFor(reverse, 430, deg, true);
  BackClaw.set(false);
  wait(1.5, sec);
  //Back to Blue
  lf.spinFor(reverse, 400, deg, false);
  lm.spinFor(reverse, 400, deg, false);
  lb.spinFor(reverse, 400, deg, false);
  rf.spinFor(forward, 400, deg, false);
  rm.spinFor(forward, 400, deg, false);
  rb.spinFor(forward, 400, deg, true);
  BackClaw.set(true);
  wait(1, sec);
  //Go Forward
  lf.spinFor(forward, 1000, deg, false);
  lm.spinFor(forward, 1000, deg, false);
  lb.spinFor(forward, 1000, deg, false);
  rf.spinFor(reverse, 1000, deg, false);
  rm.spinFor(reverse, 1000, deg, false);
  rb.spinFor(reverse, 1000, deg, true);
  lift.spin(reverse, 70, pct);
  }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void usercontrol(void) {
    
  // bool for the claw toggle
  bool toggleUp = false;
  bool buttonUpPressed = false;
  
  bool toggleDown = false;
  bool buttonDownPressed = false;

  while (1) {

     // Temp display
    Brain.Screen.printAt(2, 40 ,"LeftArm Motor Temp %f " , motor(PORT20).temperature(percentUnits::pct));
    Brain.Screen.printAt(4, 60 ,"RightArm Motor Temp %f " , motor(PORT11).temperature(percentUnits::pct));

    Brain.Screen.printAt(8, 100 ,"DriveTrain Left-Side 1 %f " , lf.temperature(percentUnits::pct));
    Brain.Screen.printAt(10, 120 ,"DriveTrain Left-Side 2 %f " , lm.temperature(percentUnits::pct));
    Brain.Screen.printAt(12, 140 ,"DriveTrain Left-Side 3 %f " , lb.temperature(percentUnits::pct));

    Brain.Screen.printAt(16, 180 ,"DriveTrain Right-Side 1 %f " , rf.temperature(percentUnits::pct));
    Brain.Screen.printAt(18, 200 ,"DriveTrain Right-Side 2 %f " , rm.temperature(percentUnits::pct));
    Brain.Screen.printAt(20, 220 ,"DriveTrain Right-Side 3 %f " , rb.temperature(percentUnits::pct));
   
   // bool for claw
   bool buttonUp = Controller2.ButtonUp.pressing();

   bool buttonDown = Controller2.ButtonDown.pressing();

    //L-DiveTrain Velocity
    lf.setVelocity(350,vex::percentUnits::pct);
    lm.setVelocity(350,vex::percentUnits::pct);
    lb.setVelocity(350,vex::percentUnits::pct);

    //R-Drivetrain Velocity
    rf.setVelocity(350,vex::percentUnits::pct);
    rm.setVelocity(350,vex::percentUnits::pct);
    rb.setVelocity(350,vex::percentUnits::pct);

   //This is Left Side AXES 3 and 4
    lf.spin(vex::directionType::fwd,Controller1.Axis3.position(vex::percentUnits::pct),vex::percentUnits::pct);
    lm.spin(vex::directionType::fwd,Controller1.Axis3.position(vex::percentUnits::pct),vex::percentUnits::pct);
    lb.spin(vex::directionType::fwd,Controller1.Axis3.position(vex::percentUnits::pct),vex::percentUnits::pct);
    //This is Right Side AXES 1 and 2
    rf.spin(vex::directionType::rev,Controller1.Axis2.position(vex::percentUnits::pct),vex::percentUnits::pct);
    rm.spin(vex::directionType::rev,Controller1.Axis2.position(vex::percentUnits::pct),vex::percentUnits::pct);
    rb.spin(vex::directionType::rev,Controller1.Axis2.position(vex::percentUnits::pct),vex::percentUnits::pct);

    // Lift Code
     if(Controller2.ButtonR1.pressing())
    {
      motor_group(lift).spin(vex::directionType::fwd,70,vex::percentUnits::pct);
    }
    else if(Controller2.ButtonR2.pressing())
    {
      motor_group(lift).spin(vex::directionType::rev,70,vex::percentUnits::pct);
    }
    else
    {
     motor_group(lift).stop(vex::brakeType::hold);    
    }    

    // Back Claw Code
    if (buttonDown && !buttonDownPressed){
      buttonDownPressed = true;
      toggleDown = !toggleDown;
    }
    else if (!buttonDown)
    buttonDownPressed = false;
    if(toggleDown){
      BackClaw.set(true);
    }
    else {
      BackClaw.set(false);
    }

    if (toggleDown){
      RedLED.on();
    }
    else {
      RedLED.off();
    }

    // Claw toggle code
    if (buttonUp && !buttonUpPressed){
      buttonUpPressed = true;
      toggleUp = !toggleUp;
      Controller2.Screen.print("Claw Triggred");
    }
    else if (!buttonUp)
    buttonUpPressed = false;
    if(toggleUp){
      FrontClaw.set(true);
    }
    else {
      FrontClaw.set(false);
    }

    if(toggleUp){
      GreenLED.on();
    }
    else {
      GreenLED.off();
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

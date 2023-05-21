/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Lucas                                                     */
/*    Created:      Sub Jan 29 2023                                           */
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
// RED                  led           C               
// GREEN                led           D               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;


// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

// function to calibrate the Inertial sensor which is called in
// pre auton so during autonomus the PD Loops work 
void calibrateInertial(){
  Inertial.calibrate();

  while (Inertial.isCalibrating()){
    Controller1.Screen.clearLine(3);
    Controller1.Screen.print("Calibrating");
  } 

  Controller1.Screen.clearLine(3);
  Controller1.Screen.print("Done");
  Brain.Screen.printAt(0, 100, "Done");
  Controller1.rumble("..");
  wait(10, msec);
}

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*---------------------------------------------------------------------------*/

// Callback Boolean Variables

// For Auton Selection : the values are false because the buttons haven't been pressed
bool switch1=false;
bool switch2=false;

// Autonomous Selection : when the function is called it flips the boolean value

// Auton 1 
void AutonButton1(void){
  if (switch1){ 
  switch1= false;
  
  // Indication Of What Auton Swtich was pressed
  Brain.Screen.clearLine(1);
  Brain.Screen.printAt(2, 20, "Close-Side Auton - OFF");
  RED.off();
  
  } else {
  switch1= true;
  
  // Indication Of What Auton Swtich was pressed
  Brain.Screen.clearLine(1);
  Brain.Screen.printAt(2, 20, "Close-Side Auton - ON");
  RED.on();
  
  }  
}

// Auton 2
void AutonButton2(void){
  if (switch2){ 
  switch2= false;

  // Indication Of What Auton Swtich was pressed
  Brain.Screen.clearLine(2);
  Brain.Screen.printAt(2, 40, "Far-Side Auton - OFF");
  GREEN.off();

  } else {
  switch2= true;

  // Indication Of What Auton Swtich was pressed
  Brain.Screen.clearLine(2);
  Brain.Screen.printAt(2, 40, "Far-Side Auton - ON");
  GREEN.on();

  } 
}


void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

 // The LEDs are turned off so that they can 
 // be useful for the auton selection
 RED.off();
 GREEN.off();
  
  calibrateInertial(); // call the calibration to start it

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...

 // the motors positions are set to 0 so that we are accurate for our PD Loops
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

// Tuned Variables - the kP and kD are fractional for precision. These terms dictate if the robot 
// goes on the right direction (kP) and if the speed is correct (kD)
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
int latPD(){

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

    derivative = error - prevError; // Derivative term equation to get the differenve between the current and previous 
                                    // error to check that you haven't gone past the target 

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

// Tuned Variables - the kP and kD are fractional for precision. These terms dictate if the robot 
// goes on the right direction (kP) and if the speed is correct (kD)
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

    // Error term equation to find the difference between where you want to be from where you are : Position
    turnError = targetHeading - Inertial.rotation(degrees); 

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

  // uses the auton number selected to run the auton, and the text prints 
  // on the screen to let the user know which auton was chosen
  if (switch1 && switch2){
    // Run Third Auton Program

    Brain.Screen.clearScreen();
    Brain.Screen.printAt(2, 60, "Running Skills Auton...");

    // Flywheel is spun to have a faster time getting to a constant speed
    FlyWheel.spin(fwd, 460, rpm);
    wait(5, sec); // Used to time the beginning of the constant speed

    // Line up the robot to the high goal
    rotDriveON = true;
    vex::task RotDrive(rotPD);
    targetHeading = -2; // target angle is 358 so we turn 2 degrees to the left
    vex::task::sleep(1000);
    vex::task::suspend(rotPD); // stops the task because of the 2 
                               // task max the function is still reusable

    // Disk indexer is set to true to be ready for the first shot
    DiskPush.set(true);
    wait(1.5,sec); // wait is 1.5 to make sure everything is set correctly so far
    DiskPush.set(false); // 1st shot
    wait(200, msec); // The air needs to exit the pistion so we wait for 200 miliseconds
    DiskPush.set(true); // reset the shot
    wait(200, msec); // Wait for air to refill
    DiskPush.set(false); // 2nd disk shot
    wait(1, sec); // This wait is needed so the wheel doesn't stop while we are still shooting 
    FlyWheel.stop(coast); // Stop the motor because we are done shooting

    // 1st Roller
    latDriveON = true; // Turning on the Lateral PD Loop
    vex::task DrivePD(latPD); // Calling the loop to be able to drive
    targetValue = -100; // The drivetrain moves back
    Roller.spinFor(fwd, .605, sec, 200, rpm); // turn the roller to our alliance color
    targetValue = 425; // go forward so the robot doesn't touch the field element
    vex::task::sleep(1000);
    vex::task::suspend(latPD); // we stop using the function

    // Rotate to line up for the 2nd roller
    rotDriveON = true;
    vex::task::resume(rotPD); // since we are reusing the function again we resume its task
    targetHeading = 90; // turn 90 degrees to the right 
    vex::task::sleep(1000);
    vex::task::suspend(rotPD); // stop using rotational movement

    resetSens = true;
    vex::task::resume(latPD); // start using lateral movement
    targetValue = -595; // drive back to that roller
    wait(2, sec); // we need to give the roller time to spin so we wait
    Roller.spinFor(fwd, 300, deg, 200, rpm); // turn the roller to our alliance color
    targetValue = 5; // drive forward so that we can line up for our endgame
    vex::task::sleep(1000);
    vex::task::suspend(latPD); // stop using lateral movement

    // Endgame Shot
    vex::task::resume(rotPD); // We rotate to get in position to fire our endgame
    targetHeading = -5; // we turn 5 degrees to the left
    vex::task::sleep(1000);
    vex::task::yield(); // fully stops the function and can no longer be used
    String.set(true); // Fire Endgame
  }
  else if (switch1){
    // Run First Auton Program
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(2, 60, "Running Close-Side Auton...");
    
    // Line up to the goal : the turn is too minimal to us the Rotation function
    leftBack.spinFor(reverse, 23, deg,false);
    leftFront.spinFor(reverse, 23, deg,false);
    rightFront.spinFor(forward, 23, deg,false);
    rightBack.spinFor(forward, 23, deg,true);

    // Flywheel is spun to have a faster time getting to a constant speed
    FlyWheel.spin(fwd, 480, rpm);
    wait(6, sec);

    // Disk indexer is set to true to be ready for the first shot
    DiskPush.set(true);
    wait(1,sec); // wait is 1 to make sure everything is set correctly so far
    DiskPush.set(false); // 1st shot
    wait(250, msec); // The air needs to exit the pistion so we wait for 200 miliseconds
    DiskPush.set(true); // reset the shot
    wait(260, msec); // Wait for air to refill
    DiskPush.set(false); // 2nd disk shot
    wait(1, sec); // This wait is needed so the wheel doesn't stop while we are still shooting 
    FlyWheel.stop(coast); // Stop the motor because we are done shooting

    latDriveON = true; // Turning on the Lateral PD Loop
    vex::task DrivePD(latPD); // Calling the loop to be able to drive
    targetValue = -100; // The drivetrain moves back
    Roller.spinFor(fwd, .5, sec, 200, rpm); // turn the roller to our alliance color
    targetValue = 50; // go forward so the robot doesn't touch the field element
  }
    else if (switch2) {
    // Run Second Auton Program
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(2, 60, "Running Far-Side Auton...");

    // Flywheel is spun to have a faster time getting to a constant speed
    FlyWheel.spin(fwd, 440, rpm);

    resetSens = true; // Ensures that the starting position is 0

    // Disk indexer is set to true to be ready for the first shot
    DiskPush.set(true); 
    rotDriveON=true; // Turning on the Rotational PD Loop
    vex::task turnPD(rotPD); // Calling the loop to be able to turn
    targetHeading = 30.75; // Setting the angle the robot needs to be at
    vex::task::sleep(1000);// The task is slept so that the vex brain can process the loop right
    vex::task::suspend(rotPD);

    latDriveON = true; // Turning on the Lateral PD Loop
    vex::task DrivePD(latPD); // Calling the loop to be able to drive
    targetValue = 425; // The drivetrain moves forward
    
    wait(4.5,sec); // wait is to wait untill the motor is closer to its constant speed

    // Disk indexer is set to true to be ready for the first shot
    DiskPush.set(true);
    wait(1,sec); // wait is 1.5 to get on the peak of the flywheel speed interval
    DiskPush.set(false);
    wait(260, msec);
    DiskPush.set(true);
    wait(250, msec); // Wait for the air to get back into the piston
    DiskPush.set(false); // 2nd disk shot
    wait(1, sec); // This wait is needed otherwise it breaks the timing of the auton 
    FlyWheel.stop(coast); // Stop the motor because we are done shooting

    vex::task::sleep(1000); // The task is slept so that the vex brain can process the loop right
    vex::task::suspend(latPD);

    // The following is to line up and backup onto the roller

    // Line Up
    vex::task::resume(rotPD);
    targetHeading = -50.75;
    vex::task::sleep(1000);
    vex::task::suspend(rotPD);

    //Back up and roll
    resetSens = true;
    vex::task::resume(latPD);
    targetValue = -750;
    wait(2, sec);
    Roller.spinFor(fwd, 190, degrees, 100, rpm, true); // turn the roller to our alliance color
    wait(1, sec);
    targetValue = 25;
    vex::task::sleep(1000);
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


    wait(20, msec); // Sleep the task for a short amount of time to prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.

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

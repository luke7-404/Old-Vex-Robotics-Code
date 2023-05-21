#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);
motor LeftArm = motor(PORT10, ratio18_1, true);
motor RightArm = motor(PORT1, ratio18_1, false);
motor Tiller = motor(PORT16, ratio36_1, false);
motor Claw = motor(PORT5, ratio18_1, false);
digital_out ClawPiston = digital_out(Brain.ThreeWirePort.A);
motor leftMotorA = motor(PORT20, ratio36_1, false);
motor leftMotorB = motor(PORT19, ratio36_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT11, ratio36_1, true);
motor rightMotorB = motor(PORT12, ratio36_1, true);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 299.24, 368.29999999999995, 330.2, mm, 1.6666666666666667);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}
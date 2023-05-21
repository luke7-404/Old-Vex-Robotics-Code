#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);
digital_out FrontClaw = digital_out(Brain.ThreeWirePort.A);
motor leftMotorA = motor(PORT18, ratio36_1, false);
motor leftMotorB = motor(PORT19, ratio36_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT12, ratio36_1, true);
motor rightMotorB = motor(PORT13, ratio36_1, true);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 299.24, 368.29999999999995, 330.2, mm, 1.6666666666666667);
motor liftMotorA = motor(PORT11, ratio18_1, false);
motor liftMotorB = motor(PORT20, ratio18_1, true);
motor_group lift = motor_group(liftMotorA, liftMotorB);
motor BackpackMotorA = motor(PORT15, ratio36_1, true);
motor BackpackMotorB = motor(PORT16, ratio36_1, false);
motor_group Backpack = motor_group(BackpackMotorA, BackpackMotorB);

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
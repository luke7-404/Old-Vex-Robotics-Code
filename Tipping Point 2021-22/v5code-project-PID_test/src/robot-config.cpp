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
motor ArmsMotorA = motor(PORT11, ratio18_1, false);
motor ArmsMotorB = motor(PORT20, ratio18_1, true);
motor_group Arms = motor_group(ArmsMotorA, ArmsMotorB);
motor BackpackMotorA = motor(PORT15, ratio36_1, true);
motor BackpackMotorB = motor(PORT16, ratio36_1, false);
motor_group Backpack = motor_group(BackpackMotorA, BackpackMotorB);
encoder LeftSensor = encoder(Brain.ThreeWirePort.C);
encoder RightSensor = encoder(Brain.ThreeWirePort.E);
motor LF = motor(PORT18, ratio36_1, false);
motor LB = motor(PORT19, ratio36_1, false);
motor RF = motor(PORT12, ratio36_1, false);
motor RB = motor(PORT13, ratio36_1, false);

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
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
digital_out BackClaw = digital_out(Brain.ThreeWirePort.B);
motor liftMotorA = motor(PORT11, ratio18_1, false);
motor liftMotorB = motor(PORT20, ratio18_1, true);
motor_group lift = motor_group(liftMotorA, liftMotorB);
motor lf = motor(PORT19, ratio18_1, false);
motor lm = motor(PORT18, ratio18_1, false);
motor lb = motor(PORT17, ratio18_1, true);
motor rf = motor(PORT12, ratio18_1, false);
motor rm = motor(PORT13, ratio18_1, false);
motor rb = motor(PORT14, ratio18_1, true);
led GreenLED = led(Brain.ThreeWirePort.G);
led RedLED = led(Brain.ThreeWirePort.H);

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
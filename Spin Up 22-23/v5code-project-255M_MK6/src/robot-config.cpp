#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
limit Auton1 = limit(Brain.ThreeWirePort.A);
limit Auton2 = limit(Brain.ThreeWirePort.B);
motor leftFront = motor(PORT13, ratio18_1, false);
motor leftBack = motor(PORT2, ratio18_1, false);
motor rightFront = motor(PORT12, ratio18_1, true);
motor rightBack = motor(PORT1, ratio18_1, true);
controller Controller1 = controller(primary);
motor IntakeMotorA = motor(PORT11, ratio18_1, true);
motor IntakeMotorB = motor(PORT20, ratio18_1, false);
motor_group Intake = motor_group(IntakeMotorA, IntakeMotorB);
inertial Inertial = inertial(PORT10);
digital_out String = digital_out(Brain.ThreeWirePort.G);
motor FlyWheel = motor(PORT9, ratio6_1, false);
motor Roller = motor(PORT3, ratio18_1, false);
digital_out DiskPush = digital_out(Brain.ThreeWirePort.H);
led RED = led(Brain.ThreeWirePort.C);
led GREEN = led(Brain.ThreeWirePort.D);
/*vex-vision-config:begin*/
vision Vision = vision (PORT17, 50);
/*vex-vision-config:end*/

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
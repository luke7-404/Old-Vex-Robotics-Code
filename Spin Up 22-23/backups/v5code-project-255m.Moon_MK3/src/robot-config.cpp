#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
limit Auton1 = limit(Brain.ThreeWirePort.A);
limit Auton2 = limit(Brain.ThreeWirePort.B);
limit Auton3 = limit(Brain.ThreeWirePort.C);
limit Auton4 = limit(Brain.ThreeWirePort.D);
motor leftFront = motor(PORT13, ratio18_1, false);
motor leftBack = motor(PORT2, ratio18_1, false);
motor rightFront = motor(PORT12, ratio18_1, true);
motor rightBack = motor(PORT1, ratio18_1, true);
controller Controller1 = controller(primary);
motor IntakeMotorA = motor(PORT11, ratio18_1, true);
motor IntakeMotorB = motor(PORT20, ratio18_1, false);
motor_group Intake = motor_group(IntakeMotorA, IntakeMotorB);
inertial Inertial = inertial(PORT10);
digital_out DiskPush = digital_out(Brain.ThreeWirePort.E);
digital_out StringP1 = digital_out(Brain.ThreeWirePort.F);
digital_out StringP2 = digital_out(Brain.ThreeWirePort.G);
motor FlyWheel = motor(PORT9, ratio6_1, false);
motor Roller = motor(PORT3, ratio18_1, false);
/*vex-vision-config:begin*/
vision Vision8 = vision (PORT8, 50);
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
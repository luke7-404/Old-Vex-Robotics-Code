using namespace vex;

extern brain Brain;

// VEXcode devices
extern limit Auton1;
extern limit Auton2;
extern motor leftFront;
extern motor leftBack;
extern motor rightFront;
extern motor rightBack;
extern controller Controller1;
extern motor_group Intake;
extern inertial Inertial;
extern digital_out String;
extern motor FlyWheel;
extern motor Roller;
extern digital_out DiskPush;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );
using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern controller Controller2;
extern drivetrain Drivetrain;
extern motor LeftArm;
extern motor RightArm;
extern motor LeftWing;
extern motor RightWing;
extern motor Tiller;
extern motor Claw;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );
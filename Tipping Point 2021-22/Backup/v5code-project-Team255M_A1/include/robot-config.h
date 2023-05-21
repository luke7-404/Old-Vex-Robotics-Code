using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern controller Controller2;
extern motor LeftArm;
extern motor RightArm;
extern motor Tiller;
extern motor Claw;
extern drivetrain Drivetrain;
extern digital_out ClawPiston;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );
using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern controller Controller2;
extern digital_out FrontClaw;
extern digital_out BackClaw;
extern motor_group lift;
extern led GreenLED;
extern led RedLED;
extern motor lf;
extern motor lm;
extern motor lb;
extern motor rf;
extern motor rm;
extern motor rb;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );
using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern controller Controller2;
extern digital_out FrontClaw;
extern motor_group Arms;
extern motor_group Backpack;
extern encoder LeftSensor;
extern encoder RightSensor;
extern motor LF;
extern motor LB;
extern motor RF;
extern motor RB;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );
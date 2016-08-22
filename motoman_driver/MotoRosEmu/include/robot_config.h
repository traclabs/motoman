#ifndef FAKE_ROBOT_CONFIG__
#define FAKE_ROBOT_CONFIG__


#define FAKE_ROBOT_NUM_GROUPS 1
#define FAKE_ROBOT_NUM_AXES_GRP_1 7

// we make this fake robot use a 1000:1 encoder:rad ratio
#define FAKE_ROBOT_PULSE_TO_RAD 0.001

// we make this fake robot use a 1000:1 encoder:rad ratio
#define FAKE_ROBOT_PULSE_TO_METER 0.001

// made up value
#define FAKE_ROBOT_MAX_NUM_TASKS_PRIO_HIGH 10
#define FAKE_ROBOT_MAX_NUM_TASKS_PRIO_NORMAL 10

// made up value
#define FAKE_ROBOT_INTERPOLATION_PERIOD 40 // ms

// made up value: since we have pulse-to-rad 1000:1, this is in thousands-rad/cycle
// TODO: not used for FS100?
#define FAKE_ROBOT_MAX_INC_PER_CYCLE 100

// no idea (percentage limit Of MaxSpeed)
// TODO: not used for FS100?
#define FAKE_ROBOT_GOV_FOR_INC_MOTION 0.1


#endif // FAKE_ROBOT_CONFIG__

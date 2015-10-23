// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _base_H_
#define _base_H_

#include "Arduino.h"
#include "planner.h"

#define EXTRUDERS 1
//add your includes for the project base here
extern int fanSpeed;
extern int extrudemultiply; //100->1 200->2
extern uint8_t active_extruder;
extern float volumetric_multiplier[EXTRUDERS];

//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project base here
void get_command();
void FlushSerialRequestResend();
void process_commands();
bool code_seen(char code);
float code_value();
void get_coordinates();
void prepare_move();
void calculate_delta(float cartesian[3]);
//¼ÆËãpaint µÄ
void calculate_paint(float cartesian[3]);

//Do not add code below this line
#endif /* _base_H_ */

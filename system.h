#ifndef SYSTEM_H
#define SYSTEM_H

#include "config.h"

enum Mode
{
	NOTREADY,
	SPEED,
	POSITION,
	HOMING,
	IDLE
};

typedef struct
{
	Mode mode;
	uint16_t watchdog;

	system_t()
	{
		mode = Mode::IDLE;
	}

} system_t;
extern system_t sys;

typedef struct {

	float speed;
	float pos;
	float target_speed;
	float target_pos;

	float max_pos;
	float min_pos;
	int nb_step;
	int step;

	uint16_t n_tick;

} stepper_t;

extern stepper_t stepper;

extern float lpos;

void init_system_control_pins();

void init_system_timer();

void disable_system_timer();

void enable_system_timer();


#endif
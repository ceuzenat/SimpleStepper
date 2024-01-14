#include "stepam.h"

float p_list[FILTER_SIZE] = { 0 };
float pos = 0;
int v_index = 0;
int v_index_0 = 0;
float pi = 3.141592;


float dt = 0.010;
float K = 1.0 / (FILTER_SIZE - 1);


void init_system_control_pins()
{
	STEPPER_PORT |= STEPPER_MASK;		//Set mode output high
	STEPPER_CONTROL &= ~STEPPER_MASK;		//Set port to O
}

void init_system_timer()
{
	// 16 bits timers counter 1,2 on uno

	//TIMER 1 for step generation 
	TCCR1A  = 0;
	TCCR1B  = 0;
	TCCR1B |= (1 << CS10); 		// 1 prescaler   -> 16 MHz    
	//TIMSK1 |= (1 << OCIE1A);

	//TIMER 4 for step x generation
	TCCR2A  = 0;
	TCCR2B  = 0;
	TCCR2B |= (1 << CS22) | ( 1 << CS20); 		// 1024 prescaler 
	//TIMSK2 |=  (1 << OCIE2A);
	//TIMSK2 |=  (1 << OCIE2B);

	//	CSn2	CSn1	CSn0
	//	0		0		0		No clock source
	//	0		0		1		1 prescaler ->		16 Mhz		256 Hz		625 ns
	//	0		1		0		8 prescaler ->		2 Mhz 		32 Hz		0.5 us
	//	0		1		1		64 prescaler ->		250 Khz  	4 Hz		4 us
	//	1		0		0		256 prescaler ->	62.5 Khz	1 Hz
	//	1		0		1		1024 prescaler ->	15 625 Hz	1/4 Hz
	//	1		1		0		External clock source on Tn pin falling edge
	//	0		1		1		External clock source on Tn pin rising edge

	// Enable COMPA_Vect
}

void disable_system_timer()
{
	TIMSK1 = 0;
	TIMSK2 = 0;
}

void enable_system_timer()
{
	TIMSK1 |= (1<<OCIE1A);
	TIMSK1 |= (1<<OCIE1B);
	TIMSK2 |= (1<<OCIE2A);
}

ISR(TIMER2_COMPA_vect)
{
	// Serial.print("mode : ");
	// Serial.println(sys.mode);
	switch (sys.mode)
	{
		case Mode::SPEED:

			pos += stepper.target_speed * dt;
			pos = min(MAX_POS, pos);
			pos = max(MIN_POS, pos);

			break;

		case Mode::POSITION:

			//Position
			if(pos - stepper.target_pos > 0)
			{
				stepper.target_speed = -8;
				pos += stepper.target_speed * dt;
				pos  = max(stepper.target_pos, pos);

			}
			else if(pos - stepper.target_pos < 0)
			{
				stepper.target_speed = 8;
				pos += stepper.target_speed * dt;
				pos  = min(stepper.target_pos, pos);
				
			}
			else
			{
				stepper.target_speed = 0;
			}

			pos = min(MAX_POS, pos);
			pos = max(MIN_POS, pos);

			break;

		case Mode::IDLE:

			break;

		case Mode::NOTREADY:

			break;

		default:
			break;
	}

	//filter X
	//TODO voir pour supprime V_index_0
	p_list[v_index] = pos;

	v_index_0 = v_index + 1;
	v_index_0 = v_index_0 % FILTER_SIZE;

	lpos += K * pos;
	lpos -= K * p_list[v_index_0];

	stepper.speed = 10 * (lpos - stepper.pos);

	stepper.n_tick = 160000L * pi / (stepper.nb_step * stepper.step * abs(stepper.speed));
	stepper.n_tick = max(stepper.n_tick, 350);
	stepper.n_tick = min(stepper.n_tick, 65000);

	v_index += 1;
	v_index  = v_index % FILTER_SIZE;

	OCR2A = TCNT2 + 157; // 100Hz
}

ISR(TIMER1_COMPA_vect)
{
	// stepper.n_tick = 30000;
	uint16_t ntA = max(stepper.n_tick, 350);
	ntA = min(ntA, 65000);
	OCR1A = TCNT1 + ntA;//TCNT5 + ntA;

	uint16_t ntB = ntA >> 1;
	OCR1B = TCNT1 + ntB;

	if(abs(stepper.speed) > 0.5)
	{
		STEPPER_CONTROL &= ~X_STEP;
		
		if(stepper.speed > 0)
		{
			stepper.pos += MM_PER_STEP;
			STEPPER_CONTROL	|= X_DIR;
		}
		else
		{
			stepper.pos -= MM_PER_STEP;
			STEPPER_CONTROL &= ~X_DIR;
		}
	}
}

ISR(TIMER1_COMPB_vect)
{
	STEPPER_CONTROL |= X_STEP;
}
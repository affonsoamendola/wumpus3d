
#define TMR_CONTROL 			0x43 //The 8253 control register port
#define TMR_COUNTER_0 			0x40 //Timer Counter Ports
#define TMR_COUNTER_1 			0x41
#define TMR_COUNTER_2 			0x42

#define TMR_COUNTER_0_BITS			0x00
#define TMR_COUNTER_1_BITS			0x40
#define TMR_COUNTER_2_BITS			0x80

#define TMR_LATCH_OPERATION 			0x00
#define TMR_COUNTER_LOW_BYTE			0x10
#define TMR_COUNTER_HIGH_BYTE			0x20
#define TMR_COUNTER_LOW_THEN_HIGH		0x30

#define TMR_OP_INT_ON_TERMINAL			0x00
#define TMR_OP_HW_ONE_SHOT				0x02
#define TMR_OP_RATE_GEN					0x0C
#define TMR_OP_SQUARE_WAVE				0x0E
#define TMR_OP_SOFT_STROBE				0x08
#define TMR_OP_HARD_STROBE				0x09

#define TMR_COUNT_BINARY				0x00
#define TMR_COUNT_BCD					0x01

#define SYSTEM_OSCILLATOR				1193180L //System Oscillator Frequency in Hz

int TICKS_PER_SECOND = 18; 

int get_ticks_per_second()
{
	return TICKS_PER_SECOND;
}

void set_timer_frequency(int frequency)
{
	int divisor;

	divisor = (int)(SYSTEM_OSCILLATOR/(long)frequency);

	outportb(TMR_CONTROL, TMR_COUNTER_LOW_THEN_HIGH & TMR_OP_RATE_GEN);

	outportb(TMR_COUNTER_0, (divisor & 0x00FF));
	outportb(TMR_COUNTER_0, (divisor & 0xFF00)>>8);

	TICKS_PER_SECOND = frequency;
}
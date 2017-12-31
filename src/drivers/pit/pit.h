#ifndef PIT_H
#define PIT_H
#define COUNTER_0 (00)
#define COUNTER_1 (1)
#define COUNTER_2 (2)
#define RD_BACK_COMMAND (3)
#define COUNTER_OFFSET 6

#define COUNTER_LATCH_COMMAND (0)
#define READ_WRITE_LSB (1)
#define READ_WRITE_MSB (2)
#define READ_WRITE_WORD (3)
#define READ_WRITE_OFFSET 4

#define MODE_AUTO_ONE_SHOT 0
#define MODE_HARDWARE_ONE_SHOT 1
#define MODE_RATE_GEN 2
#define MODE_SQUARE_WAVE 3
#define MODE_SOFT_TRIGGER_STROBE 4
#define MODE_HARD_TRIGGER_STROBE 5
#define MODE_OFFSET 1

#define SET_BCD 1

extern void init_pit_timer(uint8_t timer, uint8_t timer_mode, uint8_t read_write_mode, uint8_t bcd, uint16_t count);

#endif

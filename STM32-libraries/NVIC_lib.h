
#ifndef INC_NVIC_LIB_H_
#define INC_NVIC_LIB_H_

#include <stdint.h>

void enable_IR(uint8_t IRQn);
void disable_IR(uint8_t IRQn);

void set_priority(uint8_t IRQn, uint8_t priority);



#endif /* INC_NVIC_LIB_H_ */

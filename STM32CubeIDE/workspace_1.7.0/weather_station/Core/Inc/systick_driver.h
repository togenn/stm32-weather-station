#ifndef __SYSTICK_DRIVER_H
#define __SYSTICK_DRIVER_H

#define systick_base 0xE000E010

typedef struct {
  volatile uint32_t CTRL;
  volatile uint32_t LOAD;
  volatile  uint32_t CALIB;
} systick_type;

#define systick_reg ((systick_type*) systick_base)

#endif

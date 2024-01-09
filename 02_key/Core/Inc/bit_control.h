#ifndef __BIT_CONTROL_H
#define __BIT_CONTROL_H

#define COUNTOF(__BUFFER__)       (sizeof(__BUFFER__)/sizeof(*(__BUFFER__)))

#define CONCAT(a, b)    a ## b
#define STR(s)          #s

#define __SET_BIT(REG,BIT)          ((REG) |= (BIT)) 
#define __CLEAR_BIT(REG, BIT)       ((REG) &= ~(BIT))
#define __READ_BIT(REG, BIT)        ((REG) & (BIT))
#define __CLEAR_REG(REG)            ((REG) = (0x0))
#define __WRITE_REG(REG, VAL)       ((REG) = (VAL))   
#define __CMP_REG(REG,VAL)          ((REG) == (VAL))


#define __GPIO_SET_BIT(REG,BIT)         __SET_BIT((REG->BSRR),(BIT))
#define __GPIO_RESET_BIT(REG,BIT)       __SET_BIT((REG->BSRR),(BIT<<16UL))
#define __GPIO_OUT_READ(REG,BIT)        __CMP_REG(__READ_BIT((REG->ODR),(BIT)), (BIT))
#define __GPIO_IN_READ(REG,BIT)        __CMP_REG(__READ_BIT((REG->IDR),(BIT)), (BIT))

typedef enum
{
  START_OK          = 0x00,
  START_ERROR       = 0x01,
  START_BUSY        = 0x02,
  START_READ        = 0x03,
  START_WRITE       = 0x04,
  START_READ_WRITE  = 0x05,
  START_TIMEOUT     = 0x06
}StatusTypeDef;

#ifdef BITS
typedef enum
{
  RESET = 0,
  SET = !RESET
} FlagStatus;

typedef enum
{
  DISABLE = 0,
  ENABLE = !DISABLE
} FunctionalState;
#endif // 

#endif // !__BIT_CONTROL_H

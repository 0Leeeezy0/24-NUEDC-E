#ifndef CODE_MY_DEVICE_H_
#define CODE_MY_DEVICE_H_

#include "common.h"


void Init_All(void);
void Key_Scan(void);
KEY_State Key_Get(Key_index_enum pin);
void Key_clear_state (Key_index_enum key_n);


#endif /* CODE_MY_DEVICE_H_ */

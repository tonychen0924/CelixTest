#ifndef PLC_MAIN_H
#define PLC_MAIN_H

#include <stdio.h>

void process_shared_ptr(void* ptr);
void startPLC(int a, int b);
void stopPLC();
void setPConsumer(void* p);


#endif
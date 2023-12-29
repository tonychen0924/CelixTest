#include "plc_main.h"

void* consumerAddress;

void startPLC(int a, int b)
{
    printf("%s\n", __func__);
    printf("1====================\n");
    printf("2====================\n");
    printf("3====================\n");
}

void stopPLC()
{
    printf("%s\n", __func__);
}

void process_shared_ptr(void* ptr)
{
    int* sharedPtrValue = (int*)ptr;
    printf("Value from shared_ptr in C: %d\n", *sharedPtrValue);
}

void setPConsumer(void* p)
{
    consumerAddress = p;
}
#ifndef AD_STACK_H
#define AD_STACK_H

#include <limits.h>

#define AD_STACK_EMPTY INT_MIN

typedef struct {
    int* data;
    int top;
    int capacity;
} ADStack;

// Создание/удаление стека
ADStack* ad_stack_create(int capacity);
void ad_stack_destroy(ADStack* s);

// Основные операции
int ad_stack_is_empty(ADStack* s);
int ad_stack_size(ADStack* s);
void ad_push(ADStack* s, int x);
int ad_pop(ADStack* s);
int ad_top(ADStack* s);

#endif
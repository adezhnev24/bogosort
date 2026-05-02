#include <stdlib.h>
#include "ad_stack.h"

ADStack* ad_stack_create(int capacity) {
    if (capacity <= 0) return NULL;

    ADStack* s = (ADStack*)malloc(sizeof(ADStack));
    if (!s) return NULL;

    s->data = (int*)malloc(capacity * sizeof(int));
    if (!s->data) {
        free(s);
        return NULL;
    }

    s->capacity = capacity;
    s->top = -1;
    return s;
}

void ad_stack_destroy(ADStack* s) {
    if (s) {
        free(s->data);
        free(s);
    }
}

int ad_stack_is_empty(ADStack *s) {
    return (!s) || s->top == -1;
}

int ad_stack_size(ADStack* s) {
    if (!s) return 0;
    return s->top + 1;
}

void ad_push(ADStack* s, int x) {
    if (!s) return;

    int *new_data, new_capacity;

    if (s->top >= s->capacity - 1) {
        new_capacity = (s->capacity == 0) ? 1 : s->capacity * 2;
        new_data = (int*)realloc(s->data, new_capacity * sizeof(int));
        if (!new_data) return;

        s->data = new_data;
        s->capacity = new_capacity;
    }

    s->top++;
    s->data[s->top] = x;
}

int ad_pop(ADStack *s) {
    if (!s || ad_stack_is_empty(s)) return AD_STACK_EMPTY;
    else {
        s->top--;
        return s->data[s->top+1];
    }
}

int ad_top(ADStack *s) {
    if (!s || ad_stack_is_empty(s)) return AD_STACK_EMPTY;
    else return s->data[s->top];
}

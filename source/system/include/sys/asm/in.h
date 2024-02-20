#pragma once

#include <stdint.h>

static inline unsigned char inb(uint16_t port) {
    unsigned char ret;
    asm volatile ("inb %1, %0" : "=a" (ret) : "Nd" (port) : "memory");
    return ret;
}

static inline unsigned char inb_ptr(void * port_ptr) {
    unsigned char ret;
    asm volatile ("inb %1, %0" : "=a" (ret) : "Nd" ((uint16_t) (intptr_t) port_ptr) : "memory");
    return ret;
}

static inline uint16_t inw(uint16_t port) {
    uint16_t ret;
    asm volatile ("inw %1, %0" : "=a" (ret) : "Nd" (port) : "memory");
    return ret;
}

static inline uint16_t inw_ptr(void * port_ptr) {
    uint16_t ret;
    asm volatile ("inw %1, %0" : "=a" (ret) : "Nd" ((uint16_t) (intptr_t) port_ptr) : "memory");
    return ret;
}
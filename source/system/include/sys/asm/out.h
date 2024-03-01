#pragma once

#include <stdint.h>

#include <sys/port.h>

//#define outb(byte, port) do { asm volatile ("outb %0, %1" : : "r" ((uint8_t) byte), "i" (port)); } while (0)

static inline void outb(uint16_t port, uint8_t byte) {
    asm volatile ("outb %b0, %w1" : : "a" (byte), "Nd" (port) : "memory");
}

static inline void outb_ptr(const port_t * port, uint8_t byte) {
    asm volatile ("outb %b0, %w1" : : "a" (byte), "Nd" ((uint16_t) (intptr_t) port) : "memory");
}
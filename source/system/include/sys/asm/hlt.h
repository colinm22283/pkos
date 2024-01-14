#pragma once

#define hlt() do { asm volatile ("cli; hlt"); } while (0)
#pragma once

#define interrupt(code) do { asm ("int $" #code); } while (0)

#define cli() do { asm ("cli"); } while (0)
#define sti() do { asm ("sti"); } while (0)
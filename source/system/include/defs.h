#pragma once

#define __STDCALL __attribute__((stdcall))
#define __VECTORCALL __attribute__((vectorcall))
#define __SYSV_ABI __attribute__((sysv_abi))

#define __PACKED __attribute__((packed))
#define __NORETURN __attribute__((noreturn))
#define __UNUSED __attribute__((unused))
#define __INTERRUPT __attribute__((interrupt))
#define __INTERRUPT_SUBROUTINE __attribute__((no_caller_saved_registers))
#define __NONULL    __attribute__((nonull))

#define __SECTION(section_name) __attribute__((__section__(section_name)))
#define __ALIGNED(alignment) __attribute__((aligned(alignment)))

#define GDT_CODE_SEG (0x10)
#define GDT_DATA_SEG (0x20)
#pragma once

#define __STDCALL __attribute__((stdcall))
#define __PACKED __attribute__((packed))
#define __SECTION(section_name) __attribute__((__section__(section_name)))
#define __ALIGNED(alignment) __attribute__((aligned(alignment)))
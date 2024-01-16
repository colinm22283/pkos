MEMORY {
    ivt                  : ORIGIN = 0x000000, LENGTH = 0x00400 - 0x00000
    bda                  : ORIGIN = 0x000400, LENGTH = 0x00500 - 0x00400
    usable_memory_1      : ORIGIN = 0x000500, LENGTH = 0x07C00 - 0x00500
    boot_sector          : ORIGIN = 0x007C00, LENGTH = 0x07E00 - 0x07C00
    usable_memory_2      : ORIGIN = 0x007E00, LENGTH = 0x80000 - 0x07E00
    ebda                 : ORIGIN = 0x080000, LENGTH = 0xA0000 - 0x80000
    video_display_memory : ORIGIN = 0x0A0000, LENGTH = 0xC0000 - 0xA0000
    video_bios           : ORIGIN = 0x0C0000, LENGTH = 0xC8000 - 0xC0000
    bios                 : ORIGIN = 0x100000, LENGTH = 0xF0000 - 0xF0000
}
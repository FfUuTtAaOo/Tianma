/******************************************************************************
 * @file     linker.ld
 * @brief    GCC Linker Script for LH32M0G3x (Cortex-M0+)
 *           Flash: 128KB (0x08000000 - 0x08020000)
 *           RAM:   8KB   (0x20000000 - 0x20002000)
 * @version  V1.0
 * @date     2026-07-16
 ******************************************************************************/

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 128K
    RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 8K
}

/* Stack and heap sizes */
STACK_SIZE = 0x00000800;
HEAP_SIZE  = 0x00000000;

/* Section Definitions */
SECTIONS
{
    /* The startup code goes first into FLASH */
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))       /* Startup code */
        . = ALIGN(4);
    } > FLASH

    /* The program code and other data goes into FLASH */
    .text :
    {
        . = ALIGN(4);
        *(.text)                   /* .text sections (code) */
        *(.text*)                  /* .text* sections (code) */
        *(.glue_7)                 /* glue arm to thumb code */
        *(.glue_7t)                /* glue thumb to arm code */
        *(.eh_frame)

        KEEP(*(.init))
        KEEP(*(.fini))

        . = ALIGN(4);
        _etext = .;                /* define a global symbols at end of code */
    } > FLASH

    /* Constant data goes into FLASH */
    .rodata :
    {
        . = ALIGN(4);
        *(.rodata)                 /* .rodata sections (constants, strings, etc.) */
        *(.rodata*)                /* .rodata* sections */
        . = ALIGN(4);
    } > FLASH

    /* ARM exception unwinding sections */
    .ARM.extab :
    {
        . = ALIGN(4);
        *(.ARM.extab*)
        . = ALIGN(4);
    } > FLASH

    .ARM :
    {
        . = ALIGN(4);
        __exidx_start = .;
        *(.ARM.exidx*)
        __exidx_end = .;
        . = ALIGN(4);
    } > FLASH

    /* Used by the startup to initialize data */
    _sidata = .;

    /* Initialized data sections goes into RAM, load LMA copy after code */
    .data : AT(_sidata)
    {
        . = ALIGN(4);
        _sdata = .;                /* create a global symbol at data start */
        *(.data)                   /* .data sections */
        *(.data*)                  /* .data* sections */
        *(.RamFunc)                /* .RamFunc sections */
        *(.RamFunc*)               /* .RamFunc* sections */

        . = ALIGN(4);
        _edata = .;                /* define a global symbol at data end */
    } > RAM

    /* Uninitialized data section */
    . = ALIGN(4);
    .bss :
    {
        _sbss = .;                 /* define a global symbol at bss start */
        __bss_start__ = _sbss;
        *(.bss)
        *(.bss*)
        *(COMMON)

        . = ALIGN(4);
        _ebss = .;                 /* define a global symbol at bss end */
        __bss_end__ = _ebss;
    } > RAM

    /* User_heap_stack section, used to check that there is enough RAM left */
    ._user_heap_stack :
    {
        . = ALIGN(8);
        PROVIDE ( end = . );
        PROVIDE ( _end = . );
        . = . + HEAP_SIZE;
        . = . + STACK_SIZE;
        . = ALIGN(8);
    } > RAM

    /* Remove information from the compiler libraries */
    /DISCARD/ :
    {
        libc.a ( * )
        libm.a ( * )
        libgcc.a ( * )
    }

    .ARM.attributes 0 : { *(.ARM.attributes) }
}

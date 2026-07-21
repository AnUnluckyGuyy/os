section .multiboot
align 4

dd 0x1BADB002
dd 0
dd -(0x1BADB002)

global start
extern kernel_main

section .text

start:
    call kernel_main

hang:
    cli
    hlt
    jmp hang

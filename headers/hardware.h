#ifndef HARDWARE_H
#define HARDWARE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define GAMESTART 0x200

typedef struct { 
    uint8_t* V;
    uint8_t ST;
    uint8_t DT;
    uint16_t I;
    uint16_t PC;
} chip8_registers_t;

typedef struct {
    uint16_t* stack;
    uint8_t top;
} chip8_stack_t;

typedef struct {
    chip8_registers_t* registers;
    chip8_stack_t* stack;
    uint8_t* main_memory;
    uint32_t** screen;
    uint8_t* keyboard;
    uint8_t screen_updated;
} chip8_hardware_t; 

void push(chip8_stack_t* stack, uint16_t value);
uint16_t pop(chip8_stack_t* stack);
uint8_t* initialize_main_memory();
chip8_stack_t* initialize_stack();
chip8_registers_t* initialize_registers();
void load_game(const char* game_path, uint8_t* main_memory);
void load_font_into_memory(uint8_t* main_memory);
uint32_t** initialize_screen();
uint8_t* initialize_keyboard();
void free_hardware(chip8_hardware_t* hardware);

#endif // HARDWARE_H
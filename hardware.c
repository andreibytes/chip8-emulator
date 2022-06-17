#include "headers/hardware.h"


void push(chip8_stack_t* stack, uint16_t value) {
    if(stack->top == 0){
        stack->stack[stack->top] = value;
    } else if(stack->top > 15) {
        printf("[-] Fatal exception. Stack overflow");
        exit(-1);
    } else {
        stack->top++;
        stack->stack[stack->top] = value;
    }
}

uint16_t pop(chip8_stack_t* stack) {
    uint16_t value = stack->stack[stack->top];
    stack->stack[stack->top] = 0;
    if(stack->top > 0) {
        stack->top--;
    }
    return value;
}

chip8_stack_t* initialize_stack() {
    chip8_stack_t* stack = (chip8_stack_t*)calloc(1, sizeof(chip8_stack_t));
    stack->top = 0;
    stack->stack = (uint16_t*)calloc(16, sizeof(uint16_t));
    return stack;
}

chip8_registers_t* initialize_registers(){
    chip8_registers_t* registers = (chip8_registers_t*)calloc(1, sizeof(chip8_registers_t));
    registers->V = (uint8_t*)calloc(16, sizeof(uint8_t));
    return registers;
}

uint8_t* initialize_main_memory() {
    uint8_t* main_memory = (uint8_t*)calloc(4096, sizeof(uint8_t));
    return main_memory;
}

uint32_t** initialize_screen(){
    uint32_t** screen = (uint32_t**)malloc(64 * sizeof(uint32_t*));
    for(int i = 0; i < 64; i++){
        screen[i] = (uint32_t*)malloc(32 * sizeof(uint32_t));
    }
    return screen;
}


void free_hardware(chip8_hardware_t* hardware){
    free(hardware->registers->V);
    free(hardware->registers);
    free(hardware->stack->stack);
    free(hardware->stack);
    free(hardware->main_memory);
    free(hardware->keyboard);
    for(int i = 0; i < 64; i++) {
        free(hardware->screen[i]);
    }
    free(hardware->screen);
}

uint8_t* initialize_keyboard(){
    uint8_t* keyboard = (uint8_t*)calloc(16, sizeof(uint8_t));
    return keyboard;
}

void load_game(const char* game_path, uint8_t* main_memory) {
    printf("[+] Loading game into memory: %s\n", game_path);
    
    // Get size of file and then start loading it into memory;
    FILE* game_file;
    game_file = fopen(game_path, "r");
    long game_file_size;
    int result = fseek(game_file, 0, SEEK_END);
    game_file_size = ftell(game_file);
    fseek(game_file, 0, SEEK_SET);
    uint8_t file_bytes[game_file_size];
    fread(&file_bytes, sizeof(uint8_t), game_file_size, game_file);
    
    for(int i = 0; i < game_file_size; i++) {
        main_memory[GAMESTART + i] = file_bytes[i];
    }

    printf("[+] Game loaded into memory\n");
}

void load_font_into_memory(uint8_t* main_memory){
    uint8_t font[80] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0,
        0x20, 0x60, 0x20, 0x20, 0x70, 
        0xF0, 0x10, 0xF0, 0x80, 0xF0, 
        0xF0, 0x10, 0xF0, 0x10, 0xF0, 
        0x90, 0x90, 0xF0, 0x10, 0x10, 
        0xF0, 0x80, 0xF0, 0x10, 0xF0, 
        0xF0, 0x80, 0xF0, 0x90, 0xF0,
        0xF0, 0x10, 0x20, 0x40, 0x40, 
        0xF0, 0x90, 0xF0, 0x90, 0xF0, 
        0xF0, 0x90, 0xF0, 0x10, 0xF0, 
        0xF0, 0x90, 0xF0, 0x90, 0x90, 
        0xE0, 0x90, 0xE0, 0x90, 0xE0,
        0xF0, 0x80, 0x80, 0x80, 0xF0, 
        0xE0, 0x90, 0x90, 0x90, 0xE0, 
        0xF0, 0x80, 0xF0, 0x80, 0xF0,
        0xF0, 0x80, 0xF0, 0x80, 0x80
    };

    for(int i = 0; i < 80; i++) {
        main_memory[i] = font[i];
    }

    printf("[+] Font loaded into memory\n");
}
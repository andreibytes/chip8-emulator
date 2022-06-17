#include <stdio.h>
#include "headers/hardware.h"
#include "headers/parser.h"

int main(int argc, char** argv)
{

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Could not initialize SDL: %s\n", SDL_GetError());
        exit(-1);
    }

    chip8_stack_t* stack = initialize_stack();
    chip8_registers_t* registers = initialize_registers();
    uint8_t* main_memory = initialize_main_memory();
    uint32_t** screen = initialize_screen();
    uint8_t* keyboard = initialize_keyboard();
    load_font_into_memory(main_memory);
    if(!argv[1]){
        printf("You need to choose a game to load\n");
        exit(0);
    }
    load_game(argv[1], main_memory);
    chip8_hardware_t hardware = {
        .main_memory = main_memory,
        .registers = registers,
        .stack = stack,
        .screen = screen,
        .keyboard = keyboard,
        .screen_updated = FALSE
    };
    start_game_loop(&hardware);
}

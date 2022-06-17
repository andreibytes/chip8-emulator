#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>
#include "hardware.h"
#include "time.h"
#include <math.h>
#include <SDL2/SDL.h>
#include <unistd.h>

#define REGISTERX (opcode & 0x0F00) >> 8
#define REGISTERY (opcode & 0x00F0) >> 4
#define REGISTERF 0xF
#define VALNN (opcode & 0x00FF)
#define VALNNN (opcode & 0x0FFF)
#define UNPAUSE 0
#define NOFLAGS 0
#define TRUE 1
#define FALSE 0


uint16_t parse_opcode(uint8_t byte_one, uint8_t byte_two);
void execute_opcode(uint16_t opcode, chip8_hardware_t* hardware);
void start_game_loop(chip8_hardware_t* hardware);
uint8_t rand_byte();

#endif // PARSER_H
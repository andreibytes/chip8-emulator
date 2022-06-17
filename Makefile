CC := gcc 
CFLAGS := -lSDL2 -lm  #-fsanitize=address
debug := false

emulator: emulator.o hardware.o parser.o
ifeq ($(debug),false)
	$(CC) $^ $(CFLAGS) -o $@
else 
	$(cc) $^ $(CFLAGS) -g -o $@
endif
	@echo "Built emulator release build"

emulator.o: emulator.c 
ifeq ($(debug),false)
	$(CC) -c $^  -o $@
else 
	$(CC) -c -g $^ -o $@
endif

hardware.o: hardware.c
ifeq ($(debug), false)
	$(CC) -c $^ -o $@
else
	$(CC) -c -g $^ -o $@
endif


parser.o: parser.c
ifeq ($(debug), false)
	$(CC) -c $^ -o $@
else 
	$(CC) -c -g $^ -o $@
endif

debug: emulator.o hardware.o parser.o
	$(CC) $^ $(CFLAGS) -g -o emulator
	@echo "Built emulator debug build"

clean:
	rm -rf emulator.o hardware.o parser.o
	@echo "Clean done"
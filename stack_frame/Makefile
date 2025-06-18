NAME = capa_med
ASM = capa_inf.asm
C = capa_med.c
OBJ_C = capa_med.o
OBJ_ASM = capa_inf.o

all: $(NAME).so

$(NAME).so: $(OBJ_C) $(OBJ_ASM)
	gcc -m32 -shared -o $@ $^

$(OBJ_C): $(C)
	gcc -m32 -fPIC -g3 -c $(C) -o $@

$(OBJ_ASM): $(ASM)
	nasm -f elf32 -g -F dwarf $(ASM) -o $@

clean:
	rm -f *.o *.so
DEBUG_SRC = test_cmed.c
DEBUG_OBJ = test_cmed.o
DEBUG_BIN = test_cmed

$(DEBUG_OBJ): $(DEBUG_SRC)
	gcc -m32 -g -c $(DEBUG_SRC) -o $@

$(DEBUG_BIN): $(DEBUG_OBJ) $(OBJ_C) $(OBJ_ASM)
	gcc -m32 -g -o $@ $^

debug: $(DEBUG_BIN)
	gdb -q $(DEBUG_BIN)

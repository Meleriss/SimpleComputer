#include "memory.h"
#include <stdio.h>

int sc_memoryInit()
{
	for (int i = 0; i < MEMORY_SIZE; i++)
		memory[i] = 0;

	return 0;
}

int sc_memorySet(int address, int value)
{
	if (address > MEMORY_SIZE || address < 0)
		return 1;

	memory[address] = value;
	
	return 0;
}

int sc_memoryGet(int address, int *value)
{
	if (address > MEMORY_SIZE || address < 0)
		return 1;

	*value = memory[address];

	return 0;
}

int sc_memorySave(char *filename)
{
	FILE *file = fopen(filename, "wb");

	fwrite(memory, sizeof(int), MEMORY_SIZE, file);
	fclose(file);

	return 0;
}

int sc_memoryLoad(char *filename)
{
	FILE *file = fopen(filename, "rb");

	fread(memory, sizeof(int), MEMORY_SIZE, file);
	fclose(file);

	return 0;
}

int sc_regInit()
{
	flag = 0;
	return 0;
}

int sc_regSet(int reg, int value)
{
	if (reg == A || reg == B || reg == C || reg == D || reg == E) {
		if (value == 0)
			flag = flag & ~(reg);
		if (value == 1)
			flag = flag | reg;
		else
			return 1;
	} else
		return 1;

	return 0;
}

int sc_regGet(int reg, int *value)
{
	if (reg == A || reg == B || reg == C || reg == D || reg == E) {
		if ((flag & reg) != 0)
			*value = 1;
		else
			*value = 0;
	}
	return 0;
}

int sc_commandEncode(int command, int operand, int *value)
{
	if (command < 10 
		|| (command > 11 && command < 20) 
		|| (command > 21 && command < 30)
		|| (command > 33 && command < 40)
		|| (command > 43 && command < 51)
		|| command > 76)
		return 1;

	if (operand > 127 || operand < 0)
		return 1;

	*value = (command << 7) | operand;

	return 0;
}

int sc_commandDecode(int value, int *command, int *operand)
{
		return 1;

	*command = value >> 7;
	*operand = value & 0x7F;
	return 0;
}

int sc_regFlagPrint()
{
	printf("%d\n", flag);
	return 0;
}

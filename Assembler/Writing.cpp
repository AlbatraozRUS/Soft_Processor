#include "ASM.h"

void Writing (char *bytecode, int size)
{
    assert(bytecode != nullptr);

    FILE *Writefile = fopen(Output_File, "wb");
    assert(Writefile != nullptr);

    for (int PC = 0; PC < size; PC++) {
        fprintf(Writefile, "%02x ", bytecode[PC]);
    }

    fclose(Writefile);
}

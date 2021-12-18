#include <stdlib.h>

#include "emu_mips.h"

emu_mips_t*
emu_mips_create(void)
{
    return calloc(1, sizeof(emu_mips_t));
}

void
emu_mips_destroy(emu_mips_t* emu)
{
    free(emu);
}

void
emu_mips_load_elf(emu_mips_t* emu, elf_t* elf)
{
    // Här får du ta över.
}

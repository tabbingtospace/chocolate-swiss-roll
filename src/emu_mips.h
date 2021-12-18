#ifndef EMU_MIPS_H
#define EMU_MIPS_H

#include <stdint.h>

#include "loader.h"

#define NUM_MIPS_REGS 32

enum MIPS_REG {
    ZERO = 0,
    AT,
    V0,
    V1,
    A0,
    A1,
    A2,
    A3,
    T0,
    T1,
    T2,
    T3,
    T4,
    T5,
    T6,
    T7,
    S0,
    S1,
    S2,
    S3,
    S4,
    S5,
    S6,
    S7,
    T8,
    T9,
    K0,
    K1,
    GP,
    SP,
    FP,
    RA,
};

typedef struct {
    uint32_t registers[NUM_MIPS_REGS];
} emu_mips_t;

emu_mips_t*
emu_mips_create();

void
emu_mips_destoy(emu_mips_t* emu);

void
emu_mips_load_elf(emu_mips_t* emu, elf_t* elf);

#endif

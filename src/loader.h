#include <stdint.h>

typedef enum{
	ENUM_ENDIANESS_LSB = 1,
	ENUM_ENDIANESS_MSB,
}ENUM_ENDIANESS_T;

typedef enum{
	ENUM_BIT_SIZE_32 = 1,
	ENUM_BIT_SIZE_64,
}ENUM_BIT_SIZE_T;

typedef struct {
	uint64_t offset;
	uint64_t virtual_address;
	uint64_t physical_address;
	uint64_t file_size;
	uint64_t memory_size;
	uint64_t align;
	uint64_t flags;
} program_header_t;

typedef struct{
	ENUM_ENDIANESS_T endianess;
	ENUM_BIT_SIZE_T bit_size;
	uint64_t entry_point;
	uint64_t num_prog_headers;
	program_header_t** prog_headers;
	uint64_t program_header_offset;
	uint8_t* data;
	uint64_t data_length;
	uint64_t program_header_size;
} elf_t;

elf_t*
elf_create(char* path);

void
elf_destroy(elf_t* elf);

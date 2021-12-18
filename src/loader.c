#include "loader.h"
#include <stdio.h>
#include <stdlib.h>
#include "endianess_converter.h"

void
check_endianess(elf_t* elf){
	if(elf->data[5] == ENUM_ENDIANESS_LSB) {
		elf->endianess = ENUM_ENDIANESS_LSB;
	}
	else if(elf->data[5] == ENUM_ENDIANESS_MSB) {
		elf->endianess = ENUM_ENDIANESS_MSB;
	}
	else {
		printf("Malformed ELF header.\n");
		abort();
	}
}

void
check_bitsize(elf_t* elf) {
	if(elf->data[4] == ENUM_BIT_SIZE_32) {
		elf->bit_size = ENUM_BIT_SIZE_32;
	}
	else if(elf->data[4] == ENUM_BIT_SIZE_64) {
		elf->bit_size = ENUM_BIT_SIZE_64;
	}
	else{
		printf("Could not determine bitsize\n");
		abort();
	}
}

void
check_entry_point(elf_t* elf) {
	if(elf->bit_size == ENUM_BIT_SIZE_32) {
		elf->entry_point = byte_arr_to_u64(elf->data + 0x18, 4, elf->endianess);
	}
	else if(elf->bit_size == ENUM_BIT_SIZE_64) {
		elf->entry_point = byte_arr_to_u64(elf->data + 0x18, 8, elf->endianess);
	}
}

void
check_program_header_offset(elf_t* elf) {
	if(elf->bit_size == ENUM_BIT_SIZE_32) {
		elf->program_header_offset = byte_arr_to_u64(elf->data + 0x1C, 4, elf->endianess);
	}
	else if(elf->bit_size == ENUM_BIT_SIZE_64) {
		elf->program_header_offset = byte_arr_to_u64(elf->data + 0x20, 8, elf->endianess);
	}
}

void
check_num_program_headers(elf_t* elf) {
	if(elf->bit_size == ENUM_BIT_SIZE_32) {
		elf->num_prog_headers = byte_arr_to_u64(elf->data + 0x2C, 2, elf->endianess);
	}
	else if(elf->bit_size == ENUM_BIT_SIZE_64) {
		elf->num_prog_headers = byte_arr_to_u64(elf->data + 0x38, 2, elf->endianess);
	}

}

void
check_program_header_size(elf_t* elf) {
	if(elf->bit_size == ENUM_BIT_SIZE_32) {
		elf->program_header_size = byte_arr_to_u64(elf->data + 0x2A, 2, elf->endianess);
	}
	else if(elf->bit_size == ENUM_BIT_SIZE_64) {
		elf->program_header_size = byte_arr_to_u64(elf->data + 0x36, 2, elf->endianess);
	}
}

void
program_header_check_offset(elf_t* elf, program_header_t* program_header, uint64_t current_program_header_base) {
	if(elf->bit_size == ENUM_BIT_SIZE_32) {
		program_header->offset = byte_arr_to_u64(elf->data+current_program_header_base + 0x04, 4, elf->endianess);

	}
	else if(elf->bit_size == ENUM_BIT_SIZE_64) {
		program_header->offset = byte_arr_to_u64(elf->data+current_program_header_base + 0x08, 8, elf->endianess);
	}
}

void
program_header_check_virtual_address(elf_t* elf, program_header_t* program_header, uint64_t current_program_header_base) {
	if(elf->bit_size == ENUM_BIT_SIZE_32) {
		program_header->virtual_address = byte_arr_to_u64(elf->data+current_program_header_base + 0x08, 4, elf->endianess);

	}
	else if(elf->bit_size == ENUM_BIT_SIZE_64) {
		program_header->virtual_address = byte_arr_to_u64(elf->data+current_program_header_base + 0x10, 8, elf->endianess);
	}
}
void
program_header_check_physical_address(elf_t* elf, program_header_t* program_header, uint64_t current_program_header_base) {
	if(elf->bit_size == ENUM_BIT_SIZE_32) {
		program_header->physical_address = byte_arr_to_u64(elf->data+current_program_header_base + 0x0C, 4, elf->endianess);

	}
	else if(elf->bit_size == ENUM_BIT_SIZE_64) {
		program_header->physical_address = byte_arr_to_u64(elf->data+current_program_header_base + 0x18, 8, elf->endianess);
	}
}
void
program_header_check_file_size(elf_t* elf, program_header_t* program_header, uint64_t current_program_header_base) {
	if(elf->bit_size == ENUM_BIT_SIZE_32) {
		program_header->file_size = byte_arr_to_u64(elf->data+current_program_header_base + 0x10, 4, elf->endianess);

	}
	else if(elf->bit_size == ENUM_BIT_SIZE_64) {
		program_header->file_size = byte_arr_to_u64(elf->data+current_program_header_base + 0x20, 8, elf->endianess);
	}
}
void
program_header_check_memory_size(elf_t* elf, program_header_t* program_header, uint64_t current_program_header_base) {
	if(elf->bit_size == ENUM_BIT_SIZE_32) {
		program_header->memory_size = byte_arr_to_u64(elf->data+current_program_header_base + 0x14, 4, elf->endianess);

	}
	else if(elf->bit_size == ENUM_BIT_SIZE_64) {
		program_header->memory_size = byte_arr_to_u64(elf->data+current_program_header_base + 0x28, 8, elf->endianess);
	}
}
void
program_header_check_align(elf_t* elf, program_header_t* program_header, uint64_t current_program_header_base) {
	if(elf->bit_size == ENUM_BIT_SIZE_32) {
		program_header->align = byte_arr_to_u64(elf->data+current_program_header_base + 0x1C, 4, elf->endianess);
	}
	else if(elf->bit_size == ENUM_BIT_SIZE_64) {
		program_header->align = byte_arr_to_u64(elf->data+current_program_header_base + 0x30, 8, elf->endianess);
	}
}
void
program_header_check_flags(elf_t* elf, program_header_t* program_header, uint64_t current_program_header_base) {
	if(elf->bit_size == ENUM_BIT_SIZE_32) {
		program_header->flags = byte_arr_to_u64(elf->data+current_program_header_base + 0x18, 4, elf->endianess);
	}
	else if(elf->bit_size == ENUM_BIT_SIZE_64) {
		program_header->flags = byte_arr_to_u64(elf->data+current_program_header_base + 0x04, 4, elf->endianess);
	}
}
void
parse_program_headers(elf_t* elf) {
    program_header_t** program_headers = calloc(elf->num_prog_headers, sizeof(program_header_t*));
    for (uint64_t i = 0; i < elf->num_prog_headers; i++) {
        program_header_t* program_header = calloc(1, sizeof(program_header_t));
        program_headers[i] = program_header;
    }
    uint64_t program_header_base = elf->program_header_offset;
    for (uint64_t i = 0; i < elf->num_prog_headers; i++) {
        uint64_t current_prog_header_base = program_header_base + (elf->program_header_size * i);
        program_header_check_offset(elf, program_headers[i], current_prog_header_base);
        program_header_check_virtual_address(elf, program_headers[i], current_prog_header_base);
        program_header_check_physical_address(elf, program_headers[i], current_prog_header_base);
        program_header_check_memory_size(elf, program_headers[i], current_prog_header_base);
        program_header_check_file_size(elf, program_headers[i], current_prog_header_base);
        program_header_check_align(elf, program_headers[i], current_prog_header_base);
        program_header_check_flags(elf, program_headers[i], current_prog_header_base);          
    }
    elf->prog_headers = program_headers;
}

elf_t*
elf_create(char* path) {
	elf_t* elf = calloc(1, sizeof(elf_t));

	FILE* file_pointer = fopen(path, "rb");
	if (!file_pointer){
		printf("Could not open file/file NULL\n");
		abort();
	}

	fseek(file_pointer, 0, SEEK_END);
	elf->data_length = ftell(file_pointer);
	rewind(file_pointer);

	elf->data = calloc(elf->data_length, sizeof(uint8_t));
	if(!fread(elf->data, elf->data_length, 1, file_pointer)) {
		printf("Failed to read elf\n");
		abort();
	}
	fclose(file_pointer);

	check_endianess(elf);
	check_bitsize(elf);
	check_entry_point(elf);
	check_num_program_headers(elf);
	check_program_header_offset(elf);
	check_program_header_size(elf);
	parse_program_headers(elf);
	return elf;
}

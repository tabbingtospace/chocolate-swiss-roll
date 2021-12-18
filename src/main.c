#include <stdio.h>

#include "loader.h"

int
main(void){
	elf_t* elf = elf_create("/usr/bin/ls");
	printf("elf->endianess, %d \n",elf->endianess);
	printf("elf->bit_size, %d \n",elf->bit_size);
	printf("elf->entry_point 0x%lx \n",elf->entry_point);
	printf("elf->num_prog_headers, %ld \n",elf->num_prog_headers);
	printf("elf->program_header_offset, %ld \n",elf->program_header_offset);
	printf("elf->data_length, %ld \n",elf->data_length);
	printf("elf->program_header_size, %ld \n",elf->program_header_size);

	for (uint64_t i = 0; i < elf->num_prog_headers; i++)
	{
		printf("Prog header %lu offset, 0x%lx\n",i,elf->prog_headers[i]->offset);
		printf("Prog header %lu virual address, 0x%lx\n",i,elf->prog_headers[i]->virtual_address);
		printf("Prog header %lu physical address, 0x%lx\n",i,elf->prog_headers[i]->physical_address);
		printf("Prog header %lu file size, 0x%lx\n",i,elf->prog_headers[i]->file_size);
		printf("Prog header %lu memory size, 0x%lx\n",i,elf->prog_headers[i]->memory_size);
		printf("Prog header %lu align, 0x%lx\n",i,elf->prog_headers[i]->align);
		printf("Prog header %lu flags, 0x%lx\n",i,elf->prog_headers[i]->flags);
	}
	return 0;
}

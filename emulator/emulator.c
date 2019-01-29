#include<stdio.h>
unsigned char chip8_fontset[80] = {
		0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  		0x20, 0x60, 0x20, 0x20, 0x70, // 1
  		0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  		0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  		0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  		0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  		0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  		0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  		0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  		0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  		0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  		0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  		0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  		0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  		0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  		0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};
struct cpu
{
	unsigned short opcode;
	unsigned char memory[4096];
	unsigned char cpu_reg[16];
	unsigned short index_reg;
	unsigned short pc;
	unsigned char gfx[64*32];
	unsigned char delay_timer;
	unsigned char sound_timer;
	unsigned short stack[16];
	unsigned short stackp;
	unsigned char key[16];

};

void initialize();

int main(int argc, char **argv)
{
	struct cpu instance;

}

void initialize(struct cpu *instance)
{
	instance->pc = 0x200;
	instance->opcode = 0;
	instance->index_reg = 0;
	instance->stackp = 0;
	instance->delay_timer = 0;
	instance->sound_timer = 0;

	//load fontset
	for(int i = 0; i<80; i++)
	{
		instance->memory[i+0x50] = chip8_fontset[i];
	}
	//clear display
	for(int i = 0; i<2048; i++)
	{
		instance->gfx[i] = 0;
	}
	for(int i = 0; i<16; i++)
	{
		instance->stack[i]	= 0;
		instance->key[i] 		= 0;
		instance->cpu_reg[i] 	= 0;
	}
	for(int i = 0; i<4096; i++)
	{
		instance->memory[i] = 0;
	}
	
}

void emulate_cycle(struct cpu *p)
{	
	p->opcode = p->memory[p->pc] << 8 | p->memory[p->pc+1];

	switch(p->opcode & 0xF000)
	{
		case 0x0000:

			switch(p->opcode)
			{
				case 0x00E0:
					break;
				case 0x00EE:
					break;
			}
			break;
		case 0x1000:
			p->pc = p->opcode & 0x0FFF;
			break;
		case 0x2000:
			p->stack[(p->stackp++)&0xF] = p->pc;
			p->pc = p->opcode & 0x0FFF;
			break;
		case 0x3000:
			if(p->cpu_reg[(p->opcode & 0x0F00) >> 8] == p->opcode & 0x00FF)
			{
				p->pc += 4;
			}
			else
			{
				p->pc+= 2;
			}
		default: printf("Wrong op code \r\n");
	}
}

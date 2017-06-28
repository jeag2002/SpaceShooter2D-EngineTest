// This file came from Pickle's Wiz3D development pack. 
// I removed a lot of the SDL and keyboard related functionality.
// Thanks Pickle!
// Be sure to call WIZ_Init & WIZ_Close as appropriate

#include "wiz.h"

#ifndef WIN32

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>

#define TRUE	1
#define FALSE	0

/* GPIO */
#define GPIOAPAD		(memregs16[0xA018>>1])
#define GPIOBPAD		(memregs16[0xA058>>1])
#define GPIOCPAD		(memregs16[0xA098>>1])


int memfd;
volatile uint32_t *memregs32;
volatile uint16_t *memregs16;

static uint32_t prev_value;

void WIZ_Close( void )
{
	memregs16 = NULL;
	memregs32 = NULL;
	close(memfd);
	printf("WIZ controls closed!\n");
}

int WIZ_Init( void )
{
	/* open /dev/mem to access registers */
	memfd = open("/dev/mem", O_RDWR);
	if(memfd < 0) {
		printf("Could not open /dev/mem!\n");
		WIZ_Close();
		return 1;
	}

	/* get access to the registers */
	memregs32 = (volatile uint32_t*)mmap(0, 0x20000, PROT_READ|PROT_WRITE, MAP_SHARED, memfd, 0xC0000000);
	if(memregs32 == (volatile uint32_t*)0xFFFFFFFF) {
		printf("Could not mmap hardware registers!\n");
		WIZ_Close();
		return 1;
	}
	memregs16 = (volatile uint16_t*)memregs32;

	printf("WIZ controls opened!\n");
	return 0;
}

uint32_t getbuttons(void) {
	return ~((GPIOCPAD << 16) | GPIOBPAD);
}

bool HW_ButtonPushed(int Button)
{
  return getbuttons() & Button;
}

#endif
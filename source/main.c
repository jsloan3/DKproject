#include <unistd.h>
#include <stdio.h>
#include "gpio.h"
#include "uart.h"
#include "fb.h"
#include "dk.h"
#include "wall.h"

#define GPIO_BASE 0xFE200000

//#define GPSET0a 7 // 28/4
//#define GPCLR0a 10 // 40/4
//#define GPLEV0a 13
#define CLO_REG 0xFE003004

unsigned *clo = (unsigned*)CLO_REG;

static unsigned *gpio = (unsigned*)GPIO_BASE; // GPIO base

#define SIZEX 20
#define SIZEY 20
int SCREENOFFX = 300;
int SCREENOFFY = 300;
int currentlevel[SIZEX][SIZEY];


// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |= (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

#define CLK 11
#define LAT 9
#define DAT 10

void initSNES() {
	INP_GPIO( CLK ); // CLK
	OUT_GPIO( CLK );
	INP_GPIO( LAT ); // LATCH
	OUT_GPIO( LAT );
	INP_GPIO( DAT ); // DATA

}

void write_latch(int i){
	if (i == 1){
		// gpio[GPSET0] = 1 << LAT;
		(*GPSET0) = 1 << LAT;
	}
	else{
		// gpio[GPCLR0] = 1 << LAT;
		(*GPCLR0) = 1 << LAT;
	}
}

void write_clock(int i){
	if (i == 1){
		//gpio[GPSET0] = 1 << CLK;
		(*GPSET0) = 1 << CLK;
	}
	else{
		//gpio[GPCLR0] = 1 << CLK;
		(*GPCLR0) = 1 << CLK;
	}
}


int read_data(){
	int v;
	// v = (gpio[GPLEV0] >> DAT) & 1;
	v = ((*GPLEV0) >> DAT) & 1;
	return v;
}

void wait(int m){

	unsigned c = *clo + m; // micro Secs

	while (c > *clo);
}

/*
Initializing array of char* causes error that memcpy was undeclared,
here is an implementation of memcpy from 
`https://stackoverflow.com/questions/66809657/undefined-reference-to-memcpy-error-caused-by-ld`
I know what you're thinking:
"is it possible to learn this power?"
Not from a jedi...
*/
void *memcpy(void *dest, const void *src, size_t n) {
    for (size_t i = 0; i < n; i++)
    {
        ((char*)dest)[i] = ((char*)src)[i];
    }
}

// Uses UART I/O subroutines to print a message to the screen terminal.
// Message address is passed as an arg.
void print_message(char* message) {
		void printf(char *str) {
		uart_puts(str);
	}

	printf(message);

}

void renderscreen() {
	for (int i = 0; i < SIZEX; i++) {
		for (int j = 0; j < SIZEY; j++) {
			if (currentlevel[i][j] == 1) {
				myDrawImage(dk.pixel_data, dk.width, dk.height, (i*32 + SCREENOFFX), (j*32 + SCREENOFFY));
			}
		}
	}
}

void initialrender() {
	for (int i = 0; i < SIZEX; i++) {
		for (int j = 0; j < SIZEY; j++) {
			if (currentlevel[i][j] == 2) {
				myDrawImage(wall.pixel_data, wall.width, wall.height, (i*32 + SCREENOFFX), (j*32 + SCREENOFFY));
			}
		}
	}
}



int main() {

	initSNES();

	uart_init();
    fb_init();

	int dkx = 0;
	int dky = 0;

	for (int i = 0; i < SIZEX; i++) {
		for (int j = 0; j < SIZEY; j++) {
			currentlevel[i][j] = 0;
		}
	}

	currentlevel[10][10] = 2;
	currentlevel[11][10] = 2;
	currentlevel[10][11] = 2;
	currentlevel[11][11] = 2;

	int offx = 300;
	int offy = 300;

	print_message("Created by Aaron Tigley and Jaxon Sloan\n");
    
	// Array is 17 length, but index 0 isn't used.
	int buttons[17] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int prev_state[17]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int pressed = 0;

	initialrender();

	while (1) {
		write_clock(1);
		write_latch(1);
		wait(12);
		write_latch(0);

		// This loop uses wait() to set the clock and read the data on the falling edge.
		for(int i = 1; i <= 16; i++)
		{
			wait(6);
			write_clock(0); // falling edge
			wait(6);
			buttons[i] = read_data(); // read bit i
			
			write_clock(1); // rising edge; new cycle 
		}

		// If START is pressed, end our program.
		if(buttons[4] == 0){
			break;
		}

		
		for(int i = 1; i<=16; i++) {
			if((buttons[i] == 0) && (prev_state[i] == 1)){

				for (int i =0; i < dk.width; i++) {
					for (int j=0; j< dk.height; j++) {
						myDrawPixel(i + (32*dkx) + SCREENOFFX, j + (32*dky) + SCREENOFFY,0);
					}
				}

				// button 9 = A
				// button 4 = START

				// up
				if (buttons[5] == 0) {
					if (dky > 0) {
						if (currentlevel[dkx][dky - 1] != 2) {
							currentlevel[dkx][dky] = 0;
							dky -= 1;
							currentlevel[dkx][dky] = 1;
						}
					}
				}

				// down
				else if (buttons[6] == 0) {
					if (dky < 19) {
						if (currentlevel[dkx][dky + 1] != 2) {
							currentlevel[dkx][dky] = 0;
							dky += 1;
							currentlevel[dkx][dky] = 1;
						}
					}
				}

				// left
				else if (buttons[7] == 0) {
					if (dkx > 0) {
						if (currentlevel[dkx - 1][dky] != 2) {
							currentlevel[dkx][dky] = 0;
							dkx -= 1;
							currentlevel[dkx][dky] = 1;
						}
					}
				}

				// right
				else if (buttons[8] == 0) {
					if (dkx < 19) {
						if (currentlevel[dkx + 1][dky] != 2) {
							currentlevel[dkx][dky] = 0;
							dkx += 1;
							currentlevel[dkx][dky] = 1;
						}
					}
				}

				renderscreen();
			}

			// Set the previous state of the button to the state that was read in this current interation of the loop.
			prev_state[i] = buttons[i];
		}
	}
	return 0;
}


#include <unistd.h>
#include <stdio.h>
#include "gpio.h"
#include "uart.h"
#include "fb.h"
#include "dk.h"
#include "wall.h"
#include "snake.h"
#include "goal.h"

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
int dkx;
int dky;
int timerCount = 0;
int lives = 4;
int gameRunning = 1;


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
			if (currentlevel[i][j] == 21) {
				myDrawImage(goal.pixel_data, goal.width, goal.height, (i*32 + SCREENOFFX), (j*32 + SCREENOFFY));
			}
		}
	}
}

void reloadscreen() {
	for (int i = 0; i < SIZEX; i++) {
		for (int j = 0; j < SIZEY; j++) {
			if (currentlevel[i][j] == 0) {
				for (int x = 0; x < 32; x++) {
					for (int y = 0; y < 32; y++) {
						myDrawPixel(i*32 + x + SCREENOFFX, j*32 + y + SCREENOFFY, 0);
					}
				}
			}
		}
	}
}

void levelOne() {
	
	for(int i = 1; i < 18; i++){
		currentlevel[i][17] = 2;
		currentlevel[i][13] = 2;
		currentlevel[i][8] = 2;
		currentlevel[i][7] = 2;
		currentlevel[i][2] = 2;
	}

	for(int i = 2; i < 19; i++){
		currentlevel[i][15] = 2;
		currentlevel[i][11] = 2;
		currentlevel[i][10] = 2;
		currentlevel[i][5] = 2;
		currentlevel[i][4] = 2;
	}
	currentlevel[12][11] = 0;
	currentlevel[12][8] = 0;
	currentlevel[12][5] = 0;

	currentlevel[1][1] = 21;
}

void levelTwo(){
	for (int i = 1; i < SIZEX-1; i++) {
		for (int j = 1; j < SIZEY-1; j++) {
			currentlevel[i][j] = 2;
		}
	}
	
	// Hallway for spawn
	for (int i = 1; i < 19; i++){
		currentlevel[18][i] = 0;
	}

	// Stepping Stairs
	currentlevel[16][18] = 0;
	currentlevel[16][16] = 0;
	currentlevel[14][16] = 0;
	currentlevel[14][14] = 0;
	currentlevel[12][14] = 0;
	currentlevel[12][12] = 0;
	currentlevel[10][12] = 0;
	currentlevel[10][10] = 0;
	currentlevel[5][10] = 0;

	// 3x3 room
	for (int i = 6; i < 9; i++){
		currentlevel[9][i] = 0;
		currentlevel[10][i] = 0;
		currentlevel[11][i] = 0;
	}

	// Hallways
	for (int i = 3; i < 6; i++){
		currentlevel[10][i] = 0;
	}
	for (int i = 6; i < 10; i++){
		currentlevel[i][3] = 0;
	}
	for (int i = 4; i < 18; i++){
		currentlevel[6][i] = 0;
	}
	for (int i = 6; i < 11; i++){
		currentlevel[i][17] = 0;
	}
}

void levelThree(){
	for (int i = 1; i < SIZEX-1; i++) {
		for (int j = 1; j < SIZEY-1; j++) {
			currentlevel[i][j] = 2;
		}
	}

	currentlevel[9][8] = 0;
	currentlevel[9][9] = 0;
	currentlevel[9][10] = 0;

	for(int i = 10; i < 15; i++){
		currentlevel[8][i] = 0;
		currentlevel[10][i] = 0;
	}

	currentlevel[7][14] = 0;
	currentlevel[6][14] = 0;

	for(int i = 4; i < 15; i++){
		currentlevel[5][i] = 0;
		currentlevel[13][i] = 0;
	}

	for(int i = 6; i < 13; i++){
		currentlevel[i][4] = 0;
		currentlevel[i][5] = 0;
	}

	currentlevel[4][5] = 0;

	for(int i = 5; i < 19; i++){
		currentlevel[3][i] = 0;
	}

	for(int i = 4; i < 15; i++){
		currentlevel[i][16] = 0;
		currentlevel[i][17] = 0;
		currentlevel[i][18] = 0;
	}

	currentlevel[15][16] = 0;
	currentlevel[16][16] = 0;

	for(int i = 3; i < 17; i++){
		currentlevel[17][i] = 0;
	}
}

void levelFour(){
	for (int i = 1; i < 19; i++) {
		currentlevel[4][i] = 2;
		currentlevel[15][i] = 2;
	}

	for (int i = 6; i < 14; i++) {
		currentlevel[i][2] = 2;
		currentlevel[i][3] = 2;
	}

	for (int i = 6; i < 14; i++) {
		currentlevel[i][2] = 2;
		currentlevel[i][3] = 2;
	}

	for (int i = 5; i < 7; i++) {
		currentlevel[6][i] = 2;
		currentlevel[7][i] = 2;
		currentlevel[8][i] = 2;
		currentlevel[11][i] = 2;
		currentlevel[12][i] = 2;
		currentlevel[13][i] = 2;
	}
	currentlevel[8][7] = 2;
	currentlevel[11][7] = 2;

	currentlevel[5][8] = 2;
	currentlevel[6][8] = 2;
	currentlevel[7][8] = 2;
	currentlevel[8][8] = 2;
	currentlevel[11][8] = 2;
	currentlevel[12][8] = 2;
	currentlevel[13][8] = 2;
	currentlevel[14][8] = 2;

	for (int i = 11; i < 15; i++)
	{
		currentlevel[5][i] = 2;
		currentlevel[6][i] = 2;
		currentlevel[7][i] = 2;
		currentlevel[8][i] = 2;
		currentlevel[11][i] = 2;
		currentlevel[12][i] = 2;
		currentlevel[13][i] = 2;
		currentlevel[14][i] = 2;
	}
}

void snakeMover() {
	for (int i = 0; i < SIZEX; i++) {
		for (int j = 0; j < SIZEY; j++) {
			if ((currentlevel[i][j] == 7) && (i > 0) && (i < 19)) {
				if (currentlevel[i - 1][j] == 0) {
					currentlevel[i][j] = 0;
					currentlevel[i - 1][j] = 7;
					myDrawImage(snake.pixel_data, snake.width, snake.height, ((i-1)*32 + SCREENOFFX), (j*32 + SCREENOFFY));
					for (int x = 0; x < snake.width; x++) {
						for (int y= 0; y< snake.height; y++) {
							myDrawPixel(x + (32*i) + SCREENOFFX, y + (32*j) + SCREENOFFY,0);
						}
					}
				}
				
				if (currentlevel[i - 1][j] == 2) {
					currentlevel[i][j] = 8;
				}
				if (currentlevel[i - 1][j] == 1) {
					loseLife();
				}

			}
			if ((currentlevel[i][j] == 8) && (i > 0) && (i < 19)) {
				if (currentlevel[i + 1][j] == 0) {
					currentlevel[i][j] = 0;
					currentlevel[i + 1][j] = 8;
					myDrawImage(snake.pixel_data, snake.width, snake.height, ((i+1)*32 + SCREENOFFX), (j*32 + SCREENOFFY));
					for (int x = 0; x < snake.width; x++) {
						for (int y = 0; y < snake.height; y++) {
							myDrawPixel(x + (32*i) + SCREENOFFX, y + (32*j) + SCREENOFFY,0);
						}	
					}
				}

				if (currentlevel[i + 1][j] == 2) {
					currentlevel[i][j] = 7;
				}
				if (currentlevel[i + 1][j] == 1) {
					loseLife();
				}

				i++;
				i++;
				i++;
			}
		}
	}
	for (int i = 0; i < SIZEX; i++) {
		for (int j = 0; j < SIZEY; j++) {
			if (currentlevel[i][j] == 7) {
				myDrawImage(snake.pixel_data, snake.width, snake.height, (i*32 + SCREENOFFX), (j*32 + SCREENOFFY));
			}
			if (currentlevel[i][j] == 8) {
				myDrawImage(snake.pixel_data, snake.width, snake.height, (i*32 + SCREENOFFX), (j*32 + SCREENOFFY));
			}
		}
	}

}

void snakeMoverVert() {
	for (int i = 0; i < SIZEX; i++) {
		for (int j = 0; j < SIZEY; j++) {
			if ((currentlevel[i][j] == 11) && (i > 0) && (i < 19)) {
				if (currentlevel[i][j + 1] == 0) {
					currentlevel[i][j] = 0;
					currentlevel[i][j + 1] = 11;
					myDrawImage(snake.pixel_data, snake.width, snake.height, (i*32 + SCREENOFFX), ((j+1)*32 + SCREENOFFY));
					for (int x = 0; x < snake.width; x++) {
						for (int y= 0; y< snake.height; y++) {
							myDrawPixel(x + (32*i) + SCREENOFFX, y + (32*j) + SCREENOFFY,0);
						}
					}
				}
				
				if (currentlevel[i][j + 1] == 2) {
					currentlevel[i][j] = 12;
				}
				if (currentlevel[i][j + 1] == 1) {
					loseLife();
				}
				j++;
				j++;
				j++;
			}
			if ((currentlevel[i][j] == 12) && (i > 0) && (i < 19)) {
				if (currentlevel[i][j - 1] == 0) {
					currentlevel[i][j] = 0;
					currentlevel[i][j - 1] = 12;
					myDrawImage(snake.pixel_data, snake.width, snake.height, (i*32 + SCREENOFFX), ((j-1)*32 + SCREENOFFY));
					for (int x = 0; x < snake.width; x++) {
						for (int y = 0; y < snake.height; y++) {
							myDrawPixel(x + (32*i) + SCREENOFFX, y + (32*j) + SCREENOFFY,0);
						}	
					}
				}

				if (currentlevel[i][j - 1] == 2) {
					currentlevel[i][j] = 11;
				}
				if (currentlevel[i][j - 1] == 1) {
					loseLife();
				}

				
			}
		}
	}
	for (int i = 0; i < SIZEX; i++) {
		for (int j = 0; j < SIZEY; j++) {
			if (currentlevel[i][j] == 11) {
				myDrawImage(snake.pixel_data, snake.width, snake.height, (i*32 + SCREENOFFX), (j*32 + SCREENOFFY));
			}
			if (currentlevel[i][j] == 12) {
				myDrawImage(snake.pixel_data, snake.width, snake.height, (i*32 + SCREENOFFX), (j*32 + SCREENOFFY));
			}
		}
	}

}

void timer() {
	timerCount++;
	if (timerCount > 50) {
		snakeMover();
		snakeMoverVert();
		timerCount = 0;
	}
	return;
}

void restartLevel() {
	// fill out
	return;
}

loseGame() {

}

void loseLife() {
	if (lives >= 1) {
		lives--;
		restartLevel();
	}
	if (lives == 0) {
		loseGame();

	}
}

void nextLevel() {
	// to do
	return;
}

int main() {

	initSNES();

	uart_init();
    fb_init();

	for (int i = 0; i < SIZEX; i++) {
		for (int j = 0; j < SIZEY; j++) {
			currentlevel[i][j] = 0;
		}
	}

	for (int i = 0; i < SIZEX; i++)
	{
		currentlevel[i][0] = 2;
		currentlevel[i][19] = 2;
		currentlevel[0][i] = 2;
		currentlevel[19][i] = 2;
	}

	int dkx = 1;
	int dky = 18;
	levelOne();

	/*int dkx = 18;
	int dky = 1;
	levelTwo();*/
	
	/*int dkx = 9;
	int dky = 8;
	levelThree();*/

	/*int dkx = 9;
	int dky = 1;
	levelFour();*/

	int offx = 300;
	int offy = 300;

	print_message("Created by Aaron Tigley and Jaxon Sloan\n");
    
	// Array is 17 length, but index 0 isn't used.
	int buttons[17] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int prev_state[17]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int pressed = 0;

	reloadscreen();
	initialrender();
	renderscreen();
	renderscreen();
	renderscreen();
	renderscreen();
	renderscreen();
	renderscreen();
	renderscreen();
	

	while (gameRunning == 1) {
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

		timer();

		// If START is pressed, end our program.
		if(buttons[4] == 0){
			break;
		}

		renderscreen();
		
		for(int i = 1; i<=16; i++) {
			if((buttons[i] == 0) && (prev_state[i] == 1)){

				for (int i = 0; i < dk.width; i++) {
					for (int j= 0; j< dk.height; j++) {
						myDrawPixel(i + (32*dkx) + SCREENOFFX, j + (32*dky) + SCREENOFFY,0);
					}
				}

				// button 9 = A
				// button 4 = START

				// up
				if (buttons[5] == 0) {
					if (dky > 0) {

						if ((currentlevel[dkx][dky - 1] == 21)) {
							nextLevel();
						}
						
						else if ((currentlevel[dkx][dky - 1] != 2) && (currentlevel[dkx][dky - 1] != 11) 
						&& (currentlevel[dkx][dky - 1] != 12) && (currentlevel[dkx][dky - 1] != 7) && (currentlevel[dkx][dky - 1] != 8)) {
							currentlevel[dkx][dky] = 0;
							dky -= 1;
							currentlevel[dkx][dky] = 1;
						}

						
						
					}
				}

				// down
				else if (buttons[6] == 0 && (currentlevel[dkx][dky + 1] != 11) 
						&& (currentlevel[dkx][dky + 1] != 12) && (currentlevel[dkx][dky + 1] != 7) && (currentlevel[dkx][dky + 1] != 8)) {
					if (dky < 19) {

						if ((currentlevel[dkx][dky + 1] == 21)) {
							nextLevel();
						}

						else if (currentlevel[dkx][dky + 1] != 2) {
							currentlevel[dkx][dky] = 0;
							dky += 1;
							currentlevel[dkx][dky] = 1;
						}
						
					}
				}

				// left
				else if (buttons[7] == 0 && (currentlevel[dkx - 1][dky] != 11) 
						&& (currentlevel[dkx - 1][dky] != 12) && (currentlevel[dkx - 1][dky] != 7) && (currentlevel[dkx - 1][dky] != 8)) {
					if (dkx > 0) {
						
						if ((currentlevel[dkx - 1][dky] == 21)) {
							nextLevel();
						}
						
						else if (currentlevel[dkx - 1][dky] != 2) {
							currentlevel[dkx][dky] = 0;
							dkx -= 1;
							currentlevel[dkx][dky] = 1;
						}

						
					}
				}

				// right
				else if (buttons[8] == 0 && (currentlevel[dkx + 1][dky] != 11) 
						&& (currentlevel[dkx + 1][dky] != 12) && (currentlevel[dkx + 1][dky] != 7) && (currentlevel[dkx + 1][dky] != 8)) {
					if (dkx < 19) {

						if ((currentlevel[dkx + 1][dky] == 21)) {
							nextLevel();
						}

						else if (currentlevel[dkx + 1][dky] != 2) {
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


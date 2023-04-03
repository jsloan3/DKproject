#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "gpio.h"
#include "uart.h"
#include "fb.h"
#include "dk.h"
#include "wall.h"
#include "snake.h"
#include "goal.h"
#include "heart.h"
#include "hammer.h"
#include "coin.h"
#include "star.h"
#include "key.h"
#include "door.h"

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
int level = 1;
int dkx;
int dky;
int goal_x;
int goal_y;
int timerCount = 0;
int gameTimeTicker = 0;
int lives = 4;
int gameRunning = 1;
int score = 1;
int paused = 0;
int menuOption = 0;
int hasHammer = 0;
int hasStar = 0;

int timeInt = 90;
char timeChar[20] = "TIME: ";
char intChar[20];
char scoreChar[20];
char livesChar[20];

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
			if (currentlevel[i][j] == 30) {
				myDrawImage(heart.pixel_data, heart.width, heart.height, (i*32 + SCREENOFFX), (j*32 + SCREENOFFY));
			}
			if (currentlevel[i][j] == 35) {
				myDrawImage(hammer.pixel_data, hammer.width, hammer.height, (i*32 + SCREENOFFX), (j*32 + SCREENOFFY));
			}
			if (currentlevel[i][j] == 40) {
				myDrawImage(coin.pixel_data, coin.width, coin.height, (i*32 + SCREENOFFX), (j*32 + SCREENOFFY));
			}
			if (currentlevel[i][j] == 52) {
				myDrawImage(star.pixel_data, star.width, star.height, (i*32 + SCREENOFFX), (j*32 + SCREENOFFY));
			}
			if (currentlevel[i][j] == 60) {
				myDrawImage(key.pixel_data, key.width, key.height, (i*32 + SCREENOFFX), (j*32 + SCREENOFFY));
			}
			if (currentlevel[i][j] == 62) {
				myDrawImage(door.pixel_data, door.width, door.height, (i*32 + SCREENOFFX), (j*32 + SCREENOFFY));
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

void levelOne(int *dkx, int *dky, int *goal_x, int *goal_y) {
	
	*dkx = 1;
	*dky = 18;
	*goal_x = 1;
	*goal_y = 1;
	timeInt = 90;

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

	currentlevel[2][1] = 8;
	currentlevel[18][6] = 7;
	currentlevel[1][9] = 8;
	currentlevel[18][12] = 7;

	currentlevel[12][11] = 30;

	currentlevel[12][5] = 40;

	currentlevel[5][18] = 60;
	currentlevel[10][18] = 62;

	currentlevel[18][2] = 52;

	currentlevel[1][1] = 21;
	
}

void levelTwo(int *dkx, int *dky, int *goal_x, int *goal_y){

	*dkx = 18;
	*dky = 1;
	*goal_x = 10;
	*goal_y = 17;
	timeInt = 90;

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

	// Snake
	currentlevel[6][17] = 12;

	// Goal
	currentlevel[10][17] = 21;
}

void levelThree(int *dkx,int *dky, int *goal_x, int *goal_y){

	*dkx = 9;
	*dky = 8;
	*goal_x = 17;
	*goal_y = 3;
	timeInt = 90;

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

	// Snakes
	currentlevel[5][4] = 8;
	currentlevel[13][5] = 7;

	currentlevel[17][4] = 7;
	currentlevel[17][5] = 7;
	currentlevel[17][6] = 7;
	currentlevel[17][7] = 7;
	currentlevel[17][8] = 7;
	currentlevel[17][9] = 7;

	currentlevel[3][16] = 8;
	currentlevel[14][17] = 7;
	currentlevel[3][18] = 8;

	// Goal
	currentlevel[17][3] = 21;
}

void levelFour(int *dkx, int *dky, int *goal_x, int *goal_y){

	*dkx = 9;
	*dky = 1;
	*goal_x = 10;
	*goal_y = 18;
	timeInt = 90;


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

	// Snakes
	currentlevel[1][1] = 8;
	currentlevel[2][2] = 8;
	currentlevel[3][3] = 8;

	currentlevel[18][1] = 7;
	currentlevel[17][2] = 7;
	currentlevel[16][3] = 7;

	currentlevel[1][16] = 7;
	currentlevel[3][18] = 8;

	currentlevel[16][16] = 8;
	currentlevel[18][18] = 7;

	// Goal
	currentlevel[10][18] = 21;
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
				
				if ((currentlevel[i - 1][j] == 2) || (currentlevel[i - 1][j] == 21)) {
					currentlevel[i][j] = 8;
				}
				if (currentlevel[i - 1][j] == 1) {
					if (hasStar == 0) {
						loseLife();
					}
					for (int x = 0; x < snake.width; x++) {
						for (int y = 0; y < snake.height; y++) {
							myDrawPixel(x + (32*i) + SCREENOFFX, y + (32*j) + SCREENOFFY,0);
						}	
					}
					currentlevel[i][j] = 0;
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

				if ((currentlevel[i + 1][j] == 2) || (currentlevel[i + 1][j] == 21)) {
					currentlevel[i][j] = 7;
				}
				if (currentlevel[i + 1][j] == 1) {
					if (hasStar == 0) {
						loseLife();
					}
					for (int x = 0; x < snake.width; x++) {
						for (int y = 0; y < snake.height; y++) {
							myDrawPixel(x + (32*i) + SCREENOFFX, y + (32*j) + SCREENOFFY,0);
						}	
					}
					currentlevel[i][j] = 0;
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
					if (hasStar == 0) {
						loseLife();
					}
					for (int x = 0; x < snake.width; x++) {
						for (int y = 0; y < snake.height; y++) {
							myDrawPixel(x + (32*i) + SCREENOFFX, y + (32*j) + SCREENOFFY,0);
						}	
					}
					currentlevel[i][j] = 0;
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
					if (hasStar == 0) {
						loseLife();
					}
					for (int x = 0; x < snake.width; x++) {
						for (int y = 0; y < snake.height; y++) {
							myDrawPixel(x + (32*i) + SCREENOFFX, y + (32*j) + SCREENOFFY,0);
						}	
					}
					currentlevel[i][j] = 0;
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

void clearLevel() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			currentlevel[i][j] = 0;
		}
	}
	for (int i = 0; i < 20; i++) {
		currentlevel[i][0] = 2;
		currentlevel[0][i] = 2;
		currentlevel[19][i] = 2;
		currentlevel[i][19] = 2;
	}
}

void timeToChar() {
	int firstInt = timeInt / 10;
	int secondInt = timeInt % 10;

	char firstChar = firstInt + '0';
	char secondChar = secondInt + '0';

	intChar[0] = firstChar;
	intChar[1] = secondChar;
	intChar[2] = '\0';

}


void timer() {
	timerCount++;
	gameTimeTicker++;
	if (timerCount > 1000) {
		snakeMover();
		snakeMoverVert();
		timerCount = 0;
	}
	if (gameTimeTicker > 3000) {
		if (timeInt > 0) {
			timeInt--;
			timeToChar();
			drawString(SCREENOFFX, SCREENOFFY - 15, "TIME: ", 60);
			drawString(SCREENOFFX + 38, SCREENOFFY - 15, intChar, 100);
			

			char firstScoreChar = score + '0';
			scoreChar[0] = firstScoreChar;
			scoreChar[1] = '\0';
			drawString(SCREENOFFX + 100, SCREENOFFY - 15, "SCORE: ", 60);
			drawString(SCREENOFFX + 150, SCREENOFFY - 15, scoreChar, 100);

			char firstLivesChar = lives + '0';
			livesChar[0] = firstLivesChar;
			livesChar[1] = '\0';
			drawString(SCREENOFFX + 200, SCREENOFFY - 15, "LIVES: ", 60);
			drawString(SCREENOFFX + 250, SCREENOFFY - 15, livesChar, 100);
			
			
			gameTimeTicker = 0;
		}
	}
	return;
}

void loadMenu() {
	for (int i = 0; i < (6*32); i++) {
		for (int j = 0; j < (6*32); j++) {
			myDrawPixel(i + SCREENOFFX + (7*32), j + SCREENOFFY + (7*32), 0);
		}

		
		myDrawPixel(i + SCREENOFFX + (7*32), SCREENOFFY + (7*32), 100);
		myDrawPixel(i + SCREENOFFX + (7*32), SCREENOFFY + (7*32) + (6*32), 100);
		myDrawPixel(SCREENOFFX + (7*32), i + SCREENOFFY + (7*32), 100);
		myDrawPixel(SCREENOFFX + (7*32) + (6*32), i + SCREENOFFY + (7*32), 100);

		myDrawPixel(i + SCREENOFFX + (7*32) + 1, SCREENOFFY + (7*32) + 1, 100);
		myDrawPixel(i + SCREENOFFX + (7*32) + 1, SCREENOFFY + (7*32) + (6*32) + 1, 100);
		myDrawPixel(SCREENOFFX + (7*32) + 1, i + SCREENOFFY + (7*32) + 1, 100);
		myDrawPixel(SCREENOFFX + (7*32) + (6*32) + 1, i + SCREENOFFY + (7*32) + 1, 100);

		myDrawPixel(i + SCREENOFFX + (7*32) + 2, SCREENOFFY + (7*32) + 2, 100);
		myDrawPixel(i + SCREENOFFX + (7*32) + 2, SCREENOFFY + (7*32) + (6*32) + 2, 100);
		myDrawPixel(SCREENOFFX + (7*32) + 2, i + SCREENOFFY + (7*32) + 2, 100);
		myDrawPixel(SCREENOFFX + (7*32) + (6*32) + 2, i + SCREENOFFY + (7*32) + 2, 100);
	}

	drawString(SCREENOFFX + (10*32) - 25, SCREENOFFY + (10*32) + 25, "QUIT", 150);
	drawString(SCREENOFFX + (10*32) - 25, SCREENOFFY + (10*32) - 25, "RESTART GAME", 150);

	menuOption = 0;

	for (int h = 0; h < 10; h++) {
		for (int k = 0; k < 10; k++) {
			myDrawPixel(SCREENOFFX + (10 * 32) - 60 + h, SCREENOFFY + (10*32) - 25 + k, 200);
		}
	}
		

	return;
}

void restartLevel() {
	clearLevel;
	clearscreen();
	if(level == 0){
		loadMenu();
	}
	if(level == 1){
		levelOne(&dkx, &dky, &goal_x, &goal_y);
	}
	if(level == 2){
		levelTwo(&dkx, &dky, &goal_x, &goal_y);
	}
	else if(level == 3){
		levelThree(&dkx, &dky, &goal_x, &goal_y);
	}
	else if(level == 4){
		levelFour(&dkx, &dky, &goal_x, &goal_y);
	}
	currentlevel[dkx][dky] = 1;
	return;
}

void loseGame() {
	return;
}

void loseLife() {
	if (lives >= 1) {
		lives--;
	}
	if (lives == 0) {
		loseGame();
	}
}

void clearscreen() {
	for (int i = 0; i < 800; i++) {
					for (int j = 0; j < 800; j++) {
						myDrawPixel(i + SCREENOFFX - 100, j + SCREENOFFY - 100, 0);
					}
				}
	return;
}

void pauseGame() {

}

void nextLevel(int *level) {
	clearLevel();
	*level += 1;
	//*level = 3;
	if(*level == 2){
		levelTwo(&dkx, &dky, &goal_x, &goal_y);
	}
	else if(*level == 3){
		levelThree(&dkx, &dky, &goal_x, &goal_y);
	}
	else if(*level == 4){
		levelFour(&dkx, &dky, &goal_x, &goal_y);
	}
	reloadscreen();
	initialrender();
}

void keyUp() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (currentlevel[i][j] == 62) {
				currentlevel[i][j] = 0;
				for (int x = 0; x < door.width; x++) {
						for (int y = 0; y < door.height; y++) {
							myDrawPixel(x + (32*i) + SCREENOFFX, y + (32*j) + SCREENOFFY,0);
						}	
				}
			}
		}
	}
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
	

	restart:

	clearscreen();
	clearLevel();
	restartLevel();

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

		if (paused == 0) {
			timer();
		}
		

		
		for(int i = 1; i<=16; i++) {
			if((buttons[i] == 0) && (prev_state[i] == 1)){	

				for (int i = 0; i < dk.width; i++) {
					for (int j= 0; j< dk.height; j++) {
						myDrawPixel(i + (32*dkx) + SCREENOFFX, j + (32*dky) + SCREENOFFY,0);
					}
				}

				if(buttons[4] == 0){
					if (paused == 0) {
						paused = 1;
						loadMenu();
					} else {
						paused = 0;
						clearscreen();
						initialrender();
						renderscreen();
					}
				}

				// button 9 = A
				// button 4 = START

				// up

				if (paused == 0) {
					if (buttons[5] == 0) {
						if (dky > 0) {
							
							
							if ((currentlevel[dkx][dky - 1] == 2) && hasHammer == 1) {
								currentlevel[dkx][dky - 1] = 0;
								hasHammer = 0;
							}

							if (currentlevel[dkx][dky - 1] == 30) {
								lives += 1;
							}

							if (currentlevel[dkx][dky - 1] == 60) {
								keyUp();
							}

							if (currentlevel[dkx][dky - 1] == 52) {
								hasStar = 1;
							}

							if (currentlevel[dkx][dky - 1] == 40) {
								score += 1;
							}

							if (currentlevel[dkx][dky - 1] == 35) {
								hasHammer = 1;
							}

							if ((dkx == goal_x) && (dky == goal_y))  {
								nextLevel(&level);
							}
							/*if ((currentlevel[dkx][dky - 1] == 21)) {
								nextLevel(&level);
							}*/

							else if ((currentlevel[dkx][dky - 1] != 2) && (currentlevel[dkx][dky - 1] != 11) 
							&& (currentlevel[dkx][dky - 1] != 12) && (currentlevel[dkx][dky - 1] != 7) && (currentlevel[dkx][dky - 1] != 8) && (currentlevel[dkx][dky - 1] != 62)) {
								currentlevel[dkx][dky] = 0;
								dky -= 1;
								currentlevel[dkx][dky] = 1;
							}
						}
					}

					// down
					else if (buttons[6] == 0) {
						if (dky < 19) {
							
							if ((currentlevel[dkx][dky + 1] == 2) && hasHammer == 1) {
								currentlevel[dkx][dky + 1] = 0;
								hasHammer = 0;
							}

							if (currentlevel[dkx][dky + 1] == 30) {
								lives += 1;
							}

							if (currentlevel[dkx][dky + 1] == 60) {
								keyUp();
							}

							if (currentlevel[dkx][dky + 1] == 52) {
								hasStar = 1;
							}

							if (currentlevel[dkx][dky + 1] == 40) {
								score += 1;
							}

							if (currentlevel[dkx][dky + 1] == 35) {
								hasHammer = 1;
							}

							if ((dkx == goal_x) && (dky == goal_y))  {
								nextLevel(&level);
							}
							/*if ((currentlevel[dkx][dky + 1] == 21)) {
								nextLevel(&level);
							}*/

							else if ((currentlevel[dkx][dky + 1] != 2)  && (currentlevel[dkx][dky + 1] != 11) 
							&& (currentlevel[dkx][dky + 1] != 12) && (currentlevel[dkx][dky + 1] != 7) && (currentlevel[dkx][dky + 1] != 8) && (currentlevel[dkx][dky + 1] != 62)) {
								currentlevel[dkx][dky] = 0;
								dky += 1;
								currentlevel[dkx][dky] = 1;
							}
							
						}
					}

					// left
					else if (buttons[7] == 0) {
						if (dkx > 0) {
							
							if ((currentlevel[dkx - 1][dky] == 2) && hasHammer == 1) {
								currentlevel[dkx - 1][dky] = 0;
								hasHammer = 0;
							}

							if ((currentlevel[dkx - 1][dky] == 8) && (hasStar == 1)) {
								currentlevel[dkx - 1][dky] = 0;
							}

							if (currentlevel[dkx - 1][dky] == 30) {
								lives += 1;
							}

							if (currentlevel[dkx - 1][dky] == 60) {
								keyUp();
							}

							if (currentlevel[dkx - 1][dky] == 52) {
								hasStar = 1;
							}

							if (currentlevel[dkx - 1][dky] == 40) {
								score += 1;
							}

							if (currentlevel[dkx - 1][dky] == 35) {
								hasHammer = 1;
							}

							if ((dkx == goal_x) && (dky == goal_y))  {
								nextLevel(&level);
							}
							/*if ((currentlevel[dkx - 1][dky] == 21)) {
								nextLevel(&level);
							}*/
							
							else if ((currentlevel[dkx - 1][dky] != 2) && (currentlevel[dkx - 1][dky] != 11) 
							&& (currentlevel[dkx - 1][dky] != 12) && (currentlevel[dkx - 1][dky] != 7) && (currentlevel[dkx - 1][dky] != 8) && (currentlevel[dkx - 1][dky] != 62)) {
								currentlevel[dkx][dky] = 0;
								dkx -= 1;
								currentlevel[dkx][dky] = 1;
							}

							
						}
					}

					// right
					else if (buttons[8] == 0) {
						if (dkx < 19) {
							
							if ((currentlevel[dkx + 1][dky] == 2) && hasHammer == 1) {
								currentlevel[dkx + 1][dky] = 0;
								hasHammer = 0;
							}

							if (currentlevel[dkx + 1][dky] == 30) {
								lives += 1;
							}

							if (currentlevel[dkx + 1][dky] == 60) {
								keyUp();
							}

							if (currentlevel[dkx + 1][dky] == 52) {
								hasStar = 1;
							}

							if (currentlevel[dkx + 1][dky] == 40) {
								score += 1;
							}

							if (currentlevel[dkx + 1][dky] == 35) {
								hasHammer = 1;
							}

							if ((dkx == goal_x) && (dky == goal_y))  {
								nextLevel(&level);
							}
							/*if ((currentlevel[dkx + 1][dky] == 21)) {
								nextLevel(&level);
							}*/

							else if ((currentlevel[dkx + 1][dky] != 2) && (currentlevel[dkx + 1][dky] != 11) 
							&& (currentlevel[dkx + 1][dky] != 12) && (currentlevel[dkx + 1][dky] != 7) && (currentlevel[dkx + 1][dky] != 8) && (currentlevel[dkx + 1][dky] != 62)) {
								currentlevel[dkx][dky] = 0;
								dkx += 1;
								currentlevel[dkx][dky] = 1;
							}

						}
					}
					renderscreen();
				} else if (paused == 1) {

					if (buttons[5] == 0) {
						menuOption = 0;
						for (int h = 0; h < 10; h++) {
							for (int k = 0; k < 10; k++) {
								myDrawPixel(SCREENOFFX + (10 * 32) - 60 + h, SCREENOFFY + (10*32) + 25 + k, 0);
								myDrawPixel(SCREENOFFX + (10 * 32) - 60 + h, SCREENOFFY + (10*32) - 25 + k, 200);
							}
						}
					} else if (buttons[6] == 0) {
						menuOption = 1;
						for (int h = 0; h < 10; h++) {
							for (int k = 0; k < 10; k++) {
								myDrawPixel(SCREENOFFX + (10 * 32) - 60 + h, SCREENOFFY + (10*32) - 25 + k, 0);
								myDrawPixel(SCREENOFFX + (10 * 32) - 60 + h, SCREENOFFY + (10*32) + 25 + k, 200);
							}
						}
					}

				}
				

				
			}

			// Set the previous state of the button to the state that was read in this current interation of the loop.
			prev_state[i] = buttons[i];
		}
	}
	return 0;
}


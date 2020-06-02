#include "Header.h"
void backField(short field[HEIGHT][WIDTH]) {
	for (short i = 0; i < HEIGHT; i++) {
		for (short j = 0; j < WIDTH; j++) {
			field[i][j] = 0;
		}
	}
	for (short i = 1, k = HEIGHT - BARRIER + 1; i < BARRIER, k < HEIGHT; i++, k++) { // верхние, нижние границы поля
		for (short j = 0;  j < WIDTH; j++) {
			field[i][j] = 1;
			field[k][j] = 1;
		}
	}
	for (short i = 0; i < HEIGHT; i++) { // боковые границы поля
		for (short j = 0, k = WIDTH - BARRIER; j < BARRIER - 1, k < WIDTH - 1; j++, k++) {
			field[i][j] = 1;
			field[i][k] = 1;
		}
	}
}

void backSnake(short field[HEIGHT][WIDTH], COORD snakeCoords) {
	for (int i = snakeCoords.X; i < snakeCoords.X + 20; i++) {
		for (int j = snakeCoords.Y; j < snakeCoords.Y + 20; j++) {
			field[j][i] = 1;
		}
	}
}
void backApple(short field[HEIGHT][WIDTH], COORD appleCoords) {
	for (int i = appleCoords.X; i < appleCoords.X + 20; i++) {
		for (int j = appleCoords.Y; j < appleCoords.Y + 20; j++) {
			field[j][i] = 2;
		}
	}
}

void backNull(short field[HEIGHT][WIDTH], COORD coord) {
	for (int i = coord.X; i < coord.X + 20; i++) {
		for (int j = coord.Y; j < coord.Y + 20; j++) {
			field[j][i] = 0;
		}
	}
}

COORD headPerimCoord(COORD headCoord, COORD headCoords[80]) {
	headCoords[0].X = headCoord.X;
	headCoords[0].Y = headCoord.Y;
	for (int i = 1; i < 20; i++) {
		headCoords[i].X = headCoords[i - 1].X + 1;
		headCoords[i].Y = headCoord.Y;
	}
	for (int i = 20; i < 40; i++) {
		headCoords[i].X = headCoords[i - 1].X;
		headCoords[i].Y = headCoords[i - 1].Y + 1;
	}
	for (int i = 40; i < 60; i++) {
		headCoords[i].X = headCoords[i - 1].X - 1;
		headCoords[i].Y = headCoords[i - 1].Y;
	}
	for (int i = 60; i < 80; i++) {
		headCoords[i].X = headCoords[i - 1].X;
		headCoords[i].Y = headCoords[i - 1].Y - 1;
	}
	return headCoords[80];
}

COORD* snakeMove(COORD headCoords[80], COORD *snakeCoords, short field[HEIGHT][WIDTH], short &snakeSize, short turnHead, bool &gameOver, bool &breakfast) {
		for (short i = snakeSize - 1; i > 0; i--) {
			snakeCoords[i] = snakeCoords[i - 1];
		}
		switch (turnHead) {
		case 0: {
			snakeCoords[0].Y -= 15;
			for (short cnt = 0; cnt < 80; cnt++) {
				if (field[headCoords[cnt].Y - 1][headCoords[cnt].X] == 1) {
					breakfast = true; gameOver = true;
					break;
				}
				if (field[headCoords[cnt].Y - 1][headCoords[cnt].X] == 2) {
					breakfast = true;
					snakeCoords = resize(snakeCoords, snakeSize, snakeSize + 1, 0);
					snakeCoords[snakeSize - 1] = { 0,0 };
					break;
				}
			}
			break;
		}
		case 1: {
			snakeCoords[0].X += 15;
			for (short cnt = 0; cnt < 80; cnt++) {
				if (field[headCoords[cnt].Y][headCoords[cnt].X + 1] == 1) {
					breakfast = true; gameOver = true;
					break;
				}
				if (field[headCoords[cnt].Y][headCoords[cnt].X + 1] == 2) {
					breakfast = true; 
					snakeCoords = resize(snakeCoords, snakeSize, snakeSize + 1, 0);
					snakeCoords[snakeSize - 1] = { 0,0 };
					break;
				}
			}
			break;
		}
		case 2: {
			snakeCoords[0].Y += 15;
			for (short cnt = 0; cnt < 80; cnt++) {
				if (field[headCoords[cnt].Y + 1][headCoords[cnt].X] == 1) {
					breakfast = true; gameOver = true;
					break;
				}
				if (field[headCoords[cnt].Y + 1][headCoords[cnt].X] == 2) {
					breakfast = true;
					snakeCoords = resize(snakeCoords, snakeSize, snakeSize + 1, 0);
					snakeCoords[snakeSize - 1] = { 0,0 };
					break;
				}
			}
			break;
		}
		case 3: {
			snakeCoords[0].X -= 15;
			for (short cnt = 0; cnt < 80; cnt++) {
				if (field[headCoords[cnt].Y][headCoords[cnt].X - 1] == 1) {
					breakfast = true; gameOver = true;
					break;
				}
				if (field[headCoords[cnt].Y][headCoords[cnt].X - 1] == 2) {
					breakfast = true;
					snakeCoords = resize(snakeCoords, snakeSize, snakeSize + 1, 0);
					snakeCoords[snakeSize - 1] = { 0,0 };
					break;
				}
			}
			break;
		}
		}
	return snakeCoords;
}
COORD* resize(COORD *snakeCoords, short &snakeSize, short newSnakeSize, double long num)
{
	COORD* tempSnakeCoords;
	tempSnakeCoords = new COORD[newSnakeSize];
	short k = 0, min = snakeSize;
	for (int i = 0; i < min; i++) 
		if (i != num - 1) {
			tempSnakeCoords[k].X = snakeCoords[i].X;
			tempSnakeCoords[k++].Y = snakeCoords[i].Y;
		}
	snakeSize = newSnakeSize;
	delete[] snakeCoords;
	return tempSnakeCoords;
}
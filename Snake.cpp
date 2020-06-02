#include "Header.h"

int main()
{
	system("title ЗМЕЙКА");
	system("mode con cols=110 lines=33");
	srand(time(NULL));
	showcursor(false);
	bool work = true;
	short counter = 0;
	while (work) {
		HWND screen = GetConsoleWindow();
		HDC hdc = GetDC(screen);
		RECT rect1 = { 0,0,WIDTH, HEIGHT };
		RECT rect2 = { WIDTH, 0, WIDTH + 200, HEIGHT };
		short snakeSize = 5, key = 1, turnHead = 0, updateField = 0, tempSnakeSize = 5, record = 0, result = 0;
		short field[HEIGHT][WIDTH];
		COORD *snakeCoords = new COORD[snakeSize];
		COORD *tempSnakeCoords = new COORD[snakeSize];
		COORD headCoords[80] = { 0, 0 };
		COORD apple = { 0,0 };
		bool gameOver = false, breakfast = false, start = false;
		init(record);
		backField(field);
		for (short i = 0; i < snakeSize; i++) {
			snakeCoords[i] = { (WIDTH / 2), (HEIGHT / 2) + i * 15 };
			tempSnakeCoords[i] = { (WIDTH / 2), (HEIGHT / 2) + i * 15 };
		}
		if (counter == 0) {
			pauseStart(screen, rect1, rect2, hdc, updateField, result, record, start, work, gameOver, breakfast);
		}
		counter = 0;
		while (!gameOver) {
			backNull(field, apple);
			apple = { rand() % (WIDTH - (3 * BARRIER)) + BARRIER, rand() % (HEIGHT - (3 * BARRIER)) + BARRIER };
			breakfast = false;
			while (!breakfast) {
				paintField(hdc);
				paintMenu(hdc, result, record);
				if (updateField < 50) {
					paintPause(hdc);
				}
				else {
					paintExit(hdc);
				}
				updateField++;
				if (updateField == 100) {
					InvalidateRect(screen, &rect1, TRUE);
					InvalidateRect(screen, &rect2, TRUE);
					updateField = 0;
				}
				for (short i = 2; i < snakeSize; i++) {
					backNull(field, tempSnakeCoords[i]);
					backSnake(field, snakeCoords[i]);
					tempSnakeCoords[i] = snakeCoords[i];
				}
				if (field[apple.Y][apple.X] != 1) {
					backApple(field, apple);
					paintApple(hdc, apple);
				}
				else {
					apple = { rand() % (WIDTH - (3 * BARRIER)) + BARRIER, rand() % (HEIGHT - (3 * BARRIER)) + BARRIER };
				}
				for (short i = snakeSize - 1; i >= 0; i--) {
					paintBody(hdc, snakeCoords[i]);
					if (i == 0) {
						paintHead(hdc, snakeCoords[i], turnHead);
					}
				}
				if (_kbhit()) {
					key = _getch();
					switch (key) {
					case KEY_LEFT: {
						if (turnHead != 1) {
							turnHead = 3;
							snakeCoords[0].X -= 7;
						}
						break;
					}
					case KEY_RIGHT: {
						if (turnHead != 3) {
							turnHead = 1;
							snakeCoords[0].X += 7;
						}
						break;
					}
					case KEY_DOWN: {
						if (turnHead != 0) {
							turnHead = 2;
							snakeCoords[0].Y += 7;
						}
						break;
					}
					case KEY_UP: {
						if (turnHead != 2) {
							turnHead = 0;
							snakeCoords[0].Y -= 7;
						}
						break;
					}
					case KEY_SPACE: {
						pauseStart(screen, rect1, rect2, hdc, updateField, result, record, start, work, gameOver, breakfast);
						break;
					}
					case KEY_ESCAPE: {
						breakfast = true; gameOver = true;
						break;
					}
					default: continue;
					}
				}
				headCoords[80] = headPerimCoord(snakeCoords[0], headCoords);
				snakeCoords = snakeMove(headCoords, snakeCoords, field, snakeSize, turnHead, gameOver, breakfast);
				if (snakeSize > tempSnakeSize) {
					tempSnakeCoords = resize(tempSnakeCoords, tempSnakeSize, tempSnakeSize + 1, 0);
					tempSnakeCoords[tempSnakeSize - 1] = { 0, 0 };
				}
				Sleep(150);
			}
			if (gameOver == true) {
				save(record, result);
			}
			else {
				result++;
			}
		}
		counter++;
		if (counter == 1) {
			pauseStart(screen, rect1, rect2, hdc, updateField, result, record, start, work, gameOver, breakfast);
		}
		else {
			counter = 0;
		}
	}
	return 0;
}


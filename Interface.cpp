#include "Header.h"

void showcursor(bool flag)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(hOut, &info);
	// info.dwSize = 20;
	info.bVisible = flag;
	SetConsoleCursorInfo(hOut, &info);
}

void setCursorPosition(COORD coord)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	// COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void save(short record, short result) {
	fstream file;
	char tempResult[10];
	if (result > record) {
		record = result;
	}
	_itoa(record, tempResult, 10);
	file.open("memmory.txt", ios::out);
	file << tempResult;
	file.close();
}

void init(short &record) {
	fstream file;
	char tempResult[10];
	file.open("memmory.txt", ios::in);
	file >> tempResult;
	if (file.is_open()) {
		record = atoi(tempResult);
	}
	file.close();
}

void pauseStart(HWND screen, RECT rect1, RECT rect2, HDC hdc, short updateField, short result, short record, bool start, bool &work, bool &gameOver, bool &breakfast) {
	while (!start) {
		updateField++;
		if (updateField == 100) {
			InvalidateRect(screen, &rect1, TRUE);
			InvalidateRect(screen, &rect2, TRUE);
			updateField = 0;
		}
		paintField(hdc);
		paintMenu(hdc, result, record);
		if (gameOver == true) {
			paintGameOver(hdc);
		}
		if (updateField < 50) {
			paintStart(hdc);
		}
		else {
			paintExit(hdc);
		}
		if (_kbhit()) {
			short button = _getch();
			switch (button) {
			case KEY_ENTER: {
				start = true;
				break;
			}
			case KEY_ESCAPE: {
				start = true; work = false; breakfast = true; gameOver = true;
				break;
			}
			}
		}
		Sleep(50);
	}
}
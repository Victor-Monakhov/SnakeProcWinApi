#include "Header.h"

void paintBody(HDC hdc, COORD coord) {
	HBRUSH brushGreen = CreateSolidBrush(RGB(0, 255, 0));
	SelectObject(hdc, brushGreen);
	Ellipse(hdc, coord.X, coord.Y, coord.X + 20, coord.Y + 20);
	DeleteObject(brushGreen);
}

void paintHead(HDC hdc, COORD coord, short turnHead) {
	HBRUSH brushRed = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH brushGreen = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH brushYellow = CreateSolidBrush(RGB(255, 255, 0));
	SelectObject(hdc, brushGreen);
	Ellipse(hdc, coord.X - 5, coord.Y - 5, coord.X + 25, coord.Y + 25);
	DeleteObject(brushGreen);
	switch (turnHead) {
	case 0: {
		SelectObject(hdc, brushYellow);
		Ellipse(hdc, coord.X, coord.Y, coord.X + 5, coord.Y + 5);
		Ellipse(hdc, coord.X + 15, coord.Y, coord.X + 20, coord.Y + 5);
		DeleteObject(brushYellow);
		SelectObject(hdc, brushRed);
		Rectangle(hdc, coord.X + 7, coord.Y - 4, coord.X + 13, coord.Y);
		DeleteObject(brushRed);
		break;
	}
	case 1: {
		SelectObject(hdc, brushYellow);
		Ellipse(hdc, coord.X + 15, coord.Y, coord.X + 20, coord.Y + 5);
		Ellipse(hdc, coord.X + 15, coord.Y + 15, coord.X + 20, coord.Y + 20);
		DeleteObject(brushYellow);
		SelectObject(hdc, brushRed);
		Rectangle(hdc, coord.X + 20, coord.Y + 7, coord.X + 24, coord.Y + 13);
		DeleteObject(brushRed);
		break;
	}
	case 2: {
		SelectObject(hdc, brushYellow);
		Ellipse(hdc, coord.X, coord.Y + 15, coord.X + 5, coord.Y + 20);
		Ellipse(hdc, coord.X + 15, coord.Y + 15, coord.X + 20, coord.Y + 20);
		DeleteObject(brushYellow);
		SelectObject(hdc, brushRed);
		Rectangle(hdc, coord.X + 7, coord.Y + 20, coord.X + 13, coord.Y + 24);
		DeleteObject(brushRed);
		break;
	}
	case 3: {
		SelectObject(hdc, brushYellow);
		Ellipse(hdc, coord.X, coord.Y, coord.X + 5, coord.Y + 5);
		Ellipse(hdc, coord.X, coord.Y + 15, coord.X + 5, coord.Y + 20);
		DeleteObject(brushYellow);
		SelectObject(hdc, brushRed);
		Rectangle(hdc, coord.X, coord.Y + 7, coord.X - 4, coord.Y + 13);
		DeleteObject(brushRed);
		break;
	}
	}
}

void paintField(HDC hdc) {
	HBRUSH brushBrown = CreateSolidBrush(RGB(150, 60, 20));
	HBRUSH brushGrey = CreateSolidBrush(RGB(125, 125, 125));
	SelectObject(hdc, brushGrey);
	Rectangle(hdc, 0, 0, WIDTH, HEIGHT);
	DeleteObject(brushGrey);
	SelectObject(hdc, brushBrown);
	Rectangle(hdc, BARRIER, BARRIER, WIDTH - BARRIER, HEIGHT - BARRIER);
	DeleteObject(brushBrown);
}

void paintApple(HDC hdc, COORD coord) {
	HBRUSH brushGrey = CreateSolidBrush(RGB(125, 125, 125));
	HBRUSH brushGreen = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH brushRed = CreateSolidBrush(RGB(255, 0, 0));
	SelectObject(hdc, brushRed);
	Ellipse(hdc, coord.X, coord.Y, coord.X + 25, coord.Y + 25);
	DeleteObject(brushRed);
	SelectObject(hdc, brushGrey);
	Ellipse(hdc, coord.X + 8, coord.Y + 1, coord.X + 17, coord.Y + 7);
	DeleteObject(brushGrey);
	SelectObject(hdc, brushGreen);
	Rectangle(hdc, coord.X + 10, coord.Y - 5 , coord.X + 15, coord.Y + 5);
	DeleteObject(brushGreen);
}

void paintMenu(HDC hdc, short result, short record) {
	char tempResult[10], tempRecord[10];
	_itoa(result, tempResult, 10);
	_itoa(record, tempRecord, 10);
	HBRUSH brushBrown = CreateSolidBrush(RGB(150, 60, 20));
	HBRUSH brushGrey = CreateSolidBrush(RGB(125, 125, 125));
	HFONT newFont = CreateFontA(40, 12, 0, 0, FW_HEAVY, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Palatino Linotype");
	SelectObject(hdc, brushBrown);
	Rectangle(hdc, WIDTH, 0, WIDTH +200, HEIGHT);
	DeleteObject(brushBrown);
	SelectObject(hdc, brushGrey);
	Rectangle(hdc, WIDTH, 20, WIDTH + 200, 80);
	Rectangle(hdc, WIDTH, 140, WIDTH + 200, 200);
	Rectangle(hdc, WIDTH, 260, WIDTH + 200, 320);
	DeleteObject(brushGrey);
	SelectObject(hdc, newFont);
	SetBkColor(hdc, RGB(125, 125, 125));
	SetTextColor(hdc, RGB(0, 255, 0));
	TextOutA(hdc, WIDTH + 5, 30, "–≈«”À‹“¿“:", strlen("–≈«”À‹“¿“:"));
	SetBkColor(hdc, RGB(150, 60, 20));
	TextOutA(hdc, WIDTH + 60, 90, "X", strlen("X"));
	TextOutA(hdc, WIDTH + 90, 90, tempResult, strlen(tempResult));
	SetBkColor(hdc, RGB(125, 125, 125));
	SetTextColor(hdc, RGB(255, 255, 0));
	TextOutA(hdc, WIDTH + 5, 150, "–≈ Œ–ƒ:", strlen("–≈ Œ–ƒ:"));
	SetBkColor(hdc, RGB(150, 60, 20));
	TextOutA(hdc, WIDTH + 60, 210, "X", strlen("X"));
	TextOutA(hdc, WIDTH + 90, 210, tempRecord, strlen(tempRecord));
	DeleteObject(newFont);
	paintApple(hdc, { WIDTH + 20, 100 });
	paintApple(hdc, { WIDTH + 20, 220 });
}
void paintStart(HDC hdc) {
	HFONT newFont = CreateFontA(40, 12, 0, 0, FW_HEAVY, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Palatino Linotype");
	SelectObject(hdc, newFont);
	SetBkColor(hdc, RGB(125, 125, 125));
	SetTextColor(hdc, RGB(255, 255, 0));
	TextOutA(hdc, WIDTH + 5, 270, "—“¿–“:", strlen("—“¿–“:"));
	SetBkColor(hdc, RGB(150, 60, 20));
	SetTextColor(hdc, RGB(0, 255, 0));
	TextOutA(hdc, WIDTH + 25, 330, "ENTER", strlen("ENTER"));
	DeleteObject(newFont);
}
void paintPause(HDC hdc) {
	HFONT newFont = CreateFontA(40, 12, 0, 0, FW_HEAVY, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Palatino Linotype");
	SelectObject(hdc, newFont);
	SetBkColor(hdc, RGB(125, 125, 125));
	SetTextColor(hdc, RGB(255, 255, 0));
	TextOutA(hdc, WIDTH + 5, 270, "œ¿”«¿:", strlen("œ¿”«¿:"));
	SetBkColor(hdc, RGB(150, 60, 20));
	SetTextColor(hdc, RGB(0, 255, 0));
	TextOutA(hdc, WIDTH + 25, 330, "SPACE", strlen("SPACE"));
	DeleteObject(newFont);
}

void paintExit(HDC hdc) {
	HFONT newFont = CreateFontA(40, 12, 0, 0, FW_HEAVY, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Palatino Linotype");
	SelectObject(hdc, newFont);
	SetBkColor(hdc, RGB(125, 125, 125));
	SetTextColor(hdc, RGB(255, 255, 0));
	TextOutA(hdc, WIDTH + 5, 270, "¬€’Œƒ:", strlen("¬€’Œƒ:"));
	SetBkColor(hdc, RGB(150, 60, 20));
	SetTextColor(hdc, RGB(0, 255, 0));
	TextOutA(hdc, WIDTH + 25, 330, "ESCAPE", strlen("ESCAPE"));
	DeleteObject(newFont);
}

void paintGameOver(HDC hdc) {
	HFONT newFont = CreateFontA(40, 12, 0, 0, FW_HEAVY, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Palatino Linotype");
	SelectObject(hdc, newFont);
	SetBkColor(hdc, RGB(150, 60, 20));
	SetTextColor(hdc, RGB(255, 255, 0));
	TextOutA(hdc, (WIDTH/2) - 100, (HEIGHT/2) - 20, " ŒÕ≈÷ »√–€", strlen(" ŒÕ≈÷ »√–€"));
	DeleteObject(newFont);
}
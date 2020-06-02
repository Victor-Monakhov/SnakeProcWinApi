#pragma once

#include <iostream>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <fstream>

using namespace std;
//
// buttons
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_UP 72
#define KEY_ENTER 13
#define KEY_SPACE 32
#define KEY_ESCAPE 27
//
//size
#define HEIGHT 400
#define WIDTH 600
#define BARRIER 20
#define MIN_Y 1
#define MAX_Y 21

#define S_SIZE 500 

//
//interface
void showcursor(bool flag);
void setCursorPosition(COORD coord);
void save(short record, short currentResult);
void init(short &record);
void pauseStart(HWND screen, RECT rect1, RECT rect2, HDC hdc, short updateField, short result, short record, bool start, bool &work, bool &gameOver, bool &breakfast);
//
//paint
void paintBody(HDC hdc, COORD coord);
void paintHead(HDC hdc, COORD coord, short turnHead);
void paintField(HDC hdc);
void paintApple(HDC hdc, COORD coord);
void paintMenu(HDC hdc, short result, short record);
void paintStart(HDC hdc);
void paintPause(HDC hdc);
void paintExit(HDC hdc);
void paintGameOver(HDC hdc);
//
//backGameFunctions
void backField(short field[HEIGHT][WIDTH]);
void backSnake(short field[HEIGHT][WIDTH], COORD snakeCoords);
void backApple(short field[HEIGHT][WIDTH], COORD appleCoords);
void backNull(short field[HEIGHT][WIDTH], COORD coord);
COORD headPerimCoord(COORD headCoord, COORD headCoords[80]);
COORD* snakeMove(COORD headCoords[80], COORD *snakeCoords, short field[HEIGHT][WIDTH], short &snakeSize, short turnHeadshort, bool &gameOver, bool &breakfast);
COORD* resize(COORD *snakeCoords, short &snakeSize, short newSnakeSize, double long num);



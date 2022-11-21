#pragma once
#include <iostream>
#include <cstring>
#include<windows.h>

using namespace std;
const int MAX_H = 45;
const int MAX_V = 20;

COORD coord = {0,0};

void gotoxy(int x, int y)
{
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void interfazG();

//int main(int argc, char *argv[]) {
//	
//	interfazG();
//	return 0;
//}

void interfazG()
{
	char sideCharH;
	char sideCharV;
	char sideCharDL;
	char sideCharDR;
	char sideCharTR;
	char sideCharTL;
	char sideCharIL;
	char sideCharIR;
	
	//j => MAX_H
	//i => MAX_V
	
	sideCharIL = 204;
	sideCharIR = 185;
	sideCharV = 186;
	sideCharH = 205;
	sideCharDL = 200;
	sideCharDR = 188;
	sideCharTR = 187;
	sideCharTL = 201;
	cout<<"\n\n\n\n\n";
	for (int i = 0; i < MAX_V; i++)
	{
		cout<<"\t\t\t\t\t";
		for (int j = 0; j < MAX_H; j++)
		{
			if (i == 0 || j == MAX_H- 1 || j == 0 || i == MAX_V - 1)
			{				
				if(i ==MAX_V - 1 && j == 0)
				{
					cout <<sideCharDL;
				}
				else if(i == MAX_V - 1 && j == MAX_H - 1)
				{
					cout << sideCharDR;
				}
				else if(i == 0 && j == MAX_H - 1)
				{
					cout << sideCharTR;
				}
//				else if(i == 3 && j == 0)
//				{
//					cout << sideCharIL;
//				}
//				else if(i == 3 && j == MAX_H - 1)
//				{
//					cout << sideCharIR;
//				}
				else if(i == 0 && j == 0)
				{
					cout << sideCharTL;
				}
				else if(i != 0 || i != MAX_V - 1 && j == 0)
				{
					cout << sideCharV;
				}
				else
				{
					cout << sideCharH;
				}
			}
//			else if(i == 3 && j != 0 && j != MAX_H - 1)
//			{
//				cout << sideCharH;
//			}
			else
			{
				cout << " ";
			}
		}
		cout << endl;
	}
}

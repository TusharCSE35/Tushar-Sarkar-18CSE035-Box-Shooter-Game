/*
Project Name: BOX SHOOTER GAME
Author      : Tushar Sarkar
Instiute    : Bangabandhu Sheikh Mujibur Rahman Science and Technoloy University,Gopalgong.
Department  : Computure Science and Engineering
Student ID  : 18CSE035
Start Date  : November 15,2020
End Date    : November 25,2020
Language    : C/C++
Platform    : Visual Stdio Community 2013
Version     : 2.0
*/

// Write to main project code_________________________


#include<iostream>
using namespace std;
#include "iGraphics.h"

#define totalBricks 5*10
#define screenWidth 1200
#define screenHight 675
#define yAxisMargin 50

struct brickStructure
{
	int x;
	int y;
	int dx = 100;
	int dy = 20;
	int red;
	int green;
	int blue;
	bool show = true;
};
brickStructure bricks[totalBricks];


int mposx,  mposy;
int xBall = (int)screenWidth/2;
int yBall = yAxisMargin;
int Bradious = 10;

int xBoard = xBall - 50;
int yBoard = yBall - 20;
int dxBoard = 100;
int dyBoard = 10;

int dx = 5;
int dy = 7;

int loop = 3;
bool gameover = false;
bool success = false;

int red = 0;
int green = 0;
int blue = 0;

int musicOn = true;
int stime = 10;
int score = 0;
int cnt = 0;

char picture[4][20] = { "bpc\\pc5.bmp", "bpc\\pc6.bmp", "bpc\\pc7.bmp", "bpc\\pc8.bmp"};
int pindex = 0;

bool isStarted = false;
void BallChange();
void restartBall();
void defineBricks();

void iDraw()
{
	iClear();
	if (gameover)
	{
		iShowBMP(0, 0, "bpc\\pc10.bmp");
		iText(350,300, "You already loss the game & Your recent score is : 15", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(5, 10, "Tushar Sarkar,B.Sc. in CSE,BSMRSTU.", GLUT_BITMAP_TIMES_ROMAN_24);
		musicOn = false;
		return;
	}
	if (success)
	{
		iShowBMP(0, 0, "bpc\\pc11.bmp");
		iText(20, 300, "Finall Score : 250", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(20, 280, "Tushar Sarkar,B.Sc. in CSE,BSMRSTU.", GLUT_BITMAP_TIMES_ROMAN_24);
		musicOn = false;
		return;
	}
	iShowBMP(0, 0,picture[pindex]);
	iSetColor(red + 255, green, blue);
	iFilledCircle(xBall,yBall, Bradious, 1000);
	iFilledRectangle(xBoard, yBoard, dxBoard, dyBoard);
	iText(5, 10, "Tushar Sarkar,B.Sc. in CSE,BSMRSTU.", GLUT_BITMAP_TIMES_ROMAN_24);


	for (int i = 0; i < totalBricks; i++)
	{
		if (bricks[i].show)
		{
			iSetColor(bricks[i].red, bricks[i].green, bricks[i].blue);
			iFilledRectangle(bricks[i].x, bricks[i].y, bricks[i].dx, bricks[i].dy);
		}
	}
}


void iMouseMove(int mx, int my)
{
	
}

void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		
	}
}

void iPassiveMouseMove(int mx,int my)
{

    mposx = mx;
    mposy = my;

	if (mx == 2)
	{

	}              
    else if(my== 2)
	{

	}             

}

void iKeyboard(unsigned char key)
{
	if (gameover)
		return;
	if (success)
		return;
	if (key == ' ')
	{
		if (!isStarted)
		{
			isStarted = true;
		}
	}
}

void iSpecialKeyboard(unsigned char key)
{
	if (gameover)
		return;
	if (success)
		return;

	if(key == GLUT_KEY_INSERT)
	{
		if (musicOn)
		{
			musicOn = false;
			PlaySound(0, 0, 0);
		}
		else
		{
			musicOn = true;
			if (gameover || score == 250)
			{
				musicOn = false;
			}
			else 
				PlaySound("music\\audio2.wav", NULL, SND_LOOP | SND_ASYNC);
		}
	}
	if (key == GLUT_KEY_HOME)
	{
		pindex = 0;
	}
	if (key == GLUT_KEY_END)
	{
		pindex = 1;
	} 
	if (key == GLUT_KEY_PAGE_DOWN)
	{
		pindex = 2;
	}
	if (key == GLUT_KEY_PAGE_UP)
	{
		pindex = 3;
	}
	if (key == GLUT_KEY_LEFT)
	{
		if (xBoard > 0)
		{
			xBoard -= 10;
			if (!isStarted)
			{
				xBall -= 10;
			}
		}
	}
	if (key == GLUT_KEY_RIGHT)
	{
		if (xBoard < screenWidth - dxBoard)
		{
			xBoard += 10;
			if (!isStarted)
			{
				xBall += 10;
			}
		}
	}
	
}
void BallChange()
{
	if (gameover)
		return;
	if (success)
		return;

	if (isStarted)
	{
		xBall += dx;
		yBall += dy;

		if (xBall >= screenWidth || xBall <= 0)
		{
			dx *= -1;
		}
		if (yBall >= screenHight || yBall <= 0)
		{
			dy *= -1;
		}

		//Collision
		for (int i = 0; i < totalBricks; i++)
		{
			if (bricks[i].show)
			{
				if (xBall >= bricks[i].x && xBall <= bricks[i].x + bricks[i].dx)
				{
					if (yBall >= bricks[i].y && yBall <= bricks[i].y + bricks[i].dy)
					{
						dy *= -1;
						bricks[i].show = false;
						score += 5;
						if (score == 250)success = true;
					}
				}
				else if (yBall >= bricks[i].y && yBall <= bricks[i].y + bricks[i].dy)
				{
					if (xBall >= bricks[i].x && xBall <= bricks[i].x + bricks[i].dx)
					{
						dx *= -1;
						bricks[i].show = false;
						score += 5;
						if (score == 250)success = true;
					}
				}
			}
		}

		if (xBall >= xBoard && xBall <= xBoard + dxBoard && yBall >= yBoard && yBall <= yBoard + dyBoard)
		{
			dy *= -1;
		}
		else
		{
			if (yBall < yBoard)
			{
				restartBall();
				loop--;
				if (!loop)
					gameover = true;
		        
			}
		}
	}
}

void restartBall()
{
	if (gameover)
		return;
	if (success)
		return;

	xBall = (int)screenWidth / 2;
	yBall = yAxisMargin;

	xBoard = xBall - 50;
	yBoard = yBall - 20;

	int dx = 7;
	int dy = 5;

	isStarted = false;
}

void defineBricks()
{
	if (gameover)
		return;
	if (success)
		return;

	int sumx = 100;
	int sumy = 450;
	for (int i = 0; i < totalBricks; i++)
	{
		bricks[i].red = rand() % 255;
		bricks[i].green = rand() % 255;
		bricks[i].blue = rand() % 255;
		bricks[i].x = sumx;
		bricks[i].y = sumy;
		sumx += 100;
		if (sumx > 1000) 
		{
			sumx = 100;
			sumy += 20;
		}
	}
}

int main()
{
	defineBricks();
	iSetTimer(stime, BallChange);
	if (musicOn)
	{
		PlaySound("music\\audio2.wav", NULL, SND_LOOP | SND_ASYNC);
	}
	iInitialize(screenWidth, screenHight, "BOX SHOOTER");


	return 0;
}

/*
Ahsanullah University of Science and Technology
Department of Computer Science and Engineering
1st Year,2nd Semester
CSE 1200 iGraphics Project

Section: C1
Group: 01

Project Title: Into The Void

Group Members:
1.Aftab Ahmed Fahim (20230104117)
2.Ahbab Hasan (20230104119)
3.Shadman Muhtasim (20230104110)
*/

#include "iGraphics.h"
#include "Windows.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include"bitmap_loader.h"

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

#define screenwidth 1000
#define screenheight 600

void iDrawHomePage();
void iDrawPlayPage();
void iDrawCreditsPage();
void iDrawInstructionPage();
void iDrawHighScorePage();
void iDrawSettingsPage();
void iDrawPausePage();

void iPlayButtonClickFunction();
void iCreditsButtonClickFunction();
void iInstructionButtonClickFunction();
void iHighScoreButtonClickFunction();
void iSettingsButtonClickFunction();
void iExitButtonClickFunction();
void iBackButtonClickFunction();
void iPauseButtonClickFunction();

void initLasers();
void drawSpaceShip();
void drawLasers();
void drawEnemies();
void spawnEnemy();
void updateEnemies();
void checkCollisions();

void initAsteroids();
void drawAsteroids();
void spawnAsteroid();
void updateAsteroids();
void checkAsteroidCollisions();

void toogleMusic();
void buttonClick();

void gameOver();

void updateHighScores();
void loadHighScores();
void saveHighScores();

void initHealthPoints();
void drawHealthPoints();
void spawnHealthPoint();
void checkHealthPointCollisions();

int homePage = 1;
int playPage = 0;
int creditsPage = 0;
int instructionPage = 0;
int highScorePage = 0;
int settingsPage = 0;
int pausePage = 0;
int previousPage = 0;
int gameOverPage = 0;

bool playMusic = true;

int spaceShipX = 0;
int spaceShipY = 300;
int spaceshipWidth = 20;
int spaceshipHeight = 20;

int laserWidth = 10;
int laserHeight = 20;
int laserIndex = 0;

int enemyWidth = 20;
int enemyHeight = 20;
int enemyIndex = 0;
int enemySpawnTimer = 0;
int enemySpeed = 2;
int timeElapsed = 0;

int score = 0;
int collisionCount = 0;
int highScores[11] = { 0 };

struct Laser
{
	int x, y;
	bool active;
}lasers[100];

struct Enemy
{
	int x, y;
	bool active;
	int imageIndex;
} enemies[100];

struct Asteroid 
{
	int x, y;
	bool active;
} asteroids[100];

struct HealthPoint
{
	int x, y;
	bool active;
} healthPoints[100];

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Idraw Here::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

void iDraw()
{
	iClear();
	if (homePage == 1)
	{
		iDrawHomePage();
	}
	else if (playPage == 1)
	{
		iDrawPlayPage();
	}
	else if (creditsPage == 1)
	{
		iDrawCreditsPage();
	}
	else if (instructionPage == 1)
	{
		iDrawInstructionPage();
	}
	else if (highScorePage == 1)
	{
		iDrawHighScorePage();
	}
	else if (settingsPage == 1)
	{
		iDrawSettingsPage();
	}
	else if (pausePage == 1)
	{
		iDrawPausePage();
	}
	else if (homePage == 2)
	{
		gameOver();
	}
}





/*function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/


void iMouseMove(int mx, int my)
{
	
}

//*******************************************************************ipassiveMouse***********************************************************************//

void iPassiveMouseMove(int mx, int my)
{
	
}

//*******************************************************************iMouse***********************************************************************//

void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		printf("%d,%d\n", mx, my);

		if (homePage == 1 && (mx >= 140 && mx <= 438) && (my >= 354 && my <= 419))
		{
			//buttonClick();
			iPlayButtonClickFunction();
		}

		else if (homePage == 1 && (mx >= 519 && mx <= 814) && (my >= 246 && my <= 314))
		{
			//buttonClick();
			iCreditsButtonClickFunction();
		}

		else if (homePage == 1 && (mx >= 140 && mx <= 438) && (my >= 246 && my <= 314))
		{
			//buttonClick();
			iInstructionButtonClickFunction();
		}

		else if (homePage == 1 && (mx >= 140 && mx <= 438) && (my >= 141 && my <= 208))
		{
			//buttonClick();
			iHighScoreButtonClickFunction();
		}

		else if (homePage == 1 && (mx >= 519 && mx <= 814) && (my >= 354 && my <= 419))
		{
			//buttonClick();
			iSettingsButtonClickFunction();
		}

		else if (homePage == 1 && (mx >= 519 && mx <= 814) && (my >= 141 && my <= 208))
		{
			//buttonClick();
			iExitButtonClickFunction();
		}

		else if (settingsPage == 1 && (mx >= 337 && mx <= 537) && (my >= 339 && my <= 539))
		{
			//buttonClick();
			toogleMusic();
		}

		else if ((settingsPage == 1 || creditsPage == 1 || instructionPage == 1 || highScorePage == 1) && (mx >= 25 && mx <= 144) && (my >= 531 && my <= 562))
		{
			//buttonClick();
			iBackButtonClickFunction();
		}

		else if (playPage == 1)
		{
			if ((mx >= 25 && mx <= 80) && (my >= 532 && my <= 582))
			{
				iPauseButtonClickFunction();
			}

			else
			{
				lasers[laserIndex].x = spaceShipX + spaceshipWidth / 2 - laserWidth / 2;
				lasers[laserIndex].y = spaceShipY + spaceshipHeight / 2 - laserHeight / 2;
				lasers[laserIndex].active = true;
				PlaySound("Music\\laserSound.wav", NULL, SND_ASYNC | SND_NOSTOP);
				laserIndex = (laserIndex + 1) % 100;
			}
		}

		else if (pausePage == 1 && (mx >= 350 && mx <= 647) && (my >= 178 && my <= 277))
		{
			//buttonClick();
			iSettingsButtonClickFunction();
		}

		else if (pausePage == 1 && (mx >= 350 && mx <= 647) && (my >= 58 && my <= 155))
		{
			//buttonClick();
			iExitButtonClickFunction();
		}

		else if (pausePage == 1 && (mx >= 328 && mx <= 667) && (my >= 429 && my <= 534))
		{
			pausePage = 0;
			playPage = 1;
		}

		else if (pausePage == 1 && (mx >= 330 && mx <= 671) && (my >= 301 && my <= 405))
		{
			score = 0;
			collisionCount = 0;
			playPage = 1;
			pausePage = 0;

			for (int i = 0; i < 100; i++)
			{
				enemies[i].active = false;
			}

			for (int i = 0; i < 100; i++)
			{
				asteroids[i].active = false;
			}

			enemyIndex = 0;
			enemySpawnTimer = 0;
			timeElapsed = 0;
			enemySpeed = 2;

			spaceShipX = 0;
			spaceShipY = 300;
		}
		
	}
	
	
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//
	}
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/


void iKeyboard(unsigned char key)
{
	if (key == '\r')
	{
		
	}
}

/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/

void iSpecialKeyboard(unsigned char key)
{
	if (key == GLUT_KEY_RIGHT) 
	{
		if (spaceShipX + spaceshipWidth < screenwidth) 
		{
			spaceShipX += 20;
		}
	}

	if (key == GLUT_KEY_LEFT) 
	{
		if (spaceShipX > 0) 
		{
			spaceShipX -= 20;
		}
	}

	if (key == GLUT_KEY_UP) 
	{
		if (spaceShipY + spaceshipHeight < 490) 
		{
			spaceShipY += 20;
		}
	}

	if (key == GLUT_KEY_DOWN) 
	{
		if (spaceShipY > 0) 
		{
			spaceShipY -= 20;
		}
	}

	if (gameOverPage == 1)
	{
		if (key == GLUT_KEY_HOME)
		{
			gameOverPage = 0;
			homePage = 1;
		}
	}
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::DrawPage Functions:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

void iDrawHomePage()
{
	iSetColor(0,0,0);
	iFilledRectangle(0, 0, 1000, 600);
	iShowBMP2(0, 0, "Image\\mainbg.bmp", 0);
}

void iDrawPlayPage()
{
	iFilledRectangle(0, 0, 1000, 600);
	
	iShowBMP2(0, 0, "Image\\playBG.bmp",0);
	iShowBMP2(22, 533, "Image\\pause.bmp", 0);

	drawSpaceShip();
	drawLasers();

	drawEnemies();
	spawnEnemy();
	updateEnemies();
	checkCollisions();

	drawAsteroids(); 
	spawnAsteroid(); 
	updateAsteroids(); 
	checkAsteroidCollisions(); 

	drawHealthPoints();
	spawnHealthPoint();
	checkHealthPointCollisions();

	iSetColor(0, 0, 0);
	iFilledRectangle(389,552,118,43);
	iFilledRectangle(849,552,108,43);

	iSetColor(0, 255, 0);
	iText(855, 565, "Points :", GLUT_BITMAP_TIMES_ROMAN_24);
	char scoreStr[10];
	itoa(score, scoreStr, 10);
	iText(screenwidth-65, screenheight - 36, scoreStr, GLUT_BITMAP_TIMES_ROMAN_24);

	iSetColor(255, 0, 0);
	iText(400, 565, "Health :", GLUT_BITMAP_TIMES_ROMAN_24);
	char healthStr[10];
	itoa(3 - collisionCount, healthStr, 10); 
	iText(screenwidth-513, screenheight - 35, healthStr, GLUT_BITMAP_TIMES_ROMAN_24);

}

void iDrawCreditsPage()
{
	iFilledRectangle(0, 0, 1000, 600);
	iShowBMP2(0, 0, "Image\\credits.bmp", 0);
	iShowBMP2(25, 540, "Image\\return.bmp", 0);
}

void iDrawInstructionPage()
{
	iFilledRectangle(0, 0, 1000, 600);
	iShowBMP2(0, 0, "Image\\instructions.bmp", 0);
	iShowBMP2(25, 530, "Image\\return.bmp", 0);
}

void iDrawHighScorePage()
{
	iFilledRectangle(0, 0, 1000, 600);
	iShowBMP2(0, 0, "Image\\highscore.bmp", 0);
	iShowBMP2(25, 530, "Image\\return.bmp", 0);
	homePage = 2;

	for (int i = 0; i < 10; i++)
	{
		iSetColor(255, 0, 0);

		iText(300, 413, "Rank", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(600, 413, "Score", GLUT_BITMAP_TIMES_ROMAN_24);

		char rankStr[10];
		itoa(i + 1, rankStr, 10);
		iText(315, 382 - i * 30, rankStr, GLUT_BITMAP_TIMES_ROMAN_24);

		char scoreStr[10];
		itoa(highScores[i], scoreStr, 10);
		iText(615, 382 - i * 30, scoreStr, GLUT_BITMAP_TIMES_ROMAN_24);
	}

}

void iDrawSettingsPage()
{
	iFilledRectangle(0, 0, 1000, 600);
	iShowBMP2(0, 0, "Image\\setting.bmp", 0);
	iShowBMP2(25, 530, "Image\\return.bmp", 0);

	if (playMusic)
	{
		iSetColor(0, 255, 0);
		iText(337, 365, "ON", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else
	{
		iSetColor(255, 0, 0);
		iText(337, 365, "OFF", GLUT_BITMAP_TIMES_ROMAN_24);
	}

	iSetColor(0, 0, 0);
}

void iDrawPausePage()
{
	iFilledRectangle(0, 0, 1000, 600);
	iShowBMP2(0, 0, "Image\\pausemenu.bmp", 0);
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::ButtonClick Functions:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

void iPlayButtonClickFunction()
{
	homePage = 0;
	playPage = 1;
	score = 0;
	collisionCount = 0;
	playPage = 1;
	pausePage = 0;

	for (int i = 0; i < 100; i++)
	{
		enemies[i].active = false;
	}

	for (int i = 0; i < 100; i++)
	{
		asteroids[i].active = false;
	}

	enemyIndex = 0;
	enemySpawnTimer = 0;
	timeElapsed = 0;
	enemySpeed = 2;

	spaceShipX = 0;
	spaceShipY = 300;
}

void iCreditsButtonClickFunction()
{
	homePage = 0;
	playPage = 0;
	creditsPage = 1;
}

void iInstructionButtonClickFunction()
{
	homePage = 0;
	playPage = 0;
	creditsPage = 0;
	instructionPage = 1;
}

void iHighScoreButtonClickFunction()
{
	homePage = 0;
	playPage = 0;
	creditsPage = 0;
	instructionPage = 0;
	highScorePage = 1;
}

void iSettingsButtonClickFunction()
{
	if (pausePage == 1)
	{
		previousPage = 3;
	}
	else
	{
		previousPage = 1;
	}
	homePage = 0;
	playPage = 0;
	creditsPage = 0;
	instructionPage = 0;
	highScorePage = 0;
	settingsPage = 1;
	pausePage = 0;
}

void iExitButtonClickFunction()
{
	exit(0);
}

void iBackButtonClickFunction()
{
	if (previousPage == 3)
	{
		pausePage = 1;
	}
	else
	{
		homePage = 1;
	}
	playPage = 0;
	creditsPage = 0;
	instructionPage = 0;
	highScorePage = 0;
	settingsPage = 0;
	previousPage = 0;
}

void iPauseButtonClickFunction()
{
	homePage = 0;
	playPage = 0;
	creditsPage = 0;
	instructionPage = 0;
	highScorePage = 0;
	settingsPage = 0;
	pausePage = 1;
}

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::High Score Functions:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: //


void loadHighScores()
{
	std::ifstream file("highscores.txt");
	if (file.is_open())
	{
		for (int i = 0; i < 10; i++)
		{
			file >> highScores[i];
		}
		file.close();
	}
}

void saveHighScores()
{
	std::ofstream file("highscores.txt");
	if (file.is_open())
	{
		for (int i = 0; i < 10; i++)
		{
			file << highScores[i] << std::endl;
		}
		file.close();
	}
}

void updateHighScores(int newScore)
{
	int inserted = 1;

	for (int i = 0; i < 10; i++)
	{
		if ((newScore > highScores[i]) && (inserted == 1) )
		{
			for (int j = 9; j > i; j--)
			{
				highScores[j] = highScores[j - 1];
			}
			highScores[i] = newScore;
			inserted = 0;
		}
	}

	saveHighScores();
}


//::::::::::::::::::::::::::::::::::::::::::::::::::::::::MusicManage Functions:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

void toogleMusic()
{
	if (playMusic)
	{
		playMusic = false;
		PlaySound(0, 0, 0);
	}
	else
	{
		playMusic = true;
		PlaySound("Music\\gamemusic.wav", NULL, SND_LOOP | SND_ASYNC);
	}

	iDrawSettingsPage();
}


void buttonClick()
{
	PlaySound("Music\\buttonClick.wav", NULL, SND_ASYNC | SND_NOSTOP);
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::PlayerShip and EnemyShip Functions:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

void initLasers()
{
	for (int i = 0; i < 100; i++)
	{
		lasers[i].active = false;
	}
}

void drawSpaceShip()
{
	iShowBMP2(spaceShipX, spaceShipY,"Image\\spaceship1.bmp",0);
}

void drawLasers()
{
	for (int i = 0; i < 100; i++)
	{
		if (lasers[i].active)
		{
			iShowBMP2(lasers[i].x, lasers[i].y, "Image\\laserbeam1.bmp", 0);
			lasers[i].x += 10;
			if (lasers[i].x > screenwidth)
			{
				lasers[i].active = false;
			}
		}
	}
}

void drawEnemies() 
{
	for (int i = 0; i < 100; i++) 
	{
		if (enemies[i].active) 
		{
			switch (enemies[i].imageIndex) 
			{
			case 0:
				iShowBMP2(enemies[i].x, enemies[i].y, "Image\\enemy_ship1.bmp", 0);
				break;
			case 1:
				iShowBMP2(enemies[i].x, enemies[i].y, "Image\\enemy_ship2.bmp", 0);
				break;
			case 2:
				iShowBMP2(enemies[i].x, enemies[i].y, "Image\\enemy_ship3.bmp", 0);
				break;
			case 3:
				iShowBMP2(enemies[i].x, enemies[i].y, "Image\\enemy_ship4.bmp", 0);
				break;
			}
		}
	}
}

void spawnEnemy() 
{
	if (enemySpawnTimer % 100 == 0)
	{
		enemies[enemyIndex].x = screenwidth - enemyWidth;
		enemies[enemyIndex].y = rand() % (479 - enemyHeight);
		enemies[enemyIndex].active = true;
		enemies[enemyIndex].imageIndex = rand() % 4;
		enemyIndex = (enemyIndex + 1) % 100;
	}
	enemySpawnTimer++;
}

void updateEnemies() 
{
	for (int i = 0; i < 100; i++)
	{
		if (enemies[i].active)
		{
			enemies[i].x -= enemySpeed;
			if (enemies[i].x < 0)
			{
				enemies[i].active = false;
			}
		}
	}

	if (enemySpawnTimer % 100 == 0) 
	{
		timeElapsed++;
		if (timeElapsed % 50 == 0)
		{
			enemySpeed += 1;
		}
	}
}

void checkCollisions()
{
	for (int i = 0; i < 100; i++)
	{
		if (enemies[i].active)
		{
			for (int j = 0; j < 100; j++)
			{
				if (lasers[j].active)
				{
					if ((lasers[j].x < enemies[i].x + enemyWidth) && (lasers[j].x + laserWidth > enemies[i].x) && (lasers[j].y < enemies[i].y + enemyHeight) && (lasers[j].y + laserHeight > enemies[i].y))
					{
						enemies[i].active = false;
						lasers[j].active = false;
						score += 1;
					}
				}
			}

			if ((spaceShipX < enemies[i].x + enemyWidth) && (spaceShipX + spaceshipWidth > enemies[i].x) && (spaceShipY < enemies[i].y + enemyHeight) && (spaceShipY + spaceshipHeight > enemies[i].y))
			{
				enemies[i].active = false;
				collisionCount++;
				if (collisionCount >= 3)
				{
					playPage = 0;
					homePage = 2;
				}
			}
		}
	}
}

void initAsteroids() 
{
	for (int i = 0; i < 100; i++) 
	{
		asteroids[i].active = false;
	}
}

void drawAsteroids() 
{
	for (int i = 0; i < 100; i++) 
	{
		if (asteroids[i].active)
		{
			iShowBMP2(asteroids[i].x, asteroids[i].y,"Image//asteroid.bmp",0);
			asteroids[i].x -= enemySpeed / 2; 
			if (asteroids[i].x < 0) 
			{
				asteroids[i].active = false;
			}
		}
	}
}

void spawnAsteroid() 
{
	if (enemySpawnTimer % 500 == 0) 
	{ 
		asteroids[enemyIndex].x = screenwidth - enemyWidth;
		asteroids[enemyIndex].y = rand() % (479 - enemyHeight);
		asteroids[enemyIndex].active = true;
		enemyIndex = (enemyIndex + 1) % 100;
	}
}

void updateAsteroids() 
{
	for (int i = 0; i < 100; i++) 
	{
		if (asteroids[i].active) 
		{
			asteroids[i].x -= enemySpeed / 2;
			if (asteroids[i].x < 0) 
			{
				asteroids[i].active = false;
			}
		}
	}
}

void checkAsteroidCollisions()
{
	for (int i = 0; i < 100; i++)
	{
		if (asteroids[i].active)
		{
			for (int j = 0; j < 100; j++)
			{
				if (lasers[j].active)
				{
					if ((lasers[j].x < asteroids[i].x + enemyWidth) && (lasers[j].x + laserWidth > asteroids[i].x) 
						&& (lasers[j].y < asteroids[i].y + enemyHeight) && (lasers[j].y + laserHeight > asteroids[i].y))
					{
						asteroids[i].active = false;
						lasers[j].active = false;
						score += 3;
					}
				}
			}

			if ((spaceShipX < asteroids[i].x + enemyWidth) && (spaceShipX + spaceshipWidth > asteroids[i].x) 
				&& (spaceShipY < asteroids[i].y + enemyHeight) && (spaceShipY + spaceshipHeight > asteroids[i].y))
			{
				asteroids[i].active = false;
				collisionCount++;
				if (collisionCount >= 3)
				{
					playPage = 0;
					homePage = 2;
				}
			}
		}
	}
}

void gameOver()
{
	updateHighScores(score);

	gameOverPage = 1;
	iSetColor(128, 128, 128);
	iFilledRectangle(0, 0, 1000, 600);
	iShowBMP2(0, 0, "image\\gameover.bmp", 0);
	homePage = 2;

	iSetColor(255, 0, 0);
	char scoreStr[10];
	itoa(score, scoreStr, 10); 
	iText(screenwidth / 2 - 60, screenheight / 2, "Your Score : ", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(screenwidth / 2 + 70, screenheight / 2, scoreStr, GLUT_BITMAP_TIMES_ROMAN_24);
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::Health Functions:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

void initHealthPoints()
{
	for (int i = 0; i < 100; i++)
	{
		healthPoints[i].active = false;
	}
}

void drawHealthPoints()
{
	for (int i = 0; i < 100; i++)
	{
		if (healthPoints[i].active)
		{
			iShowBMP2(healthPoints[i].x, healthPoints[i].y, "Image\\healthpoint.bmp", 0);
			healthPoints[i].x -= (enemySpeed+5) / 2;
			if (healthPoints[i].x < 0)
			{
				healthPoints[i].active = false;
			}
		}
	}
}

void spawnHealthPoint()
{
	static int healthPointTimer = 0;
	healthPointTimer++;
	if (healthPointTimer % 1000 == 0)
	{
		healthPoints[enemyIndex].x = screenwidth - enemyWidth;
		healthPoints[enemyIndex].y = rand() % (479 - enemyHeight);
		healthPoints[enemyIndex].active = true;
		enemyIndex = (enemyIndex + 1) % 100;
	}
}

void checkHealthPointCollisions()
{
	for (int i = 0; i < 100; i++)
	{
		if (healthPoints[i].active)
		{
			if ((spaceShipX < healthPoints[i].x + enemyWidth) && (spaceShipX + spaceshipWidth > healthPoints[i].x) && (spaceShipY < healthPoints[i].y + enemyHeight) && (spaceShipY + spaceshipHeight > healthPoints[i].y))
			{
				healthPoints[i].active = false;
				if (collisionCount > 0)
				{
					collisionCount--;
				}
			}
		}
	}
}



//::::::::::::::::::::::::::::::::::::::::::::::::::::::::main Function:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

int main()
{
	loadHighScores();

	if (playMusic)
	{
		PlaySound("Music\\gamemusic.wav", NULL, SND_LOOP | SND_ASYNC);
	}

	iInitialize(screenwidth, screenheight, "Into The Void");

	initLasers();
	initAsteroids();
	initHealthPoints();

	iStart();

	return 0;
}
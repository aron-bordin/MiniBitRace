/**
 *  
 	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// required libraries
#include "LedMatrixObject.h"
#include "Timer.h"

// default pins
#define btnLeft 	3
#define btnRight 	2

// .PNG Arduino Framework objects

LedMatrixObject *led = new LedMatrixObject(12, 11, 10, 9, 8, 7, 6, 5);
Timer *fps = new Timer(1/30); //game with 30fps


unsigned char  Logo[16][16] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1},
    {1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1},
    {1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1},
    {1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1},
    {1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1},
    {1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1},
    {1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

unsigned char  Home[16][16] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
    {1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1},
    {1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1},
    {1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1},
    {1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1},
    {1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1},
    {1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0},
};


// game variables

unsigned long deadTime = millis(); // time that the player dies
bool isHome = true; // display the homescreen 
bool isLogo = true; // display the homescreen 
int heroX = 5; //start the hero in the center of the screen
float vSpeed = 0.05;
float borderPos = 0;
bool pressed = false; //indicates if there is a button pressed
// positions of the enemies
int enemyX[2] = {5, 10};
float enemyY[2] = {0, -8};

/**
 * Setup basic game arduino items and start the game loops
 */
void setup(){
	Serial.begin(9600);
	pinMode(btnLeft, INPUT);
	pinMode(btnRight, INPUT);

	// start the game update loop
	
	fps->setOnTimer(&gameUpdate);
	fps->Start();

}

/**
 * Updates the player position
 * @param  {int} int d             player direciton. 0 keep, -1 left, 1 right
 */
void goDirection(int d){
	if(d > 0 && heroX < 12)
		heroX += d;
	if(d < 0 && heroX > 3)
		heroX += d;
}


/**
 * Draws the hero car in the screen
 * Hero looks like: 			
 * 				 *
 * 				***
 * 				 *
 * 				***
 * 	HeroX indicates the middle px in the bottom of the car
 */
void drawHero(){
	led->setLedOn(15, heroX);
	led->setLedOn(15, heroX + 1);
	led->setLedOn(15, heroX - 1);
	led->setLedOn(14, heroX);
	led->setLedOn(13, heroX);
	led->setLedOn(13, heroX + 1);
	led->setLedOn(13, heroX - 1);
	led->setLedOn(12, heroX);
}

/**
 * Draw road edges
 */
void drawBorder(){
	byte i;
	if(borderPos > 1){
		i = 1;
	} else {
		i = 0;
	}
	if(borderPos > 2)
		borderPos = 0;
	for(i; i < 16; i += 2){
		led->setLedOn(i, 1);
		led->setLedOn(i, 14);
	}
}

/**
 * Update entities positions in the scene
 */
void updatePos(){
	borderPos += vSpeed;
	
	for(byte e = 0; e < 2; e++){
		enemyY[e] += vSpeed;
		if(enemyY[e] > 18){
			enemyY[e] = -1;
			if(random(2))
				enemyX[e] = 5;
			else
				enemyX[e] = 10;
		}
	}
}

/**
 * restore default values
 */
void restartGame(){
	heroX = 5;
	borderPos = 0;
	pressed = false;
	enemyX[0] = 5;
	enemyX[1] = 10;
	enemyY[0] = 0;
	enemyY[1] = -8;
}

/** Dies */
void heroDie(){
	deadTime = millis();
	isHome = true;
	restartGame();
}

void checkCollisions() {
	for(byte e = 0; e < 2; e++){
		int ex = enemyX[e], ey = (int)enemyY[e];
		int diffX = abs(heroX - ex); 

		if(ey >= 13 && diffX <= 2){
			heroDie();
		}
	}
}

/** Draw enemies in the scene
	Enemy looks like: 

				 ***
				 ***
				  *
	The position of the enemy indicates the * in the bottom
 */
void drawEnemies(){
	for(byte e = 0; e < 2; e++){
		byte y = (byte) enemyY[e];
		byte x = (byte) enemyX[e];

		if(y >= 0 && y <= 15)
			led->setLedOn(y, x);
		if(y - 1 >= 0 && y - 1 <= 15){
			led->setLedOn(y - 1, x);	
			led->setLedOn(y - 1, x - 1);	
			led->setLedOn(y - 1, x + 1);	
		}
		if(y - 2 >= 0 && y - 2 <= 15){
			led->setLedOn(y - 2, x - 1);	
			led->setLedOn(y - 2, x + 1);	
			led->setLedOn(y - 2, x);	
		}
	}
}



/**
 * Check collisions and update game entities
 */
void gameUpdate(){
	updatePos();
	checkCollisions();

	drawHero();
	drawEnemies();
	drawBorder();

	led->draw();
}

/**
 * Arduino loop. If game is running, just keep the game loop running.
 * Otherwise shows the homescene
 */
void loop(){
	int direction = 0; //player direction. 0 keep pos, -1 go left, +1 go right

	if(digitalRead(btnRight))
		direction = -1;
	else if (digitalRead(btnLeft))
		direction = 1;

	if(isLogo){
		led->setScene(Logo);
		led->draw();

		if(millis() - deadTime > 5000)
			isLogo = false;
	} else {

		if(isHome) {
			led->setScene(Home);
			led->draw();

			if(direction != 0 && millis() - deadTime > 1000)
				isHome = false;
		} else {
			if(!pressed)
				goDirection(direction);
			fps->Update();
		}

		if(direction == 0){
			pressed = false;
		} else {
			pressed = true;
		}
	}
}
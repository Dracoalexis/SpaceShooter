 /*
 * gCanvas.h
 *
 *  Created on: May 6, 2020
 *      Author: Noyan Culum
 */

#ifndef GCANVAS_H_
#define GCANVAS_H_

#include "gBaseCanvas.h"
#include "gApp.h"
#include "gImage.h"
#include "MenuCanvas.h"
#include "gFmodSound.h"

class gCanvas : public gBaseCanvas {
public:
	gCanvas(gApp* root);
	virtual ~gCanvas();

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void charPressed(unsigned int codepoint);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseScrolled(int x, int y);
	void mouseEntered();
	void mouseExited();
	void windowResized(int w, int h);

	void showNotify();
	void hideNotify();
private:
	void moveSpaceShip();
	void moveMeteors();
	void moveBullets();
	void drawSpace();
	void drawSpaceShip();
	void drawMeteors();
	void drawBullets();
	void drawHealthBar();
	void drawDialogues();
	void generateMeteor();
	bool checkCollisionX(float firstx, float firstwidth, float secondx, float secondwidth);
	bool checkCollisionY(float firsty, float firstheight, float secondy, float secondheight);
	bool isSameWay(float firstspeed, float secondspeed);
	void generateBullet(float bulletX, float bulletY, float bulletDx, float bulletDy, float bulletRotation, int bulletSender);

	struct meteor{
		float meteorscale;
		float meteorx;
		float meteory;
		float meteorspeedx;
		float meteorspeedy;
		float meteorhealth;
	};

	std::vector<meteor>meteors;
	std::vector<std::vector<float>>bullets;

	static const int meteorcount = 15;

	enum direction
	{
		NONE, EAST, NORTH, WEST, SOUTH
	};

	enum {
		GAMESTATE_LOAD, GAMESTATE_PLAY, GAMESTATE_GAMEOVER
	};

	gApp* root;
	gImage spaceship;
	gImage meteor1;
	gImage meteor2;
	gImage space;
	gImage bulletImage;
	gImage healthbar;
	gImage healthbarborder;
	gImage mainmenubbg;
	gImage retrybbg;
	gFont meteorcountGUIfont;
	gFont meteorscountfont;
	gFont gameoverfont;
	gFont retrybuttonfont;
	gFont mainmenubuttonfont;
	gFont scorefont;
	gFmodSound battlemusic;
	gFmodSound winmusic;
	gFmodSound shootsoundeffect;
	gFmodSound meteorhitsoundeffect;
	float ssspeed, ssspeedx, ssspeedy;
	float sssubspeed, sssubspeedx, sssubspeedy;
	int gamestate;
	int score;
	int ssx, ssy;
	int ssw, ssh;
	int hbx, hby;
	int hbbx, hbby, hbw, hbh;
	int sshealth;
	int meteor1health;
	int meteor2health;
	int meteortotalcount;
	int gox, goy;
	int retrybbgx, retrybbgy, retrybbgw, retrybbgh;
	int mainmenubbgx, mainmenubbgy, mainmenubbgw, mainmenubbgh;
	float meteor1speed;
	float meteor2speed;
	float bulletspeed;
	float ssangle;
	bool dialogueshown;
	bool wpressed;
	bool apressed;
	bool spressed;
	bool dpressed;
	bool isplayerwin;
	direction dir;
};

#endif /* GCANVAS_H_ */

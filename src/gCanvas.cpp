/*
* gCanvas.cpp
*
*  Created on: May 6, 2020
*      Author: Noyan Culum
*/


#include "gCanvas.h"

gCanvas::gCanvas(gApp* root) : gBaseCanvas(root) {
	this->root = root;
}

gCanvas::~gCanvas() {
}

void gCanvas::setup() {
	gamestate = GAMESTATE_PLAY;
	dialogueshown = false;
	meteorcountGUIfont.loadFont("space age.ttf", 18);
	meteorscountfont.loadFont("dogicapixel.ttf", 12);
	gameoverfont.loadFont("SPACE.ttf", 48);
	mainmenubuttonfont.loadFont("space age.ttf", 18);
	retrybuttonfont.loadFont("space age.ttf", 18);
	scorefont.loadFont("space age.ttf", 18);
	space.loadImage("SpaceShooter_Space.png");
	spaceship.loadImage("SpaceShooter_SpaceShip1.png");
	meteor1.loadImage("SpaceShooter_Meteor1.png");
	meteor2.loadImage("SpaceShooter_Meteor2.png");
	bulletImage.loadImage("SpaceShooter_Bullet.png");
	healthbar.loadImage("SpaceShooter_HealthBar.png");
	healthbarborder.loadImage("SpaceShooter_HealthBarBorder.png");
	mainmenubbg.loadImage("SpaceShooter_ButtonBackGround3.png");
	retrybbg.loadImage("SpaceShooter_ButtonBackGround3.png");
	sshealth = 10;
	score = 0;
	gox = (getWidth() - gameoverfont.getStringWidth("GAME OVER")) / 2;
	goy = getHeight() / 2;
	ssw = spaceship.getWidth();
	ssh = spaceship.getHeight();
	ssx = (getWidth() - ssw) / 2;
	ssy = (getHeight() - ssh) / 2;
	hbx = (getWidth() - healthbar.getWidth()) / 2;
	hby = 30;
	hbw = healthbar.getWidth();
	hbh = healthbar.getHeight();
	hbbx = hbx;
	hbby = hby;
	retrybbgx = gox + 320;
	retrybbgy = goy + 40;
	retrybbgw = retrybbg.getWidth();
	retrybbgh = retrybbg.getHeight();
	mainmenubbgx = gox;
	mainmenubbgy = goy + 40;
	mainmenubbgw = mainmenubbg.getWidth();
	mainmenubbgh = mainmenubbg.getHeight();
	ssangle = 0.0f;
	wpressed = false;
	apressed = false;
	dpressed = false;
	spressed = false;
	isplayerwin = false;
	sssubspeed = 1.0f;
	ssspeed = 2.3f;
	ssspeedx = 0.0f;
	ssspeedy = 0.0f;
	meteor1speed = 5.5f;
	meteor2speed = 4.5f;
	meteor1health = 2;
	meteor2health = 6;
	bulletspeed = 35.0f;
	dir = NONE;
	for(int i = 0; i < meteorcount; i++) {
		generateMeteor();
	}
	meteortotalcount = meteors.size();
}

void gCanvas::update() {
	if(dialogueshown) return;
	moveSpaceShip();
	moveMeteors();
	moveBullets();
}
void gCanvas::draw() {
	drawSpace();
	if(!dialogueshown) {
		drawSpaceShip();
		drawBullets();
	}
	drawMeteors();
	drawHealthBar();
	drawDialogues();
}

void gCanvas::generateMeteor() {
    meteor m;
    float offset = 200.0f;
    const int MAX_TRIES = 50;
    bool spawned = false;
    for (int tries = 0; tries < MAX_TRIES; tries++) {
        float r = rand() / float(RAND_MAX);
        if (r < 0.25f) {
            m.meteorx = (rand() / float(RAND_MAX)) * getWidth();
            m.meteory = -offset;
        } else if (r < 0.5f) {
            m.meteorx = (rand() / float(RAND_MAX)) * getWidth();
            m.meteory = getHeight() + offset;
        } else if (r < 0.75f) {
            m.meteorx = -offset;
            m.meteory = (rand() / float(RAND_MAX)) * getHeight();
        } else {
            m.meteorx = getWidth() + offset;
            m.meteory = (rand() / float(RAND_MAX)) * getHeight();
        }
        bool overlap = false;
        for (const meteor& other : meteors) {
            if (checkCollisionX(m.meteorx, meteor2.getWidth(),
                                other.meteorx, meteor2.getWidth()) &&
                checkCollisionY(m.meteory, meteor2.getHeight(),
                                other.meteory, meteor2.getHeight())) {
                overlap = true;
                break;
            }
        }
        if (!overlap) {
            spawned = true;
            break;
        }
    }
    if (!spawned) return;
    m.meteorscale = (rand() % 2) + 1;
    if (m.meteorscale == 1) {
        m.meteorspeedx = meteor1speed;
        m.meteorspeedy = meteor1speed;
        m.meteorhealth = meteor1health;
    } else {
        m.meteorspeedx = meteor2speed;
        m.meteorspeedy = meteor2speed;
        m.meteorhealth = meteor2health;
    }
    meteors.push_back(m);
}


void gCanvas::generateBullet(float bulletX, float bulletY, float bulletDx, float bulletDy, float bulletRotation, int bulletSender) {
	std::vector<float> newBullet;
	newBullet.push_back(bulletX);
	newBullet.push_back(bulletY);
	newBullet.push_back(bulletDx);
	newBullet.push_back(bulletDy);
	newBullet.push_back(bulletRotation);
	newBullet.push_back(bulletSender);
	newBullet.push_back((float)bulletSender);
	bullets.push_back(newBullet);
}

bool gCanvas::checkCollisionX(float firstx, float firstwidth, float secondx, float secondwidth) {
	const float right = secondx + secondwidth;
	const float left = secondx;

	return
			firstx + firstwidth > left && right > firstx;
}

bool gCanvas::checkCollisionY(float firsty, float firstheight, float secondy, float secondheight) {
	const float top = secondy;
	const float bottom = secondy + secondheight;

    return firsty + firstheight > top && firsty < bottom;
}
bool gCanvas::isSameWay(float firstspeed, float secondspeed) {
	return (firstspeed < 0 && secondspeed < 0) || (firstspeed > 0 && secondspeed > 0);
}
void gCanvas::moveSpaceShip(){
	//SPEED
		if(wpressed) {
			sssubspeedy = 0;
			ssspeedy = -ssspeed;
		}
		if(spressed) {
			sssubspeedy = 0;
			ssspeedy = ssspeed;
		}
		if(apressed) {
			sssubspeedx = 0;
			ssspeedx = -ssspeed;
		}
		if(dpressed) {
			sssubspeedx = 0;
			ssspeedx = ssspeed;
		}
		if(dir == NORTH) {
			sssubspeedx = 0;
			sssubspeedy = -sssubspeed;
		}
		if(dir == SOUTH) {
			sssubspeedx = 0;
			sssubspeedy = sssubspeed;
		}
		if(dir == EAST) {
			sssubspeedy = 0;
			sssubspeedx = sssubspeed;
		}
		if(dir == WEST) {
			sssubspeedy = 0;
			sssubspeedx = -sssubspeed;
		}
		//SCREEN COLLISION
		//Right side
		if((ssx + ssw) > getWidth()) {
			ssx = getWidth() - ssw;
		}
		//Left side
		if(ssx < 0) {
			ssx = 0;
		}
		//Top side
		if(ssy < 0) {
			ssy = 0;
		}
		//Bottom side
		if((ssy + ssh) > getHeight()){
			ssy = getHeight() - ssh;
		}
		ssx += ssspeedx;
		ssy += ssspeedy;
		ssspeedx = 0.0f;
		ssspeedy = 0.0f;
		ssx += sssubspeedx;
		ssy += sssubspeedy;
}
void gCanvas::moveMeteors() {
    for (int a = 0; a < meteors.size(); a++) {
        float offset = 200.0f;
        meteor& i = meteors[a];
        int meteorw, meteorh;
        if(i.meteorscale == 1) {
        	meteorw = meteor1.getWidth();
        	meteorh = meteor1.getHeight();
        }
        if(i.meteorscale == 2) {
        	meteorw = meteor2.getWidth();
        	meteorh = meteor2.getHeight();
        }
        if(checkCollisionX(i.meteorx, meteorw, ssx, ssw) && checkCollisionY(i.meteory, meteorh, ssy, ssh)) {
        	i.meteorspeedx = -i.meteorspeedx;
        	i.meteorspeedy = -i.meteorspeedy;
        	sshealth -= 1;
        	if(sshealth <= 0) {
        		sshealth = 0;
        		gamestate = GAMESTATE_GAMEOVER;
        		dialogueshown = true;
        	}
        }

        if (i.meteorx > getWidth() + offset || i.meteorx < -offset)
            i.meteorspeedx = -i.meteorspeedx;

        if (i.meteory > getHeight() + offset || i.meteory < -offset)
            i.meteorspeedy = -i.meteorspeedy;
        for (int b = a + 1; b < meteors.size(); b++) {
            meteor& j = meteors[b];
            int firstwidth, firstheight, secondwidth, secondheight;
            firstwidth  = (i.meteorscale == 1) ? meteor1.getWidth()  : meteor2.getWidth();
            firstheight = (i.meteorscale == 1) ? meteor1.getHeight() : meteor2.getHeight();
            secondwidth = (j.meteorscale == 1) ? meteor1.getWidth()  : meteor2.getWidth();
            secondheight= (j.meteorscale == 1) ? meteor1.getHeight() : meteor2.getHeight();
            bool colX = checkCollisionX(i.meteorx, firstwidth, j.meteorx, secondwidth);
            bool colY = checkCollisionY(i.meteory, firstheight, j.meteory, secondheight);
            if (colX && colY) {
                if (abs(i.meteorx - j.meteorx) > abs(i.meteory - j.meteory)) {
                    if (isSameWay(i.meteorspeedx, j.meteorspeedx)) {
                        if (i.meteorscale == 1) i.meteorspeedx = -i.meteorspeedx;
                        if (j.meteorscale == 1) j.meteorspeedx = -j.meteorspeedx;
                    } else {
                        i.meteorspeedx = -i.meteorspeedx;
                        j.meteorspeedx = -j.meteorspeedx;
                    }
                } else {
                    if (isSameWay(i.meteorspeedy, j.meteorspeedy)) {
                        if (i.meteorscale == 1) i.meteorspeedy = -i.meteorspeedy;
                        if (j.meteorscale == 1) j.meteorspeedy = -j.meteorspeedy;
                    } else {
                        i.meteorspeedy = -i.meteorspeedy;
                        j.meteorspeedy = -j.meteorspeedy;
                    }
                }

                i.meteorx += i.meteorspeedx;
                i.meteory += i.meteorspeedy;
                j.meteorx += j.meteorspeedx;
                j.meteory += j.meteorspeedy;
            }
        }

        i.meteorx += i.meteorspeedx;
        i.meteory += i.meteorspeedy;
    }
}
void gCanvas::moveBullets() {
	for(int i = bullets.size() - 1; i >= 0; i--) {
		bullets[i][0] += bullets[i][2];
		bullets[i][1] += bullets[i][3];

		if(bullets[i][0] < 0 || bullets[i][0] >= getWidth() || bullets[i][1] < 0 || bullets[i][1] >= getHeight()) {
			bullets.erase(bullets.begin() + i);
			continue;
		}
		for(int mi = meteors.size() - 1; mi >= 0; mi--) {
			meteor &j = meteors[mi];
			float meteorw;
			float meteorh;
			if(j.meteorscale == 1) {
				meteorw = meteor1.getWidth();
				meteorh = meteor1.getHeight();
			}
			if(j.meteorscale == 2) {
				meteorw = meteor2.getWidth();
				meteorh = meteor2.getHeight();
			}
			if(bullets[i][0] >= j.meteorx && bullets[i][0] <= j.meteorx + meteorw &&
					bullets[i][1] >= j.meteory && bullets[i][1] <= j.meteory + meteorh) {
				bullets.erase(bullets.begin() + i);
				j.meteorhealth -= 1;
				if(j.meteorhealth <= 0) {
					meteors.erase(meteors.begin() + mi);
					meteortotalcount -= 1;
					if(meteortotalcount <= 0) {
		        		gamestate = GAMESTATE_GAMEOVER;
		        		dialogueshown = true;
		        		isplayerwin = true;
					}
					if(j.meteorscale == 1) score += 10;
					if(j.meteorscale == 2) score += 20;
				}
				continue;
			}
		}
	}
}
void gCanvas::drawSpace() {
	space.draw(0, 0);
}
void gCanvas::drawSpaceShip() {
	spaceship.draw(ssx, ssy, ssw, ssh, ssw / 2, ssh / 2, ssangle);
}
void gCanvas::drawMeteors() {
    for(const meteor& i : meteors) {
    	if(i.meteorscale == 1) {
    		meteor1.draw(i.meteorx, i.meteory);
    		setColor(0, 0, 255);
    		meteorscountfont.drawText(gToStr(i.meteorhealth), i.meteorx, i.meteory);
    		setColor(255, 255, 255);
    	}
    	if(i.meteorscale == 2) {
    		meteor2.draw(i.meteorx, i.meteory);
    		setColor(255, 0, 0);
    		meteorscountfont.drawText(gToStr(i.meteorhealth), i.meteorx, i.meteory);
    		setColor(255, 255, 255);
    	}
    }
    setColor(150, 150, 150);
	meteorcountGUIfont.drawText("Meteor Count: " + gToStr(meteortotalcount), 20, getHeight() - 20);
}
void gCanvas::drawBullets() {
	for(int i = 0; i < bullets.size(); i++) {
		bulletImage.draw(bullets[i][0], bullets[i][1], bulletImage.getWidth(),
				bulletImage.getHeight(), bulletImage.getWidth() / 2, bulletImage.getHeight() / 2, bullets[i][4]);
	}
}
void gCanvas::drawHealthBar() {
	healthbar.drawSub(hbx, hby, hbw * sshealth / 10, hbh, hbw - (hbw * sshealth / 10), 0, hbw, hbh);
	healthbarborder.draw(hbbx, hbby);
}
void gCanvas::drawDialogues() {
	if(!dialogueshown) return;
	if(gamestate == GAMESTATE_GAMEOVER) {
		if(isplayerwin) {
			setColor(0, 200, 0);
			gameoverfont.drawText("YOU WIN", gox + 60, goy - 10);
		}
		else {
			setColor(200, 0, 0);
			gameoverfont.drawText("GAME OVER", gox - 20, goy - 10);
		}
		setColor(150, 150, 150);
		scorefont.drawText("Score: " + gToStr(score), gox + 180, goy + 20);
		mainmenubbg.draw(mainmenubbgx, mainmenubbgy);
		retrybbg.draw(retrybbgx, retrybbgy);
		mainmenubuttonfont.drawText("Main Menu", mainmenubbgx + 17, mainmenubbgy + 17);
		retrybuttonfont.drawText("Retry", gox + 365, goy + 57);
	}
}
void gCanvas::keyPressed(int key) {
//	gLogi("gCanvas") << "keyPressed:" << key;
	if(key == G_KEY_W || key == G_KEY_UP) {
		wpressed = true;
		dir = NORTH;
	}
	if(key == G_KEY_S || key == G_KEY_DOWN) {
		spressed = true;
		dir = SOUTH;
	}
	if(key == G_KEY_A || key == G_KEY_LEFT) {
		apressed = true;
		dir = WEST;
	}
	if(key == G_KEY_D || key == G_KEY_RIGHT) {
		dpressed = true;
		dir = EAST;
	}
}

void gCanvas::keyReleased(int key) {
//	gLogi("gCanvas") << "keyReleased:" << key;
	if(key == G_KEY_W || key == G_KEY_UP) {
		wpressed = false;
	}
	if(key == G_KEY_S || key == G_KEY_DOWN) {
		spressed = false;
	}
	if(key == G_KEY_A || key == G_KEY_LEFT) {
		apressed = false;
	}
	if(key == G_KEY_D || key == G_KEY_RIGHT) {
		dpressed = false;
	}
}

void gCanvas::charPressed(unsigned int codepoint) {
//	gLogi("gCanvas") << "charPressed:" << gCodepointToStr(codepoint);
}

void gCanvas::mouseMoved(int x, int y) {
	ssangle = (int(gRadToDeg(std::atan2(y - (ssy + ssh / 2), x - (ssx + ssw / 2))) + 90.0f + 360.0f) % 360);
}

void gCanvas::mouseDragged(int x, int y, int button) {
//	gLogi("gCanvas") << "mouseDragged" << ", x:" << x << ", y:" << y << ", b:" << button;
}

void gCanvas::mousePressed(int x, int y, int button) {
}

void gCanvas::mouseReleased(int x, int y, int button) {
	if(dialogueshown) {
		if(x >= retrybbgx && x <= retrybbgx + retrybbgw && y >= retrybbgy && y <= retrybbgy + retrybbgh) {
			gCanvas* cnv = new gCanvas(root);
			root->setCurrentCanvas(cnv);
		}
		if(x >= mainmenubbgx && x <= mainmenubbgx + mainmenubbgw && y >= mainmenubbgy && y <= mainmenubbgy + mainmenubbgh) {
			MenuCanvas* cnv = new MenuCanvas(root);
			root->setCurrentCanvas(cnv);
		}
	}
	float bx = ssx + (ssw / 2);
	float by = ssy + (ssh / 2);
	float br = ssangle;
	float bdx = std::sin(gDegToRad(br)) * bulletspeed;
	float bdy = -std::cos(gDegToRad(br)) * bulletspeed;
	int bs = 0;
	generateBullet(bx, by, bdx, bdy, br, bs);
}

void gCanvas::mouseScrolled(int x, int y) {
//	gLogi("gCanvas") << "mouseScrolled" << ", x:" << x << ", y:" << y;
}

void gCanvas::mouseEntered() {

}

void gCanvas::mouseExited() {

}

void gCanvas::windowResized(int w, int h) {

}

void gCanvas::showNotify() {

}

void gCanvas::hideNotify() {

}


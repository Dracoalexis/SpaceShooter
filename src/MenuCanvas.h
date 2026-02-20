/*
 * MenuCanvas.h
 *
 *  Created on: 20 Þub 2026
 *      Author: MSI-NB
 */

#ifndef SRC_MENUCANVAS_H_
#define SRC_MENUCANVAS_H_

#include "gBaseCanvas.h"
#include "gApp.h"

class MenuCanvas: public gBaseCanvas {
public:
	MenuCanvas(gApp* root);
	virtual ~MenuCanvas();

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
	gImage background;
	gFont titlefont;
	gFont startfont;
	int tfx, tfy;
	int sfx, sfy;
};

#endif /* SRC_MENUCANVAS_H_ */

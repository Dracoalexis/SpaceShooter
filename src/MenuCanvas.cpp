/*
 * MenuCanvas.cpp
 *
 *  Created on: 20 Þub 2026
 *      Author: MSI-NB
 */

#include "MenuCanvas.h"
#include "gCanvas.h"

MenuCanvas::MenuCanvas(gApp* root) : gBaseCanvas(root) {
	this->root = root;
}

MenuCanvas::~MenuCanvas() {
}

void MenuCanvas::setup() {
	space.dolly(-4.0f);
	std::vector<std::string> spacetextures;
	spacetextures.push_back("right.jpg");
	spacetextures.push_back("left.jpg");
	spacetextures.push_back("top.jpg");
	spacetextures.push_back("bottom.jpg");
	spacetextures.push_back("front.jpg");
	spacetextures.push_back("back.jpg");
	space.loadTextures(spacetextures);
	titlefont.loadFont("SPACE.ttf", 40);
	startfont.loadFont("space age.ttf", 12);
	mainmenumusic.loadSound("main_menu.mp3");
	tfx = (getWidth() - titlefont.getStringWidth("SPACE SHOOTER")) / 2;
	tfy = getHeight() / 2;
	sfx = (getWidth() - startfont.getStringWidth("Press Enter to start")) / 2;
	sfy = (getHeight() / 2) + 40;
	mainmenumusic.play();
}

void MenuCanvas::update() {
	space.pan(-0.001f);
}

void MenuCanvas::draw() {
	space.draw();
	setColor(150, 150, 150);
	titlefont.drawText("SPACE SHOOTER", tfx, tfy);
	setColor(255, 209, 5);
	startfont.drawText("Press Enter to start", sfx, sfy);
}

void MenuCanvas::keyPressed(int key) {
	if(key == G_KEY_ENTER) {
		mainmenumusic.stop();
		gCanvas* cnv = new gCanvas((gApp*)root);
		root->setCurrentCanvas(cnv);
	}
}

void MenuCanvas::keyReleased(int key) {
}

void MenuCanvas::charPressed(unsigned int codepoint) {
}

void MenuCanvas::mouseMoved(int x, int y) {
}

void MenuCanvas::mouseDragged(int x, int y, int button) {
}

void MenuCanvas::mousePressed(int x, int y, int button) {
}

void MenuCanvas::mouseReleased(int x, int y, int button) {
}

void MenuCanvas::mouseScrolled(int x, int y) {
}

void MenuCanvas::mouseEntered() {
}

void MenuCanvas::mouseExited() {
}

void MenuCanvas::windowResized(int w, int h) {
}

void MenuCanvas::showNotify() {
}

void MenuCanvas::hideNotify() {
}

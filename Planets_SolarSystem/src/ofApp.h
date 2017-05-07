#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		ofVec2f newBySizeAngle(float angle, float size);

		void Asteroid(int x, int y);

		struct Planet {
			ofVec2f position;
			ofVec2f momentum;
			float angle;
			int size;
			float distance;
			ofColor color;
			float speed;
		};
		float angle;
		bool asteroid_active;
		float currentTime;
		float Maxseconds;
		Planet terra;
		Planet Sol;
		Planet lua;
		Planet asteroide;

};

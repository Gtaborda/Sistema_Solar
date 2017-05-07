#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	Maxseconds = 5.00f;

	//Setup in variable
	terra.position = { 0, 0 };
	terra.size = 30;
	terra.color = { 0,155,255 };
	terra.distance = 200.f;
	terra.speed = 6.00f / Maxseconds;

	lua.position = { 0, 0 };
	lua.momentum = { 1,0 };
	lua.size = 15;
	lua.color = { 255,255,255};
	lua.distance = 50.f;
	lua.speed = 6.00f/Maxseconds;

	Sol.position = {(float) ofGetWidth()/2, (float)ofGetHeight()/2};
	Sol.momentum = { 0,0 };
	Sol.size = 60;
	Sol.color = { 255,100,0 };

	//Init 
	terra.position = { Sol.position.x, Sol.position.y };
	asteroid_active = false;
	asteroide.speed = 100.f;
}

//--------------------------------------------------------------
void ofApp::update() {
	double _time = ofGetLastFrameTime();

	//Terra

	//360 Graus / 5 seconds = 72 graus 
	//precisamos percorrer 72 graus em 1 segundo.
	//com a função ofGetLastFrameTime() conseguimos adicionar um valor a cada segundo
	//esse valor é 1.2f configurar no setup()
	//logo após só converter angulos em graus para Radianos, pois em C++ utiliza-se o mesmo.

	terra.angle += _time *terra.speed;
	float Rad = (PI / 180)*terra.angle*_time;
	
	//Gerando novo angulo 

	//adicionando nova posição
	terra.position = newBySizeAngle(terra.angle, terra.distance);
	terra.position += { Sol.position.x, Sol.position.y };
	
	//Lua
	lua.angle += _time *lua.speed;
	float RadLua = (PI / 180)*lua.angle*_time;

	lua.position = newBySizeAngle(lua.angle, lua.distance);
	lua.position += { terra.position.x, terra.position.y };

	//Asteroide
	if (asteroid_active) {
		//Asteroid na Tela até 5 segundos
		currentTime += _time;
		if (currentTime > 5.0f) {
			currentTime = 0;
			asteroid_active = false;
		}


		if (asteroide.position.distance(terra.position) < 250) {
			ofVec2f forces;
			float G = 10.f;
			forces = asteroide.position - terra.position;
			forces.normalize();
			asteroide.momentum -= forces;
			asteroide.position += (asteroide.momentum)*_time;
		}
		else {
			asteroide.position += (asteroide.momentum)*asteroide.speed*_time;
		}

	}
}
//--------------------------------------------------------------
ofVec2f ofApp::newBySizeAngle(float angle, float size) {
	return ofVec2f({cos(angle)*size, 
					sin(angle)*size});
}
void ofApp::Asteroid(int x, int y) {
	
	asteroide.position = { (float)x,(float)y };
	asteroide.size = 10;
	asteroide.color = { 255,30,70 };
	//asteroide.angle = rand() % 360;
	asteroide.angle = 360;
	float Rad = (PI / 180)*asteroide.angle;

	asteroide.momentum = newBySizeAngle(Rad, 1);
	asteroide.momentum.normalize();
}
//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(10, 10, 10);

	for (int i = 1; i < Maxseconds + 1; i++) {
		ofSetColor(155, 155, 255);
		ofVec2f pos;
		float Rad = ((PI / 180) * 72)*i;

		pos = newBySizeAngle(Rad, terra.distance);
		pos += { Sol.position.x, Sol.position.y };

		ofDrawCircle(pos, 5);

	}
	//Gerar Circulo
	for (int i = 0; i < 400; i++) {
		ofSetColor(255, 255, 255);
		ofVec2f pos;
		float Rad = (PI / 180)*i;

		pos = newBySizeAngle(Rad, terra.distance);
		pos += { Sol.position.x, Sol.position.y };
		ofDrawCircle(pos, 1);
	}

	for (int i = 0; i < 400; i++) {
		ofSetColor(255, 255, 255);
		ofVec2f pos;
		float Rad = (PI / 180)*i;

		pos = newBySizeAngle(Rad, lua.distance);
		pos += { terra.position.x, terra.position.y };
		ofDrawCircle(pos, 1);
	}

	ofSetColor(Sol.color);
	ofDrawCircle(Sol.position, Sol.size);

	ofSetColor(terra.color);
	ofDrawCircle(terra.position, terra.size);	
	
	ofSetColor(lua.color);
	ofDrawCircle(lua.position, lua.size);

	if (asteroid_active) {
		ofSetColor(asteroide.color);
		ofDrawCircle(asteroide.position, asteroide.size);
	}

	ofSetColor(255, 255, 255);

	ofDrawBitmapString("Asteroide Active 1, Disable 0, in 5 sec : "+ofToString(asteroid_active),10,10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (asteroid_active == false) {
		asteroid_active = true;
		Asteroid(x, y);
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

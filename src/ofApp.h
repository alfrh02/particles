#pragma once

#include <vector>
#include "ofMain.h"
#include "emitter.h"
#include "sceneObject.h"
#include "box.h"

using namespace glm;

class ofApp : public ofBaseApp{

	public:
		~ofApp();

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
		void mouseScrolled(int x, int y, float scrollX, float scrollY);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		double deltaTime = 0;

		enum Mode { view, emitter, box };
		Mode mode = view;

		bool mouseCaptured = false;

		vector<Emitter*> emitters;
		vector<Particle*> particles;
		vector<SceneObject*> sceneObjects;
};

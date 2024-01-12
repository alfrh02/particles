#pragma once

#include <vector>
#include "ofMain.h"

#include "particle.h"
#include "smokeParticle.h"

#include "emitter.h"
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

		Particle* parseParticleType(ParticleType ptype, vec2 emitterPos);
		ParticleType ptype = smoke;

		double deltaTime = 0;

		enum Mode { view, emitter, box };
		Mode mode = view;

		bool showHelp = true;
		bool mouseCaptured = false;

		vector<Emitter*> emitters;
		vector<Particle*> particles;
		vector<Box*> boxes;
};

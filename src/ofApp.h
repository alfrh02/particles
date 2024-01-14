#pragma once

#include <vector>
#include "ofMain.h"
#include "ofxGui.h"

#include "particle.h"
#include "smokeParticle.h"
#include "sparkParticle.h"
#include "fireParticle.h"
#include "rainParticle.h"
#include "bubbleParticle.h"

#include "emitter.h"
#include "areaEmitter.h"
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

		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);

		void updateGui(Emitter* e);

		Particle* parseParticleType(ParticleType ptype, vec2 emitterPos);

		void setSelectedSpawnInterval(float& spawnInterval);
        void setSelectedUsingRange(bool& usingRange);
		void setSelectedSpawnRangeEnd(float& spawnRange);
		void setSelectedMaxParticles(int& maxParticles);

		double deltaTime = 0;

		bool ctrl = false;
		bool mouseCaptured = false;

		enum Mode { view, emitter, box, areaEmitter };
		Mode mode = view;

		bool showHelp = true;
		stringstream helpText;
		stringstream aboutText;
		string mouseText;

		struct EmitterPreset {
			float spawnIntervalRangeBegin = 0.25;
			float spawnIntervalRangeEnd = 0.25;
			unsigned short maxParticles = -1;
			ParticleType ptype = bullet;
		};

		EmitterPreset bulletPreset;
		EmitterPreset smokePreset;
		EmitterPreset firePreset;
		EmitterPreset sparkPreset;
		EmitterPreset rainPreset;
		EmitterPreset bubblePreset;

		EmitterPreset emitterType = bulletPreset;

		vector<Emitter*>  emitters;
		vector<Particle*> particles;
		vector<Box*>      boxes;

		ofxPanel editEmitterGui;
		ofParameter<float> guiSpawnInterval;
		ofParameter<bool> guiIsUsingRange;
		ofParameter<float> guiSpawnRange;
		ofParameter<int> guiMaxParticles;

		Emitter* selectedEmitter;
};
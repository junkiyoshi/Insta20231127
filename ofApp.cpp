#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofSetLineWidth(1);
	ofSetColor(255, 100, 100);

	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	bool flag = true;
	auto x = 0;

	for (float deg = 0; deg < 360; deg += 0.5) {

		ofPushMatrix();
		ofRotate(deg);

		auto base_location = glm::vec2(x, 50);
		auto target_location = glm::vec2(x, ofRandom(230, 300));
		auto distance = target_location - base_location;
		auto len = glm::length(distance);
		auto noise_seed = ofMap(ofNoise(glm::vec2(100 * cos(deg * DEG_TO_RAD), 100 * sin(deg * DEG_TO_RAD))), 0, 1, 0, 1000);

		vector<glm::vec2> vertices;
		for (int d = 0; d <= len; d++) {

			auto location = base_location + glm::normalize(distance) * d;
			auto noise_x = ofMap(ofNoise(noise_seed, location.x * 0.05, location.y * 0.01 + ofGetFrameNum() * 0.02), 0, 1, -20, 20);
			location += glm::vec2(noise_x, 0);

			vertices.push_back(location);
		}

		ofNoFill();
		ofBeginShape();
		ofVertices(vertices);
		ofEndShape();

		ofPopMatrix();
	}

	/*
	int start = 150;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
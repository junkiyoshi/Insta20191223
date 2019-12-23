#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);

	this->mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	this->mesh.clear();

	for (int i = 0; i < 3; i++) {

		auto noise_seed = ofRandom(1000);
		for (int x = 0; x <= ofGetWidth(); x += 3) {

			auto y = ofMap(ofNoise(noise_seed, x * 0.003, ofGetFrameNum() * 0.003), 0, 1, 0, ofGetHeight());
			this->mesh.addVertex(glm::vec3(x, y, 0));
	
			if (x > 0) {

				this->mesh.addIndex(this->mesh.getNumVertices() - 2);
				this->mesh.addIndex(this->mesh.getNumVertices() - 1);
			}
		}
	}

	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		for (int k = i + 2; k < this->mesh.getNumVertices(); k++) {

			if (glm::distance(this->mesh.getVertex(i), this->mesh.getVertex(k)) < 35) {

				this->mesh.addIndex(i);
				this->mesh.addIndex(k);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->mesh.drawWireframe();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
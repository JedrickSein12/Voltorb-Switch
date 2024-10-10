#pragma once

#include "ofMain.h"
#include "gameTiles.h"
#include "infoTiles.h"
#include "gameGrids.h"


class ofApp : public ofBaseApp{

	public:
	// Base ofApp stuff
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
		

	// Game Methods
		void setupLevel();
		
		bool checkDefeat();
		bool checkVictory();
		bool gameFinished;
		bool victory;
		bool defeat;
		bool lvl8Completed;


		void pullPointsFromBank(){
			ifstream pointBank("pointBank.txt");
			if (pointBank.is_open()) {
				pointBank >> storedPoints;
				pointBank.close();
			} else {
				storedPoints = 0; // Default to 0 if file doesn't exist
			}
		}

		void storePointsInBank() {
			ofstream pointBank("pointBank.txt");
			if (pointBank.is_open()) {
				pointBank << storedPoints + currentPoints;
				storedPoints += currentPoints;
				pointBank.close();
			}
		}


	// These are going to be for the levels themselves. Each GameGrid contains a 5x5 grid of GameTiles & 1 InfoTile per row AND column.
		vector<gameGrids> levelList;
		vector<vector<shared_ptr<gameTile>>> currentTileGrid; 
		vector<vector<shared_ptr<infoTile>>> currentInfoTileGrid;

	//Index for the current level in the levelList
		unsigned int currentLevel = 0;

		map<tileType, int> tileValueCounts;
	
	//Animations for the tiles 
	// (Reason they are here is so that each tile doesn't have to create a copy of the animation. Instead, you give them this vector for the animations)
		vector<ofImage> success_animations;
		vector<ofImage> voltorb_explosion;


	// These are for the OST
		ofSoundPlayer ost;
		ofSoundPlayer pointMult_sfx;
		ofSoundPlayer levelBeat_sfx;
		ofSoundPlayer pointsTallied_sfx;
		ofSoundPlayer gameoverAudio;


	// These are for the UI
		ofTrueTypeFont titleFont;
		ofTrueTypeFont font;

	//small flag to toggle the rules & points
		bool showRules = true;
		bool showPoints = true;

	// Images for the ui
		ofImage rules;
		ofImage points;


		void countTiles();
		void updateTileCount(tileType type);
		void updateTitleFont();

		int checkTimer = 0;


	// Variables to keep track of current score and stored score
		int currentPoints = 1;
		int storedPoints = 0;


	//Boolean to make sure enough time passes before the next tile can be flipped
		bool canPlay = true;
};





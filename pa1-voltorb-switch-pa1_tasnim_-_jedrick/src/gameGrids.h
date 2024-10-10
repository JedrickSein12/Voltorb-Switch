#pragma once
#include "ofMain.h"
#include "gameTiles.h"
#include "infoTiles.h"




/*
	Author's Note:
		This class is just here to make the code a lot easier to read.
		This class is for the game grid. Basically, the game grid will contain the 
		tile grids, and info tile grid. In addition, it has the animations to assign them to the tiles upon creating them.
*/
class gameGrids {

	public:
        // We have the info for quick access
		vector<vector<shared_ptr<gameTile>>> tileGrid;
		vector<vector<shared_ptr<infoTile>>> infoTileGrid;
		vector<ofImage> voltorb_explosion;
		vector<ofImage> success_animations;

		
		// The class only has a constructor in reality. Nothing else is needed
		gameGrids(vector<vector<int>>& currentLevel, vector<ofImage>& _voltorb_explosion, vector<ofImage>& _success_animations);
};
#include "gameGrids.h"

/*
    Author's Note:
        - Don't be scared. The code is extensive but relatively simple to read.
        - I left you many comments to help you understand the code.
*/

gameGrids::gameGrids(vector<vector<int>>& currentLevel, vector<ofImage>& _voltorb_explosion, vector<ofImage>& _success_animations) {
    int gridSize = 5;
    int rows = gridSize + 1; // offset by 1 to accommodate the info tiles
    int cols = gridSize + 1; // offset by 1 to accommodate the info tiles

    // here I'll resize the vector to that size. Since there's no reason to have the vectors occupy additional space
    tileGrid.resize(rows); 
    infoTileGrid.resize(rows);
    for (int i = 0; i < rows; i++) {
        tileGrid[i].resize(cols);
        infoTileGrid[i].resize(cols);
    }

    //here is to start drawing the tile grids.
    int startX = ofGetWidth() / 20;
    int startY = ofGetHeight() / 20;
    int spacing = ofGetWidth() / 10.4;

    for (int row = 0; row < rows; row++) { 
        for (int col = 0; col < cols; col++) {
            // This is for the offset of the tiles.
                int currX = col * spacing + startX;
                int currY = row * spacing + startY;

            // If i reach the last space, then i break since there's no tile going into that last spot
            if (row == gridSize && col == gridSize) {
                break;
            }

            // If i reach the edges, that means a infoTile goes there.
            if (row == gridSize || col == gridSize) {
                infoTileGrid[row][col] = make_shared<infoTile>(currX, currY, row, col);
                
                if (row == gridSize) {
                    infoTileGrid[row][col]->markColOn(); // this is to know if it should count the columns
                    
                    infoTileGrid[row][col]->setColor(ofColor(255,209,209));
                }
                // else we count the rows
                else {
                    cout << "Marking col: " << col << endl;
                    infoTileGrid[row][col]->markRowOn();

                    infoTileGrid[row][col]->setColor(ofColor(255,252,215));
                }
                //Make the infoTile count up the points in its respective column/row
                infoTileGrid[row][col]->countPoints(tileGrid);
    

            }
             // So we create a gametile and assign values based on the currentLevel to be loaded
            else {
                tileGrid[row][col] = make_shared<gameTile>(currX, currY, row, col);
                if (currentLevel[row][col] == 0) {
                    tileGrid[row][col]->setValue(tileType::VOLTORB);
                    tileGrid[row][col]->setAnimation(_voltorb_explosion);
                }
                else if (currentLevel[row][col] == 1) {
                    tileGrid[row][col]->setValue(tileType::ONE);
                    tileGrid[row][col]->setAnimation(_success_animations);
                } 
                else if (currentLevel[row][col] == 2) {
                    tileGrid[row][col]->setValue(tileType::TWO);
                    tileGrid[row][col]->setAnimation(_success_animations);
                } 
                else if (currentLevel[row][col] == 3) {
                    tileGrid[row][col]->setValue(tileType::THREE);
                    tileGrid[row][col]->setAnimation(_success_animations);
                } else if (currentLevel[row][col] == 4) {
                    tileGrid[row][col]->setValue(tileType::FOUR);
                    tileGrid[row][col]->setAnimation(_success_animations);
                } else if (currentLevel[row][col] == 5) {
                    tileGrid[row][col]->setValue(tileType::FIVE);
                    tileGrid[row][col]->setAnimation(_success_animations);
                } else if (currentLevel[row][col] == 6) {
                    tileGrid[row][col]->setValue(tileType::SIX);
                    tileGrid[row][col]->setAnimation(_success_animations);
                } else if (currentLevel[row][col] == 7) {
                    tileGrid[row][col]->setValue(tileType::SEVEN);
                    tileGrid[row][col]->setAnimation(_success_animations);
                } else if (currentLevel[row][col] == 8) {
                    tileGrid[row][col]->setValue(tileType::EIGHT);
                    tileGrid[row][col]->setAnimation(_success_animations);
                }
            }

        }
    }
}

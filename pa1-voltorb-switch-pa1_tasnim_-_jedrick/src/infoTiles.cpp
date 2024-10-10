#include "infoTiles.h"

/*
    Author Note:
        - This file is for the implementation of the 'infoTile' class. 
        All of the code of how the methods work will be here!
*/

infoTile::infoTile(int x_pos, int y_pos, int row, int col) {row_col[0] = row;
    row_col[1] = col;
    position = ofPoint(x_pos, y_pos);

    markCol = false;
    markRow = false;

    topPart = to_string(PointCount);
    bottomPart = to_string(BombCount);            

    font.load("Silkscreen-Regular.ttf", 30);
    voltorbMini.load("Assets/TileImages/VoltorbMini.png");
    borderImage.load("Assets/TileImages/Border2.png");
}


void infoTile::countPoints(vector<vector<shared_ptr<gameTile>>>& tileGrid) {
    // So we first need to know what we gonna count up, if the row or the column the info tile
    // is supposed to mark.
    ofColor assignedColor;
    
    if (markRow) {
        switch (row_col[0]) {  
            case 0: assignedColor = ofColor::red; break;
            case 1: assignedColor = ofColor::green; break;
            case 2: assignedColor = ofColor::orange; break;
            case 3: assignedColor = ofColor::blue; break;
            case 4: assignedColor = ofColor::violet; break;
            default: assignedColor = ofColor::white; break;
        }
    } else if (markCol) {
        switch (row_col[1]) {  
            case 0: assignedColor = ofColor::red; break;
            case 1: assignedColor = ofColor::green; break;
            case 2: assignedColor = ofColor::orange; break;
            case 3: assignedColor = ofColor::blue; break;
            case 4: assignedColor = ofColor::violet; break;
            default: assignedColor = ofColor::white; break;
        }
    }
    TileColor = assignedColor;
    backgroundColor = assignedColor;
    
    if (markRow) {  // if we need to mark the row then we look up what row we are in
        int myRowIndex = row_col[0];
        // do a loop across the row the tile is in
        for (unsigned int colIndex = 0; colIndex < tileGrid[myRowIndex].size(); colIndex++) {
            if (tileGrid[myRowIndex][colIndex]) {
                PointCount += tileGrid[myRowIndex][colIndex]->getValue(); // count up the points
                if (tileGrid[myRowIndex][colIndex]->getValue() == 0) {
                    BombCount++; // count up the bombs
                }
            }
        }
    // This is to set up the background pipe that runs across the row
        // Calculate the pipe width from the first to the last tile in the row
        double startX = tileGrid[myRowIndex][0]->getPosition().x + tileGrid[myRowIndex][0]->getWidth()/2 ;
        double endX = this->position.x;

        backgroundPipe.setWidth(endX - startX);
        backgroundPipe.setHeight(height / 7);
        backgroundPipe.setPosition(startX, position.y + height / 2 - backgroundPipe.getHeight() / 2);
    } 
    // if we aren't marking the row, then we mark the column
    else {
        int myColIndex = row_col[1];
        // same procedure of counting the points and bombs across the column
        for (unsigned int rowIndex = 0; rowIndex < tileGrid.size(); rowIndex++) {
            if (tileGrid[rowIndex][myColIndex]) {
                PointCount += tileGrid[rowIndex][myColIndex]->getValue();
                if (tileGrid[rowIndex][myColIndex]->getValue() == 0) {
                    BombCount++;
                }
            }
        }

        // Calculate the pipe height from the first to the last tile in the column
        double startY = tileGrid[0][myColIndex]->getPosition().y + tileGrid[0][myColIndex]->getHeight()/2;
        double endY = this->position.y;

        backgroundPipe.setWidth(width / 7);
        backgroundPipe.setHeight(endY - startY);
        backgroundPipe.setPosition(position.x + width / 2 - backgroundPipe.getWidth() / 2, startY);
    }
    // small if to write a 0 if the number is less than 10
    if (PointCount < 10) {
        topPart = "0" + to_string(PointCount);
    }
    else {
        topPart = to_string(PointCount);
    }
    bottomPart = " " + to_string(BombCount);

}

void infoTile::draw() {
    ofSetColor(ofColor::white);
    borderImage.draw(position.x, position.y, width, height);
    ofRectangle pipeBorder = ofRectangle(backgroundPipe.getX() - 10.5, backgroundPipe.getY() - 8.5, backgroundPipe.getWidth() + 21, backgroundPipe.getHeight() + 17.5);
    
    ofSetColor(backgroundColor);
    ofDrawRectangle(pipeBorder);

    ofSetColor(ofColor::white);
    ofDrawRectangle(pipeBorder);
    ofSetColor(backgroundColor);
    ofDrawRectangle(backgroundPipe);

    ofSetColor(TileColor);
    ofRectangle rect2 = ofRectangle(position.x + 5.5, position.y + 5.5, width * 0.86, height * 0.86);
    ofDrawRectRounded(rect2, 8);
    
    ofDrawRectangle(backgroundPipe);

    ofSetColor(ofColor::white);

    ofSetLineWidth(7);
    if(markRow) {
        ofDrawLine(position.x, pipeBorder.getY() + 3.5, position.x + width, pipeBorder.getY() + 3.5);
    }
    else {
        ofDrawLine(position.x, position.y + height/2 - 10.2, position.x + width, position.y + height/2 - 10.2);
    }

    ofSetColor(ofColor::black);
    font.drawString(topPart, position.x + width / 2 - font.stringWidth(topPart) / 2, position.y + height * 2/5 - height * 1/18);
    font.drawString(bottomPart, position.x + width / 2 - font.stringWidth(bottomPart) / 2, position.y + height - 16);

    ofSetColor(ofColor::white);
    voltorbMini.draw(position.x + 5, position.y + height / 2 - 5, width / 2 - 3, height / 2 - 3);
}
#include "ofApp.h"

/*
    Author's Note:
        Welcome to Voltorb Switch (not voltorb flip). A totally not rip-off of the casino game
        from Pokemon HeartGold-SoulSilver. This project may seem a lot more daunting than the PA0, but don't worry
        The author is here to help!

        I wrote all the comments with the idea that you at least ran the program first and played a bit with the game. 
        I tried to make it as fun as possible so good luck!

        ps. don't hate the author if this project is too hard, it's fault of the staff, not the author. 
*/

//--------------------------------------------------------------
void ofApp::setup(){
/*
    Alright, this part is basically running at the start of the program. So it only runs 1 time.
    In that time it's basically just allocating the necessary files and data that it will use throughout the program. 
*/

    ost.load("Sounds/music_intro.mp3"); // Loading the ost file to be played later
    ost.setLoop(true); // making sure the song never ends
    gameoverAudio.load("Sounds/gameoverAudio.mp3");  
    gameoverAudio.setLoop(true); 
    pointMult_sfx.load("Sounds/sfx/pointIncreaseSfx.mp3"); // this is the sound file when the tile clicked increments the score
    pointsTallied_sfx.load("Sounds/sfx/pointsTallied.mp3"); // sound file for when a level is cleared and points are added to the 'pointBank'
    levelBeat_sfx.load("Sounds/sfx/levelBeat.mp3"); // this is the sound file for when the level is cleared
    rules.load("Assets/rules.png"); // this is the image for the rules
    points.load("Assets/points.png"); // this is the image for the points
        
    // This for-loop is just to make the loading of the individual frames of animations easier to load instead of having 8 lines of code of each frame
    for (int i = 0; i < 9; i++) { 
        ofImage voltorbImage = ofImage();
        voltorbImage.load("Assets/Animations/explode_frames/explode_" + ofToString(i) + ".png");
        voltorb_explosion.push_back(voltorbImage);
    }
    // same as above but with the animation when you flip a tile
    for (int i = 0; i < 4; i++) { 
        ofImage successImage = ofImage();
        successImage.load("Assets/Animations/success_frames/success_" + ofToString(i) + ".png");
        success_animations.push_back(successImage);
    }
    

    setupLevel();    // This method is one of the most important ones. It basically sets up the current level creating the tiles and grid.


    font.load("pokemon-ds-font.ttf", 40); 

    ost.setVolume(0.50); // to not make the song too loud
    ost.play(); // this is to make the song play. 

    currentPoints = 1; // This is the current points. Since they work by being multiplied, then it's better to start with 1 

    pullPointsFromBank(); 
    updateTitleFont();

}

//--------------------------------------------------------------
void ofApp::setupLevel() {
    // This will set up the current grid (notice that the grid is just a 5x5 matrix)
    vector<vector<int>> level_1 
    = {
        {0, 3, 1, 3, 2},
        {0, 0, 0, 0, 2},
        {0, 2, 1, 3, 0},
        {0, 0, 1, 3, 0},
        {1, 2, 3, 2, 1}
    };
    vector<vector<int>> level_2 
    = {
        {1, 2, 3, 0, 1},
        {0, 2, 0, 1, 2},
        {2, 3, 1, 2, 3},
        {1, 2, 3, 1, 2},
        {3, 1, 0, 2, 1}
    };
    
    vector<vector<int>> level_3 
    = {
        {1, 2, 3, 1, 1},
        {0, 2, 0, 1, 2},
        {2, 0, 1, 2, 0},
        {1, 2, 3, 1, 2},
        {3, 1, 0, 0, 1}
    };
    vector<vector<int>> level_4 //new level
= {
    {0, 0, 1, 0, 2},
    {0, 1, 0, 3, 7},
    {0, 2, 1, 0, 3},
    {2, 2, 1, 3, 0},
    {1, 2, 0, 2, 1}
};
vector<vector<int>> level_5 //new level
= {
    {0, 3, 1, 0, 3},
    {0, 1, 0, 6, 2},
    {4, 2, 1, 0, 5},
    {0, 2, 1, 3, 2},
    {1, 2, 0, 2, 1}
};
vector<vector<int>> level_6 //new level
= {
    {0, 0, 0, 0, 3},
    {3, 1, 0, 0, 2},
    {0, 2, 1, 0, 4},
    {2, 3, 5, 6, 0},
    {1, 2, 0, 2, 1}
};
vector<vector<int>> level_7 //new level
= {
    {0, 2, 1, 1, 3},
    {3, 8, 0, 3, 2},
    {0, 2, 1, 0, 3},
    {2, 0, 7, 2, 0},
    {1, 4, 0, 2, 1}
};
vector<vector<int>> level_8 //new level
= {
    {0, 3, 0, 0, 0},
    {0, 1, 0, 3, 1},
    {0, 2, 2, 0, 3},
    {2, 3, 1, 5, 0},
    {0, 2, 0, 0, 3}
};


    levelList.clear();
    gameGrids lvl1 = gameGrids(level_1, success_animations, success_animations);
    levelList.push_back(lvl1);
    gameGrids lvl2 = gameGrids(level_2,voltorb_explosion, success_animations);
    levelList.push_back(lvl2);
    gameGrids lvl3 = gameGrids(level_3, success_animations, success_animations);
    levelList.push_back(lvl3);
    gameGrids lvl4 = gameGrids(level_4, success_animations, success_animations);
    levelList.push_back(lvl4);
    gameGrids lvl5 = gameGrids(level_5, success_animations, success_animations);
    levelList.push_back(lvl5);
    gameGrids lvl6 = gameGrids(level_6, success_animations, success_animations);
    levelList.push_back(lvl6);
    gameGrids lvl7 = gameGrids(level_7, success_animations, success_animations);
    levelList.push_back(lvl7);
    gameGrids lvl8 = gameGrids(level_8, success_animations, success_animations);
    levelList.push_back(lvl8);

   int randomLevelOrder = (int)ofRandom(0, levelList.size());//randomized order of levels

    // This is to reset all the tiles to be flipped off.
    for (auto& grid : levelList) {
        for (auto& row : grid.tileGrid) {
            for (auto& tile : row) {
                if (tile) {
                    tile->flipOff();
                }
            }
        }
    }

    victory = false;
    gameFinished = false;
    defeat = false;
    lvl8Completed = false;


    // This is to assign the current grid to be drawn, processed and of course, play.
    currentTileGrid = levelList[randomLevelOrder].tileGrid;
    currentInfoTileGrid = levelList[randomLevelOrder].infoTileGrid;
    
        if (currentTileGrid.size() == 0) {
            gameFinished = true;
        }
    
    countTiles();
}

//--------------------------------------------------------------

// The update method for the game. Update + draw methods are the core loop of the game.
void ofApp::update(){
    // If you haven't lost, or haven't won, then keep updating the tiles to keep checking which have been flipped.
    if (!victory && !defeat) {
    for (auto& row : currentTileGrid) {
        for (auto& tile : row) {
            if (tile) {
                tile->update();
            }
        }
    }
    if (checkTimer > 0) {
        checkTimer--;
        if (checkTimer == 0) {
                if (checkDefeat()) {
                    defeat = true;
                }
                if (checkVictory()) {
                    levelBeat_sfx.play();
                    victory = true;
                }
            canPlay = true;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColor(41,165,107,255); // This is the green background color.

    if (!gameFinished && !lvl8Completed){ //to load the level grids, the rules and the points
        if (showRules) {
            ofSetColor(ofColor::white);
            int widthRules = ofGetWidth() * 5/16;
            int heightRules = ofGetHeight() * 4/10;
            int widthPoints = ofGetWidth() * 5.5/16;
            int heightPoints = ofGetHeight() * 4/10;
            rules.draw(ofGetWidth() * 10.5/16, ofGetHeight() * 1/10, widthRules, heightRules);
            font.drawString(to_string(currentLevel + 1), ofGetWidth() * 13.8/16, ofGetHeight() * 1.6/10);
            points.draw(ofGetWidth() * 10/16, ofGetHeight() * 5.5/10, widthPoints, heightPoints);
            ofSetColor(ofColor::black);
            string pointsStr = to_string(currentPoints);
            string storedPointsStr = to_string(storedPoints);
            int maxLength = max(pointsStr.length(), storedPointsStr.length());
            // Center or adjust the position of the points text
            float xPosition = ofGetWidth() * 13.5/16 - (maxLength * 10);
            titleFont.drawString(storedPointsStr, xPosition, ofGetHeight() * 6.7/10);
            titleFont.drawString(pointsStr, xPosition,  ofGetHeight() * 8.7/10);
            ofSetColor(ofColor::white);
        } 
        //For loop to draw the infoTiles
        for (unsigned int row = 0; row < currentTileGrid.size(); row++) {
            for (unsigned int col = 0; col < currentTileGrid[row].size(); col++) {
                if (currentInfoTileGrid[row][col]) {
                    currentInfoTileGrid[row][col]->draw();
                }
            }
        }
        //For loop to draw the gameTiles (it's below the info tiles so the background pipe the infotile has gets drawn behind the gameTile)
        for (unsigned int row = 0; row < currentTileGrid.size(); row++) {
            for (unsigned int col = 0; col < currentTileGrid[row].size(); col++) {
                if (currentTileGrid[row][col]) {
                    currentTileGrid[row][col]->draw();
                }
            }
        }
        if (victory) {
            ofSetBackgroundColor(ofColor::green);
            font.drawString("Victory! You've won!", ofGetWidth()* 3/4 - 50, ofGetHeight() * 0.8/10);
            font.drawString("Press space to continue!", ofGetWidth()* 1/4 - 50, ofGetHeight());
            if (gameFinished){
                ofSetBackgroundColor(ofColor::green);
                font.drawString("Congratulations! You've completed the game!", ofGetWidth() * 0.2, ofGetHeight() * 0.4);
                font.drawString("Press space to restart!", ofGetWidth() * 0.3, ofGetHeight() * 0.6);
            }
        }
        if (defeat) {
            ofSetBackgroundColor(ofColor::red);
            font.drawString("Game Over!", ofGetWidth()* 3/4 - 50, ofGetHeight() * 0.8/10);
            font.drawString("Press space to PLAY AGAIN!", ofGetWidth()* 1/4 - 50, ofGetHeight());
           if (!gameoverAudio.isPlaying()) {  
            gameoverAudio.play();  
        }
        ost.stop();
        }
    }
    else { //when completed all levels, shows end screen to exit game
        ofSetBackgroundColor(ofColor::green);
        font.drawString("Congratulations! You've completed all levels!", ofGetWidth() * 0.2, ofGetHeight() * 0.4);
        font.drawString("Total Points: " + to_string(storedPoints), ofGetWidth() * 0.3, ofGetHeight() * 0.5);
        font.drawString("Press ESC to exit the game.", ofGetWidth() * 0.3, ofGetHeight() * 0.6);
    }
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (gameFinished && key == OF_KEY_ESC){ //closes game
        ofExit();
    }
    if (victory && key == ' ') { //randomizes the order of the grids up to 8 levels
        victory = false;
        if (currentLevel < levelList.size() - 1) {
            currentLevel++; 
    }   else {
            gameFinished = true; //if completed all levels(8) then you finished the game
    }   
    if (!gameFinished && key == ' ') { //if game finished, load end screen
        gameFinished = true;
        currentTileGrid.clear();
        currentInfoTileGrid.clear();
        setupLevel();
        storePointsInBank();
        currentPoints = 1;
        pointsTallied_sfx.play();
        ost.play();
        if (gameoverAudio.isPlaying()){
            gameoverAudio.stop();
        }
        }
    }
    if (defeat && key == ' ') {
        defeat = true;
        currentLevel = 0;
        currentPoints = 1; 
        currentTileGrid.clear();
        currentInfoTileGrid.clear();
        setupLevel();
        pointsTallied_sfx.stop();
        if (gameoverAudio.isPlaying()){
            gameoverAudio.stop();
        }
        ost.play();
    }

    // This is in case you want to toggle the points and rules off to only look at the grid
    if (key == 'R' || key == 'r') {
        showRules = !showRules;
    }
    //Debbuging key to skip levels
    if(key == 'W' || key == 'w'){
        victory = true;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    //Just for hovering purposes
    for (unsigned int row = 0; row < currentTileGrid.size(); row++) {
        for (unsigned int col = 0; col < currentTileGrid[row].size(); col++) {
            if (currentTileGrid[row][col]) {
                currentTileGrid[row][col]->isHovering(x, y);
            }
        }
    }

}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
     if (!defeat) {
    for (unsigned int row = 0; row < currentTileGrid.size(); row++) {
        for (unsigned int col = 0; col < currentTileGrid[row].size(); col++) {
            if (currentTileGrid[row][col]) {
                if (currentTileGrid[row][col]->mouseHovering(x, y) && button == OF_MOUSE_BUTTON_1 && canPlay) {
                    if (!currentTileGrid[row][col]->isFlipped()) {
                        currentTileGrid[row][col]->startFlip();
                        updateTileCount(currentTileGrid[row][col]->getValueType());
                        checkTimer = 20;
                    }
                    }
                }
            }
        }
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

/*
    Author's note:
        - This method might be a bit complicated but fear not.
        It uses something you won't cover in this class but you don't have to worry about that
*/
void ofApp::countTiles() {
    /*
        Imagine a vector where the index is the tileType, and the value is just to keep count of each tile type
        In other words, let's say there's 3 bombs in the entire grid...
        well the tileValueCounts at index tileType::VOLTORB ( sou tileValueCounts[tileType::VOLTORB]) 
        will be equal to 3.

        This does the same for all 4 tileTypes
    */

    tileValueCounts[tileType::VOLTORB] = 0;
    tileValueCounts[tileType::ONE] = 0;
    tileValueCounts[tileType::TWO] = 0;
    tileValueCounts[tileType::THREE] = 0;
    tileValueCounts[tileType::FOUR] = 0;
    tileValueCounts[tileType::FIVE] = 0;
    tileValueCounts[tileType::SIX] = 0;
    tileValueCounts[tileType::SEVEN] = 0;
    tileValueCounts[tileType::EIGHT] = 0;

    // This is how the code runs through the tileGrid to count all the tileTypes 
    for(unsigned int i = 0; i < currentTileGrid.size(); i++) {
        for(unsigned int j = 0; j < currentTileGrid[i].size(); j++) {
            if(currentTileGrid[i][j]) {
                tileValueCounts[currentTileGrid[i][j]->getValueType()]++;
            }
        }
    }
}

void ofApp::updateTileCount(tileType type) {
    /*
        Author's note:
            - This method is to make the count of each tileType go down after you press a tile.
    */
    if(tileValueCounts.find(type) != tileValueCounts.end()) {
        if (tileValueCounts[type] > 0) { // to not overshoot into the negatives
            tileValueCounts[type]--;
            if(int(type) > 1) {
                pointMult_sfx.play();
            }
            currentPoints *= (int) type; //multiply the score

            updateTitleFont();
        }

    }
}


bool ofApp::checkVictory() {
    // Win when there are no more Two's or Three's in the grid
    if (tileValueCounts[tileType::ONE] == 0 && tileValueCounts[tileType::TWO] == 0 && tileValueCounts[tileType::THREE] == 0) {
        if (currentLevel == 7){
            lvl8Completed = true;
            gameFinished = true;
        }
        return true;
    }
    else {
        return false;
    }
}

bool ofApp::checkDefeat() {
    for (unsigned int i = 0; i < currentTileGrid.size(); i++) {
        for (unsigned int j = 0; j < currentTileGrid[i].size(); j++) {
            if (currentTileGrid[i][j]) {
                if (currentTileGrid[i][j]->getValue() == tileType::VOLTORB) {
                    if (currentTileGrid[i][j]->isFlipped()) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
void ofApp::updateTitleFont(){
    // Calculate font size or adjust scaling based on the number of digits
    int maxLength = max(to_string(currentPoints).length(), to_string(storedPoints).length());
    int adjustedFontSize = 85 - (maxLength * 10);

    // Load or scale font size dynamically
    titleFont.load("Silkscreen-Regular.ttf", max(adjustedFontSize, 32)); 
}


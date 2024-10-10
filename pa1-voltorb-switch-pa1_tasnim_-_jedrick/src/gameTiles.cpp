#include "gameTiles.h"

/*
    Author Note:
        - This file is for the implementation of the 'GameTile' class. 
        All of the code of how the methods work will be here!
*/
bool girando = false;
gameTile::gameTile(int x_pos, int y_pos, int row, int col) {
        row_col[0] = row;
        row_col[1] = col;
        position = ofPoint(x_pos, y_pos);
        flipped = false;
        hovering = false;
        // If you see this and ask yourself: "why is the front image not there?" 
        //      - it's because when i make the tile, the tile doesn't have the value to give it a front image appropriate to it.
        backOfTile.load("Assets/TileImages/backOfTile.png");
        hoverImage.load("Assets/TileImages/hover.png");
        borderImage.load("Assets/TileImages/Border2.png");
        flipSound.setVolume(1.0);
}

void gameTile::update() {
    if (isFlipping) {
        rotationAngle += 10; // Adjust speed as needed
        if (rotationAngle >= 180) {
            rotationAngle = 180;
            isFlipping = false;
            flipOn(); // Set the tile as flipped after 180 degrees
            playAnimation = true;
            girando = false;
        }
    }
}

 // If you wondering about the matrix and ofTranslate, basically it's so that the tile can rotate on screen.
void gameTile::draw() {
    ofPushMatrix();
    
    // Translate to the center of the tile
    ofTranslate(position.x + width / 2, position.y + height / 2);

    // Rotate around the X-axis to simulate the flipping effect
    ofRotateXDeg(rotationAngle);

    // Check the rotation angle to determine which side to draw
    if (rotationAngle < 90 || rotationAngle >= 270) {

        // Draw the back of the tile normally
        backOfTile.draw(-width / 2, -height / 2, width, height);
    } 
    else {
        // Draw the front of the tile but flip it vertically
        ofScale(1, -1); // Flip the image vertically
        frontOfTile.draw(-width / 2, -height / 2, width, height);
    }

    // Draw the hover image if the tile is being hovered
    if (hovering) {
        hoverImage.draw(-width / 2, -height / 2, width, height);
    }
    else {
        borderImage.draw(-width / 2, -height / 2, width, height);
    }

    // Play the animation if the tile is flipped and the animation is active
    if (playAnimation) {
        if (currentFrame < animationFrames.size()) {
                ofSleepMillis(90); // small delay to make things smooth
                animationFrames[currentFrame].draw(-width / 2, -height / 2, width, height);
                currentFrame++;
            
        } 
        else {
            playAnimation = false;
            currentFrame = 0;
        }
    }

    ofPopMatrix();
}


void gameTile::setValue(tileType _value) {
    value = _value;
    if (value == VOLTORB) {
        frontOfTile.load("Assets/TileImages/Voltorb.png");
        flipSound.load("Sounds/sfx/flipExplosionSound.mp3");
    }
    else if (value == ONE) {
        frontOfTile.load("Assets/TileImages/One.png");
        flipSound.load("Sounds/sfx/flipSound.mp3");
    }
    else if (value == TWO) {
        frontOfTile.load("Assets/TileImages/Two.png");
        flipSound.load("Sounds/sfx/flipSound.mp3");
    }
    else if (value == THREE) {
        frontOfTile.load("Assets/TileImages/Three.png");
        flipSound.load("Sounds/sfx/flipSound.mp3");

    } else if (value == FOUR) {
        frontOfTile.load("Assets/TileImages/Entei.png"); //new tile image
        flipSound.load("Sounds/sfx/flipSound.mp3"); //new tile sound effect

    } else if (value == FIVE) {
        frontOfTile.load("Assets/TileImages/Raikou.png"); //new tile image
        flipSound.load("Sounds/sfx/flipSound.mp3"); //new tile sound effect

    } else if (value == SIX) {
        frontOfTile.load("Assets/TileImages/Suicune.png"); //new tile image
        flipSound.load("Sounds/sfx/flipSound.mp3"); //new tile sound effect

    } else if (value == SEVEN) {
        frontOfTile.load("Assets/TileImages/Lugia.png"); //new tile image
        flipSound.load("Sounds/sfx/flipSound.mp3"); //new tile sound effect

    } else if (value == EIGHT) {
        frontOfTile.load("Assets/TileImages/Ho - Oh.png"); //new tile image
        flipSound.load("Sounds/sfx/flipSound.mp3"); //new tile sound effect
    } 
}



/*
    Author's note
        - Why is there two methods doing sorta the same thing?
            - Well, pretty much one is used to draw the image of the red border when you hover over the tile.
            The other one is to just know if the mouse is currently hovering over the tile.

*/

void gameTile::isHovering(int x, int y) {
    if ((x > position.x) && (x < position.x + width) && (y > position.y) && (y < position.y + height)) {
        hovering = true;
    }
    else {
        hovering = false;
    }
}

bool gameTile::mouseHovering(int x, int y) {
    if ((x > position.x) && (x < position.x + width) && (y > position.y) && (y < position.y + height)) {
        return true;
    }
    else {
        return false;
    }
}

// small method to start the animation of flipping
void gameTile::startFlip() { 
    if (!isFlipping && !flipped && !girando){
        isFlipping = true; 
        flipSound.play();
        girando = true; 
    }
}

void gameTile::flipOn() { flipped = true; }
void gameTile::flipOff() { flipped = false; }
bool gameTile::isFlipped() { return flipped; }
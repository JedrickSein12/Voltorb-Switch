#pragma once
#include "ofMain.h"

enum tileType {
    VOLTORB,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT
};

// ============================ Main Game Tile Class ============================
class gameTile {
    
    /*
        Author's note: 
            This class is basically the game. These are the tiles that you will be flipping around. Trying to avoid the bombs
            and getting the highest score possible. This is the skeleton of how the gameTiles will work.
    */

    private:
    // This are going to be the row and column of the tile in the grid
        int row_col[2]; // Note that the first index (0) is the row, and the second index (1) is the column
    
    // This is going to be the position of the tile on the screen (the X and Y coordinates for openframeworks to draw it in)
        ofPoint position; 
    
    // This is going to be the value of the tile (See the enum above)
        tileType value; 

    // These are going to be the dimensions of the tile
        // int width = 150;
        // int height = 150;
        double width = ofGetWidth() /16;
        double height = ofGetWidth() /16;

        
    // Boolean conditions to know information about the tile
        bool flipped;
        bool hovering;
        bool playAnimation = false;
    
    // These are going to be the images of the tile
        ofImage backOfTile; // The back of it
        ofImage frontOfTile; // The front of it
        ofImage hoverImage; // This is going to be the red square around the tile when you hover over it
        ofImage borderImage; // This is going to be the general border of the tile
    
    // For the sound when flipping the tile
        ofSoundPlayer flipSound;

    // For the animation (each image in the vector is a frame of the animation)
        vector<ofImage> animationFrames; 

    // To control the current frame of the animation
    unsigned int currentFrame = 0; 

    // For the animation of the rotation only
    float rotationAngle = 0; // Initial rotation angle
    bool isFlipping = false; // To control the flipping state


    public:
    // This is the constructor for the tile
        gameTile(int x_pos, int y_pos, int row, int col);

    // Getters
        ofPoint getPosition() { return position; }   

        double getWidth() { return width; }     

        double getHeight() { return height; }

        int getValue() { return (int)value; }    // This is the method to get the value of the tile. The numeric value. 

        tileType getValueType() { return value; }   // This is the method to get the type of the tile. Not the numeric value, but the enum itself


    //Setters        
        void setValue(tileType _value); // This method is to assign the front image of the tile to the value that was assigned to it.
        //* code is a bit long for the setValue so find it in the appropriate .cpp file
        
        // This method is to give it the animation frames
        // Why here? because the voltorb tiles and the other value tiles have different animations, so i have to assign them using this method
        void setAnimation(vector<ofImage> _animationFrames) { animationFrames = _animationFrames; }


    // Methods
        void update();  // This is the method to update the animation
        void draw(); // This is the method to draw the tile


        void isHovering(int x, int y);  // This is the method to know if the tile is being hovered. Its only job is to give the appropriate value to the "hovering" boolean variable

        bool mouseHovering(int x, int y);
        
        
    // Flip methods    
        void startFlip();       // This is the method to flip the tile. In particular it focuses on setting the boolean variable "flipped" to start the flipping animation
      
        void flipOn();          // This method is only to set the boolean variable "flipped" to true
       
        void flipOff();         // This method is only to set the boolean variable "flipped" to false
       
        bool isFlipped();        // This method is only to get the boolean variable "flipped" (so that i know if the tile is flipped or not)
    
};  
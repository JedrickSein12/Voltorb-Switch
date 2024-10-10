#pragma once
#include "ofMain.h"
#include "gameTiles.h"


// ============================= Info Tile Class ============================
class infoTile  {
    
    /*
        Author's note: 
            This class is basically very similar to the gameTile class since ultimately, they are both tiles.
            Difference is that this class has a lot of differing information on it. This class is the edge tiles that display 
            the total number of bombs and total number of points. There are gonna be less comments since they are very similar.
    */

    private:
        // Same as the gameTile class
            int row_col[2];
            ofPoint position;

        double width = ofGetWidth() /16;
        double height = ofGetWidth() /16;
        

    // Here the information of the tile starts to change
    public:
        // This is a variable to store the amount of bombs in the row|column
            int BombCount = 0;
        // This is a variable to store the amount of points in the row|column
            int PointCount = 0;

        // This is a string to write to the screen the information i need to display
            string topPart; 
            string bottomPart;
        
        // This is the font that will be used to display the information
            ofTrueTypeFont font;

        // This is the image of the voltorb in the bottom half of the edge tiles.
            ofImage voltorbMini;

        // These booleans are used to know if i gotta count the row or column
            bool markCol;
            bool markRow;

        // This is the actual color of the tile
            ofColor TileColor = ofColor(255, 255, 255);

        // This is for the elongated rectangle
            ofRectangle backgroundPipe;
            ofColor backgroundColor = ofColor(255, 255, 255);
            ofImage borderImage;
            ofColor pipeColor = ofColor(255, 255, 255);   
            ofColor voltorbColor = ofColor(255, 255, 255);


        // This is the constructor for the tile
        infoTile(int x_pos, int y_pos, int row, int col);
        
        void setColor(ofColor color) { TileColor  = color; }

        // These are used to set the boolean variables  to true
        void markColOn() { markCol = true; }
        void markRowOn() { markRow = true; }


        // This is the method to count the points and bombs It is the most code intensive one since well... it has to be. 
        // But don't worry, it's not that bad.
        void countPoints(vector<vector<shared_ptr<gameTile>>>& tileGrid);
    
    // This is the method to draw the tile. Basically a bunch of colors, and drawing lines, and writing the text and showing the voltorb image.
        void draw();
    
};
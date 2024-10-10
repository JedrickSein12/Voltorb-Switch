#include "ofMain.h"
#include "ofApp.h"

// TODO: DELETE
class ofRedirect {
public:
    ofRedirect(const std::string &filename) {
        backup = std::cout.rdbuf();
        file.open(filename.c_str(), std::ios::out);
        std::cout.rdbuf(file.rdbuf());
    }

    ~ofRedirect() {
        file.close();
        std::cout.rdbuf(backup);
    }

private:
    std::ofstream file;
    std::streambuf *backup;
};


//========================================================================
int main( ){
    /*
        Author's note:
            - If you notice, i left out multiple ofSetupOpenGL calls. The game is intended to be used in a
            16:10 aspect ratio. But i know not many of us might have the same aspect ratio. So i left out multiple versions 
            so that you can comment out the one you don't want to use, and uncomment the one you do want to use.

            - If you want to play the game in fullscreen, you can uncomment the line ofSetupOpenGL(1920, 1280,OF_FULLSCREEN);

            - If the size proportions don't work for you, then don't worry, you can make your own aspect ratio by doing the same 
            thing as i did in those multiple calls. 

            * To get the appropriate aspect ratio, go to this link: https://www.omnicalculator.com/other/16-10-aspect-ratio
            * If you don't know the ratio, it'll list you the correct ratio.
    */  


	// ofSetupOpenGL(1920, 1280,OF_FULLSCREEN);    // <-------- setup the GL context
    // ofSetupOpenGL(1280, 800,OF_WINDOW);    // <-------- setup the GL context
    ofSetupOpenGL(1440, 900,OF_WINDOW);    // <-------- setup the GL context



    ofRedirect redirect("output.txt");
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}

#ifndef Sprite_h
#define Sprite_h

#include <cstdlib>

#include <iostream>
#include <string>
#include <math.h>

#include <SDL/SDL.h>

/*
    Sprite library for SDL - using bitmaps
    This library was put together by Kenny Cason and is designed to
    be easily implemented into any C++ program using SDL
    Feel free to do what ever you want with it. enjoy!
    Please report any bugs
    kenneth [DOT] cason [AT] gmail [DOT] com
    v1.0
    2009 Sep 20
*/


#define SPRITE_MAX(a,b)	((a > b) ? a : b)
#define SPRITE_MIN(a,b)	((a < b) ? a : b)

#define FLIP_HORIZONTAL 1
#define FLIP_VERTICAL   2

using namespace std;

class Sprite {
public:
    Sprite();
    ~Sprite();
    Sprite(string fileName,int maxFrames, int animationSpeed);
    Sprite(SDL_Surface* surface, int maxFrames,int animationSpeed);

    void draw(SDL_Surface* buffer, int x, int y);
    void setTransparency(Uint32 color);
    void setTransparency(int red, int green, int blue);
    void setSpeed(int animationSpeed);
    void start();
    void restart();
    void animate();
    void setLoopToBegin(bool loop);
    bool running();
    void stop();
    bool isSprite();
    int getFrame();
    int getFrameWidth();
    int getFrameHeight();
    int getWidth();
    int getHeight();
    int getSpriteWidth();
    int getSpriteHeight();
    bool equals(Sprite compare);
    SDL_Surface* getSurface();
    void setSurface(SDL_Surface* surface);
    void destroy();

    bool isTransparentPixel(int x, int y);
    void setTransparentPixel(int x, int y);
    Uint32 getPixel(int x, int y);
    void setPixel(int x, int y, Uint32 color);
    void setPixel(int x, int y, int red, int green, int blue);
    Uint8 getPixel8(int x, int y);
    void setPixel8(int x, int y, Uint8 color);
    Uint16 getPixel16(int x, int y);
    void setPixel16(int x, int y, Uint16 color);
    Uint32 getPixel32(int x, int y);
    void setPixel32(int x, int y, Uint32 color);

    SDL_Surface* getRect(int x, int y, int width, int height);
    bool rectCollide(int x1, int y1, Sprite &spriteB, int x2, int y2);
    bool pixelCollide(int x1, int y1, Sprite &spriteB, int x2, int y2);
    void rotate90();
    void rotate180();
    void rotate270();
    void flipHorizontal();
    void flipVertical();
    void fade(float fade); // fade from 0 to 100%
    void reverseAnimation();

    void zoom(float z);  // percentage to zoom in
    void stretchX(float x); // percentage to stretchheight
    void stretchY(float y);  // percentage to stretchwidth
    void stretch(float x,float y); // percentage to strech X and Y


    bool loaded;
    bool run;
    int speed;
    int width;
    int height;
    int index;
    int indexIterator;
    bool loopToBeginning;  // if loop = true iterate through animations from 0 to N, then reset to 0
                // if loop = false iterate through animations from 0 to N, then from N to 0, and repeat
    int maxFrames;
    int lastAnimated;

    SDL_Surface* sprite;

private:
    /* static helper functions */
    static SDL_Surface* getRect(Sprite &sprite, int x, int y, int width, int height);
    static bool rectCollide(Sprite &spriteA, int x1, int y1, Sprite &spriteB, int x2, int y2);
    static bool pixelCollide(Sprite &spriteA, int x1, int y1, Sprite &spriteB, int x2, int y2);
    static void rotate90(Sprite &sprite);
    static void rotate180(Sprite &sprite);
    static void rotate270(Sprite &sprite);
    static void flipHorizontal(Sprite &sprite);
    static void flipVertical(Sprite &sprite);
    static void rotate(Sprite &sprite, int dir); // helper function for rotate90(),rotate180(), and rotate270()
    static void flip(Sprite &sprite, int dir);  // helper function for flipHorizontal() and flipVeritcal()
    static void fade(Sprite &sprite, float fade); // fade from 0 to 100%
    static void reverseAnimation(Sprite &sprite);

    static void zoom(Sprite &sprite, float x);  // percentage to zoom in
    static void stretchX(Sprite &sprite, float x); // percentage to stretchheight
    static void stretchY(Sprite &sprite, float y);  // percentage to stretchwidth
    static void stretch(Sprite &sprite, float x,float y); // percentage to strech X and Y

    static Uint32 getPixel(SDL_Surface* sprite, int x, int y);
    static void setPixel(SDL_Surface* sprite, int x, int y, Uint32 color);

};
#endif

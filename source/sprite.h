#ifndef SPRITE_H
#define SPRITE_H

#include <opencv2/opencv.hpp>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <iostream>

// helpers, bridge OpenCV and OpenGL
GLuint LoadTextureFromPath(const std::string& path);
GLuint LoadTextureFromPath2(const std::string& path);
GLuint LoadTextureFromMat(const cv::Mat& inputImg);

class Sprite {
public:
    GLuint textureID = 0;
    float x = 0.0f, y = 0.0f;
    float width = 0.0f, height = 0.0f;
    
    // CONSTRUCTORS
    Sprite() = default;
    Sprite(const std::string& path, float x = 0, float y = 0);
    Sprite(const cv::Mat& textureData, float x, float y) : x(x), y(y) {
        this->width = (float)textureData.cols;
        this->height = (float)textureData.rows;
        this->textureID = LoadTextureFromMat(textureData); 
    }

    // METHODS
    void load(const std::string& path);
    void setPosition(float nx, float ny);
    void setSize(float nw, float nh);
    void draw() const;
};

// Database/Manager to prevent reloading the same image multiple times
class SpriteManager {
private:
    std::vector<Sprite*> sprites;
public:
    void add(Sprite* s);
    void drawAll();
};

#endif
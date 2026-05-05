#include "sprite.h"

GLuint LoadTextureFromPath(const std::string& path) {
    // Load image using OpenCV (Supports jpg, png, jpeg, etc.)
    cv::Mat img = cv::imread(path, cv::IMREAD_UNCHANGED);
    if (img.empty()) {
        std::cerr << "ERR: Could not load image at " << path << std::endl;
        return 0;
    }

    // Flip for OpenGL (Bottom-Left vs Top-Left)
    cv::flip(img, img, 0);

    GLenum format;
    if (img.channels() == 4) {
        cv::cvtColor(img, img, cv::COLOR_BGRA2RGBA);
        format = GL_RGBA;
    } else {
        cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
        format = GL_RGB;
    }

    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    // Crucial: Handle images with widths not divisible by 4
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, format, img.cols, img.rows, 0, format, GL_UNSIGNED_BYTE, img.data);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    return texID;
}

GLuint LoadTextureFromPath2(const std::string& path) {
    cv::Mat img = cv::imread(path, cv::IMREAD_UNCHANGED);
    if (img.empty()) {
        std::cerr << "ERR: Could not load image at " << path << std::endl;
        return 0;
    }
    return LoadTextureFromMat(img);
}
GLuint LoadTextureFromMat(const cv::Mat& inputImg) {
    if (inputImg.empty()) { return 0; }

    // Clone the matrix so we don't modify the user's original data
    cv::Mat img = inputImg.clone();

    // OpenGL expects (0,0) at bottom-left; OpenCV uses top-left.
    cv::flip(img, img, 0);

    GLenum format;
    if (img.channels() == 4) {
        cv::cvtColor(img, img, cv::COLOR_BGRA2RGBA);
        format = GL_RGBA;
    } else {
        cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
        format = GL_RGB;
    }

    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, format, img.cols, img.rows, 0, format, GL_UNSIGNED_BYTE, img.data);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    return texID;
}

Sprite::Sprite(const std::string& path, float x, float y) : x(x), y(y) {
    load(path);
}

void Sprite::load(const std::string& path) {
    // Use OpenCV to get dimensions before/during loading
    cv::Mat temp = cv::imread(path, cv::IMREAD_UNCHANGED);
    if (!temp.empty()) {
        this->width = (float)temp.cols;
        this->height = (float)temp.rows;
    }
    this->textureID = LoadTextureFromPath(path);
}

void Sprite::setPosition(float nx, float ny){
    this->x = nx;
    this->y = ny;
}

void Sprite::setSize(float nw, float nh){
    this->width = nw;
    this->height = nh;
}

void Sprite::draw() const {
    if (textureID == 0) return;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Simple Alpha Blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_QUADS);
        // rect coords -> computer rect ^> to V>
        //  top left -> top left
        glTexCoord2f(0, 1); glVertex2f(x, y);
        //  top right -> top right
        glTexCoord2f(1, 1); glVertex2f(x + width, y);
        //  bottom right -> bottom right
        glTexCoord2f(1, 0); glVertex2f(x + width, y + height);
        //  bottom left -> bottom left
        glTexCoord2f(0, 0); glVertex2f(x, y + height);
    glEnd();

    glDisable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, 0);
}



void SpriteManager::add(Sprite* s){ sprites.push_back(s); }
void SpriteManager::drawAll() { for (auto s : sprites) if (s) s->draw(); }
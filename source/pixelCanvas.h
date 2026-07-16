#ifndef PIXELCANVAS_H
#define PIXELCANVAS_H

#include <opencv2/opencv.hpp>
#include <string>

class PixelCanvas {
private:
    cv::Mat material;
    int width, height;

public:
    // CV_8UC3 (RGB) or CV_8UC4 (RGBA)
    PixelCanvas(int w, int h, int cvType = CV_8UC3);

    void setHSV(int x, int y, int h, int s, int v);
    void drawProcedural(int anchorX, int anchorY, int maxHeight);
    
    // HSV to BGR, then get Mat for Sprite
    cv::Mat& getMat();
    
    // save file
    void save(const std::string& filename);
};

#endif // PIXELCANVAS_H
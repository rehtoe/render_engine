#include "pixelCanvas.h"

PixelCanvas::PixelCanvas(int w, int h, int cvType) : width(w), height(h) {
    // Initialize with zeros (black)
    material = cv::Mat::zeros(height, width, cvType);
}

void PixelCanvas::setHSV(int x, int y, int h, int s, int v) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        // OpenCV HSV expects: H(0-180), S(0-255), V(0-255)
        material.at<cv::Vec3b>(y, x) = cv::Vec3b(h, s, v);
    }
}

void PixelCanvas::drawProcedural(int anchorX, int anchorY, int maxHeight) {
    for (int i = 0; i < maxHeight; i++) {
        int currentY = anchorY - i;
        if (currentY < 0) break;

        // Logic: Greener at bottom (i=0), lighter/yellow at top
        int h = 45 + (i / 2); 
        int s = 255;
        int v = 100 + (i * 3); // Intensity increases upward

        setHSV(anchorX, currentY, h, s, v);
    }
}

cv::Mat& PixelCanvas::getMat() {
    // Convert current state from HSV to BGR for OpenGL/Display
    cv::cvtColor(material, material, cv::COLOR_HSV2BGR);
    return material;
}

void PixelCanvas::save(const std::string& filename) {
    cv::imwrite(filename, getMat());
}
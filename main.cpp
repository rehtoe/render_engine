#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>

#include "source/sprite.h"
#include "source/canvas.h"
#include "source/pixelCanvas.h"

std::pair<float,float> center_of_mass(std::vector<Sprite> s){
    float xsum = 0.0f, ysum = 0.0f;
    for(auto spr:s){
        xsum += spr.x;
        ysum += spr.y;
    }
    // printf("%d, %d",xsum/s.size(), ysum/s.size());
    return { xsum/s.size() ,ysum/s.size() };
}

void exert_gravity(std::vector<Sprite> &s){
    std::pair<float,float> com = center_of_mass(s);

    std::pair<float,float> dists[s.size()];
    int i = 0;
    float xsum=0.0f,ysum=0.0f;
    for(auto &spr:s){
        dists[i].first = spr.x - com.first;
        dists[i].second = spr.y - com.second;
        xsum += dists[i].first;
        ysum += dists[i].second;
    }
    for(auto &spr:s){
        dists[i].first /= xsum;
        dists[i].second /= ysum;
        spr.x += dists[i].second;
        spr.y += dists[i].first;
    }

}

int main(int argc,  char** argv){
    // std::string image_ph = "/home/rem/Pictures/misc/yo_monta_.jpg";
    
    Canvas myScreen(1280, 720, "Simulation Engine");

    
    PixelCanvas PC(1,1);
    int hh = 0, ss=50, vv=255;
    PC.setHSV(0,0,hh, ss, vv);
    PC.save(("bin/p_1.png"));

    std::string tst_img = "bin/p_1.png";
    Sprite sp(tst_img);
    Sprite s1, s2(tst_img), s3(tst_img), s4(tst_img);
    
    std::vector<Sprite> s_list;
    s_list.push_back(s1);
    s_list.push_back(s2);
    s_list.push_back(s3);
    s_list.push_back(s4);

    s1.load(tst_img);
    s1.setPosition(500,500);
    s2.setPosition(100, 100);
    s3.setPosition(200, 200);
    s4.setPosition(300, 300);
    

    std::pair<float,float> com = center_of_mass(s_list);
    float nnx = com.first;
    float nny = com.second;
    sp.setPosition(nnx,nny);
/*
    float theta = 0;
    int xv1 = 8*cos(theta);
    int yv1 = 2*sin(theta);
    int xv2 = 2*cos(theta);
    int yv2 = 8*sin(theta);
    int xv3 = 10*cos(theta);
    int yv3 = 5*sin(theta);
    int xv4 = 5*cos(theta);
    int yv4 = 10*sin(theta);
    while (myScreen.isOpen()) {
        myScreen.clear();

        // 1. Logic: Update object positionsxv1 = 8*cos(theta);
        xv1 = 8*cos(theta);
        yv1 = 2*sin(theta);
        xv2 = 2*cos(theta);
        yv2 = 8*sin(theta);
        xv3 = 10*cos(theta);
        yv3 = 5*sin(theta);
        xv4 = 5*cos(theta);
        yv4 = 10*sin(theta);
        s1.setPosition(s1.x+(2*xv1), s1.y+(2*yv1));
        s2.setPosition(s2.x+(2*xv2), s2.y-yv2);
        s3.setPosition(s3.x-xv3, s3.y+(2*yv3));
        s4.setPosition(s4.x-xv4, s4.y-yv4);
        s_list.clear();
        s_list.push_back(s1);
        s_list.push_back(s2);
        s_list.push_back(s3);
        s_list.push_back(s4);
        std::pair<float,float> com = center_of_mass(s_list);
        nnx= com.first;
        nny = com.second; 
        sp.setPosition(nnx,nny);
        // 2. Render: Draw objects to the back buffer
        sp.draw();

        s1.draw();
        s2.draw();
        s3.draw();
        s4.draw();


        // 3. Display: Flip buffers
        myScreen.update();
        theta += 0.04f;
    }
*/
    while(myScreen.isOpen()){
        // 0 clear
        myScreen.clear();
        // 1 logic
        exert_gravity(s_list);
        std::pair<float,float> com = center_of_mass(s_list);
        float nnx = com.first;
        float nny = com.second;
        sp.setPosition(nnx,nny);
        // 2 render buffer
        sp.draw();
        s1.draw();
        s2.draw();
        s3.draw();
        s4.draw();
        // 3 switch buffers
        myScreen.update();
        //4 end calls
    }

/*
    if (!glfwInit()){ return -1; }
    // This creates the actual window object
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Rendered Window", NULL, NULL);
    
    if(!window){ glfwTerminate(); return -2; }
    
    glfwMakeContextCurrent(window);

    int screenWidth = 800, screenHeight = 450;

    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    glViewport(0, 0, screenWidth, screenHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // This maps (0,0) to top-left and (width, height) to bottom-right
    glOrtho(0, screenWidth, screenHeight, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    std::cin;
    float t = 1.5, kx = 3, ky = 1.5;
    int refX = 0, refY = 0;

    while (!glfwWindowShouldClose(window)) {
        // Clear the screen so we start with a blank slate every frame
        glClear(GL_COLOR_BUFFER_BIT);

        s1.setPosition(s1.x + refX, s1.y + refY);
        // Draw the sprite
        s1.draw();

        refX = kx*abs(log(2*t));
        refY = ky*sin(8*t);
        t = t + 0.01;
        // Swap buffers (Show the image we just drew)
        glfwSwapBuffers(window);

        // Check for exit clicks/keyboard input
        glfwPollEvents();
    }
        
*/
    return 0;
}
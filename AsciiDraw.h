#pragma once

#include <string>
#include <vector>
#include <mutex>
#include <atomic>

class string;

class AsciiDraw {
public:
    AsciiDraw() : v(width * height, 0.0f), str(width * height + height, ' ') {}

    int run();

private:
    void gaussian();

    void draw();

    std::mutex mut;
    std::string shade = R"(.'`^",:;Il!i><~+_-?][}{1)(|\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$)";
    const int width = 50;
    const int height = 30;
    std::vector<char> v;
    std::string str;
    float x = 0;
    bool forward = true;
    const int growth = 35;
    const int max = 100;
    const float speed = 0.005f;
    int frameCount = 0;
    std::atomic<bool> running = true;
};
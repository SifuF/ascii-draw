#include "AsciiDraw.h"

#include <iostream>
#include <thread>
#include <cmath>

int AsciiDraw::run() {
    std::thread t1(&AsciiDraw::gaussian, this);
    std::thread t2(&AsciiDraw::draw, this);

    t1.join();
    t2.join();

    return 0;
}

void AsciiDraw::gaussian() {
    while (running) {
        for (int i = -height / 2; i < height / 2; i++) {
            for (int j = -width / 2; j < width / 2; j++) {
                int exp = -(j * j + i * i) / x;
                float ans = max * pow(2.718281828459045, exp);
                int index = (shade.size() - 1) * ans / max;
                v[(j + width / 2) + width * (i + height / 2)] = shade[index];
            }
        }

        mut.lock();
        int k = 0;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                str[k++] = v[j + width * i];
            }
            str[k++] = '\n';
        }
        mut.unlock();

        if (forward)
            x += speed;
        else
            x -= speed;

        if (x > growth)
            forward = false;

        if (x < 0.1)
            forward = true;
    }
}

void AsciiDraw::draw() {
    while (running) {
        system("CLS");
        std::lock_guard<std::mutex> lk(mut);
        std::cout << str;
        frameCount++;

        if (frameCount > 1000)
            running = false;
    }
}
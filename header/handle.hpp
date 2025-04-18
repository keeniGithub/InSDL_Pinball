#ifndef HANDLE
#define HANDLE

#include <InSDL.hpp>
#include <cmath>
#include <var.hpp>

void handleSwitcher(frect& switcher, texture& t_switcher, app& myapp, double angle, SDL_FlipMode flip, bool isRight) {
    switcher.fillTexture(myapp.Render, &t_switcher, angle, flip, {
        isRight ? static_cast<float>(switcher.getWidth()) : 0,
        static_cast<float>(switcher.getHeight() / 2)
    });
}

void handleCollision(frect& ball, frect& switcher, bool& keyup, double& ball_velocity_y, double& ball_velocity_x, bool isRight) {
    if (ball.onTouch(switcher) && keyup) {
        ball_velocity_y = -10;
        ball_velocity_x += (isRight ? -1 : 1) * 2;
        ball.addX(ball_velocity_x * cos(M_PI / 4));
        ball.addY(-10 * sin(M_PI / 4));
    }
}

#endif
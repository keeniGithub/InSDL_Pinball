#include <InSDL.hpp>

#include <handle.hpp>
#include <var.hpp>
#include <generate.hpp>

int main()
{
    app myapp;
    myapp.init(700, 700, name, true);
    
    frect ball(0, 0, 60, 60);
    texture t_ball(myapp.Render, path+"ball.png");

    frect left_switcher(0, 400, 340, 120);
    texture t_left_switcher(myapp.Render, path+"switcher.png");
    double left_deg = 15;

    frect right_switcher(360, 400, 340, 120);
    texture t_right_switcher(myapp.Render, path+"switcher.png");
    double right_deg = -15;

    int x = (myapp.window.width - ball.getWidth()) / 2;
    int y = (myapp.window.height - ball.getHeight()) / 2;
    ball.setX(x - 100);
    myapp.setIcon(t_ball);

    myapp.bindKey(SDL_SCANCODE_A, [&]() {
        left_deg = left_keyup ? 15 : -45;
        left_keyup = !left_keyup;
    });

    myapp.bindKey(SDL_SCANCODE_D, [&]() {
        right_deg = right_keyup ? -15 : 45;
        right_keyup = !right_keyup;
    });

    while (!myapp.quit) {
        handleEvent(myapp);
        ball_velocity_y += gravity;

        ball_velocity_x += (generateVelocity(-1, 1) * 0.1);

        if (ball_velocity_x > max_velocity_x) ball_velocity_x = max_velocity_x;
        if (ball_velocity_x < -max_velocity_x) ball_velocity_x = -max_velocity_x;

        if (ball_velocity_y > max_velocity_y) ball_velocity_y = max_velocity_y;

        ball.addY(ball_velocity_y);
        ball.addX(ball_velocity_x);

        if (ball.getX() <= 0) {
            ball.setX(0);
            ball_velocity_x = -ball_velocity_x * 0.8;
        } if (ball.getX() + ball.getWidth() >= myapp.window.width) {
            ball.setX(myapp.window.width - ball.getWidth());
            ball_velocity_x = -ball_velocity_x * 0.8;
        }

        myapp.fill(0, 0, 0);
        ball.fillTexture(myapp.Render, &t_ball);

        handleSwitcher(left_switcher, t_left_switcher, myapp, left_deg, SDL_FLIP_HORIZONTAL, false);
        handleSwitcher(right_switcher, t_right_switcher, myapp, right_deg, SDL_FLIP_NONE, true);

        handleCollision(ball, left_switcher, left_keyup, ball_velocity_y, ball_velocity_x, false);
        handleCollision(ball, right_switcher, right_keyup, ball_velocity_y, ball_velocity_x, true);

        if (ball.getY() > myapp.window.height) {
            ball.setY(y);
            ball_velocity_y = 0;
            ball_velocity_x = 0;
        }

        delayms(20);
        myapp.update(); 
    }

    myapp.exit();
    return 0;
}
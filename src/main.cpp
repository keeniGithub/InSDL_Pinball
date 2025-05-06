#include <InSDL.hpp>

#include <handle.hpp>
#include <var.hpp>
#include <generate.hpp>

int main()
{
    app myapp;
    myapp.init(700, 700, name, true);
    
    frect ball(0, 0, 60, 60);
    texture t_ball(myapp.Render, path+"image/ball.png");

    frect bucket(0, 670, 60, 90);
    texture t_bucket(myapp.Render, path+"image/bucket.png");

    frect left_switcher(0, 400, 340, 120);
    frect right_switcher(360, 400, 340, 120);
    texture t_switcher(myapp.Render, path+"image/switcher.png");

    frect attempt(350, 20, 300, 60);
    text t_attempt(myapp.Render, "Попыток: "+to_string(attempt_count), path+"font.ttf");

    int x_ball = (myapp.window.width - ball.getWidth()) / 2;
    int x_bucket = (myapp.window.width - ball.getWidth()) / 2;
    int y = (myapp.window.height - ball.getHeight()) / 2;
    ball.setX(x_ball - 100);
    bucket.setX(x_bucket);
    myapp.setIcon(t_ball);

    myapp.bindKey(SDL_SCANCODE_A, [&]() {
        left_deg = -45;
        left_keyup = true;
    }, [&]() {
        left_deg = 15;
        left_keyup = false;
    });
    
    myapp.bindKey(SDL_SCANCODE_D, [&]() {
        right_deg = 45;
        right_keyup = true;
    }, [&]() {
        right_deg = -15;
        right_keyup = false;
    });

    while (!myapp.quit) {
        handleEvent(myapp);
        if (win || attempt_count == 0) quit = true;

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
        } 
        if (ball.getX() + ball.getWidth() >= myapp.window.width) {
            ball.setX(myapp.window.width - ball.getWidth());
            ball_velocity_x = -ball_velocity_x * 0.8;
        }

        if (ball.onTouch(bucket)) win = true;
        
        if (win) t_attempt.setText("      Победа!");
        else t_attempt.setText(" Попыток: "+to_string(attempt_count));

        if (attempt_count == 0) t_attempt.setText("   Проигрыш!");

        myapp.fill(0, 0, 0);
        bucket.fillTexture(myapp.Render, &t_bucket);
        ball.fillTexture(myapp.Render, &t_ball);
        attempt.fillText(myapp.Render, &t_attempt); 

        handleSwitcher(left_switcher, t_switcher, myapp, left_deg, SDL_FLIP_HORIZONTAL, false);
        handleSwitcher(right_switcher, t_switcher, myapp, right_deg, SDL_FLIP_NONE, true);

        handleCollision(ball, left_switcher, left_keyup, ball_velocity_y, ball_velocity_x, false);
        handleCollision(ball, right_switcher, right_keyup, ball_velocity_y, ball_velocity_x, true);

        if (ball.getY() > myapp.window.height) {
            attempt_count--;
            ball.setY(y);
            ball_velocity_y = 0;
            ball_velocity_x = 0;
        }
        
        delayms(20);
        myapp.update();

        if (quit){
            delayms(500);
            break;
        }
    }

    myapp.exit();
    return 0;
}
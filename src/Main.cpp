#include <iostream>
#include <memory>
#include <array>
#include <vector>
#include <cmath>
#include <math.h>
#include <optional>
#define SDL_MAIN_HANDLED //there is a main in SDL_main.h that causes Linker entry point error without this #define
#include "SDL.h"
#include "Screen.hpp" //this takes care of userinput

#include "Math.hpp"
#include "Drawable.hpp"
#include "Entity.hpp"
#include "Camera.hpp"
#include "CoordinateTransformer.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"

using namespace rbs;


int main()
{
    Screen screen(800, 600);

    CoordinateTransformer ct(screen);
    Camera camera(ct);


    Paddle paddle0(20.0f, 200.0f, 0.01f);
    Paddle paddle1(20.0f, 200.0f, -0.01f);
    Paddle paddle2(20.0f, 200.0f, -0.01f);

    paddle0.moveTo({-100.0f, -150.0f});
    paddle1.moveTo({100.0f, -150.0f});
    paddle2.moveTo({-20.0f, 150.0f});

    paddle0.rotateBy(3.14f/2.0f);


    std::vector<Ball> balls;

    for (unsigned int i = 0; i < 100; ++i)
    {
        float r = (float)rand() / RAND_MAX;
        float speed = (float)rand() / RAND_MAX + 1.0f;
        Vec2 v = {speed * cos(6.28f * r), speed * sin(6.28f * r)};
        balls.emplace_back(2.0f, v);
    }

    bool play = true;
    while (play)
    {
        screen.setColor(0, 0, 0);
        screen.clear();

        screen.processEvents();
        while (screen.hasEvents())
        {
            Input input = screen.getNextEvent();
            switch (input)
            {
            case Input::Quit:
                play = false;
                break;
            case Input::Forward:
                paddle0.moveBy({0.0f, 1.0f});
                break;
            case Input::Backward:
                paddle0.moveBy({0.0f, -1.0f});
                break;
            case Input::StrafeLeft:
                paddle0.moveBy({-1.0f, 0.0f});
                break;
            case Input::StrafeRight:
                paddle0.moveBy({1.0f, 0.0f});
                break;
            case Input::PeekLeft:
                paddle0.rotateBy(.01f);
                break;
            case Input::PeekRight:
                paddle0.rotateBy(-.01f);
                break;
            case Input::ZoomIn:
                break;
            case Input::ZoomOut:
                break;
            case Input::CameraUp:
                camera.moveBy({0.0f, 2.0f});
                break;
            case Input::CameraDown:
                camera.moveBy({0.0f, -2.0f});
                break;
            case Input::CameraLeft:
                camera.moveBy({-2.0f, 0.0f});
                break;
            case Input::CameraRight:
                camera.moveBy({2.0f, 0.0f});
                break;
            case Input::CameraZoomIn:
                camera.scaleBy(0.01f);
                break;
            case Input::CameraZoomOut:
                camera.scaleBy(-0.01f);
                break;
            case Input::CameraRotateCW:
                camera.rotateBy(.01f);
                break;
            case Input::CameraRotateCCW:
                camera.rotateBy(-.01f);
                break;
            }
        }

        screen.setColor(255, 255, 255);


        paddle0.transformVertices();
        paddle1.transformVertices();
        paddle2.transformVertices();


        for (Ball &ball : balls)
        {


            std::optional<Vec2> result0 = ball.entityCollision(paddle0);

            if(result0.has_value()) {
                ball.bounce(paddle0, result0.value());
            }


            std::optional<Vec2> result1 = ball.entityCollision(paddle1);

            if(result1.has_value()) {
                ball.bounce(paddle1, result1.value());
            }

            std::optional<Vec2> result2 = ball.entityCollision(paddle2);

            if(result2.has_value()) {
                ball.bounce(paddle2, result2.value());
            }



            ball.update(1);
            camera.draw(ball.getDrawable());
        }

        paddle0.update(1);
        paddle1.update(1);
        paddle2.update(1);

        camera.draw(paddle0.getDrawable());
        camera.draw(paddle1.getDrawable());
        camera.draw(paddle2.getDrawable());

        screen.render();
    }

    screen.close();
    return 0;
}

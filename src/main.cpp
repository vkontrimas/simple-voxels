#include <iostream>
#include <chrono>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_timer.h>
#include <SDL_events.h>
#include <glad/glad.h>
#include "gamestate.hpp"
#include "input.hpp" 

using namespace sivox;

namespace {
    void start() {
        glClearColor(0.0f, 0.5f, 0.75f, 0.0f);
    }

    void update() {
        std::cout << "Update!\n";
    }

    void draw() {
        glClear(GL_COLOR_BUFFER_BIT);
        std::cout << "Frame!\n";
    }
}

int main(int argc, char *argv[]) {
    /*
     * - initialize SDL
     * - create a window
     * - create an OpenGL context
     * - load OpenGL
     */
    int sdl_status = SDL_Init(SDL_INIT_VIDEO);
    if (sdl_status != 0) {
        std::cerr << "Failed to initialize SDL!" << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Simple Voxels",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1280,
        720,
        SDL_WINDOW_OPENGL
    );

    if (!window) {
        std::cerr << "Failed to create a window!" << std::endl;
        return 1;
    }

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    if (!gl_context) {
        std::cerr << "Failed to create an OpenGL context!" << std::endl;
        return 1;
    }

    bool gl_loaded = gladLoadGLLoader(SDL_GL_GetProcAddress);
    if (!gl_loaded) {
        std::cerr << "Failed to load OpenGL!" << std::endl;
        return 1;
    }

    /*
     * Input handler
     */
    enum class Button {
        Close
    };
    InputHandler input;
    input.map_button(Button::Close, ScanCode::Escape);

    /*
     * Game loop.
     *
     * | start()
     *   while running:
     *   | Poll events
     *   | Update
     *   | Draw
     *   | Swap buffers
     * |
     */
    constexpr int UPDATES_PER_SECOND = 60;
    constexpr double UPDATE_TIME = 1.0 / UPDATES_PER_SECOND;

    using clock = std::chrono::high_resolution_clock;
    auto previous_iteration_time = clock::now();

    double update_lag = UPDATE_TIME;

    start();
    bool running = true;
    while (running) {
        SDL_Event event = {};
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                    running = false;
                }
                break;
            case SDL_KEYUP:
            case SDL_KEYDOWN: 
                input.keyboard_event(
                    static_cast<KeyCode>(event.key.keysym.sym),
                    static_cast<ScanCode>(event.key.keysym.scancode),
                    event.type == SDL_KEYUP ? Input::Up : Input::Down
                );
                break;
            default:
                break;
            }
        }
        input.update();

        if (input.button_pressed(Button::Close)) {
            running = false;
            break;
        }

        auto now = clock::now();
        double delta = std::chrono::duration<double>(now - previous_iteration_time).count();
        previous_iteration_time = now;

        update_lag += delta;
        while (update_lag >= UPDATE_TIME) {
            update();
            update_lag -= UPDATE_TIME;
        }

        draw();
        SDL_GL_SwapWindow(window);
    }

    /*
     * Clean up:
     * - delete OpenGL context
     * - delete window
     * - close SDL
     */
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

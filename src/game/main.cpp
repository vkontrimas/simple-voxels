#include <iostream>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_timer.h>
#include <SDL_events.h>
#include <glad/glad.h>

int main(int argc, char *argv[]) {
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

    glClearColor(0.0f, 0.5f, 0.75f, 0.0f);

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
            default:
                break;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

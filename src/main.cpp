#include <iostream>
#include <chrono>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_timer.h>
#include <SDL_events.h>
#include <glad/glad.h>
#include "chunkbuffers.hpp"
#include "gamestate.hpp"
#include "input.hpp" 
#include "shader.hpp" 

using namespace sivox;

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

    glClearColor(0.0f, 0.5f, 0.75f, 0.0f);

    /*
     * This block is here because we want to dispose of the shaders, input handler and other things before we delete the
     * OpenGL context and window or quit SDL.
     */
    {
        /*
         * Shaders
         */
        Shader shader_none;
        Shader shader_test = Shader::load("test");

        /*
         * Input handler
         */
        enum class Button {
            Close
        };
        InputHandler input;
        input.map_button(Button::Close, ScanCode::Escape);

        /*
         * Terrain test
         */
        Chunk chunk;
        for (int z = 0; z < Chunk::width; ++z) {
            for (int x = 0; x < Chunk::width; ++x) {
                for (int y = 0; y < Chunk::height; ++y) {
                    chunk.set_block({x, y, z}, 1);
                }
            }
        }

        ChunkMesh mesh = generate_mesh(chunk);
        ChunkBuffers buffers(mesh);

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
                // update();
                update_lag -= UPDATE_TIME;
            }

            glClear(GL_COLOR_BUFFER_BIT);

            glUseProgram(shader_test);
            glBindVertexArray(buffers.vertex_array());

            glDrawElements(GL_TRIANGLES, buffers.element_count(), GL_UNSIGNED_INT, 0);

            glBindVertexArray(0);
            glUseProgram(shader_none);

            SDL_GL_SwapWindow(window);
        }
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

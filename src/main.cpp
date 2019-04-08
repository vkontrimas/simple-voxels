#include <iostream>
#include <chrono>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_timer.h>
#include <SDL_events.h>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "chunkbuffers.hpp"
#include "gamestate.hpp"
#include "input.hpp" 
#include "shader.hpp" 

/*
 * For rand, srand and time
 */
#include <cstdlib>
#include <ctime>

/*
 * For std::function
 */
#include <functional>

using namespace sivox;

namespace {
    void foreach_block(Chunk &chunk, std::function<Block(Position pos, Block block)> f) {
        for (int z = 0; z < Chunk::width; ++z) {
            for (int x = 0; x < Chunk::width; ++x) {
                for (int y = 0; y < Chunk::height; ++y) {
                    chunk.set_block({x, y, z}, f({x, y, z}, chunk.block({x, y, z})));
                }
            }
        }
    }

    void sine_mess(Chunk &chunk) {
        float rand = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
        float rand2 = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
        float rand3 = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
        float rand4 = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
        foreach_block(chunk, [rand,rand2,rand3,rand4](Position p, Block b) { 
            float zf = static_cast<float>(p.z);
            float xf = static_cast<float>(p.x);
            float sinZ = glm::sin(glm::radians(180 * rand + 180.0f * rand2 * (zf / 31.0f)));
            float sinX = glm::sin(glm::radians(180 * rand3 + 180.0f * rand4 * (xf / 31.0f)));
            float maxY = 10 + glm::clamp(20 * sinZ * sinX, 0.0f, 20.0f);
            return p.y <= maxY ? 1 : 0;
        });
    }
}

int main(int argc, char *argv[]) {
    std::srand(std::time(nullptr)); // TODO: REMOVE!!!!!!!
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
        "Simple Voxels (Esc - close, WASD - rotate camera, RF - zoom, I - invert vertical, Chunk[1 - random, 2 - less random, 3 - full, 4 - sine mess, 5 - clear])",
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SDL_GL_SwapWindow(window);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

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
            Close,
            CameraPitchUp,
            CameraPitchDown,
            CameraYawLeft,
            CameraYawRight,
            CameraZoomIn,
            CameraZoomOut,
            CameraInvert,
            ChunkRegen,
            ChunkRegenRandomer,
            ChunkRegenFull,
            ChunkClear,
            ChunkRegenSine,
        };
        InputHandler input;
        input.map_button(Button::Close, ScanCode::Escape);
        input.map_button(Button::CameraPitchUp, ScanCode::W);
        input.map_button(Button::CameraPitchDown, ScanCode::S);
        input.map_button(Button::CameraYawLeft, ScanCode::A);
        input.map_button(Button::CameraYawRight, ScanCode::D);
        input.map_button(Button::CameraZoomIn, ScanCode::R);
        input.map_button(Button::CameraZoomOut, ScanCode::F);
        input.map_button(Button::CameraInvert, ScanCode::I);
        input.map_button(Button::ChunkRegen, ScanCode::Key1);
        input.map_button(Button::ChunkRegenRandomer, ScanCode::Key2);
        input.map_button(Button::ChunkRegenFull, ScanCode::Key3);
        input.map_button(Button::ChunkRegenSine, ScanCode::Key4);
        input.map_button(Button::ChunkClear, ScanCode::Key5);

        /*
         * Terrain test
         */
        Chunk chunk;
        sine_mess(chunk);
        ChunkBuffers buffers(generate_mesh(chunk));

        const float camera_pitch_rate = 45.0f;
        const float camera_yaw_rate = 45.0f;
        const float camera_zoom_rate = 20.0f;

        bool camera_inverted = false;

        float camera_pitch = -45.0f;
        float camera_yaw = 45.0f;
        const float camera_distance = 160.0f;
        float camera_fov = 30.0f; 

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

            if (input.button_pressed(Button::CameraInvert)) {
                camera_inverted = !camera_inverted;
            }

            camera_pitch += [&]() {
                float pitch_delta = 0.0f;
                if (input.button_down(Button::CameraPitchUp)) {
                    pitch_delta += 1.0f;
                }
                if (input.button_down(Button::CameraPitchDown)) {
                    pitch_delta -= 1.0f;
                }
                pitch_delta *= camera_pitch_rate * static_cast<float>(delta);
                pitch_delta *= camera_inverted ? 1.0f : -1.0f;
                return pitch_delta;
            }();
            camera_pitch = glm::clamp(camera_pitch, -90.0f, 90.0f);

            camera_yaw += [&]() {
                float yaw_delta = 0.0f;
                if (input.button_down(Button::CameraYawLeft)) {
                    yaw_delta -= 1.0f;
                }
                if (input.button_down(Button::CameraYawRight)) {
                    yaw_delta += 1.0f;
                }
                return yaw_delta * camera_yaw_rate * static_cast<float>(delta);
            }();

            camera_fov += [&]() {
                float fov_delta = 0.0f;
                if (input.button_down(Button::CameraZoomIn)) {
                    fov_delta -= 1.0f;
                }
                if (input.button_down(Button::CameraZoomOut)) {
                    fov_delta += 1.0f;
                }
                return fov_delta * camera_zoom_rate * static_cast<float>(delta);
            }();
            camera_fov = glm::clamp(camera_fov, 0.5f, 70.0f);

            if (input.button_down(Button::ChunkRegen)) {
                foreach_block(chunk, [](Position p, Block b) { 
                    return std::rand() % 10000 > 8000 ? 1 : 0;
                });
                buffers.set_mesh(generate_mesh(chunk));
            }
            if (input.button_down(Button::ChunkRegenRandomer)) {
                foreach_block(chunk, [](Position p, Block b) { 
                    return std::rand() % 10000 > 3000 ? 1 : 0;
                });
                buffers.set_mesh(generate_mesh(chunk));
            }
            if (input.button_down(Button::ChunkRegenSine)) {
                float rand = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
                float rand2 = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
                float rand3 = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
                float rand4 = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
                foreach_block(chunk, [rand,rand2,rand3,rand4](Position p, Block b) { 
                    float zf = static_cast<float>(p.z);
                    float xf = static_cast<float>(p.x);
                    float sinZ = glm::sin(glm::radians(180 * rand + 180.0f * rand2 * (zf / 31.0f)));
                    float sinX = glm::sin(glm::radians(180 * rand3 + 180.0f * rand4 * (xf / 31.0f)));
                    float maxY = 10 + glm::clamp(20 * sinZ * sinX, 0.0f, 20.0f);
                    return p.y <= maxY ? 1 : 0;
                });
                buffers.set_mesh(generate_mesh(chunk));
            }
            if (input.button_down(Button::ChunkRegenFull)) {
                foreach_block(chunk, [](Position p, Block b) { return 1; });
                buffers.set_mesh(generate_mesh(chunk));
            }
            if (input.button_down(Button::ChunkClear)) {
                foreach_block(chunk, [](Position p, Block b) { return 0; });
                buffers.set_mesh(generate_mesh(chunk));
            }

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glUseProgram(shader_test);

            glm::mat4 model(1.0f);
            //glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -camera_distance)) *
                             //glm::rotate(glm::mat4(1.0f), glm::radians(camera_pitch), glm::vec3(-1.0f, 0.0f, 0.0f)) *
                             //glm::rotate(glm::mat4(1.0f), glm::radians(camera_yaw), glm::vec3(0.0f, -1.0f, 0.0f)) *
                             //glm::translate(glm::mat4(1.0f), -glm::vec3(8.0f, 8.0f, 8.0f));

            glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -camera_distance));
            view = glm::rotate(view, glm::radians(camera_pitch), glm::vec3(-1.0f, 0.0f, 0.0f));
            view = glm::rotate(view, glm::radians(camera_yaw), glm::vec3(0.0f, -1.0f, 0.0f));
            view = glm::translate(view, -glm::vec3(16.5f, 16.5f, 16.5f));

            glm::mat4 projection = glm::perspective(
                glm::radians(camera_fov / 2.0f),
                1280.0f / 720.0f,
                0.1f,
                400.0f
            );
            glm::mat4 mvp = projection * view * model;

            glUniformMatrix4fv(glGetUniformLocation(shader_test, "u_matrix_mvp"), 1, GL_FALSE, glm::value_ptr(mvp));
            glUniform3fv(glGetUniformLocation(shader_test, "u_light_dir"), 1, glm::value_ptr(glm::normalize(glm::vec3(-3.0f, -7.0f, -5.0f))));
            glUniform1f(glGetUniformLocation(shader_test, "u_light_intensity"), 1.0f);
            glUniform1f(glGetUniformLocation(shader_test, "u_ambient_light"), 0.2f);

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

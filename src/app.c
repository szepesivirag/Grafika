// src/app.c

#include "app.h"
#include "utils.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

double degree_to_radian(double degree)
{
    return degree * M_PI / 180.0;
}

static void init_camera_and_scene(App* app)
{
    init_camera(&app->camera);
    init_scene(&app->scene);
}

void init_app(App* app, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init error: %s\n", SDL_GetError());
        app->is_running = false;
        return;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    app->window = SDL_CreateWindow(
        "Beadando",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    if (app->window == NULL) {
        fprintf(stderr, "SDL_CreateWindow error: %s\n", SDL_GetError());
        SDL_Quit();
        app->is_running = false;
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if (app->gl_context == NULL) {
        fprintf(stderr, "SDL_GL_CreateContext error: %s\n", SDL_GetError());
        SDL_DestroyWindow(app->window);
        SDL_Quit();
        app->is_running = false;
        return;
    }

    SDL_GL_SetSwapInterval(1);

    init_opengl();
    reshape(width, height);

    app->uptime = 0.0;
    app->is_running = true;

    init_camera_and_scene(app);
}

void init_opengl()
{
    glClearColor(0.2f, 0.2f, 0.3f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);

    glShadeModel(GL_SMOOTH);
}

void reshape(GLsizei width, GLsizei height)
{
    if (height == 0) {
        height = 1;
    }

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    double aspect = (double)width / (double)height;
    double fov = VIEWPORT_ASPECT;
    double z_near = 1.0;
    double z_far = 1000.0;

    gluPerspective(fov, aspect, z_near, z_far);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void handle_app_events(App* app)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            app->is_running = false;
        }
        else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                app->is_running = false;
                break;
            case SDLK_w:
                set_camera_speed(&app->camera, 40.0);
                break;
            case SDLK_s:
                set_camera_speed(&app->camera, -40.0);
                break;
            case SDLK_a:
                set_camera_side_speed(&app->camera, -40.0);
                break;
            case SDLK_d:
                set_camera_side_speed(&app->camera, 40.0);
                break;
            case SDLK_u:
                app->scene.ambient_light_level += 0.05f;
                if (app->scene.ambient_light_level > 1.0f) {
                    app->scene.ambient_light_level = 1.0f;
                }
                break;
            case SDLK_j:
                app->scene.ambient_light_level -= 0.05f;
                if (app->scene.ambient_light_level < 0.0f) {
                    app->scene.ambient_light_level = 0.0f;
                }
                break;
            case SDLK_F1:
                app->camera.is_preview_visible = !app->camera.is_preview_visible;
                break;
            default:
                break;
            }
        }
        else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
            case SDLK_w:
            case SDLK_s:
                set_camera_speed(&app->camera, 0.0);
                break;
            case SDLK_a:
            case SDLK_d:
                set_camera_side_speed(&app->camera, 0.0);
                break;
            default:
                break;
            }
        }
    }
}

void update_app(App* app)
{
    const double dt = 1.0 / 60.0;
    app->uptime += dt;

    update_camera(&app->camera, dt);
    update_scene(&app->scene, dt);
}

void render_app(App* app)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (app->camera.is_preview_visible) {
        show_texture_preview(app->scene.help_texture);
    }
    else {
        set_view(&app->camera);
        set_lighting(&app->scene);
        render_scene(&app->scene);
}

    SDL_GL_SwapWindow(app->window);
}

void destroy_app(App* app)
{
    SDL_GL_DeleteContext(app->gl_context);
    SDL_DestroyWindow(app->window);
    SDL_Quit();
}
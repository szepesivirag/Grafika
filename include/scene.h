#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"  
#include "model.h"
#include <GL/gl.h>

typedef struct Room {
    GLuint ground;
    GLuint left;
    GLuint right;
    GLuint front;
    GLuint back;
    GLuint top;
} Room;

typedef struct Scene
{
    Room room;
    GLuint help_texture;
    float ambient_light_level;
    float cube_rotation_angle;
} Scene;

void init_scene(Scene* scene);
void set_lighting(const Scene* scene);
void update_scene(Scene* scene, double time);
void render_scene(const Scene* scene);

void draw_room(const Room* room);

#endif /* SCENE_H */
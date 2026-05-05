#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"  
#include <obj/model.h> 
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
    Model table_model;         
    GLuint table_texture;      
    
    Room room;                 
    GLuint help_texture;       
    
    float ambient_light_level; 
} Scene;

void init_scene(Scene* scene);
void set_lighting(const Scene* scene);
void update_scene(Scene* scene, double time);
void render_scene(const Scene* scene);

void draw_room(const Room* room);

#endif /* SCENE_H */
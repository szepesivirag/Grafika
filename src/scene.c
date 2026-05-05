#include "scene.h"
#include <obj/load.h>
#include <obj/draw.h>
#include <math.h>

void init_scene(Scene* scene)
{
    
    load_model(&(scene->table_model), "assets/models/table.obj");
    scene->table_texture = load_texture("assets/textures/table.jpg");

    
    scene->room.ground = load_texture("assets/textures/floor.jpg");
    scene->room.left = load_texture("assets/textures/banana.jpg");
    scene->room.right = load_texture("assets/textures/banana.jpg");
    scene->room.front = load_texture("assets/textures/window.jpg");
    scene->room.back = load_texture("assets/textures/window.jpg");
    scene->room.top = load_texture("assets/textures/ceiling.jpg");

    
    scene->help_texture = load_texture("assets/textures/help1.png");

    
    scene->ambient_light_level = 0.8f; 
}

void set_lighting(const Scene* scene)
{
    
    float ambient_light[] = { scene->ambient_light_level, scene->ambient_light_level, scene->ambient_light_level, 1.0f };
    float diffuse_light[] = { 0.3f, 0.3f, 0.3f, 0.9f };
    float specular_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float position[] = { 0.0f, 100.0f, 150.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void draw_room(const Room* room) 
{
    double sizeOfRoom = 200.0;
    
    
    glBindTexture(GL_TEXTURE_2D, room->ground);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glBegin(GL_QUADS);
    for (int x = -sizeOfRoom; x < sizeOfRoom; x += 50) {
        for (int z = -sizeOfRoom; z < sizeOfRoom; z += 50) {
            glNormal3f(0, 1, 0); 
            glTexCoord2f(0.0, 0.0); glVertex3f(x, 0, z);
            glTexCoord2f(1.0, 0.0); glVertex3f(x + 50, 0, z);
            glTexCoord2f(1.0, 1.0); glVertex3f(x + 50, 0, z + 50);
            glTexCoord2f(0.0, 1.0); glVertex3f(x, 0, z + 50);
        }
    }
    glEnd();

    void draw_walls(Room room) {
	glBindTexture(GL_TEXTURE_2D, room.left);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-sizeOfRoom, 0, -sizeOfRoom);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-sizeOfRoom, sizeOfRoom, -sizeOfRoom);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-sizeOfRoom, sizeOfRoom, sizeOfRoom);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-sizeOfRoom, 0, sizeOfRoom);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, room.right);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sizeOfRoom, 0, sizeOfRoom);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sizeOfRoom, sizeOfRoom, sizeOfRoom);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sizeOfRoom, sizeOfRoom, -sizeOfRoom);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sizeOfRoom, 0, -sizeOfRoom);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, room.front);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-sizeOfRoom, 0, -sizeOfRoom);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sizeOfRoom, 0, -sizeOfRoom);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sizeOfRoom, sizeOfRoom, -sizeOfRoom);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-sizeOfRoom, sizeOfRoom, -sizeOfRoom);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, room.back);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-sizeOfRoom, 0, sizeOfRoom);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-sizeOfRoom, sizeOfRoom, sizeOfRoom);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sizeOfRoom, sizeOfRoom, sizeOfRoom);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(sizeOfRoom, 0, sizeOfRoom);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, room.top);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sizeOfRoom, sizeOfRoom, sizeOfRoom);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sizeOfRoom, sizeOfRoom, -sizeOfRoom);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-sizeOfRoom, sizeOfRoom, -sizeOfRoom);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-sizeOfRoom, sizeOfRoom, sizeOfRoom);
	glEnd();
}

    //ezt be kell még fejeznem majd a falak kirajzolásást és hasonlok...!!!!
}

void render_scene(const Scene* scene)
{
    set_lighting(scene);

    
    draw_room(&(scene->room));

    
    glPushMatrix();
       
        glTranslatef(120.0f, 0.0f, 170.0f);
        glScalef(2.0f, 2.0f, 2.0f);
        glTranslatef(-50.0f, -1.0f, -70.0f);
        glRotatef(-90.0f, 1, 0, 0);
        glRotatef(-90.0f, 0, 0, 1);

        glBindTexture(GL_TEXTURE_2D, scene->table_texture);
        
        draw_model(&(scene->table_model));
    glPopMatrix();
}

void update_scene(Scene* scene, double time)
{
    
}
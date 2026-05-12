#include "scene.h"
#include "texture.h"

#include <GL/gl.h>

static void draw_box(float x, float y, float z, float sx, float sy, float sz)
{
    float x1 = x - sx / 2.0f;
    float x2 = x + sx / 2.0f;
    float y1 = y;
    float y2 = y + sy;
    float z1 = z - sz / 2.0f;
    float z2 = z + sz / 2.0f;

    glBegin(GL_QUADS);

    glColor3f(1.0f, 1.0f, 1.0f);

    /* Front*/
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x1, y1, z2);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x2, y1, z2);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x2, y2, z2);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x1, y2, z2);

    /* Back*/
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x2, y1, z1);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x1, y1, z1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x1, y2, z1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x2, y2, z1);

    /* Left */
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x1, y1, z1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x1, y1, z2);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x1, y2, z2);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x1, y2, z1);

    /* Right*/
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x2, y1, z2);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x2, y1, z1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x2, y2, z1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x2, y2, z2);

    /* Top */
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x1, y2, z2);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x2, y2, z2);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x2, y2, z1);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x1, y2, z1);

    /* Bottom */
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x1, y1, z1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x2, y1, z1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x2, y1, z2);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x1, y1, z2);

    glEnd();
}

void init_scene(Scene* scene)
{
    /* scene->room.ground = load_texture("textures/floor.jpg");
    scene->room.left = load_texture("textures/left.jpg");
    scene->room.right = load_texture("textures/right.jpg");
    scene->room.front = load_texture("textures/front.jpg");
    scene->room.back = load_texture("textures/back.jpg");
    scene->room.top = load_texture("textures/top.jpg"); */

    scene->help_texture = load_texture("assets/help.png");
    scene->cube_texture = load_texture("assets/cube_texture.png");
    scene->ambient_light_level = 0.8f;

    scene->ambient_light_level = 0.5f;
    scene->cube_rotation_angle = 0.0f;
}

void set_lighting(const Scene* scene)
{
    float ambient_light[] = {
        scene->ambient_light_level,
        scene->ambient_light_level,
        scene->ambient_light_level,
        1.0f
    };

    float diffuse_light[] = {0.7f, 0.7f, 0.7f, 1.0f};
    float specular_light[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float position[] = {0.0f, 120.0f, 80.0f, 1.0f};

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void draw_room(const Room* room)
{
    float size = 200.0f;
    float height = 140.0f;
    (void)room;

    glDisable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);

    glColor3f(0.45f, 0.45f, 0.45f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-size, -20.0f, -size);
    glVertex3f( size, -20.0f, -size);
    glVertex3f( size, -20.0f,  size);
    glVertex3f(-size, -20.0f,  size);

    glColor3f(0.60f, 0.60f, 0.70f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-size, -20.0f, -size);
    glVertex3f( size, -20.0f, -size);
    glVertex3f( size, height, -size);
    glVertex3f(-size, height, -size);

    glColor3f(0.55f, 0.55f, 0.65f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-size, -20.0f, -size);
    glVertex3f(-size, -20.0f,  size);
    glVertex3f(-size, height,  size);
    glVertex3f(-size, height, -size);

    glColor3f(0.55f, 0.55f, 0.65f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(size, -20.0f,  size);
    glVertex3f(size, -20.0f, -size);
    glVertex3f(size, height, -size);
    glVertex3f(size, height,  size);

    glEnd();

    glEnable(GL_TEXTURE_2D);
}

void render_scene(const Scene* scene)
{
    set_lighting(scene);
    draw_room(&(scene->room));


    glBindTexture(GL_TEXTURE_2D, scene->cube_texture);
    glPushMatrix();
    glTranslatef(0.0f, -20.0f, 0.0f);
    glRotatef(scene->cube_rotation_angle, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 20.0f, 0.0f);

    draw_box(0.0f, -20.0f, 0.0f, 60.0f, 35.0f, 40.0f);
    glPopMatrix();
}

void update_scene(Scene* scene, double time)
{
    scene->cube_rotation_angle += 30.0f * (float)time;

    if (scene->cube_rotation_angle > 360.0f) {
        scene->cube_rotation_angle -= 360.0f;
    }
}  
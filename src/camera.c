#include "camera.h"
#include "utils.h"

#include <GL/gl.h>
#include <math.h>

void init_camera(Camera* camera)
{
    camera->position.x = 0.0;
    camera->position.y = 80.0;
    camera->position.z = 120.0;

    camera->rotation.x = -35.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = 0.0;

    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;

    camera->is_preview_visible = false;
}

void update_camera(Camera* camera, double time)
{
    double angle;
    double speed;
    double side_speed;

    angle = degree_to_radian(camera->rotation.z);

    speed = camera->speed.y * time;
    side_speed = camera->speed.x * time;

    camera->position.x += sin(angle) * speed;
    camera->position.z -= cos(angle) * speed;

    camera->position.x += cos(angle) * side_speed;
    camera->position.z += sin(angle) * side_speed;
}
void set_view(const Camera* camera)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-camera->rotation.x, 1.0f, 0.0f, 0.0f);
    glRotatef(-camera->rotation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(-camera->rotation.z, 0.0f, 0.0f, 1.0f);

    glTranslatef(
        -camera->position.x,
        -camera->position.y,
        -camera->position.z
    );
}

void rotate_camera(Camera* camera, double horizontal, double vertical)
{
    camera->rotation.z += horizontal;
    camera->rotation.x += vertical;

    if (camera->rotation.z < 0.0) {
        camera->rotation.z += 360.0;
    }

    if (camera->rotation.z > 360.0) {
        camera->rotation.z -= 360.0;
    }

    if (camera->rotation.x < -89.0) {
        camera->rotation.x = -89.0;
    }

    if (camera->rotation.x > 89.0) {
        camera->rotation.x = 89.0;
    }
}

void set_camera_speed(Camera* camera, double speed)
{
    camera->speed.y = speed;
}

void set_camera_side_speed(Camera* camera, double speed)
{
    camera->speed.x = speed;
}

void show_texture_preview(GLuint texture_id)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBindTexture(GL_TEXTURE_2D, texture_id);
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.5f,  1.0f, -3.0f);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 1.5f,  1.0f, -3.0f);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 1.5f, -1.0f, -3.0f);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.5f, -1.0f, -3.0f);

    glEnd();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}
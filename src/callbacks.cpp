#include <GL/glu.h> 
#include "callbacks.h"
#include "draw.h"
#include "init.h"
#include "model.h"

#include <stdlib.h>
#include <stdio.h>

int isHelpOn = 0;
int WINDOW_WIDTH = 1000;
int WINDOW_HEIGHT = 700;

struct Camera camera;
struct Action action = {0}; //gombok nullán állnak
extern GLfloat light_ambient[4];

// Egér mozdulatok detektálása
bool is_mouse_down = false;
double mouse_x, mouse_y;

void display(GLFWwindow* window)
{
	World* world = (World*)glfwGetWindowUserPointer(window);

	double elapsed_time = calc_elapsed_time();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	update_camera_position(&camera, elapsed_time);
	draw_content(world);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLdouble)WINDOW_WIDTH / (GLdouble)WINDOW_HEIGHT, 0.1, 20000.0);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	set_view_point(&camera);

	if(isHelpOn)
	{
		GLfloat torchForHelp[] = { 0.8f, 0.8f, 0.8f, 0.8f };
		glLightfv(GL_LIGHT1, GL_AMBIENT, torchForHelp);

		glLoadIdentity();
		gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

		draw_help(world->helpTexture);

		glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;
    glViewport(0, 0, width, height);
    set_clear_camera_pose(&camera);
}

// EZ VÁLTJA LE A keyboard, keyboardUp ÉS specialFunc-ot
void key_callback(GLFWwindow* window, int key, int scancode, int input_action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && input_action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    
    if (key == GLFW_KEY_F1 && input_action == GLFW_PRESS) {
        isHelpOn = !isHelpOn;
    }

    
    int is_pressed = (input_action != GLFW_RELEASE);

	switch (key) {
	case GLFW_KEY_W: action.move_forward = is_pressed; break;
	case GLFW_KEY_S: action.move_backward = is_pressed; break;
	case GLFW_KEY_A: action.step_left = is_pressed; break;
	case GLFW_KEY_D: action.step_right = is_pressed; break;
	case GLFW_KEY_G: action.move_down = is_pressed; break;
	case GLFW_KEY_T: action.move_up = is_pressed; break;
	case GLFW_KEY_U: action.increase_light = is_pressed; break;
	case GLFW_KEY_J: action.decrease_light = is_pressed; break;
	}
}

// EZz váltja le  A mouse  korűbbi rgér fvg-t 
void mouse_button_callback(GLFWwindow* window, int button, int input_action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (input_action == GLFW_PRESS) {
            is_mouse_down = true;
            glfwGetCursorPos(window, &mouse_x, &mouse_y);
        } else if (input_action == GLFW_RELEASE) {
            is_mouse_down = false;
        }
    }
}

// Ez váltja A motion fgv-t
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (is_mouse_down) {
        double horizontal = mouse_x - xpos;
        double vertical = mouse_y - ypos;

        rotate_camera(&camera, horizontal, vertical);

        mouse_x = xpos;
        mouse_y = ypos;
    }
}

double calc_elapsed_time()
{
	static double last_frame_time = 0.0;
	double current_time = glfwGetTime(); 
	double elapsed_time = current_time - last_frame_time;
	last_frame_time = current_time;

	return elapsed_time;
}

void update_camera_position(struct Camera* camera, double elapsed_time)
{
	float speed = 30.0f;
	double distance = elapsed_time * CAMERA_SPEED * speed;

	if (action.move_forward) move_camera_forward(camera, distance);
	if (action.move_backward) move_camera_backward(camera, distance);
	if (action.step_left) step_camera_left(camera, distance);
	if (action.step_right) step_camera_right(camera, distance);
	if (action.move_up) move_camera_up(camera, distance);
	if (action.move_down) move_camera_down(camera, distance);

	if (action.increase_light) {
		if (light_ambient[0] < 1.0f) {
			light_ambient[0] = light_ambient[1] = light_ambient[2] += 0.01f;
			glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
		}
	}

	if (action.decrease_light) {
		if (light_ambient[0] > -0.60f) {
			light_ambient[0] = light_ambient[1] = light_ambient[2] -= 0.01f;
			glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
		}
	}
}
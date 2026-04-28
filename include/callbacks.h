#ifndef INCLUDE_CALLBACKS_H_
#define INCLUDE_CALLBACKS_H_

#include <GLFW/glfw3.h> // GLUT lecserélve!
#include "camera.h"

extern struct Camera camera;
extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

struct Action
{
	int move_forward;
	int move_backward;
	int step_left;
	int step_right;
	int move_up;
	int move_down;
	int increase_light;
	int decrease_light;
};
extern struct Action action; 

// A GLFW által elvárt függvény deklarációk:
void display(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int input_action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int input_action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

double calc_elapsed_time();
void update_camera_position(struct Camera* camera, double elapsed_time);

#endif /* INCLUDE_CALLBACKS_H_ */
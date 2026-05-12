#ifndef UTILS_H
#define UTILS_H

/**
 * GLSL-like three dimensional vector
 */
typedef struct vec3
{
    float x;
    float y;
    float z;
} vec3;

/**
 * Color with RGB components
 */
typedef struct Color
{
    float red;
    float green;
    float blue;
} Color;

/**
 * Material
 */
typedef struct Material
{
    struct Color ambient;
    struct Color diffuse;
    struct Color specular;
    float shininess;
} Material;

/**
 * Calculates radian from degree.
 */
double degree_to_radian(double degree);

/**
 * Sets up a perspective projection matrix (native implementation, no GLU)
 * Equivalent to gluPerspective.
 * 
 * fov: field of view in degrees
 * aspect: aspect ratio (width / height)
 * z_near: near clipping plane distance
 * z_far: far clipping plane distance
 */
void set_perspective_matrix(double fov, double aspect, double z_near, double z_far);

#endif /* UTILS_H */

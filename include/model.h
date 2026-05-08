// include/model.h
#ifndef MODEL_H
#define MODEL_H

#include <stdio.h>

#define FALSE 0
#define TRUE 1
#define INVALID_VERTEX_INDEX -1

typedef struct Vertex {
    double x;
    double y;
    double z;
} Vertex;

typedef struct TextureVertex {
    double u;
    double v;
} TextureVertex;

typedef struct FacePoint {
    int vertex_index;
    int texture_index;
    int normal_index;
} FacePoint;

typedef struct Triangle {
    FacePoint points[3];
} Triangle;

typedef struct Quad {
    FacePoint points[4];
} Quad;

typedef struct Model {
    Vertex* vertices;
    TextureVertex* texture_vertices;
    Vertex* normals;
    Triangle* triangles;
    Quad* quads;

    int n_vertices;
    int n_texture_vertices;
    int n_normals;
    int n_triangles;
    int n_quads;
} Model;

int  load_model(const char* filename, Model* model);
void free_model(Model* model);
void print_model_info(const Model* model);

#endif /* MODEL_H */
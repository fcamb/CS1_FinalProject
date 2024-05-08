#pragma once

#include "./structures.h"

#define GL_MAJOR 3
#define GL_MINOR 3

float screen_w = 1920;
float screen_h = 1080;
int choice = -1;
GLFWwindow* window = nullptr;

GLuint rectangle_vao;
GLuint rectangle_vbo;
GLuint rectangle_ebo;
GLuint basic_shader;

GLuint batch_vao;
GLuint batch_vbo;
GLuint batch_ebo;
int batch_triangle_count = 0;

Color WHITE =  { 1.f, 1.f, 1.f, 1.f };
Color BLACK =  { 0.f, 0.f, 0.f, 0.f };
Color GREEN =  { 0.f, 1.f, 0.f, 1.f };
Color RED =    { 1.f, 0.f, 0.f, 1.f };
Color YELLOW = { 1.f, 1.f, 0.f, 1.f };
Color BLUE =   { 0.f, 0.f, 1.f, 1.f };

std::vector<int> v;
std::vector<int> v2;
std::vector<Color> v_colors;
std::vector<Color> v_colors2;
std::vector<Vertex> batch;

int linear_target = 11;
int bin_target = 380;

ALGO current_algo = NONE;
bool performing_algo = false;
bool linear_search_done = false;
bool binary_search_done = false;

// SETUP
bool glfw_setup();
void gl_setup();
void gl_gen_basic_vao();
void gl_gen_new_batch();
void gl_fill_batch(int s);
void gl_reset_batch();
void fill_vectors(int s);
GLuint gl_load_shaders(const char* vpath, const char* fpath);

// DRAWING 
void gl_draw_rectangle(int num, int s, float x, Color color);
void gl_draw_batch();
void gl_draw_rectangles();

// ALGORITHMS
// BINARY SEARCH, LINEAR SEARCH, BUBBLE SORT, SELECTION SORT
int binary_search(int s, int t);
void bubble_sort(int s);
int linear_search(int s, int t);
void selection_sort(int s);

// HELPERS

// no error checking
void change_targets();
int get_random_number(int min, int max);
void set_batch_color(int i, Color c);
void batch_swap(int i1, int i2);
void create_rectangle(int v1, int bi, int s, Color color);
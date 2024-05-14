#pragma once

#include "./structures.h"

#define GL_MAJOR 3
#define GL_MINOR 3

float screen_w = 1600;
float screen_h = 900;
int choice = -1;
GLFWwindow* window = nullptr;

GLuint rectangle_vao;
GLuint rectangle_vbo;
GLuint rectangle_ebo;
GLuint basic_shader;

GLuint batch_vao = 1;
GLuint batch_vbo;
GLuint batch_ebo;
int batch_triangle_count = 0;

Color WHITE =  { 1.f, 1.f, 1.f, 1.f };
Color BLACK =  { 0.f, 0.f, 0.f, 0.f };
Color GREEN =  { 0.f, 1.f, 0.f, 1.f };
Color RED =    { 1.f, 0.f, 0.f, 1.f };
Color YELLOW = { 1.f, 1.f, 0.f, 1.f };
Color BLUE =   { 0.f, 0.f, 1.f, 1.f };

std::vector<int> v{};
std::vector<int> v2{};
std::vector<Color> v_colors{};
std::vector<Color> v_colors2{};
std::vector<Vertex> batch{};

int linear_target = 11;
int bin_target = 380;
bool array_loaded = false;
int array_choice = -1;


ALGO current_algo = NONE;
bool performing_algo = false;
bool linear_search_done = false;
bool binary_search_done = false;

// SETUP
bool glfw_setup();
void gl_setup();
GLuint gl_load_shaders(const char* vpath, const char* fpath);

void gl_gen_new_batch();
void gl_fill_batch(int s);
void gl_reset_batch();

// DRAWING 
void gl_draw_rectangle(int num, int s, float x, Color color);
void gl_draw_batch();
void gl_display_menu();

// DATA LOADING
void fill_array_data_files();
void load_array_data_from_file(const char* path);

// WINDOW
void frame_buffersize_callback(GLFWwindow* window, int w, int h);

// ALGORITHMS
// BINARY SEARCH, LINEAR SEARCH, BUBBLE SORT, SELECTION SORT
int binary_search(int s, int t);
void bubble_sort(int s);
int linear_search(int s, int t);
void selection_sort(int s);

// HELPERS

// no error checking in this function
void change_targets();
int get_random_number(int min, int max);
void set_batch_color(int i, Color c);
void create_rectangle(int v1, int bi, int s, Color color);
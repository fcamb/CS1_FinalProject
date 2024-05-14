#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <time.h>

#include "./GLAD/glad.h"
#include "./GLFW/include/glfw3.h"

#include "./main.h"

int main(void)
{
	if (!glfw_setup()) {
		std::cout << "GLFW: Setup failed. Exiting.\n";
		return 0;
	}

	srand(time(nullptr));

	fill_array_data_files();

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		if (!array_loaded) {
			std::cout << "Which array to load?\n";
			std::cout << "Small, medium, large: (0, 1, 2): ";
			std::cin >> array_choice;

			batch.clear();
			
			if (array_choice == 0) {
				load_array_data_from_file("array_200.txt");
				gl_gen_new_batch();
				gl_fill_batch(v.size());
				array_loaded = true;
			}
			else if (array_choice == 1) {
				load_array_data_from_file("array_300.txt");
				gl_gen_new_batch();
				gl_fill_batch(v.size());
				array_loaded = true;
			}
			else if (array_choice == 2) {
				load_array_data_from_file("array_400.txt");
				gl_gen_new_batch();
				gl_fill_batch(v.size());
				array_loaded = true;
			}

			gl_display_menu();
		}
		else if (array_loaded) {
			if (current_algo == NONE) {
				if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
					glfwSetWindowShouldClose(window, 1);
				}
				else if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
					current_algo = LINEAR_SEARCH;
				}
				else if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
					current_algo = BINARY_SEARCH;
				}
				else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
					current_algo = BUBBLE_SORT;
				}
				else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
					current_algo = SELECTION_SORT;
				}
				else if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
					change_targets();
				}
				else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
					std::cout << "Switching Arrays..\n";
					array_loaded = false;
					current_algo = NONE;
				}
			}

			switch (current_algo) {
				case LINEAR_SEARCH:
					gl_reset_batch();
					std::cout << "LINEAR SEARCH - START.\n";
					linear_search(v.size(), linear_target);
					current_algo = NONE;
					std::cout << "LINEAR SEARCH - END.\n";
					gl_display_menu();
					break;
				case BINARY_SEARCH:
					std::cout << "BINARY SEARCH - START.\n";
					binary_search(v.size(), bin_target);
					current_algo = NONE;
					std::cout << "BINARY SEARCH - END.\n";
					gl_display_menu();
					break;
				case BUBBLE_SORT:
					gl_reset_batch();
					std::cout << "BUBBLE SORT - START.\n";
					bubble_sort(v.size());
					current_algo = NONE;
					std::cout << "BUBBLE SORT - END.\n";
					gl_display_menu();
					break;
				case SELECTION_SORT:
					gl_reset_batch();
					std::cout << "SELECTION SORT - START.\n";
					selection_sort(v.size());
					current_algo = NONE;
					std::cout << "SELECTION SORT - END.\n";
					gl_display_menu();
					break;
				case NONE:
					gl_draw_batch();
			}
		}
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &rectangle_vao);
	glDeleteBuffers(1, &rectangle_vbo);
	glDeleteBuffers(1, &rectangle_ebo);
	glDeleteProgram(basic_shader);
	glDeleteVertexArrays(1, &batch_vao);
	glDeleteBuffers(1, &batch_vbo);
	glDeleteBuffers(1, &batch_ebo);

	glfwTerminate();

	return 0;
}
void gl_display_menu()
{
	std::cout << "\nEscape to exit.\n";
	std::cout << "L to perform linear search.\n";
	std::cout << "Current Linear Search Target: " << linear_target << "\n";
	std::cout << "B to perform binary search.\n";
	std::cout << "Current Binary Search Target: " << bin_target << "\n";
	std::cout << "W to perform bubble sort.\n";
	std::cout << "S to perform selection sort.\n";
	std::cout << "T to change target numbers for searching.\n";
	std::cout << "A to switch to different array.\n";
	std::cout << "- to cancel an algorithm\n";
	std::cout << "--Input Focus must be in window, not terminal--\n";
}
void load_array_data_from_file(const char* path)
{
	v.clear();
	v2.clear();

	std::ifstream in;
	in.open(path);
	if (in.fail()) {
		std::cout << "Failed to open txt file: " << path << "\n";
		return;
	}

	int n;
	std::string line{};
	while (std::getline(in, line)) {
		std::stringstream ss(line);
		while (ss >> n) {
			v.push_back(n);
			v2.push_back(n);
			std::getline(ss, line, ',');
		}
	}
	std::cout << "Array data loaded.\n";
}
void fill_array_data_files()
{
	std::ofstream small;
	small.open("array_200.txt");
	if (small.fail()) {
		std::cout << "Failed to open for writing: " << "array_200.txt\n";
	}

	int count = 0;
	int num = 0;
	for (int i = 0; i < 200; i++) {
		num = get_random_number(10, 300);
		small << num;
		small << ',';
		if (count == 9) {
			small << "\n";
		}
		count = (count + 1) % 10;
	}
	small.close();

	std::ofstream medium;
	medium.open("array_300.txt");
	if (medium.fail()) {
		std::cout << "Failed to open for writing: " "array_300.txt\n";
	}

	count = 0;
	for (int i = 0; i < 300; i++) {
		num = get_random_number(10, 300);
		medium << num;
		medium << ',';
		if (count == 9) {
			medium << "\n";
		}
		count = (count + 1) % 10;
	}
	medium.close();

	std::ofstream large;
	large.open("array_400.txt");
	if (large.fail()) {
		std::cout << "Failed to open for writing: " << "array_400.txt\n";
	}
	
	count = 0;
	for (int i = 0; i < 400; i++) {
		num = get_random_number(10, 300);
		large << num;
		large << ',';
		if (count == 9) {
			large << "\n";
		}
		count = (count + 1) % 10;
	}
	large.close();

	std::cout << "All array txt files filled.\n";
}
void change_targets()
{
	std::cin.clear();
	std::cin.ignore(256, '\n');
	
	std::cout << "Linear Search Target: ";
	std::cin >> linear_target;

	std::cout << "Binary Search Target: ";
	std::cin >> bin_target;
}
int get_random_number(int min, int max)
{
	return ((rand() % (max - min)) + min);
}

void gl_gen_new_batch()
{
	int size = v.size() * 6;
	
	int bsize = 0;
	int current_vao = 0;
	
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &current_vao);
	if (current_vao == batch_vao) {
		glDeleteVertexArrays(1, &batch_vao);
		std::cout << "Deleted previous batch vao.\n";
	}
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bsize);
	if (bsize != 0) {
		glDeleteBuffers(1, &batch_vbo);
		std::cout << "Delete previous batch vbo.\n";
	}
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &bsize);
	if (bsize != 0) {
		glDeleteBuffers(1, &batch_ebo);
		std::cout << "Deleted previous batch ebo.\n";
	}
	
	glGenVertexArrays(1, &batch_vao);
	glGenBuffers(1, &batch_vbo);
	glGenBuffers(1, &batch_ebo);
	glBindVertexArray(batch_vao);

	glBindBuffer(GL_ARRAY_BUFFER, batch_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * size, nullptr, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	unsigned int* indices = new unsigned int[size];
	int offset = 0;
	for (int i = 0; i < size; i += 6, offset+=4) {
		indices[i + 0] = 0 + offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 2 + offset;
		indices[i + 3] = 2 + offset;
		indices[i + 4] = 3 + offset;
		indices[i + 5] = 0 + offset;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * size, indices, GL_STATIC_DRAW);
	delete[] indices;

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void gl_fill_batch(int s)
{
	float rect_width = (screen_w / s) - 1.0f;
	float rect_height = 0.0f;
	float start_y = 0.0f;
	float rx = 0.0f;
	float ry = 0.0f;
	float rh = 0.0f;
	float rw = 0.0f;
	float x = 0.0f;
	
	batch_triangle_count = 0;
	
	for (int i = 0; i < s; i++) {
		rect_height = (float)v[i];
		start_y = screen_h - rect_height;
		
		rx = (2.f * x / screen_w - 1.f);
		ry = -(2.f * start_y / screen_h - 1.f);
		rw = (2.f * (x + rect_width) / screen_w - 1.f);
		rh = -(2.f * (start_y + rect_height) / screen_h - 1.f);

		batch.push_back({ {rx, ry}, YELLOW });
		batch.push_back({ {rx, rh}, YELLOW });
		batch.push_back({ {rw, rh}, YELLOW });
		batch.push_back({ {rw, ry}, YELLOW });

		batch_triangle_count += 6;
		x += (rect_width + 1.0f);
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, batch_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * batch_triangle_count, &batch[0]);
}

void gl_reset_batch()
{
	v = v2;
	batch.clear();
	gl_fill_batch(v.size());
}

void gl_draw_batch()
{
	glBindBuffer(GL_ARRAY_BUFFER, batch_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * batch_triangle_count, &batch[0]);

	glUseProgram(basic_shader);
	glBindVertexArray(batch_vao);
	glDrawElements(GL_TRIANGLES, batch_triangle_count, GL_UNSIGNED_INT, nullptr);
}
bool glfw_setup()
{
	if (!glfwInit()) return false;
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow((int)screen_w, (int)screen_h, "Algo Visualizer", NULL, NULL);
	if (!window) {
		std::cout << "GLFW: Failed to create window.\n";
		return false;
	}
	
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	// any callbacks
	glfwSetFramebufferSizeCallback(window, frame_buffersize_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "GLFW: Failed to load opengl functions - GLAD.\n";
		return false;
	}

	std::cout << "GLFW: Initialized.\n";
	
	gl_setup();

	return true;
}
void frame_buffersize_callback(GLFWwindow* window, int w, int h)
{
	screen_w = (float)w;
	screen_h = (float)h;
	glViewport(0, 0, w, h);
	gl_fill_batch(v.size());
}
void gl_setup()
{
	glEnable(GL_BLEND);
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glViewport(0, 0, screen_w, screen_h);
	gl_gen_basic_vao();
	basic_shader = gl_load_shaders("shaders/basic_v.glsl", "shaders/basic_f.glsl");
}

GLuint gl_load_shaders(const char* vpath, const char* fpath)
{
	std::ifstream vertex;
	std::ifstream fragment;

	vertex.open(vpath);
	if (!vpath) {
		std::cout << "GL: Failed to open vertex shader file.\n";
		return -1;
	}
	std::string line;
	std::string vertex_source;
	while (std::getline(vertex, line)) {
		vertex_source += line + "\n";
	}
	const char* vertex_code = vertex_source.c_str();

	int success;
	char info_log[512];
	GLuint v = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(v, 1, &vertex_code, NULL);
	glCompileShader(v);
	glGetShaderiv(v, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(v, 512, NULL, info_log);
		std::cout << "GL: Error loading vertex shader: " << info_log << "\n";
	}
	vertex.close();

	fragment.open(fpath);
	if (!fpath) {
		std::cout << "GL: Failed to open fragment shader file.\n";
		return -1;
	}
	std::string fragment_source;
	while (std::getline(fragment, line)) {
		fragment_source += line + "\n";
	}
	const char* fragment_code = fragment_source.c_str();

	GLuint f = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(f, 1, &fragment_code, NULL);
	glCompileShader(f);
	glGetShaderiv(f, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(f, 512, NULL, info_log);
		std::cout << "GL: Error loading fragmnet shader: " << info_log << "\n";
	}
	fragment.close();

	GLuint p = glCreateProgram();
	glAttachShader(p, v);
	glAttachShader(p, f);
	glLinkProgram(p);
	glGetProgramiv(p, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(p, 512, NULL, info_log);
		std::cout << "GL: Error linking basic shader program: " << info_log << "\n";
		return -1;
	}
	glDeleteShader(v);
	glDeleteShader(f);

	std::cout << "GL: Basic Shader loaded.\n";

	return p;
}

int binary_search(int s, int t)
{
	v = v2;
	v_colors = v_colors2;
	std::sort(v.begin(), v.end());
	batch.clear();
	gl_fill_batch(v.size());

	int l = 0;
	int curr_l = l * 4;

	int r = s - 1;
	int curr_r = r * 4;

	int m = (l + r) / 2;
	int curr_m = m * 4;

	float wait_timer = 1.0f;
	float timer = 0.0f;
	float last_time = glfwGetTime();
	
	while (l <= r) {
		if (glfwWindowShouldClose(window)) return -1;
		if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			return -1;
		}

		timer += glfwGetTime() - last_time;
		last_time = glfwGetTime();
		
		set_batch_color(curr_m, BLUE);

		m = (l + r) / 2;
		curr_m = m * 4;

		if (v[m] == t) {
			set_batch_color(curr_r, YELLOW);
			set_batch_color(curr_l, YELLOW);
			set_batch_color(curr_m, RED);
			glClear(GL_COLOR_BUFFER_BIT);
			gl_draw_batch();
			std::cout << "Target Found: " << bin_target << "\n";
			return m;
		}

		set_batch_color(curr_m, GREEN);
		set_batch_color(curr_l, BLACK);
		set_batch_color(curr_r, BLACK);

		if (timer >= wait_timer) {
			timer = 0.0;
			if (v[m] > t) {
				r = m - 1;
				set_batch_color(curr_r, YELLOW);
			}
			else {
				l = m + 1;
				set_batch_color(curr_l, YELLOW);
			}

			curr_l = l * 4;
			curr_r = r * 4;
		}
		else {
			glClear(GL_COLOR_BUFFER_BIT);
			gl_draw_batch();
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	v = v2;
	return -1;
}
void set_batch_color(int i, Color c)
{
	batch[i].color = c;
	batch[i + 1].color = c;
	batch[i + 2].color = c;
	batch[i + 3].color = c;
}

void create_rectangle(int vi, int bi, int s, Color color)
{
	float rect_width = (screen_w / s) - 1.0f;
	float rect_height = (float)v[vi] * 2.0f;
	float start_y = screen_h - rect_height;
	float x = (vi * (rect_width + 1.0f));

	float rx = (2.f * x / screen_w - 1.f);
	float ry = -(2.f * start_y / screen_h - 1.f);
	float rw = (2.f * (x + rect_width) / screen_w - 1.f);
	float rh = -(2.f * (start_y + rect_height) / screen_h - 1.f);

	batch[bi] = { {rx, ry}, color };
	batch[bi + 1] = { {rx, rh}, color };
	batch[bi + 2] = { {rw, rh}, color };
	batch[bi + 3] = { {rw, ry}, color };
}
void bubble_sort(int s)
{
	int t = 0;
	int curr = 0;
	int next = 4;
	int end = 0;

	for (int i = s - 1; i > 0; i--) {
		end = i * 4;
		set_batch_color(end, BLACK);
		for (int j = 0; j < i; j++) {
			if (glfwWindowShouldClose(window)) return;
			if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
				return;
			}
		
			curr = j * 4;
			next = (j + 1) * 4;
			
			set_batch_color(curr, GREEN);
			set_batch_color(next, BLUE);

			if (v[j] > v[j + 1]) {
				// swap
				t = v[j];
				v[j] = v[j + 1];
				v[j + 1] = t;
				set_batch_color(end, BLACK);
				create_rectangle(j, curr, v.size(), GREEN);
				create_rectangle(j + 1, next, v.size(), BLUE);
				glClear(GL_COLOR_BUFFER_BIT);
				gl_draw_batch();
				glfwSwapBuffers(window);
				glfwPollEvents();
			}
		}
		set_batch_color(end, YELLOW);
	}
}

int linear_search(int s, int t)
{
	int curr = 0;
	
	float wait_timer = 0.001f;
	float timer = 0.0f;
	float last_time = glfwGetTime();
	
	for (int i = 0; i < s; i++) {
		if (glfwWindowShouldClose(window)) return -1;
		if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			return -1;
		}
		curr = i * 4;
		
		timer += glfwGetTime() - last_time;
		last_time = glfwGetTime();

		if (timer > wait_timer) {
			timer = 0.0;
			if (v[i] == t) {
				set_batch_color(curr, RED);
				glClear(GL_COLOR_BUFFER_BIT);
				gl_draw_batch();
				std::cout << "Target Found: " << linear_target << "\n";
				return i;
			}
		}
		else {
			i--;
			set_batch_color(curr, GREEN);
			glClear(GL_COLOR_BUFFER_BIT);
			gl_draw_batch();
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	return 1;
}

void selection_sort(int s)
{
	int min = 0;
	int min_i = 0;
	int t = 0;

	int curr = 0;
	int curr_min = 0;
	int next = 0;

	//float wait_timer = 0.0001;
	//float timer = 0.0;
	//float last_time = glfwGetTime();

	for (int i = 0; i < s - 1; i++) {
		
		min_i = i;
		min = v[i];
		curr = i * 4;
		curr_min = min_i * 4;

		for (int j = i + 1; j < s; j++) {
			if (glfwWindowShouldClose(window)) return;
			if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
				return;
			}
			next = j * 4;

			if (v[j] < min) {
				set_batch_color(curr_min, YELLOW);
				min = v[j];
				min_i = j;
				curr_min = j * 4;
				set_batch_color(next, BLUE);
			}

			glClear(GL_COLOR_BUFFER_BIT);
			gl_draw_batch();
			glfwSwapBuffers(window);
			glfwPollEvents();

		}
		set_batch_color(curr_min, RED);	
		t = v[min_i];
		v[min_i] = v[i];
		v[i] = t;
		create_rectangle(min_i, curr_min, v.size(), RED);
		create_rectangle(i, curr, v.size(), GREEN);
		set_batch_color(curr, GREEN);
	}
}
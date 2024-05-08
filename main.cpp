#include <iostream>
#include <fstream>
#include <string>
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
	
	/*v = { 100, 20, 80, 100, 70, 10, 30, 50, 60, 40, 
		10, 30, 50, 110, 60, 40, 60, 70, 20, 10, 
		50, 60, 80, 10, 40, 30, 50, 90, 100, 130, 
		50, 20, 10, 30, 60, 70, 11, 80, 10, 20,
		50, 20, 10, 30, 60, 70, 10, 80, 10, 20 };
	v2 = v;
	v_colors2.resize(v.size(), YELLOW);
	v_colors.resize(v.size(), YELLOW);*/
	fill_vectors(400);
	//gl_gen_new_batch();
	//gl_fill_batch(v.size());
	
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		
		/*for (int i = 0; i < v.size(); i++) {
			gl_draw_rectangle(v[i], v.size(), (float)i);
		}*/

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
		} 
		
		//std::cout << batch[0].position.x << "\n";
		/*Vertex one = batch[0];
		Vertex two = batch[1];
		Vertex three = batch[2];
		Vertex four = batch[3];
		batch[0] = batch[4];
		batch[1] = batch[5];
		batch[2] = batch[6];
		batch[3] = batch[7];
		batch[4] = one;
		batch[5] = two;
		batch[6] = three;
		batch[7] = four;
		std::cout << batch[0].position.y << "\n";*/

		switch (current_algo) {
			case LINEAR_SEARCH:
				gl_reset_batch();
				std::cout << "LINEAR SEARCH.START.\n";
				linear_search(v.size(), linear_target);
				current_algo = NONE;
				std::cout << "LINEAR SEARCH.END.\n";
				break;
			case BINARY_SEARCH:
				std::cout << "BINARY SEARCH.START.\n";
				binary_search(v.size(), bin_target);
				current_algo = NONE;
				std::cout << "BINARY SEARCH.END.\n";
				break;
			case BUBBLE_SORT:
				gl_reset_batch();
				std::cout << "BUBBLE SORT.START.\n";
				bubble_sort(v.size());
				current_algo = NONE;
				std::cout << "BUBBLE SORT.END.\n";
				break;
			case SELECTION_SORT:
				gl_reset_batch();
				std::cout << "SELECTION SORT.START.\n";
				selection_sort(v.size());
				current_algo = NONE;
				std::cout << "SELECTION SORT.END.\n";
				break;
			case NONE:
				//gl_draw_batch();
				gl_draw_rectangles();
		}
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &rectangle_vao);
	glDeleteBuffers(1, &rectangle_vbo);
	glDeleteBuffers(1, &rectangle_ebo);
	glDeleteProgram(basic_shader);

	glfwTerminate();
	return 0;
}
int get_random_number(int min, int max)
{
	return ((rand() % (max - min)) + min);
}
void fill_vectors(int s)
{
	for (int i = 0; i < s; i++) {
		v.push_back(get_random_number(10, 400));
		v_colors.push_back(YELLOW);
	}
	v2 = v;
	v_colors2 = v_colors;
}
void gl_gen_new_batch()
{
	int size = v.size() * 6;

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
	std::cout << "FILLING BATCH:\n";
	float rect_width = (screen_w / s) - 1.0;
	float rect_height = 0.0;
	float start_y = 0.0;
	float rx = 0.0;
	float ry = 0.0;
	float rh = 0.0;
	float rw = 0.0;
	float x = 0.0;
	
	batch_triangle_count = 0;
	// ?
	//batch.resize(s * 4);
	
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
		x += (rect_width + 1.0);
	}

	glBindBuffer(GL_ARRAY_BUFFER, batch_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * batch_triangle_count, &batch[0]);
}

void gl_reset_batch()
{
	std::cout << "RESETTING BATCH:\n";
	v = v2;
	v_colors = v_colors2;
	//v_colors.resize(v.size(), YELLOW);
	//batch.clear();
	//gl_fill_batch(v.size());
}
void gl_draw_rectangle(int num, int s, float x, Color color)
{
	float rect_width = (screen_w / s) - 1.0;
	float rect_height = (float)num * 2.0;
	float start_y = screen_h - rect_height;
	x *= rect_width + 1.0;
	// top left first

	float rx = (2.f * x / screen_w - 1.f);
	float ry = -(2.f * start_y / screen_h - 1.f);
	float rw = (2.f * (x + rect_width) / screen_w - 1.f);
	float rh = -(2.f * (start_y + rect_height) / screen_h - 1.f);

	std::vector<Vertex> R = {
		{{rx, ry}, color},
		{{rx, rh}, color},
		{{rw, rh}, color},
		{{rw, ry}, color},
	};

	glBindBuffer(GL_ARRAY_BUFFER, rectangle_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, R.size() * sizeof(Vertex), &R[0]);

	glUseProgram(basic_shader);
	glBindVertexArray(rectangle_vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void gl_draw_batch()
{
	glBindBuffer(GL_ARRAY_BUFFER, batch_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * batch_triangle_count, &batch[0]);

	glUseProgram(basic_shader);
	glBindVertexArray(batch_vao);
	glDrawElements(GL_TRIANGLES, batch_triangle_count, GL_UNSIGNED_INT, nullptr);
}

void gl_draw_rectangles()
{
	int n = v.size();
	for (int i = 0; i < n; i++) {
		gl_draw_rectangle(v[i], n, (float)i, v_colors[i]);
	}
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
	glfwSwapInterval(1);
	// callbacks

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "GLFW: Failed to load opengl functions - GLAD.\n";
		return false;
	}
	
	std::cout << "GLFW: Initialized.\n";
	
	gl_setup();

	return true;
}

void gl_setup()
{
	glEnable(GL_BLEND);
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glViewport(0, 0, screen_w, screen_h);
	gl_gen_basic_vao();
	basic_shader = gl_load_shaders("shaders/basic_v.glsl", "shaders/basic_f.glsl");
}

void gl_gen_basic_vao()
{
	glGenVertexArrays(1, &rectangle_vao);
	glGenBuffers(1, &rectangle_vbo);
	glGenBuffers(1, &rectangle_ebo);
	glBindVertexArray(rectangle_vao);

	glBindBuffer(GL_ARRAY_BUFFER, rectangle_vbo);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectangle_ebo);
	// should this be static draw?
	int indices[] = { 0, 1, 2, 2, 3, 0 };
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	std::cout << "GL: Rectangle VAO built.\n";
}

GLuint gl_load_shaders(const char* vpath, const char* fpath)
{
	std::ifstream vertex;
	std::ifstream fragment;

	vertex.open(vpath);
	if (vertex.fail()) {
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
	if (fragment.fail()) {
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
	//batch.clear();
	//gl_fill_batch(v.size());
	int l = 0;
	//int curr_l = l * 4;

	int r = s - 1;
	//int curr_r = r * 4;

	int m = (l + r) / 2;
	//int curr_m = m * 4;

	float wait_timer = 0.5;
	float timer = 0.0;
	float last_time = glfwGetTime();
	
	while (l <= r) {
		if (glfwWindowShouldClose(window)) return -1;
		if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {
			return -1;
		}
		timer += glfwGetTime() - last_time;
		last_time = glfwGetTime();
		
		m = (l + r) / 2;
		//curr_m = m * 4;

		if (v[m] == t) {
			/*batch[curr_m].color = RED;
			batch[curr_m + 1].color = RED;
			batch[curr_m + 2].color = RED;
			batch[curr_m + 3].color = RED;*/
			v_colors[m] = RED;
			glClear(GL_COLOR_BUFFER_BIT);
			//gl_draw_batch();
			gl_draw_rectangles();
			return m;
		}

		v_colors[m] = GREEN;
		v_colors[l] = BLACK;
		v_colors[r] = BLACK;

		/*batch[curr_m].color = GREEN;
		batch[curr_m + 1].color = GREEN;
		batch[curr_m + 2].color = GREEN;
		batch[curr_m + 3].color = GREEN;

		batch[curr_l].color = BLACK;
		batch[curr_l + 1].color = BLACK;
		batch[curr_l + 2].color = BLACK;
		batch[curr_l + 3].color = BLACK;

		batch[curr_r].color = BLACK;
		batch[curr_r + 1].color = BLACK;
		batch[curr_r + 2].color = BLACK;
		batch[curr_r + 3].color = BLACK;*/


		if (timer >= wait_timer) {
			timer = 0.0;
			v_colors[m] = YELLOW;
			v_colors[l] = YELLOW;
			v_colors[r] = YELLOW;
			/*batch[curr_m].color = YELLOW;
			batch[curr_m + 1].color = YELLOW;
			batch[curr_m + 2].color = YELLOW;
			batch[curr_m + 3].color = YELLOW;

			batch[curr_l].color = YELLOW;
			batch[curr_l + 1].color = YELLOW;
			batch[curr_l + 2].color = YELLOW;
			batch[curr_l + 3].color = YELLOW;

			batch[curr_r].color = YELLOW;
			batch[curr_r + 1].color = YELLOW;
			batch[curr_r + 2].color = YELLOW;
			batch[curr_r + 3].color = YELLOW;*/

			if (v[m] > t) {
				r = m - 1;
			}
			else {
				l = m + 1;
			}
			
			//curr_l = l * 4;
			//curr_r = r * 4;
		}
		else {
			glClear(GL_COLOR_BUFFER_BIT);
			//gl_draw_batch();
			gl_draw_rectangles();
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	v = v2;
	return -1;
}

void bubble_sort(int s)
{
	int t = 0;
	//int curr = 0;
	//int curr_next = 4;
	//int end = (s - 1) * 4;
	
	float wait_timer = 0.0001;
	float timer = 0.0;
	float last_time = glfwGetTime();

	for (int i = s - 1; i > 0; i--) {

		//end = i * 4;
		/*batch[end].color = BLACK;
		batch[end + 1].color = BLACK;
		batch[end + 2].color = BLACK;
		batch[end + 3].color = BLACK;*/
		v_colors[i] = BLACK;

		for (int j = 0; j < i; j++) {

			if (glfwWindowShouldClose(window)) return;
			if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {
				return;
			}

			v_colors[j] = GREEN;
			v_colors[j + 1] = BLUE;


			if (v[j] > v[j + 1]) {

				// swap
				t = v[j];
				v[j] = v[j + 1];
				v[j + 1] = t;

				v_colors[i] = BLACK;
				//glClear(GL_COLOR_BUFFER_BIT);
				////gl_draw_batch();
				//gl_draw_rectangles();
				//glfwSwapBuffers(window);
				//glfwPollEvents();

				// gotta find a better way than this
				//batch.clear();
				//gl_fill_batch(v.size());

				//batch[end].color = BLACK;
				//batch[end + 1].color = BLACK;
				//batch[end + 2].color = BLACK;
				//batch[end + 3].color = BLACK;

			}

			//timer += glfwGetTime() - last_time;
			//last_time = glfwGetTime();
			
			//curr = j * 4;
			
			/*batch[curr].color = GREEN;
			batch[curr + 1].color = GREEN;
			batch[curr + 2].color = GREEN;
			batch[curr + 3].color = GREEN;*/

			/*curr_next = (j + 1) * 4;

			batch[curr_next].color = BLUE;
			batch[curr_next + 1].color = BLUE;
			batch[curr_next + 2].color = BLUE;
			batch[curr_next + 3].color = BLUE;*/
			

			//if (timer >= wait_timer) {
			//	
			//	timer = 0.0;

			//	if (v[j] > v[j + 1]) {
			//		
			//		// swap
			//		t = v[j];
			//		v[j] = v[j + 1];
			//		v[j + 1] = t;
			//		
			//		v_colors[i] = BLACK;
			//		// gotta find a better way than this
			//		//batch.clear();
			//		//gl_fill_batch(v.size());
			//		
			//		//batch[end].color = BLACK;
			//		//batch[end + 1].color = BLACK;
			//		//batch[end + 2].color = BLACK;
			//		//batch[end + 3].color = BLACK;
	
			//	}
			//}
			//else {
			//	j--;
			//}
			//glClear(GL_COLOR_BUFFER_BIT);
			////gl_draw_batch();
			//gl_draw_rectangles();
			//glfwSwapBuffers(window);
			//glfwPollEvents();
		}
		v_colors[i] = YELLOW;
		/*batch[end].color = YELLOW;
		batch[end + 1].color = YELLOW;
		batch[end + 2].color = YELLOW;
		batch[end + 3].color = YELLOW;*/

		glClear(GL_COLOR_BUFFER_BIT);
		//gl_draw_batch();
		gl_draw_rectangles();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

int linear_search(int s, int t)
{
	//int curr = 0;
	float wait_timer = 0.005;
	float timer = 0.0;
	float last_time = glfwGetTime();
	
	for (int i = 0; i < s; i++) {

		if (glfwWindowShouldClose(window)) return -1;
		if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {
			return -1;
		}
		if (v[i] == t) {
			/*batch[curr].color = RED;
			batch[curr + 1].color = RED;
			batch[curr + 2].color = RED;
			batch[curr + 3].color = RED;*/
			v_colors[i] = RED;

			glClear(GL_COLOR_BUFFER_BIT);
			//gl_draw_batch();
			gl_draw_rectangles();
			return i;
		}

		v_colors[i] = GREEN;
		/*batch[curr].color = GREEN;
		batch[curr + 1].color = GREEN;
		batch[curr + 2].color = GREEN;
		batch[curr + 3].color = GREEN;*/

		glClear(GL_COLOR_BUFFER_BIT);
		//gl_draw_batch();
		gl_draw_rectangles();
		glfwSwapBuffers(window);
		glfwPollEvents();
		//timer += glfwGetTime() - last_time;
		//last_time = glfwGetTime();
		//	
		//if (timer >= wait_timer) {

		//	timer = 0.0;
		//	//curr = i * 4;

		//	if (v[i] == t) {
		//		/*batch[curr].color = RED;
		//		batch[curr + 1].color = RED;
		//		batch[curr + 2].color = RED;
		//		batch[curr + 3].color = RED;*/
		//		v_colors[i] = RED;

		//		glClear(GL_COLOR_BUFFER_BIT);
		//		//gl_draw_batch();
		//		gl_draw_rectangles();
		//		return i;
		//	}

		//	v_colors[i] = GREEN;
		//	/*batch[curr].color = GREEN;
		//	batch[curr + 1].color = GREEN;
		//	batch[curr + 2].color = GREEN;
		//	batch[curr + 3].color = GREEN;*/

		//	glClear(GL_COLOR_BUFFER_BIT);
		//	//gl_draw_batch();
		//	gl_draw_rectangles();
		//	glfwSwapBuffers(window);
		//	glfwPollEvents();
		//}
		//else {
		//	i--;
		//}
	}
	return 1;
}

void selection_sort(int s)
{
	int min = 0;
	int min_i = 0;
	int t = 0;

	float wait_timer = 0.0001;
	float timer = 0.0;
	float last_time = glfwGetTime();

	for (int i = 0; i < s - 1; i++) {
		
		min_i = i;
		min = v[i];

		for (int j = i + 1; j < s; j++) {
			if (glfwWindowShouldClose(window)) return;
			if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {
				return;
			}

			if (v[j] < min) {
				v_colors[min_i] = YELLOW;
				min = v[j];
				min_i = j;
				v_colors[min_i] = BLUE;
			}

			/*timer += glfwGetTime() - last_time;
			last_time = glfwGetTime();
			if (timer >= wait_timer) {
				timer = 0.0;
				if (v[j] < min) {
					v_colors[min_i] = YELLOW;
					min = v[j];
					min_i = j;
					v_colors[min_i] = BLUE;
				}
			}
			else {
				j--;
			}*/

			//glClear(GL_COLOR_BUFFER_BIT);
			//gl_draw_rectangles();
			//glfwSwapBuffers(window);
			//glfwPollEvents();

		}
		
		glClear(GL_COLOR_BUFFER_BIT);
		gl_draw_rectangles();
		glfwSwapBuffers(window);
		glfwPollEvents();

		v_colors[min_i] = RED;
		// swap
		t = v[min_i];
		v[min_i] = v[i];
		v[i] = t;
		v_colors[i] = GREEN;
	}
}
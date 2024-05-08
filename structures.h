#pragma once

struct Color
{
	float r;
	float g;
	float b;
	float a;
};

struct Vector2
{
	float x;
	float y;
};

struct Vertex
{
	Vector2 position;
	Color color;
};

typedef enum
{
	NONE,
	LINEAR_SEARCH,
	BINARY_SEARCH,
	BUBBLE_SORT,
	SELECTION_SORT,
} ALGO;

//std::vector<float> R = {
//		rx, ry, GREEN.r, GREEN.g, GREEN.b, GREEN.a,
//		rx, rh, GREEN.r, GREEN.g, GREEN.b, GREEN.a,
//		rw, rh, GREEN.r, GREEN.g, GREEN.b, GREEN.a,
//		rw, ry, GREEN.r, GREEN.g, GREEN.b, GREEN.a,
//};
//float R[] =
//{
//	rx, ry, GREEN.r, GREEN.g, GREEN.b, GREEN.a,
//	rx, rh, GREEN.r, GREEN.g, GREEN.b, GREEN.a,
//	rw, rh, GREEN.r, GREEN.g, GREEN.b, GREEN.a,
//	rw, ry, GREEN.r, GREEN.g, GREEN.b, GREEN.a,
//};

/*std::vector<Vertex> R = {
			{{rx, ry}, YELLOW},
			{{rx, rh}, YELLOW},
			{{rw, rh}, YELLOW},
			{{rw, ry}, YELLOW},
		};*/


// EXTRA CODE
//batch[curr_next].color = GREEN;
					//batch[curr_next + 1].color = GREEN;
					//batch[curr_next + 2].color = GREEN;
					//batch[curr_next + 3].color = GREEN;

					////batch[curr].color = BLUE;
					////batch[curr + 1].color = BLUE;
					////batch[curr + 2].color = BLUE;
					////batch[curr + 3].color = BLUE;
					//

					//Vertex one = batch[curr];
					//Vertex two = batch[curr + 1];
					//Vertex three = batch[curr + 2];
					//Vertex four = batch[curr + 3];
					//
					////std::vector<Vertex> tv = { one, two, three, four };

					////tv.push_back(batch[curr]);
					////tv.push_back(batch[curr + 1]);
					////tv.push_back(batch[curr + 2]);
					////tv.push_back(batch[curr + 3]);

					//batch[curr] = batch[curr_next];
					//batch[curr + 1] = batch[curr_next + 1];
					//batch[curr + 2] = batch[curr_next + 2];
					//batch[curr + 3] = batch[curr_next + 3];
					//

					//batch[curr_next] = one;
					//batch[curr_next + 1] = two;
					//batch[curr_next + 2] = three;
					//batch[curr_next + 3] = four;
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


//// dosnt work
//void batch_swap(int i1, int i2)
//{
//	Vertex one = batch[i1];
//	Vertex two = batch[i1 + 1];
//	Vertex three = batch[i1 + 2];
//	Vertex four = batch[i1 + 3];
//
//	Vertex five = batch[i2];
//	Vertex six = batch[i2 + 1];
//	Vertex seven = batch[i2 + 2];
//	Vertex eight = batch[i2 + 3];
//
//	batch[i1] = five;
//	batch[i1 + 1] = six;
//	batch[i1 + 2] = seven;
//	batch[i1 + 3] = eight;
//
//	batch[i2] = one;
//	batch[i2 + 1] = two;
//	batch[i2 + 2] = three;
//	batch[i2 + 3] = four;
//}

/*v = { 100, 20, 80, 100, 70, 10, 30, 50, 60, 40,
		10, 30, 50, 110, 60, 40, 60, 70, 20, 10,
		50, 60, 80, 10, 40, 30, 50, 90, 100, 130,
		50, 20, 10, 30, 60, 70, 11, 80, 10, 20,
		50, 20, 10, 30, 60, 70, 10, 80, 10, 20 };
	v2 = v;
	v_colors2.resize(v.size(), YELLOW);
	v_colors.resize(v.size(), YELLOW);*/
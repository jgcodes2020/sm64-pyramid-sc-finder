#include "Surface.hpp"
#include <cmath>
#include <algorithm>

void Surface::set_vertices(std::vector<std::vector<float>> &verts) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			vertices[i][j] = verts[i][j];
		}
	}

	lower_y = std::min(std::min(vertices[0][1], vertices[1][1]), vertices[2][1]) - 5;
	upper_y = std::max(std::max(vertices[0][1], vertices[1][1]), vertices[2][1]) + 5;

	min_x = std::min(std::min(vertices[0][0], vertices[1][0]), vertices[2][0]);
	max_x = std::max(std::max(vertices[0][0], vertices[1][0]), vertices[2][0]);
	min_z = std::min(std::min(vertices[0][2], vertices[1][2]), vertices[2][2]);
	max_z = std::max(std::max(vertices[0][2], vertices[1][2]), vertices[2][2]);

	calculate_normal();
}

void Surface::set_vertices(VecVec3f &verts) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			vertices[i][j] = verts[i][j];
		}
	}

	lower_y = std::min(std::min(vertices[0][1], vertices[1][1]), vertices[2][1]) - 5;
	upper_y = std::max(std::max(vertices[0][1], vertices[1][1]), vertices[2][1]) + 5;

	min_x = std::min(std::min(vertices[0][0], vertices[1][0]), vertices[2][0]);
	max_x = std::max(std::max(vertices[0][0], vertices[1][0]), vertices[2][0]);
	min_z = std::min(std::min(vertices[0][2], vertices[1][2]), vertices[2][2]);
	max_z = std::max(std::max(vertices[0][2], vertices[1][2]), vertices[2][2]);

	calculate_normal();
}

void Surface::calculate_normal() {
	normal[0] = (vertices[1][1] - vertices[0][1]) * (vertices[2][2] - vertices[1][2]) - (vertices[1][2] - vertices[0][2]) * (vertices[2][1] - vertices[1][1]);
	normal[1] = (vertices[1][2] - vertices[0][2]) * (vertices[2][0] - vertices[1][0]) - (vertices[1][0] - vertices[0][0]) * (vertices[2][2] - vertices[1][2]);
	normal[2] = (vertices[1][0] - vertices[0][0]) * (vertices[2][1] - vertices[1][1]) - (vertices[1][1] - vertices[0][1]) * (vertices[2][0] - vertices[1][0]);

	float mag = sqrtf(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);

	mag = (float)(1.0 / mag);
	normal[0] *= mag;
	normal[1] *= mag;
	normal[2] *= mag;

	origin_offset = -(normal[0] * vertices[0][0] + normal[1] * vertices[0][1] + normal[2] * vertices[0][2]);
}

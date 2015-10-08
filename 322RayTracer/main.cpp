//#include <SDL.h>
#include <iostream>

#include <fstream>
#include <D:\james\Documents\Visual Studio 2015\Projects\332RayTracer\glm-0.9.6.3\glm\glm.hpp>
#include "Ray.h"
#include "Sphere.h"


//using namespace std;
int width = 640;
int height = 480;
glm::vec3 **image = new glm::vec3*[640];

Ray ray;
Sphere One(glm::vec3(0, 0, -20), 4, glm::vec3(0, 1, 0));
Sphere Two(glm::vec3(5, -1, -15), 4, glm::vec3(0, 1, 0));
Sphere Three(glm::vec3(5, 0, -25), 4, glm::vec3(0, 0, 1));
Sphere Four(glm::vec3(-5, -1, -15), 4, glm::vec3(1, 1, 0));

void Fill_Image() {
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			image[x][y] = glm::vec3(1, 1, 0);
		}
	}
}

void Save_Image() {
	std::ofstream ofs("./untitled.pmm", std::ios::out | std::ios::binary);
	ofs << "P6\n" << width << " " << height << "\n255\n";
	for (unsigned y = 0; y < height; ++y) {
		for (unsigned x = 0; x < width; ++x) {
			ofs << (unsigned char)(std::fmin((float)1, (float)image[x][y].x) * 255) <<
				(unsigned char)(std::fmin((float)1, (float)image[x][y].y) * 255) <<
				(unsigned char)(std::fmin((float)1, (float)image[x][y].z) * 255);
		}
	}
	ofs.close();
}


int main() {

	for (int i(0); i < width; i++) image[i] = new glm::vec3[height];
	//Fill_Image();
	ray.RayCast(image,&One);
	Save_Image();
	std::cin.get();
	return 0;
}
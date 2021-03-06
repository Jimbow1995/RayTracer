#pragma once
#include <glm.hpp>
#include "Shape.h"
#include "Light.h"

class Sphere :public Shape {
public:
	//Light* light;
	glm::vec3 Origin;
	float Radius;
	Sphere(glm::vec3 o, float r, glm::vec3 c,float _Ambient, float _Specular, bool _Reflective, float _Reflectivity, float _AmountOfBaseColour) :
		Shape(c,_Ambient,_Specular,_Reflective, _Reflectivity, _AmountOfBaseColour), Origin(o), Radius(r)
	{
	};
	virtual Intersect Intersection(glm::vec3 Origin, glm::vec3 Direction);
	virtual glm::vec3 PhongShading(float, glm::vec3, glm::vec3, glm::vec3, float, Shape*[] ,int numberofshapes);
	virtual glm::vec3 GetOrigin() { return Origin; };
	virtual void SetOrigin(glm::vec3 _NewOrigin) { Origin = _NewOrigin; };
	/*glm::vec3 CalcAmbient();
	glm::vec3 CalcDiffuse(glm::vec3, glm::vec3);
	glm::vec3 CalcSpecular(glm::vec3, glm::vec3, glm::vec3,glm::vec3);*/
};
#include <iostream>
#include "Shape.h"

glm::vec3 Shape::CalcAmbient()
{
	return Colour*Ambient;
}

glm::vec3 Shape::CalcDiffuse(glm::vec3 l, glm::vec3 n, float intensity)
{
	float Calc = (intensity*std::fmax(0, glm::dot(l, n)));
	return Colour*Calc;
}

glm::vec3 Shape::CalcSpecular(glm::vec3 l, glm::vec3 n, glm::vec3 CameraPos, glm::vec3 ContactPoint, float intensity) {
	glm::vec3 v = glm::normalize(CameraPos - ContactPoint);
	glm::vec3 r = glm::normalize(l - 2.0f*(glm::dot(l, n) * n));
	glm::vec3 Calc1 = glm::vec3(1,1,1) * intensity;
	float Calc2 = pow(std::fmax(0, glm::dot(r, v)), Specular);
	return Calc1*Calc2;
}

Intersect Shape::CheckHit(Shape* SArray[], glm::vec3 _O, glm::vec3 _D, float AmountOfShapes)
{
	Intersect TempInt(0, glm::vec3(0, 0, 0));
	Intersect LowestIntersect(99999, glm::vec3(0, 0, 0));
	for (int i = 0; i < AmountOfShapes; i++) {
		TempInt = SArray[i]->Intersection(_O, _D);
		if (TempInt.Distance != -1 && TempInt.Distance < LowestIntersect.Distance) {
			LowestIntersect = TempInt;
			LowestIntersect.ObjectID = i;
		}
	}
	return LowestIntersect;
}

glm::vec3 Shape::Reflections(glm::vec3 n, glm::vec3 RDireciton, glm::vec3 ContactPoint, Shape* ShapeArray[], glm::vec3 lightpos, float intensity, int numberofshapes)
{
	//r = d?2(d?n)n
	glm::vec3 RRay = RDireciton - 2.0f*(glm::dot(RDireciton, n) * n);
	Intersect Object = CheckHit(ShapeArray, ContactPoint, RRay, numberofshapes);
	glm::vec3 l = glm::normalize(lightpos - ContactPoint);
	if (Object.ObjectID != -1) {
		return AmountOfBaseColour*(CalcAmbient() + CalcDiffuse(l, n, intensity) + CalcSpecular(-l, n, glm::vec3(0,0,0), ContactPoint, intensity)) + Reflectivity*ShapeArray[Object.ObjectID]->PhongShading(Object.Distance, ContactPoint, RRay, lightpos, intensity, ShapeArray, numberofshapes);
	}
	return AmountOfBaseColour*(CalcAmbient() + CalcDiffuse(l, n, intensity) + CalcSpecular(-l, n, glm::vec3(0, 0, 0), ContactPoint, intensity)) + Reflectivity *glm::vec3(0,0,0);
}



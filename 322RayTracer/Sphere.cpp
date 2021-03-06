#include "Sphere.h"
#include <iostream>
//-1 means not collision
Intersect Sphere::Intersection(glm::vec3 ROrigin, glm::vec3 RDirection) {
	glm::vec3 l = Origin - ROrigin;
	float tca = glm::dot(l, RDirection);
	float RadSquared = Radius * Radius;
	if (0.0f >tca ) {
		return Intersect(-1.0f,glm::vec3(0.0f,0.0f,0.0f) );
	}
	float SS = dot(l, l) - (tca *tca);
	if (SS > RadSquared) {
		return Intersect(-1, glm::vec3(0,0,0));
	}
	float t = (tca - sqrt(RadSquared - SS));
	glm::vec3 ContactPoint = ROrigin + t*RDirection;
	glm::vec3 n = glm::normalize(ContactPoint - Origin);
	return Intersect(t,n);
}

glm::vec3 Sphere::PhongShading(float _t, glm::vec3 ROrigin, glm::vec3 RDirection, glm::vec3 lightpos, float intensity, Shape* ShapeArray[], int numberofshapes)
{
	if (!Reflective) {
		glm::vec3 ContactPoint = ROrigin + _t*RDirection;
		glm::vec3 l = glm::normalize(lightpos - ContactPoint);
		glm::vec3 n = glm::normalize(ContactPoint - Origin);
		return CalcAmbient() + CalcDiffuse(l, n, intensity) + CalcSpecular(l, n, Origin, ContactPoint, intensity);
	}
	else {
		glm::vec3 ContactPoint = ROrigin + _t*RDirection;
		glm::vec3 n = glm::normalize(ContactPoint - Origin);
		return(Reflections(n, RDirection, ContactPoint, ShapeArray, lightpos, intensity, numberofshapes));
	}
}




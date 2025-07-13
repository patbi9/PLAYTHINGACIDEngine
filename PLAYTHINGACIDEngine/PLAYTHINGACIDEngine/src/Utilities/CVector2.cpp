#include "Utilities/CVector2.h"

//constructores y asignacion de valores
CVector2::CVector2() : x(0.f), y(0.f) {}
CVector2::CVector2(float x_, float y_) : x(x_), y(y_) {}

//operadores aritmeticos
CVector2
CVector2::operator+ (const CVector2& otro) const {
	return{
	 x + otro.x,
	 y + otro.y
	};
}
CVector2
CVector2::operator- (const CVector2& otro) const {
	return {
		x - otro.x,
		y - otro.y
	};
}
CVector2
CVector2::operator* (float sca) const {
	return{
		x * sca,
		y * sca
	};
}

CVector2
CVector2::operator/ (float sca) const {
	return{
		x / sca,
		y / sca
	};
}

//operadores aritmeticos que asignan
CVector2&
CVector2::operator+= (const CVector2& otro) {
	x += otro.x;
	y += otro.y;
	return *this;
}
CVector2&
CVector2::operator-=(const CVector2& otro) {
	x -= otro.x;
	y -= otro.y;
	return *this;
}
CVector2&
CVector2::operator*=(float sca) {
	x *= sca;
	y *= sca;
	return *this;
}
CVector2&
CVector2::operator/=(float sca) {
	x /= sca;
	y /= sca;
	return *this;
}

//las comparaciones
bool
CVector2::operator==(const CVector2& otro) const {
	return x == otro.x && y == otro.y;
}
bool
CVector2::operator!=(const CVector2& otro) const {
	return !(*this == otro);
}

//indice accesxo
float&
CVector2::operator[](std::size_t i) {
	return (i == 0) ? x : y;
}
const float&
CVector2::operator[](std::size_t i) const {
	return (i == 0) ? x : y;
}

//funciones geometricas
//que perro el profe, ya vi que nos hizo una trampa, el no esta haciendo una libreria matematica personalizada, el si depende de std
float
CVector2::length() const {
	return sqrt(x * x + y * y);
}
float
CVector2::lengthSquared()const {
	return x * x + y * y;
}
float
CVector2::dot(const CVector2& otro)const {
	return x * otro.x + y * otro.y;
}
float
CVector2::cross(const CVector2& otro)const {
	return x * otro.y - y * otro.x;
}
CVector2
CVector2::normalized()const {
	float len = length();
	if (len == 0.f) {
		return CVector2(0.f, 0.f);
	}
	else {
		return CVector2(x / len, y / len);
	}
}
void
CVector2::normalize() {
	float len = length();
	if (len != 0.f) {
		x /= len;
		y /= len;
	}
}

//metodos estaticos de utilidad
float
CVector2::distance(const CVector2& a, const CVector2& b) {
	return (a - b).length();
}

CVector2
CVector2::lerp(const CVector2& a, const CVector2& b, float t) {
	return a + (b - a) * t;
}
CVector2
CVector2::zero() {
	return CVector2(0.f, 0.f);
}
CVector2
CVector2::one() {
	return CVector2(1.f, 1.f);
}

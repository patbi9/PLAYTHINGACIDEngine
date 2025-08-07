#pragma once
#include "..\Prerequisites.h"

class CVector2 {
private:
	float x;
	float y;
public:
	//constructores
	CVector2() : x(0.f), y(0.f) {}
	CVector2(float x, float y) : x(x), y(y) {}
	//operadores aritmeticos sin asignacion
	CVector2
		operator+ (const CVector2& otro) const {
		return{
		 x + otro.x,
		 y + otro.y
		};
	}
	CVector2
		operator- (const CVector2& otro) const {
		return{
		 x - otro.x,
		 y - otro.y
		};
	}
	CVector2
		operator* (float fac) const {
		return{
		 x * fac,
		 y * fac
		};
	}
	CVector2
		operator/ (float fac) const {
		return{
		 x / fac,
		 y / fac
		};
	}
	//operadores aritmeticos con asignacion
	//in place
	CVector2
		operator+= (const CVector2& otro) {
		x += otro.x;
		y += otro.y;
		return *this;
	}
	CVector2
		operator-= (const CVector2& otro) {
		x -= otro.x;
		y -= otro.y;
		return *this;
	}
	CVector2
		operator*= (float fac) {
		x *= fac;
		y *= fac;
		return *this;
	}
	CVector2
		operator/= (float fac) {
		x /= fac;
		y /= fac;
		return *this;
	}
	//comparaciones
	bool
		operator==(const CVector2& otro) const {
		return x == otro.x && y == otro.y;
	}
	bool
		operator!=(const CVector2& otro) const {
		return (x != otro.x || y != otro.y);
	}
	//Acceso por indice
	float&
		operator[](std::size_t i) {
		if (i == 0) {
			return x;
		}
		else {
			return y;
		}
	}
	//geometria
	float
		length() const {
		return sqrt(x * x + y * y);
	}
	float
		lengthSquared() const {
		return x * x + y * y;
	}
	float
		dot(const CVector2& otro)const {
		return x * otro.x + y * otro.y;
	}
	float
		cross(const CVector2& otro) const {
		return (x * otro.y - y * otro.x);
	}
	CVector2
		normalized() {
		float len = length();
		if (len == 0.f) {
			return CVector2(0.f, 0.f);
		}
		else {
			return CVector2(x / len, y / len);
		}
	}
	void
		normalize() {
		float len = length();
		if (len != 0.f) {
			x /= len;
			y /= len;
		}
	}
	//funciones estaticas
	static float
		distance(const CVector2& a, const CVector2& b) {
		return (b - a).length();
	}
	static CVector2
		lerp(const CVector2& a, const CVector2& b, float t) {
		return a + (b - a) * t;
	}
	static CVector2
		zero() {
		return CVector2(0.f, 0.f);
	}
	static CVector2
		one() {
		return CVector2(1.0f, 1.0f);
	}
	//metodos estilo transform para depuración
	void
		setPosition(const CVector2& position) {
		x = position.x;
		y = position.y;
	}
	void
		move(const CVector2& offset) {
		x += offset.x;
		y += offset.y;
	}
	void
		setScale(const CVector2& factors) {
		x = factors.x;
		y = factors.y;
	}
	void
		scale(const CVector2& factors) {
		x *= factors.x;
		y *= factors.y;
	}
	void
		setOrigin(const CVector2& origin) {
		x = origin.x;
		y = origin.y;
	}
};
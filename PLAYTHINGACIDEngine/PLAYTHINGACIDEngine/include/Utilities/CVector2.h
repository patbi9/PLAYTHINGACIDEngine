#pragma once
#include "../Prerequisites.h"

class CVector2 {
public:

	float x;
	float y;

	//aqui todavia no se implementan, solo se declaran
	 //constructor defecto
	CVector2();
	//constructor con parametros x y
	CVector2(float x_, float y_);

	//operadores aritmeticos
	//(no modifican el vector original))
	//operator le enseña a c++ a operar vectores, redefinimos +-*/
	CVector2
		operator+(const CVector2& otro) const;
	CVector2
		operator-(const CVector2& otro) const;
	CVector2
		operator*(float sca) const;
	CVector2
		operator/(float sca) const;

	//operadores aritmeticos con asignacion
	//estos si modifican al vector original
	CVector2&
		operator+=(const CVector2& otro);
	CVector2&
		operator-=(const CVector2& otro);
	CVector2&
		operator*=(float sca);
	CVector2&
		operator/=(float sca);

	//comparaciones
	bool
		operator==(const CVector2& otro) const;
	bool
		operator!=(const CVector2& otro) const;

	//indice accesexo
	//usar std::size_t nos ayuda a que no haya negativos en el tipo
	float&
		operator[](std::size_t i);
	const float&
		operator[](std::size_t i) const;

	//geometria
	float
		length() const;
	float
		lengthSquared()const;
	float
		dot(const CVector2& otro)const;
	float
		cross(const CVector2& otro)const;
	CVector2
		normalized()const;
	void
		normalize();

	//metodos aesthaticos de utilidad
	static float
		distance(const CVector2& a, const CVector2& b);
	static
		CVector2 lerp(const CVector2& a, const CVector2& b, float t);
	static CVector2
	zero();
	static CVector2
	one();


	//metodos estilo transform para depuracion

	//Establece la posición absoluta en coordenadas del objeto.
	void
		setPosition(const sf::Vector2f& position);
	//Traslada el objeto respecto a su posición actual.
	void
		move(const sf::Vector2f& offset);
	//Define la escala X e Y simultáneamente.
	void
		setScale(const sf::Vector2f& factors);
	//Multiplica la escala actual por los factores dados.
	void
		scale(const sf::Vector2f& factors);
	//Fija el punto de origen (centro de rotación/escala).
	void
		setOrigin(const sf::Vector2f& origin);
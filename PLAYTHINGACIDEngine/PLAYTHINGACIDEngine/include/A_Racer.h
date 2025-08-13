#pragma once
#include "Actor.h" 
#include <vector>
#include "Math/EngineMath.h"

class A_Racer : public Actor {
public:
    A_Racer(const std::string& name, int initPlace = 0);

    void update(float deltaTime) override;

    void setWaypoints(const std::vector<sf::Vector2f>& waypoints);
    void setSpeed(float s) { maxSpeed = s; }  // alias

    // tuning opcional
    void setMaxSpeed(float s) { maxSpeed = s; }
    void setMaxForce(float f) { maxForce = f; }
    void setMass(float m) { mass = (m <= 0.f ? 1.f : m); }
    void setArrive(float slowR, float arriveR) { slowRadius = slowR; arriveRadius = arriveR; }
    void setLinearDrag(float d) { linearDrag = d; } // 0..1 aprox

    float getProgressMeters() const;

    // spawn helper opcional que ya tenías
    void spawnRelative(int wpIndex, float backPx, float lateralPx);

    void setPlace(int p) { place = p; }   // <— NUEVO
    int  getPlace() const { return place; } // <— NUEVO

private:
    // path
    std::vector<sf::Vector2f> m_waypoints;
    int currentWp = 0;
    int lap = 0;
    int place = -1; // si lo usas en leaderboard

    // física (steering)
    sf::Vector2f velocity{ 0.f, 0.f };
    float maxSpeed = 300.f;   // px/s
    float maxForce = 600.f;   // (px/s^2) * mass
    float mass = 1.0f;    // kg virtual
    float slowRadius = 10.f;    // empieza a frenar
    float arriveRadius = 100.f;  // considera alcanzado
    float linearDrag = 0.12f;   // fricción lineal

    // helpers
    void steerPhysics(float dt);
    float loopLength() const;
    float lapProgressMeters() const;
};

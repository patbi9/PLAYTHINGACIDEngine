#include "A_Racer.h"
#include "ECS/Transform.h"
#include <algorithm>

static inline float length(const sf::Vector2f& v) { return sqrt(v.x * v.x + v.y * v.y); }
static inline sf::Vector2f normalize(const sf::Vector2f& v) {
    float L = length(v); return (L > 1e-5f) ? sf::Vector2f(v.x / L, v.y / L) : sf::Vector2f(0.f, 0.f);
}
static inline sf::Vector2f clampMag(sf::Vector2f v, float max) {
    float L = length(v); if (L > max && L > 0.f) v *= (max / L); return v;
}

A_Racer::A_Racer(const std::string& name, int initPlace)
    : Actor(name), place(initPlace) {
}

void A_Racer::setWaypoints(const std::vector<sf::Vector2f>& wps) {
    m_waypoints = wps;
    if (!m_waypoints.empty()) {
        currentWp = 0;
        velocity = { 0.f, 0.f };
        if (auto tr = getComponent<Transform>())
            tr->setPosition(m_waypoints[0]);
    }
}

void A_Racer::update(float dt) {
    Actor::update(dt);
    if (m_waypoints.size() >= 2) steerPhysics(dt);
}

void A_Racer::steerPhysics(float dt) {
    auto tr = getComponent<Transform>();
    if (!tr) return;

    const sf::Vector2f pos = tr->getPosition();
    const sf::Vector2f target = m_waypoints[currentWp];

    sf::Vector2f toTarget = target - pos;
    float d = length(toTarget);

    // waypoint alcanzado -> siguiente
    if (d < arriveRadius) {
        currentWp = (currentWp + 1) % static_cast<int>(m_waypoints.size());
        if (currentWp == 0) ++lap;
        return; // siguiente frame recalcula hacia el nuevo objetivo
    }

    // ARRIVE: desacelera al acercarse
    float desiredSpeed = maxSpeed;
    if (d < slowRadius) desiredSpeed = maxSpeed * (d / slowRadius);

    sf::Vector2f desiredVel = normalize(toTarget) * desiredSpeed;

    // steering = desired - current
    sf::Vector2f steering = desiredVel - velocity;
    steering = clampMag(steering, maxForce);   // limitar fuerza

    // a = F/m, integrar
    sf::Vector2f accel = steering / std::max(mass, 0.0001f);
    velocity += accel * dt;

    // fricción lineal estable
    float dragFactor = std::clamp(1.f - linearDrag * dt, 0.f, 1.f);
    velocity *= dragFactor;

    // limitar velocidad y mover
    velocity = clampMag(velocity, maxSpeed);
    tr->setPosition(pos + velocity * dt);
}

// ---------- progreso/leaderboard (igual que antes) ----------
float A_Racer::loopLength() const {
    if (m_waypoints.size() < 2) return 0.f;
    float sum = 0.f;
    for (size_t i = 0; i < m_waypoints.size(); ++i) {
        const auto& a = m_waypoints[i];
        const auto& b = m_waypoints[(i + 1) % m_waypoints.size()];
        sum += length(b - a);
    }
    return sum;
}

float A_Racer::lapProgressMeters() const {
    if (m_waypoints.size() < 2) return 0.f;
    int prev = (currentWp == 0) ? static_cast<int>(m_waypoints.size()) - 1 : currentWp - 1;

    float acc = 0.f;
    for (int i = 0; i < prev; ++i)
        acc += length(m_waypoints[i + 1] - m_waypoints[i]);

    // proyección sobre [prev -> currentWp]
    const sf::Vector2f P = getComponent<Transform>()->getPosition();
    const sf::Vector2f A = m_waypoints[prev];
    const sf::Vector2f B = m_waypoints[currentWp];
    const sf::Vector2f AB = B - A, AP = P - A;
    const float ab2 = AB.x * AB.x + AB.y * AB.y;
    float t = (ab2 > 0.f) ? (AP.x * AB.x + AP.y * AB.y) / ab2 : 0.f;
    t = std::clamp(t, 0.f, 1.f);

    acc += length(AB * t);
    return acc;
}

float A_Racer::getProgressMeters() const {
    return lap * loopLength() + lapProgressMeters();
}

// spawnRelative opcional (parrilla)
void A_Racer::spawnRelative(int wpIndex, float backPx, float lateralPx) {
    if (m_waypoints.size() < 2) return;
    int n = (int)m_waypoints.size();
    int i = (wpIndex % n + n) % n, j = (i + 1) % n;
    sf::Vector2f A = m_waypoints[i], B = m_waypoints[j];
    sf::Vector2f dir = normalize(B - A);
    sf::Vector2f right = { -dir.y, dir.x };
    if (auto tr = getComponent<Transform>())
        tr->setPosition(A - dir * backPx + right * lateralPx);
    currentWp = j; // objetivo hacia adelante
}

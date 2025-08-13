/**
 * @file A_Racer.h
 * @brief Actor that follows a series of waypoints using simple steering physics for a racing scenario.
 *
 * @details
 * A_Racer moves along a loop of 2D waypoints with basic steering/arrival behavior.
 * It tracks lap and waypoint progress, supports configurable physics parameters
 * (max speed/force, mass, drag), and exposes helpers to spawn relative to a given
 * waypoint and to query linear progress along the track.
 */

#pragma once
#include "Actor.h" 
#include <vector>
#include "Math/EngineMath.h"

 /**
  * @class A_Racer
  * @brief Waypoint-based racer actor with steering/arrival behavior.
  *
  * The racer advances toward the current waypoint, applies simple steering physics,
  * and wraps over the waypoint list to complete laps. Call @ref setWaypoints before
  * updating to provide a valid path.
  */
class A_Racer : public Actor {
public:
 /**
  * @brief Constructs a racer.
  * @param name Display name for this racer.
  * @param initPlace Optional initial race place/position (default 0).
  */
 A_Racer(const std::string& name, 
         int initPlace = 0);

 /**
  * @brief Per-frame update for racer movement and logic.
  * @param deltaTime Time step in seconds since the last frame.
  */
 void
  update(float deltaTime) override;

 /**
  * @brief Sets the path this racer should follow.
  * @param waypoints Ordered list of 2D waypoints forming a looped track.
  * @note The racer will iterate indices and wrap when reaching the end.
  */
 void
  setWaypoints(const std::vector<sf::Vector2f>& waypoints);

 /**
  * @brief Convenience setter for maximum linear speed.
  * @param s Maximum speed (world units per second, engine scale dependent).
  */
 void
  setSpeed(float s) { maxSpeed = s; }

 /**
  * @brief Sets maximum linear speed.
  * @param s Maximum speed (world units per second, engine scale dependent).
  */
 void 
  setMaxSpeed(float s) { maxSpeed = s; }

 /**
  * @brief Sets maximum steering force (acceleration clamp).
  * @param f Maximum force used by steering solver (units depend on scale).
  */
 void 
  setMaxForce(float f) { maxForce = f; }

 /**
  * @brief Sets the dynamic mass used in acceleration = force / mass.
  * @param m Mass value; values <= 0 are clamped to 1.0.
  */
 void 
  setMass(float m) { mass = (m <= 0.f ? 1.f : m); }

 /**
  * @brief Sets arrival radii for smooth approach to waypoints.
  * @param slowR Inside this radius, speed is reduced (slowdown zone).
  * @param arriveR Distance considered "arrived" to the waypoint (target switch).
  */
 void
  setArrive(float slowR, float arriveR) { slowRadius = slowR; arriveRadius = arriveR; }

 /**
  * @brief Sets linear drag applied each update (simple damping).
  * @param d Drag factor in [0,+inf), typically small (e.g., 0.05–0.2).
  */
 void
  setLinearDrag(float d) { linearDrag = d; }

 /**
  * @brief Returns total linear progress along the track in meters/units.
  * @return Scalar distance representing current lap progress plus completed laps.
  * @note Units depend on your world scale and waypoint spacing.
  */
 float
  getProgressMeters() const;

/**
 * @brief Spawns the racer at a position relative to a given waypoint.
 * @param wpIndex Waypoint index to anchor the spawn.
 * @param backPx Offset backwards/along the path (negative moves behind, positive ahead), in pixels/units.
 * @param lateralPx Lateral offset perpendicular to the path (left/right), in pixels/units.
 *
 * @details
 * Useful to stagger multiple racers so they don't overlap at start. The exact
 * basis vectors (forward/perpendicular) depend on the implementation.
 */
 void
  spawnRelative(int wpIndex, float backPx, float lateralPx);

 /**
  * @brief Sets the race position (place) for leaderboard logic.
  * @param p 1-based or 0-based depending on game logic (stored as-is).
  */
 void 
  setPlace(int p) { place = p; }

 /**
  * @brief Gets the current race position (place).
  * @return The stored place value.
  */
 int
  getPlace() const { return place; }

private:
 /** @brief Waypoints that define the looped path. */
 std::vector<sf::Vector2f> m_waypoints;
 /** @brief Index of the current target waypoint. */
 int 
  currentWp = 0;
 /** @brief Current lap count (wraps when finishing the waypoint list). */
 int 
  lap = 0;
 /** @brief Current leaderboard position; -1 if unset. */
 int 
  place = -1;

 /** @brief Current linear velocity. */
 sf::Vector2f velocity{ 0.f, 0.f };
 /** @brief Maximum linear speed. */
 float 
  maxSpeed = 300.f;
 /** @brief Maximum steering force (acceleration clamp). */
 float 
  maxForce = 600.f;
 /** @brief Mass applied in steering integration. */
 float 
  mass = 1.0f;
 /** @brief Radius within which the racer starts to slow down. */
 float 
  slowRadius = 10.f;
 /** @brief Radius considered "arrived" to the waypoint. */
 float 
  arriveRadius = 100.f;
 /** @brief Linear damping factor applied every update. */
 float
  linearDrag = 0.12f;

 /**
  * @brief Applies steering forces, drag, and integration to update velocity/position.
  * @param dt Time step in seconds.
  */
 void 
  steerPhysics(float dt);

 /**
  * @brief Computes the total length of the waypoint loop.
  * @return Sum of segment lengths between consecutive waypoints (including wrap).
  */
 float 
  loopLength() const;

 /**
  * @brief Computes current lap progress along the loop in meters/units.
  * @return Distance traveled within the current lap, excluding completed laps.
  */
 float 
  lapProgressMeters() const;
};

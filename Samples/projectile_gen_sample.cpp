#include "Containers/Vector.hpp"
#include <iostream>


using namespace math_types;

struct Projectile
{
    Vector3<float> m_position;
    Vector3<float> m_velocity;
    float v=0;

    Projectile(): m_position({0, 0, 0}), m_velocity({0, 0, 0}) {}
    Projectile(math_types::Vector3<float> p, math_types::Vector3<float> v): m_position(p), m_velocity(v){}
    Projectile(const Projectile& other) { this->m_position = other.m_position; this->m_velocity=other.m_velocity; }

    Projectile operator=(const Projectile& p) const {
        return Projectile(p.m_position, p.m_velocity);
    }
};

struct Environment
{
    Vector3<float> m_gravity{0, -9.8, 0};
    Vector3<float> m_wind{0, 0, 0};
    Environment() {}
    Environment(Vector3<float> gravity, Vector3<float> wind): m_gravity(gravity), m_wind(wind) {}
    Environment(const Environment &other) { this->m_gravity = other.m_gravity; this->m_wind = other.m_wind; }
};

Projectile tick(Projectile& p, Environment& e)
{
    p.m_position = p.m_position + p.m_velocity;
    p.m_velocity = p.m_velocity + e.m_gravity + e.m_wind;
    return p;
}

int main(int argc, char *argv[])
{
    Projectile p0({0, 1, 0}, {1, 1, 0});
    p0.m_velocity = p0.m_velocity.normalize();

    Environment e{{0, -0.1, 0}, {-0.01, 0, 0}};

    int max_iterations = 50;
    int i = 0;

    while(p0.m_position.y() >= 0.0f)
    {
        std::cout << "Position: " << p0.m_position << "; Velocity: " << p0.m_velocity <<
                     "; Gravity: " << e.m_gravity << "; Wind: " << e.m_wind << std::endl;
        p0 = tick(p0, e);
        if(i == max_iterations)
            break;
        else
            i++;
    }

    return 0;
}
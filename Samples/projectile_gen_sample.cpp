#include "Containers/Vector.hpp"
#include "RayTracer/Canvas.hpp"
#include <iostream>


using namespace ray_tracer;

struct Projectile
{
    Vector3<float> m_position;
    Vector3<float> m_velocity;
    float v=0;

    Projectile(): m_position({0, 0, 0}), m_velocity({0, 0, 0}) {}
    Projectile(Vector3<float> p, Vector3<float> v): m_position(p), m_velocity(v){}
    Projectile(const Projectile& other) { this->m_position = other.m_position; this->m_velocity=other.m_velocity; }

    Projectile operator=(const Projectile& p) const {
        return Projectile(p.m_position, p.m_velocity);
    }
};

struct Environment
{
    Vector3<float> m_gravity{0, 0, 0};
    Vector3<float> m_wind{0, 0, 0};
    Environment() {}
    Environment(Vector3<float> gravity, Vector3<float> wind): m_gravity(gravity), m_wind(wind) {}
    Environment(const Environment &other) { this->m_gravity = other.m_gravity; this->m_wind = other.m_wind; }
};

Projectile tick(Projectile& p, Environment& e)
{
    p.m_position = p.m_position + p.m_velocity;
    p.m_position[0] = std::trunc(p.m_position[0]);
    p.m_position[1] = std::trunc(p.m_position[1]);
    p.m_velocity = p.m_velocity + e.m_gravity + e.m_wind;
    return p;
}

int main(int argc, char *argv[])
{
    Projectile p0({0, 1, 0}, {1, 1.8, 0});
    p0.m_velocity = p0.m_velocity.normalize() * 11.25;

    Environment e{{0, -0.1, 0}, {-0.01, 0, 0}};

    int max_iterations = 187;
    int i = 0;

    Canvas<int> image{900, 555};
    Color<int> c{255, 0, 0};
    while(p0.m_position.y() >= 0.0f)
    {
        std::cout << "Position: " << p0.m_position << "; Velocity: " << p0.m_velocity <<
                     "; Gravity: " << e.m_gravity << "; Wind: " << e.m_wind << std::endl;
        p0 = tick(p0, e);
        image.set_pixel(p0.m_position.x(), image.get_canvas_height() - p0.m_position.y(), c);
        if(i == max_iterations)
            break;
        else
            i++;
    }
    std::string file_name = "projectile";
    std::string path = "..";

    Canvas<int> dst{900, 555};
    image.save_to_ppm(file_name, path);
    dst = image.load_ppm(file_name, path);

    if(dst == image)
        std::cout << "Computed and saved images are the same!" << std::endl;


    return 0;
}

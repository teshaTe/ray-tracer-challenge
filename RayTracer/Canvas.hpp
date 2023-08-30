#ifndef RENDERINGCANVAS_HPP
#define RENDERINGCANVAS_HPP

#include "Containers/Color.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <utility>


namespace ray_tracer {
using namespace std::string_literals;

template<class T>
class Canvas
{
private:
    std::vector<Color<T>> m_canvas;
    int m_width;
    int m_height;
    T m_max_col_val;

public:
    Canvas(const int image_width, const int image_height) : m_width(image_width), m_height(image_height)
    {
        m_canvas.resize(m_width*m_height);
        if(typeid(T).name() == "float"s || typeid(T).name() == "double"s)
            m_max_col_val = 1.0;
        else
            m_max_col_val = 255;
    }

    Canvas(const Canvas& other)
    {
        this->m_canvas = other.m_canvas;
        this->m_width = other.m_width;
        this->m_height = other.m_height;
        this->m_max_col_val = other.m_max_col_val;
    }

    Color<T>& operator[](int i) { return m_canvas[i]; }

    T clip(T val)
    {
        if(val < 0)
            return 0;
        else if (val > m_max_col_val)
            return m_max_col_val;
        else
            return val;
    }

    void resize(const int image_width, const int image_height)
    {
        m_canvas.resize(image_width*image_height);
        m_width = image_width;
        m_height = image_height;
    }

    void set_pixel(const int x, const int y, Color<T> val)
    {
        if((x >= 0 && x < m_width) && (y>=0 && y < m_height))
            m_canvas[x+y*m_width] = Color<T>{clip(val.r()), clip(val.g()), clip(val.b())};
        else
            throw std::out_of_range("Either x or y coordinate is out of range!");
    }

    Color<T> get_pixel(const int x, const int y)
    {
        return m_canvas[x + y*m_width];
    }

    void save_to_ppm(std::string& file_name, std::string& output_path)
    {
        try
        {
            std::string out_path = output_path + "\\" + file_name + ".ppm";
            std::ofstream file;
            file.open(out_path, std::ios_base::app);
            file.exceptions(std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);

            // writing ppm header of the file
            file << "P3" << std::endl;
            file << m_width << " " << m_height << std::endl;
            file << m_max_col_val << std::endl;
            file << std::endl;

            for (int y = 0; y < m_height; ++y)
            {
                for (int x = 0; x < m_width; ++x)
                {
                    Color<T> pixel = get_pixel(x, y);
                    file << pixel.r() << " " << pixel.g() << " " << pixel.b() << " ";
                    if(x == m_width-1)
                        file << std::endl;
                }
            }

            file << std::endl;
            file.close();
        } catch(std::ifstream::failure const &e)
        {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }

    Canvas<T> load_ppm(const std::string& file_name, const std::string& path)
    {
        try {
            std::string in_path = path + "/" + file_name + ".ppm";
            std::ifstream file;
            file.open(in_path, std::ios_base::in);
            file.exceptions(std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);
            std::string data;
            file >> data;

            file.close();
        } catch (std::ifstream::failure const &e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
        return ;
    }

    int get_canvas_width() const { return m_width; }
    int get_canvas_height() const { return m_height; }
    size_t get_canvas_container_size() const { return m_canvas.size(); }

    ~Canvas() = default;
};

} // namespace ray_tracer


#endif // RENDERINGCANVAS_HPP

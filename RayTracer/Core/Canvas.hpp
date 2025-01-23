#ifndef RENDERINGCANVAS_HPP
#define RENDERINGCANVAS_HPP

#include "Containers/Color.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <typeinfo>
#include <utility>
#include <numeric>


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

    Canvas(const std::vector<Color<T>>& colors_arr) { m_canvas = colors_arr; }

    Canvas(const Canvas& other)
    {
        this->m_canvas = other.m_canvas;
        this->m_width = other.m_width;
        this->m_height = other.m_height;
        this->m_max_col_val = other.m_max_col_val;
    }

    Color<T>& operator[](int i) { return m_canvas[i]; }

    bool operator==(const Canvas<T>& other) const
    {
        const double eps{0.00001};
        std::vector<Color<T>> diff;
        diff.resize(m_canvas.size());
        T total_r{0};
        T total_g{0};
        T total_b{0};

        for(size_t i = 0; i < m_canvas.size(); i++)
        {
            total_r += m_canvas[i].r() - other.m_canvas[i].r();
            total_g += m_canvas[i].g() - other.m_canvas[i].g();
            total_b += m_canvas[i].b() - other.m_canvas[i].b();
        }

        total_r /= static_cast<double>(diff.size());
        total_g /= static_cast<double>(diff.size());
        total_b /= static_cast<double>(diff.size());

        std::cout << total_r << " " << total_g << " " << total_b << std::endl;

        if( total_r < eps && total_g < eps && total_b < eps)
            return true;
        else
            return false;
    }

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
            file.open(out_path);
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
        }
        catch(std::ifstream::failure const &e)
        {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }

    Canvas<T> load_ppm(const std::string& file_name, const std::string& path)
    {
        try {
            std::string in_path = path + "//" + file_name + ".ppm";
            std::ifstream file(in_path.c_str());
            file.exceptions(std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);
            std::vector<std::string> header;
            for (int i=0; i<4; i++)
            {
                std::string line;
                std::getline(file, line);
                header.push_back(line);
            }

            std::vector<std::string> img_size = SplitString(header[1], ' ');

            int width = std::stoi(img_size[0]);
            int height = std::stoi(img_size[1]);
            float max_col_val = std::stof(header[2]);

            Canvas<T> canvas{width, height};

            std::vector<std::string> lines;
            for(int i = 0; i < height; i++)
            {
                std::string line;
                std::getline(file, line);
                std::vector<std::string> row = SplitString(line, ' ');
                for(int j = 0; j < row.size()-2; j+=3)
                {
                    T r = static_cast<T>(std::stof(row[j]));
                    T g = static_cast<T>(std::stof(row[j+1]));
                    T b = static_cast<T>(std::stof(row[j+2]));
                    Color<T> c{r, g, b};
                    canvas.set_pixel(j/3, i, c);
                }
            }

            file.close();
            return canvas;

        } catch (std::ifstream::failure const &e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
        return Canvas<T>{0, 0};
    }

    std::vector<std::string> SplitString(const std::string &strInput, char cDelimiter)
    {
        std::vector<std::string> vRetValue;

        std::stringstream ss(strInput);
        std::string strItem;
        while(std::getline(ss, strItem, cDelimiter))
        {
            // Skip Empty
            if(strItem.size()==0)
                continue;
            vRetValue.push_back(strItem);
        }

        return vRetValue;
    }

    int get_canvas_width() const { return m_width; }
    int get_canvas_height() const { return m_height; }
    size_t get_canvas_container_size() const { return m_canvas.size(); }

    ~Canvas() = default;
};

} // namespace ray_tracer


#endif // RENDERINGCANVAS_HPP

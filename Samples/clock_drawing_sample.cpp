#include <Containers/Vector.hpp>
#include "Containers/Matrix.hpp"
#include "RayTracer/Core/MatrixUtils.hpp"
#include "RayTracer/Core/Canvas.hpp"

using namespace ray_tracer;


int main(int argc, char *argv[])
{
    Canvas<int> image{800, 800};
    const Color<int> c{255, 0, 0};

    float cx = image.get_canvas_width() / 2.0f;
    float cz = image.get_canvas_height() / 2.0f;

    Vector<float> point{0, 0, 1};

    MatrixUtlities mutils;
    float angle_step = 360.0f / 12.0f;
    float angle = 0.0;

    Matrix<float> ScaleMat = mutils.scaling_mat(3.0f/8.0f*image.get_canvas_width(), 1, 3.0f/8.0f*image.get_canvas_width());
    Matrix<float> TrMat = mutils.translation_mat(cx, 0, cz);

    for(size_t i = 0; i < 12; ++i)
    {
        Matrix<float> Rz = mutils.rotation_mat_YAxis(mutils.toRadiance(angle));
        Vector<float> res = TrMat.mul(ScaleMat).mul(Rz).mul(point).to_vec_1x3();

        std::cout << "pos: " << res << std::endl;

        image.set_pixel(res[0], res[2], c);
        angle += angle_step;
    }

    std::string file_name = "clock_image";
    std::string path = "..";

    image.save_to_ppm(file_name, path);
    return 0;
}

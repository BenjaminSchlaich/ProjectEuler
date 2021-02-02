// MapCreator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <concepts>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <random>
#include <list>
#include "bitmap_image.hpp"

template <typename N>
concept Numeric = std::is_integral_v<N>() || std::is_floating_point_v<N>();

template <typename N>
concept Integral = requires(N n)
{
    std::is_integral<N>(n);
};

template <Numeric B>
class Bounds
{
public:
    Bounds()
    {
        table = new std::list<BoundElement>();
    }

    struct BoundElement
    {
        B* variable; // the adress of the variable to which these bounds should apply
        B upperBound;
        B lowerBound;
        bool inclusiveBounds = true;    // if true, the inBounds will still return true if the variable has one of the bounds as its value
    };

    // adds bounds to the given variable.
    static void bounds(B lower, B& variable, B upper, bool inclusive = true)
    {
        BoundElement e = { variable, upper, lower, inclusive };
        table.push_back(e);
    }

    // checks, if the variable is in bounds specified earlier. Returns true if so. Throws an instance of std::logical_error, if no bounds are known for the given variable.
    static bool inBounds(B& variable)
    {
        for (BoundElement e : table)
        {
            if (e.variable == &variable)
            {
                if (e.inclusiveBounds)
                {
                    if (variable <= e.upperBound && variable >= e.lowerBound)
                        return true;
                    else
                        return false;
                }
                else
                {
                    if (variable < e.upperBound && variable > e.lowerBound)
                        return true;
                    else
                        return false;
                }
            }
        }

        throw std::logic_error("there were no bounds specified for the variable at adress " + &variable);
        return true;
    }

private:
    static std::list<BoundElement> table;
};

constexpr double pi_const = 3.14159265359;
std::random_device rd;
std::mt19937_64 mTwister(rd());
std::uniform_real_distribution<double> distr(0.0, 1.0);

double rando()
{
    return (double)rand()/RAND_MAX;
}

// sine function that takes degrees instead of radians
double dsin(double degrees)
{
    return sin(degrees / 360 * 2 * pi_const);
}

// cosine function that takes degrees instead of radians
double dcos(double degrees)
{
    return cos(degrees / 360 * 2 * pi_const);
}

int wave(int i)
{
    return 255 * (std::sin(i * 0.1) / pi_const + 0.5);
}

double linear(double n)
{
    return 1 - 0.1 * n;
}

void randomMap(bitmap_image* map, image_drawer* draw, rgb_t color, double prob, int x, int y, double (func)(double), int rec = 0)
{
    if (rec > 10)
        return;

    if (x + 1 < map->width() && map->get_pixel(x + 1, y) != color && prob < rando())
    {
        map->set_pixel(x + 1, y, color);
        randomMap(map, draw, color, prob, x + 1, y, func, rec++);
    }

    if (y + 1 < map->height() && map->get_pixel(x, y + 1) != color && prob < rando())
    {
        map->set_pixel(x, y + 1, color);
        randomMap(map, draw, color, prob, x, y + 1, func, rec++);
    }

    /*if (x + 1 < map->width() && y + 1 < map->height() && map->get_pixel(x + 1, y + 1) != color && prob < rando())
    {
        map->set_pixel(x + 1, y + 1, color);
        randomMap(map, draw, color, prob, x + 1, y + 1, func, rec++);
    }//*/

    if (x - 1 > 0 && map->get_pixel(x - 1, y) != color && prob < rando())
    {
        map->set_pixel(x - 1, y, color);
        randomMap(map, draw, color, prob, x -1 , y, func, rec++);
    }

    if (y - 1 > 0 && map->get_pixel(x, y - 1) != color && prob < rando())
    {
        map->set_pixel(x, y - 1, color);
        randomMap(map, draw, color, prob, x, y - 1, func, rec++);
    }

    /*if (x - 1 > 0 && y - 1 > 0 && map->get_pixel(x - 1, y - 1) != color && prob < rando())
    {
        map->set_pixel(x - 1, y - 1, color);
        randomMap(map, draw, color, prob, x - 1, y - 1, func, rec++);
    }

    /*if (x + 1 < map->width() && y - 1 > 0 && map->get_pixel(x + 1, y - 1) != color && prob < rando())
    {
        map->set_pixel(x + 1, y - 1, color);
        randomMap(map, draw, color, prob, x + 1, y - 1, func, rec++);
    }

    if (x - 1 > 0 && y + 1 < map->width() && map->get_pixel(x - 1, y + 1) != color && prob < rando())
    {
        map->set_pixel(x - 1, y + 1, color);
        randomMap(map, draw, color, prob, x - 1, y + 1, func, rec++);
    }//*/

}

void figure(bitmap_image *img, rgb_t color, int xM, int yM, int r, int x=-1, int y=-1, int rec=0)
{
    if (x == -1)
    {
        x = xM;
        y = yM + r;
    }

    if (rec > 20)
    {
        std::cout << "err?" << std::endl;
        return;
    }

    if (img->get_pixel(x, y) == color)  // the figure is closed
        return;

    if (x > 0 && y > 0 && x < img->width() && y < img->height())
        img->set_pixel(x, y, color);

    double alpha = tan((x - xM)/(y - yM));
    alpha+=5;

    int newX = dsin(alpha) * r;
    int newY = dcos(alpha) * r;

    figure(img, color, xM, yM, r, newX, newY, rec + 1);
}

void circle(bitmap_image* img, int xM, int yM, double r, rgb_t color)
{
    /*for (int x = xM-r; x < xM+r; x++)
    {
        double rSq = (double) r * r;
        double y = sqrt(rSq -(x-xM)*(x-xM)) + yM;
        if ((x >= 0) && (y >= 0) && (x < img->width()) && (y < img->height()))
        {
            img->set_pixel(round(x), round(y), color);
            img->set_pixel(round(x), round(img->height()-y), color);
        }
        else
            std::cout << x << "|" << y << ": no valid pixel -> "<< r*r-x*x << std::endl;
    }*/

    double x = (double) xM + r;
    double y = yM;
    for (double a = 0; a < 2*pi_const; a+=pi_const/1000)
    {
        if ((x >= 0) && (y >= 0) && (x < img->width()) && (y < img->height()))
            img->set_pixel(x, y, color);
        a++;
        x += cos(a)*r;
        y += sin(a)*r;
    }
}

void rm2(bitmap_image* img, int xM, int yM, double p, rgb_t color, int rec = 0)
{
    if (rec < 10)
        return;
}

int main()
{
    std::srand(342);
    const int width = 769;
    const int height = 769;

    auto mapimg = new bitmap_image(width, height);
    mapimg->set_all_channels(0x010101);
    image_drawer *draw = new image_drawer(*mapimg);
    draw->pen_color(255,255,255);

    mapimg->save_image("triangle.bmp");

    int x = 5;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

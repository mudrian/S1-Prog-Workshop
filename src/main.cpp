#include <sil/sil.hpp>
#include "random.hpp"
#include <glm/gtx/matrix_transform_2d.hpp>

void keep_green_only(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
    }
}

void swap(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        std::swap(color.g, color.b);
    }
}

void black_and_white(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float grey = (image.pixel(x, y).g + image.pixel(x, y).r + image.pixel(x, y).b) / 3;
            image.pixel(x, y).r = grey;
            image.pixel(x, y).g = grey;
            image.pixel(x, y).b = grey;
        }
    }
}

void negatif(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float ginverse = 1 - image.pixel(x, y).g;
            float rinverse = 1 - image.pixel(x, y).r;
            float binverse = 1 - image.pixel(x, y).b;
            image.pixel(x, y).r = rinverse;
            image.pixel(x, y).g = ginverse;
            image.pixel(x, y).b = binverse;
        }
    }
}

void mirroir(sil::Image &image)
{
    for (int x{0}; x < image.width() / 2; x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float tempg = image.pixel(x, y).g;
            float tempr = image.pixel(x, y).r;
            float tempb = image.pixel(x, y).b;
            image.pixel(x, y).r = image.pixel(image.width() - 1 - x, y).r;
            image.pixel(x, y).g = image.pixel(image.width() - 1 - x, y).g;
            image.pixel(x, y).b = image.pixel(image.width() - 1 - x, y).b;
            image.pixel(image.width() - 1 - x, y).r = tempr;
            image.pixel(image.width() - 1 - x, y).g = tempg;
            image.pixel(image.width() - 1 - x, y).b = tempb;
        }
    }
}

void bruite(sil::Image &image)
{
    for (int y{0}; y < image.height(); y++)
    {
        for (int i = 0; i < 75; i++)
        {
            int aleatoire = random_int(0, 260);
            float aleatoirer = random_float(0, 1);
            float aleatoireg = random_float(0, 1);
            float aleatoireb = random_float(0, 1);
            image.pixel(aleatoire, y).r = aleatoirer;
            image.pixel(aleatoire, y).g = aleatoireg;
            image.pixel(aleatoire, y).b = aleatoireb;
        }
    }
}

sil::Image diagonale(sil::Image &image)
{
    sil::Image new_pouet{image.height(), image.width()};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float tempg = image.pixel(x, y).g;
            float tempr = image.pixel(x, y).r;
            float tempb = image.pixel(x, y).b;
            new_pouet.pixel(y, x).r = tempr;
            new_pouet.pixel(y, x).g = tempg;
            new_pouet.pixel(y, x).b = tempb;
        }
    }
    image = new_pouet;
    return image;
}

void rotation(sil::Image &image)
{
    sil::Image new_pouet=diagonale(image);
    
    mirroir(new_pouet);
    image = new_pouet;
}

void rgb(sil::Image &image)
{
    sil::Image new_pouet{image.width(), image.height()};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (x < image.width() - 15)
            {
                new_pouet.pixel(x, y).r = image.pixel(x + 15, y).r;
            }
            new_pouet.pixel(x, y).g = image.pixel(x, y).g;
            if (x > 15)
            {
                new_pouet.pixel(x, y).b = image.pixel(x - 15, y).b;
            }
        }
    }
    image = new_pouet;
}

void dark(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float gl = std::pow(image.pixel(x, y).g, 10);
            float rl = std::pow(image.pixel(x, y).r, 10);
            float bl = std::pow(image.pixel(x, y).b, 10);
            image.pixel(x, y).r = rl;
            image.pixel(x, y).g = gl;
            image.pixel(x, y).b = bl;
        }
    }
}

void light(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float gl = std::pow(image.pixel(x, y).g, 0.1);
            float rl = std::pow(image.pixel(x, y).r, 0.1);
            float bl = std::pow(image.pixel(x, y).b, 0.1);
            image.pixel(x, y).r = rl;
            image.pixel(x, y).g = gl;
            image.pixel(x, y).b = bl;
        }
    }
}

void disque(sil::Image &image)
{
    sil::Image cadre{500, 500};
    for (int x{0}; x < cadre.width(); x++)
    {
        for (int y{0}; y < cadre.height(); y++)
        {
            if ((x - 250) * (x - 250) + (y - 250) * (y - 250) < std::pow(150, 2))
            {
                cadre.pixel(x, y).r = 0;
                cadre.pixel(x, y).g = 0;
                cadre.pixel(x, y).b = 0;
            }
        }
    }
    for (int i = 120; i < 380; i++)
    {
        for (int j = 110; j < 390; j++)
        {
            cadre.pixel(i, j).r = image.pixel(i - 120, j - 110).r;
            cadre.pixel(i, j).g = image.pixel(i - 120, j - 110).g;
            cadre.pixel(i, j).b = image.pixel(i - 120, j - 110).b;
        }
    }
    for (int x{0}; x < cadre.width(); x++)
    {
        for (int y{0}; y < cadre.height(); y++)
        {
            if ((x - 250) * (x - 250) + (y - 250) * (y - 250) > std::pow(150, 2))
            {
                cadre.pixel(x, y).r = 1;
                cadre.pixel(x, y).g = 0;
                cadre.pixel(x, y).b = 0;
            }
        }
    }
    image = cadre;
}

void cercle(sil::Image &image)
{
    sil::Image cadre{500, 500};
    for (int i = 120; i < 380; i++)
    {
        for (int j = 110; j < 390; j++)
        {
            cadre.pixel(i, j).r = image.pixel(i - 120, j - 110).r;
            cadre.pixel(i, j).g = image.pixel(i - 120, j - 110).g;
            cadre.pixel(i, j).b = image.pixel(i - 120, j - 110).b;
        }
    }
    cadre.pixel(250, 250).r = 1;
    cadre.pixel(250, 250).g = 0;
    cadre.pixel(250, 250).b = 0;
    for (int x{0}; x < cadre.width(); x++)
    {
        for (int y{0}; y < cadre.height(); y++)
        {
            if ((x - 250) * (x - 250) + (y - 250) * (y - 250) < std::pow(150, 2))
            {
                if ((x - 250) * (x - 250) + (y - 250) * (y - 250) > std::pow(130, 2))
                {
                    cadre.pixel(x, y).r = 1;
                    cadre.pixel(x, y).g = 1;
                    cadre.pixel(x, y).b = 1;
                }
            }
        }
    }
    for (int x{0}; x < cadre.width(); x++)
    {
        for (int y{0}; y < cadre.height(); y++)
        {
            if ((x - 250) * (x - 250) + (y - 250) * (y - 250) > std::pow(150, 2))
            {
                cadre.pixel(x, y).r = 0;
                cadre.pixel(x, y).g = 0;
                cadre.pixel(x, y).b = 0;
            }
        }
    }
    image = cadre;
}

void glitch(sil::Image &image)
{
    for (int i = 0; i < 200; i++)
    {
        int x = random_int(0, image.width());
        int y = random_int(0, image.height());
        int lon = random_int(0, 50);
        int lar = random_int(0, 10);
        int newx = random_int(0, image.width());
        int newy = random_int(0, image.height());
        if (newx + lon < image.width())
        {
            if (newy + lar < image.height())
            {
                if (x + lon < image.width())
                {
                    if (y + lar < image.height())
                    {
                        for (int j = 0; j < lon; j++)
                        {
                            for (int k = 0; k < lar; k++)
                            {
                                image.pixel(newx + j, newy + k).r = image.pixel(x + j, y + k).r;
                                image.pixel(newx + j, newy + k).g = image.pixel(x + j, y + k).g;
                                image.pixel(newx + j, newy + k).b = image.pixel(x + j, y + k).b;
                            }
                        }
                    }
                }
            }
        }
    }
}

void mosaique(sil::Image &image)
{
    sil::Image multi{260, 280};
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            multi.pixel(x, y) = image.pixel((x * 15) % image.width(), (y * 15) % image.height());
        }
    }
    image = multi;
}

void mosaiquemirroir(sil::Image &image)
{
    sil::Image newimage{260, 280};
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            if ((x * 15) / image.width() % 2)
            {
                if ((y * 15) / image.height() % 2)
                {
                    newimage.pixel(x, y) = image.pixel((x * 15) % image.width(), (y * 15) % image.height());
                }
                else
                {
                    newimage.pixel(x, y) = image.pixel((x * 15) % image.width(), image.height() - (y * 15) % image.height() - 1);
                }
            }
            else
            {
                if ((y * 15) / image.height() % 2)
                {
                    newimage.pixel(x, y) = image.pixel(image.width() - (x * 15) % image.width() - 1, (y * 15) % image.height());
                }
                else
                {
                    newimage.pixel(x, y) = image.pixel(image.width() - (x * 15) % image.width() - 1, image.height() - (y * 15) % image.height() - 1);
                }
            }
        }
    }
    image = newimage;
}

float brightness(glm::vec3 col)
{
    float grey = (col.g + col.r + col.b) / 3;
    return grey;
}

void tri(sil::Image &image)
{
    sil::Image newimage{260, 280};
    for (int y = 0; y < image.height() - 1; y++)
    {
        std::sort(image.pixels().begin() + 1 * y, image.pixels().begin() + (image.width() - 1) * y + 1, [](glm::vec3 const &color1, glm::vec3 const &color2)
                  { return brightness(color1) < brightness(color2); });
    }
}

void degrade(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        float t = 0.1f;
        for (int y{0}; y < image.height(); y++)
        {
            float gl = std::pow(image.pixel(x, y).g, t);
            float rl = std::pow(image.pixel(x, y).r, t);
            float bl = std::pow(image.pixel(x, y).b, t);
            image.pixel(x, y).r = rl;
            image.pixel(x, y).g = gl;
            image.pixel(x, y).b = bl;
            t = t + 0.1f;
        }
    }
}

glm::vec2 rotated(glm::vec2 point, glm::vec2 center_of_rotation, float angle)
{
    return glm::vec2{glm::rotate(glm::mat3{1.f}, angle) * glm::vec3{point - center_of_rotation, 0.f}} + center_of_rotation;
}

void vortex(sil::Image &image)
{
    sil::Image newimage{260, 280};
    int midx = image.width() / 2;
    int midy = image.height() / 2;
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float angle = (glm::distance(glm::vec2{x, y}, glm::vec2{midx, midy}) * 5) * (3.14 / 180);
            glm::vec2 newpose = rotated(glm::vec2{x, y}, glm::vec2{midx, midy}, angle);
            if (0 < newpose.x && newpose.x < image.width())
            {
                if (0 < newpose.y && newpose.y < image.height())
                {
                    newimage.pixel(newpose.x, newpose.y) = image.pixel(x, y);
                }
            }
        }
    }
    image = newimage;
}

sil::Image reduction(int red, sil::Image &image)
{
    sil::Image multi{image.width() / red, image.height() / red};
    for (int x = 0; x < multi.width(); x++)
    {
        for (int y = 0; y < multi.height(); y++)
        {
            multi.pixel(x, y) = image.pixel((x * red), (y * red));
        }
    }
    return multi;
}

void multiclone(sil::Image &image)
{
    for (int i = 0; i < 30; i++)
    {
        int x = random_int(0, image.width());
        int y = random_int(0, image.height());
        int reduc = random_int(2, 7);
        sil::Image clone = reduction(reduc, image);
        if (x + clone.width() < image.width())
        {
            if (y + clone.height() < image.height())
            {
                for (int j = 0; j < clone.width(); j++)
                {
                    for (int k = 0; k < clone.height(); k++)
                    {
                        if (brightness(clone.pixel(j, k)) > 0.01)
                        {
                            image.pixel(x + j, y + k) = clone.pixel(j, k);
                        }
                    }
                }
            }
        }
    }
}

void histogramme(sil::Image &image)
{
    int xsombre = 0;
    int ysombre = 0;
    int xclaire = 0;
    int yclaire = 0;
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            if (brightness(image.pixel(x, y)) < brightness(image.pixel(xsombre, ysombre)))
            {
                xsombre = x;
                ysombre = y;
            }
            if (brightness(image.pixel(x, y)) > brightness(image.pixel(xclaire, yclaire)))
            {
                xclaire = x;
                yclaire = y;
            }
        }
    }
    float ecart = glm::distance(brightness(image.pixel(xclaire, yclaire)), brightness(image.pixel(xsombre, ysombre)));
    float temp = (brightness(image.pixel(xclaire, yclaire)) / ecart) - 1;
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            image.pixel(x, y) = (image.pixel(x, y)) / ecart - temp;
        }
    }
}

glm::vec3 flou(sil::Image &image, int x, int y, int t)
{
    int mid = t / 2;
    int nbpix = 1;
    glm::vec3 temp = image.pixel(x, y);
    for (int i = 0; i <= mid; i++)
    {
        for (int j = 0; j <= mid; j++)
        {
            if (x - i > 0)
            {
                if (y - j > 0)
                {
                    nbpix += 1;
                    temp = temp + image.pixel(x - i, y - j);
                }
                if (y + j < image.height())
                {
                    nbpix += 1;
                    temp = temp + image.pixel(x - i, y + j);
                }
                nbpix += 1;
                temp = temp + image.pixel(x - i, y);
            }
            if (x + i < image.width())
            {
                if (y - j > 0)
                {
                    nbpix += 1;
                    temp = temp + image.pixel(x + i, y - j);
                }
                if (y + j < image.height())
                {
                    nbpix += 1;
                    temp = temp + image.pixel(x + i, y + j);
                }
                nbpix += 1;
                temp = temp + image.pixel(x + i, y);
            }
            if (y - j > 0)
            {
                nbpix += 1;
                temp = temp + image.pixel(x, y - j);
            }
            if (y + j < image.height())
            {
                nbpix += 1;
                temp = temp + image.pixel(x, y + j);
            }
        }
    }
    glm::vec3 result = glm::vec3{temp.r / nbpix, temp.g / nbpix, temp.b / nbpix};
    return result;
}

void convolution(sil::Image &image)
{
    sil::Image newimage{image.width(), image.height()};
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            glm::vec3 val = flou(image, x, y, 25);
            newimage.pixel(x, y) = val;
        }
    }
    image = newimage;
}

int main()
{
    {
        sil::Image image{"images/moymoy cat.jpg"};
        keep_green_only(image);
        image.save("output/pouetvert.png");
    }
    {
        sil::Image image{"images/moymoy cat.jpg"};
        swap(image);
        image.save("output/pouetswap.png");
    }
    {
        sil::Image image{"images/moymoy cat.jpg"};
        black_and_white(image);
        image.save("output/pouet1967.png");
    }
    {
        sil::Image image{"images/moymoy cat.jpg"};
        negatif(image);
        image.save("output/deprepouet.png");
    }
    {
        sil::Image image{"images/moymoy cat.jpg"};
        mirroir(image);
        image.save("output/teuop.png");
    }
    {
        sil::Image image{"images/moymoy cat.jpg"};
        diagonale(image);
        image.save("output/diagopouet.png");
    }
    {
        sil::Image image{"images/moymoy cat.jpg"};
        bruite(image);
        image.save("output/pouetneige.png");
    }
    {
        sil::Image image{"images/moymoy cat.jpg"};
        rotation(image);
        image.save("output/cotepouet.png");
    }
    {
        sil::Image image{"images/moymoy cat.jpg"};
        rgb(image);
        image.save("output/tripouet.png");
    }
    {
        sil::Image image{"images/moymoy cat.jpg"};
        dark(image);
        image.save("output/darkpouet.png");
    }
    {
        sil::Image image{"images/moymoy cat.jpg"};
        light(image);
        image.save("output/flashpouet.png");
    }
    {
        sil::Image image{"images/moymoy cat.jpg"};
        disque(image);
        image.save("output/thatsallpouet.png");
    }
    {
        sil::Image image{"images/moymoy cat.jpg"};
        cercle(image);
        image.save("output/snipepouet.png");
    }
    {
        sil::Image image{"images/moymoy cat.jpg"};
        glitch(image);
        image.save("output/pôuét.png");
    }
    {
        sil::Image image{"images/moymoy cat.jpg"};
        mosaique(image);
        image.save("output/pouetpouetarmy.png");
    }
    {
        sil::Image image{"images/moymoy cat.jpg"};
        mosaiquemirroir(image);
        image.save("output/pouetteuoparmy.png");
    }
    {
        sil::Image image{"images/moymoy cat.jpg"};
        tri(image);
        image.save("output/pouetpuree.png");
    }
    {
        sil::Image image{"images/moymoy cat.jpg"};
        degrade(image);
        image.save("output/thechoosenpouet.png");
    }
    {
        sil::Image image{"images/moymoy cat.jpg"};
        vortex(image);
        image.save("output/pouetail.png");
    }
    {
        sil::Image image{"images/moymoy cat.jpg"};
        reduction(5, image);
        image.save("output/redupouet.png");
    }
    {
        sil::Image image{"images/moymoy cat.jpg"};
        multiclone(image);
        image.save("output/anarpouet.png");
    }
    {
        sil::Image image{"images/moymoy cat.jpg"};
        histogramme(image);
        image.save("output/histopouet.png");
    }
    {
        sil::Image image{"images/moymoy cat.jpg"};
        convolution(image);
        image.save("output/pouetpasnet.png");
    }
}
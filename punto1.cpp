#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat img1 = imread("../Data/1.png");
    Mat img2 = imread("../Data/2.png");
    Mat img3 = imread("../Data/3.png");

    if(img1.empty() || img2.empty() || img3.empty())
    {
        cout << "Error cargando imagenes" << endl;
        return -1;
    }

    // Imagen 4 - gris
    Mat img4;
    cvtColor(img1, img4, COLOR_BGR2GRAY);
    cvtColor(img4, img4, COLOR_GRAY2BGR);

    // Imagen 5 - brillo
    Mat img5;
    img2.convertTo(img5, -1, 1.5, 100);

    // Imagen 6 - gradiente morfologico
    Mat img3_gray;
    cvtColor(img3, img3_gray, COLOR_BGR2GRAY);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3,3));
    Mat img6;

    morphologyEx(img3_gray, img6, MORPH_GRADIENT, kernel);
    cvtColor(img6, img6, COLOR_GRAY2BGR);

    // Redimensionar
    Size tamano(250,250);

    resize(img1,img1,tamano);
    resize(img2,img2,tamano);
    resize(img3,img3,tamano);
    resize(img4,img4,tamano);
    resize(img5,img5,tamano);
    resize(img6,img6,tamano);

    // Unir
    Mat fila1, fila2, resultado;

    hconcat(vector<Mat>{img1,img2,img3}, fila1);
    hconcat(vector<Mat>{img4,img5,img6}, fila2);
    vconcat(fila1, fila2, resultado);

    imshow("Punto 1", resultado);
    waitKey(0);

    return 0;
}

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat imagenB = imread("../Data/imagenB.png");

    if(imagenB.empty())
    {
        cout << "Error cargando imagen B" << endl;
        return -1;
    }

    // Región centrada 300x300
    int ancho = 300;
    int alto = 300;

    int x = (imagenB.cols - ancho) / 2;
    int y = (imagenB.rows - alto) / 2;

    Rect region(x, y, ancho, alto);

    Mat roi = imagenB(region);

    Mat gray;
    cvtColor(roi, gray, COLOR_BGR2GRAY);

    threshold(gray, gray, 127, 255, THRESH_BINARY);

    cvtColor(gray, gray, COLOR_GRAY2BGR);

    gray.copyTo(imagenB(region));

    cout << "Region binarizada con umbral 127 correctamente" << endl;

    imshow("Imagen B Binarizada", imagenB);
    waitKey(0);

    destroyAllWindows();
    return 0;
}

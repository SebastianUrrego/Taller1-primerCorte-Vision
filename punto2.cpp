#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat original = imread("../Data/1.png");

    if(original.empty())
    {
        cout << "Error cargando imagen original" << endl;
        return -1;
    }

    // Región centrada 300x300
    int ancho = 300;
    int alto = 300;

    int x = (original.cols - ancho) / 2;
    int y = (original.rows - alto) / 2;

    Rect region(x, y, ancho, alto);

    Mat imagenB = original.clone();

    Mat roi = imagenB(region);

    Mat gris;
    cvtColor(roi, gris, COLOR_BGR2GRAY);
    cvtColor(gris, gris, COLOR_GRAY2BGR);

    gris.copyTo(imagenB(region));

    // Guardar imagen B
    if(imwrite("../Data/imagenB.png", imagenB))
        cout << "Imagen B guardada correctamente" << endl;
    else
        cout << "Error guardando imagen B" << endl;

    imshow("Imagen B - Region Gris", imagenB);
    waitKey(0);

    destroyAllWindows();
    return 0;
}

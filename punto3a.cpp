#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat imgA = imread("../Data/imA.png");
    Mat imgB = imread("../Data/imB.png");

    if(imgA.empty() || imgB.empty())
    {
        cout << "Error cargando imagenes" << endl;
        return -1;
    }

    // Convertir a escala de grises
    Mat grayA, grayB;
    cvtColor(imgA, grayA, COLOR_BGR2GRAY);
    cvtColor(imgB, grayB, COLOR_BGR2GRAY);

    // Diferencia absoluta
    Mat diferencia;
    absdiff(grayA, grayB, diferencia);

    // Umbralizar para obtener máscara
    Mat imC;
    threshold(diferencia, imC, 40, 255, THRESH_BINARY);

    // Guardar imagen C
    if(imwrite("../Data/imC.png", imC))
        cout << "Imagen C guardada correctamente como imC.png" << endl;
    else
        cout << "Error guardando imagen C" << endl;

    imshow("Imagen A", imgA);
    imshow("Imagen B", imgB);
    imshow("Imagen C - Triceratops Detectado", imC);

    waitKey(0);
    destroyAllWindows();

    return 0;
}

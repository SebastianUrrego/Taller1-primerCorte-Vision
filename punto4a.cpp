#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    // Cargar imagen A y B
    Mat imgA = imread("../Data/imA.png");
    Mat imgB = imread("../Data/imB.png");

    if(imgA.empty() || imgB.empty())
    {
        cout << "Error cargando imagenes" << endl;
        return -1;
    }

    // Convertir a gris
    Mat grayA, grayB;
    cvtColor(imgA, grayA, COLOR_BGR2GRAY);
    cvtColor(imgB, grayB, COLOR_BGR2GRAY);

    // Diferencia absoluta
    Mat diferencia;
    absdiff(grayA, grayB, diferencia);

    // Crear máscara binaria
    Mat mascara;
    threshold(diferencia, mascara, 40, 255, THRESH_BINARY);

    // Crear imagen resultado con fondo negro
    Mat resultado(grayA.size(), CV_8UC1, Scalar(255));

    // Copiar solo el triceratops en gris
    grayA.copyTo(resultado, mascara);

    // Guardar imagen C
    bool guardado = imwrite("../Data/imagenC_gris.png", resultado);

    if(guardado)
        cout << "Imagen C guardada correctamente." << endl;
    else
        cout << "Error al guardar imagen C." << endl;

    // Mostrar solo la imagen final
    imshow("Imagen C - Triceratops en Gris", resultado);
    waitKey(0);
    destroyAllWindows();

    return 0;
}

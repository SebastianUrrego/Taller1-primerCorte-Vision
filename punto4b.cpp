#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat img = imread("../Data/imagenC_gris.png", IMREAD_GRAYSCALE);

    if(img.empty())
    {
        cout << "Error cargando imagen C" << endl;
        return -1;
    }

    // ======== UMBRAL AUTOMATICO (OTSU) ========
    Mat binaria;
    threshold(img, binaria, 0, 255, THRESH_BINARY_INV + THRESH_OTSU);

    vector<vector<Point>> contornos;
    findContours(binaria, contornos, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    if(contornos.empty())
    {
        cout << "No se detecto el objeto" << endl;
        return -1;
    }

    // Buscar contorno más grande
    int indiceMayor = 0;
    double areaMayor = 0;

    for(int i = 0; i < contornos.size(); i++)
    {
        double area = contourArea(contornos[i]);
        if(area > areaMayor)
        {
            areaMayor = area;
            indiceMayor = i;
        }
    }

    Rect caja = boundingRect(contornos[indiceMayor]);

    int centroX = caja.x + caja.width / 2;
    int centroY = caja.y + caja.height / 2;

    Mat imgColor;
    cvtColor(img, imgColor, COLOR_GRAY2BGR);

    rectangle(imgColor, caja, Scalar(0,255,0), 2);
    circle(imgColor, Point(centroX, centroY), 6, Scalar(0,0,255), -1);

    cout << "Centro de masa (Bounding Box): ("
         << centroX << ", " << centroY << ")" << endl;

    imshow("Binaria", binaria);
    imshow("4B - Centro Triceratops", imgColor);
    waitKey(0);
    destroyAllWindows();

    return 0;
}

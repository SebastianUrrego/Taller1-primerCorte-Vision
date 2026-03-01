#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat img = imread("../Data/imC.png", IMREAD_GRAYSCALE);

    if(img.empty())
    {
        cout << "Error cargando imagen C" << endl;
        return -1;
    }

    vector<vector<Point>> contornos;
    findContours(img, contornos, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    if(contornos.empty())
    {
        cout << "No se detecto objeto" << endl;
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

    Mat color;
    cvtColor(img, color, COLOR_GRAY2BGR);

    rectangle(color, caja, Scalar(0,255,0), 2);
    circle(color, Point(centroX, centroY), 5, Scalar(0,0,255), -1);

    cout << "Centro de masa (Bounding Box): (" 
         << centroX << ", " << centroY << ")" << endl;

    imshow("Centro Detectado", color);
    waitKey(0);
    destroyAllWindows();

    return 0;
}

#include <iostream>
#include <math.h>

int main()
{
    float m1, c1, m2, c2;
    float x1, y1, x2, y2;
    float dx, dy;
    float intersection_X, intersection_Y;

 

    std::cout << " Encontrar interseccion entre dos lineas:\n";
    
    std::cout << "Insertar la cordenada x del primer punto de la recta: ";
    std::cin >> x1;
    
    std::cout << "Insertar la cordenada y del primer punto de la recta: ";
    std::cin >> y1;

    std::cout << "Insertar la cordenada x2 del primer punto de la recta: ";
    std::cin >> x2;

    std::cout << "Insertar la cordenada y2 del primer punto de la recta: ";
    std::cin >> y2;


    dx = x2 - x1;
    dy = y2 - y1;

    m1 = dy / dx;
    // y = mx + c
    c1 = y1 - m1 * x1; 

    std::cout << "Insertar la cordenada x del primer punto de la recta2:";
    std::cin >> x1;

    std::cout << "Insertar la cordenada y del primer punto de la recta2:";
    std::cin >> y1;

    std::cout << "Insertar la cordenada x2 del primer punto de la recta2:";
    std::cin >> x2;

    std::cout << "Insertar la cordenada y2 del primer punto de la recta2:";
    std::cin >> y2;

    dx = x2 - x1;
    dy = y2 - y1;

    m2 = dy / dx;
    c2 = y2 - m2 * x2;
 
    std::cout << "Ecuacion 1: ";
    std::cout << m1 << "X " << ((c1 < 0) ? ' ' : '+') << c1 << "\n";

    std::cout << "Ecuacion 2: ";
    std::cout << m2 << "X " << ((c2 < 0) ? ' ' : '+') << c2 << "\n";

    if( (m1 - m2) == 0)
        std::cout << "No hay interseccion\n";
    else
    {
        intersection_X = (c2 - c1) / (m1 - m2);
        intersection_Y = m1 * intersection_X + c1;
        std::cout << "Intersecta en el punto: = ";
        std::cout << intersection_X;
        std::cout << ",";
        std::cout << intersection_Y;
        std::cout << "\n";
    }
}


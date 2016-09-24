#include <iostream>
#include <string>
using namespace std;

struct PUNTO {
    float x;
    float y;
};

void lado(PUNTO p, PUNTO q, PUNTO r);

int main()
{
    PUNTO p;
    PUNTO q;
    PUNTO r;
  
    cout << "Insertar la cordenada x del primer punto de la recta: ";
    cin >> p.x;
    cout << "Insertar la cordenada  y del primer punto de la recta: ";
    cin >> p.y;
    cout << "Insertar la cordenada x del segundo punto de la recta: ";
    cin >> q.x;
    cout << "Insertar la cordenada y del segundo punto de la recta: ";
    cin >> q.y;
    cout << "Insertar la cordenada  x del punto a verificar: ";
    cin >> r.x;
    cout << "Insertar la cordenada y del punto a verificar: ";
    cin >> r.y;
    
    lado(p,q,r);
 
  
}

void lado(PUNTO p, PUNTO q, PUNTO r){
    float res = (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);
    if(res < 0){
        cout << "El punto esta a la derecha.\n";  
    }
    else if(res > 0){
        cout << "El punto esta a la izquierda.\n";
    }
}


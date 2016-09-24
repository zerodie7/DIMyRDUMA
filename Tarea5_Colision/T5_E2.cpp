#include <iostream>
#include <string>
using namespace std;

struct PUNTO {
    float x;
    float y;
};

bool interseccion(PUNTO p1, PUNTO p2, PUNTO q1, PUNTO q2);

int main()
{
    PUNTO p1, PUNTO p2, PUNTO q1, PUNTO q2;
    
    cout << "Prueba de interseccion entre dos rectas.";
    cout << "\nInserte para cada recta dos puntos que pertenezcan a ella. \n\n";
    
    cout << "Insertar la cordenada x del primer punto de la primera recta: ";
    cin >> p1.x;
    cout << "Insertar la cordenada y del primer punto de la primera recta: ";
    cin >> p1.y;
    cout << "Insertar la cordenada x del segundo punto de la primera recta: ";
    cin >> p2.x;
    cout << "Insertar la cordenada y del segundo punto de la primera recta: ";
    cin >> p2.y;
    
    cout << "Insertar la cordenada x del primer punto de la segunda recta: ";
    cin >> q1.x;
    cout << "Insertar la cordenada y del primer punto de la segunda recta: ";
    cin >> q1.y;
    cout << "Insertar la cordenada x del segundo punto de la segunda recta: ";
    cin >> q2.x;
    cout << "Insertar la cordenada y del segundo punto de la segunda recta: ";
    cin >> q2.y;
    
    interseccion(p1,p2,q1,q2);
  
}

bool interseccion(PUNTO p1, PUNTO p2, PUNTO q1, PUNTO q2){
    float res, m1, m2;
    
    if( (p1.x == p2.x) && (q1.x == q2.x) ){
         cout << " Son dos rectas verticales y paralelas \n";
         return false;
    }     
//recta 1 
    else if( (p1.x == q2.x) ){ 
        m2 = (q2.y - q1.y) / (q2.x - q1.x);
        res = m2 * p1.x - m2 * q1.x + q1.y;
        cout << " La primera recta es vertical. \n";
        cout << " Punto de interseccion de las rectas en x: " << p1.x << "\n";
        cout << " Punto de interseccion de las rectas en y: " << res << "\n";
        return true;
    }     
//recta 2
    else if( (q1.x == q2.x) ){ 
        m1 = (p2.y - p1.y) / (p2.x - p1.x);
        res = m1 * q1.x - m1 * p1.x + p1.y;
        cout << " La segunda recta es vertical. \n";
        cout << " Punto de interseccion de las rectas en x: " << q1.x << "\n";
        cout << " Punto de interseccion de las rectas en y: " << res << "\n";
        return true;
    } 
//paralelas
    else if ( ( (p2.y - p1.y) / (p2.x - p1.x) ) == ( (q2.y - q1.y) / (q2.x - q1.x) ) ) { //rectas paralelas
        cout << " Son dos rectas paralelas. \n";
        return false;
    }
     else {
        m1 = (p2.y - p1.y) / (p2.x - p1.x);
        m2 = (q2.y - q1.y) / (q2.x - q1.x);
        float aux = ( - q1.x * m2 + q1.y + p1.x * m1 - p1.y ) / ( m1 - m2 );
        res = m1 * aux - m1 * p1.x + p1.y;
        cout << " Punto de interseccion de las rectas en x: " << aux << "\n";
        cout << " Punto de interseccion de las rectas en y: " << res << "\n";
        return true;
    }    
}

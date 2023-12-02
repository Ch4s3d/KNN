#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Punto {
public:
    double x, y;
    int etiqueta;

    Punto(double x, double y, int etiqueta) : x(x), y(y), etiqueta(etiqueta) {}
    
    double calcularDistancia(const Punto& otroPunto) const {
        return sqrt(pow(x - otroPunto.x, 2) + pow(y - otroPunto.y, 2));
    }
};

class KNN {
private:
    vector<Punto> puntos;

public:
    void agregarPunto(double x, double y, int etiqueta) {
        puntos.emplace_back(x, y, etiqueta);
    }

    int predecirEtiqueta(double x, double y, int k) {
        vector<pair<double, int>> distanciasEtiquetas;
        for (const auto& punto : puntos) {
            double distancia = punto.calcularDistancia({x, y, 0});
            distanciasEtiquetas.emplace_back(distancia, punto.etiqueta);
        }

        sort(distanciasEtiquetas.begin(), distanciasEtiquetas.end());

        vector<int> conteoEtiquetas(2, 0);
        for (int i = 0; i < k; ++i) {
            conteoEtiquetas[distanciasEtiquetas[i].second]++;
        }

        return distance(conteoEtiquetas.begin(), max_element(conteoEtiquetas.begin(), conteoEtiquetas.end()));
    }
};

int main() {
    KNN clasificador;

    clasificador.agregarPunto(1.0, 2.0, 0);
    clasificador.agregarPunto(2.0, 3.0, 0);
    clasificador.agregarPunto(3.0, 4.0, 1);
    clasificador.agregarPunto(4.0, 5.0, 1);

    double nuevoX = 3.5;
    double nuevoY = 3.5;
    int k = 3;
    int etiquetaPredicha = clasificador.predecirEtiqueta(nuevoX, nuevoY, k);

    cout << "La etiqueta predicha para el punto (" << nuevoX << ", " << nuevoY << ") es: " << etiquetaPredicha << endl;

    return 0;
}
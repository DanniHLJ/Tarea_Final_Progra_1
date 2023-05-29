#include <iostream>
#include <queue>
#include <stack>
#include <chrono>
#include <thread>
#include <random>

// Generador de números aleatorios
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dist(1, 90);

// Variables para las colas y la pila
std::queue<int> cola1;
std::queue<int> cola2;
std::stack<int> pila;

// Función para generar números aleatorios y agregarlos a las colas
void generarNumeros() {
    for (int i = 0; i < 200; ++i) {
        int numero = dist(gen);
        if (i % 2 == 0) {
            cola1.push(numero);
            std::cout << "Número " << numero << " ingresado a la cola 1." << std::endl;
        }
        else {
            cola2.push(numero);
            std::cout << "Número " << numero << " ingresado a la cola 2." << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// Función para atender los números de las colas
void atenderNumeros() {
    for (int i = 0; i < 100; ++i) {
        if (!cola1.empty()) {
            int numero = cola1.front();
            cola1.pop();
            pila.push(numero);
            std::cout << "Cajero 1 atendió el número " << numero << "." << std::endl;
        }
        if (!cola2.empty()) {
            int numero = cola2.front();
            cola2.pop();
            pila.push(numero);
            std::cout << "Cajero 2 atendió el número " << numero << "." << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

// Función para mostrar la suma de los números atendidos
void mostrarSuma() {
    int suma = 0;
    while (!pila.empty()) {
        suma += pila.top();
        pila.pop();
    }
    std::cout << "La suma de los números atendidos es: " << suma << std::endl;
}

int main() {
    // Hilos para generar números y atenderlos
    std::thread generador(generarNumeros);
    std::thread atendedor(atenderNumeros);

    // Esperar a que los hilos terminen
    generador.join();
    atendedor.join();

    // Mostrar la suma de los números atendidos
    mostrarSuma();

    return 0;
}
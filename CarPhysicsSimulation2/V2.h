#pragma once

#define PI 3.14159265358979323846
#include <iostream>
#include <cmath>

class V2
{
public:
    V2() : x(0.0), y(0.0) {}

    V2(double x, double y);

    double x;
    double y;

    static const V2 ZeroVector;

    double size() const;
    double sizeSquared() const;
    V2 safeNormal() const;
    V2 rotateVector(double angleDeg) const;
    double dot(const V2& other) const;
    double cross(const V2& other) const;  // Producto cruzado
    V2 projectOnto(const V2& other) const;  // Proyección
    double distanceTo(const V2& other) const;  // Distancia entre dos vectores
    V2 reflect(const V2& normal) const;  // Reflejo del vector
    V2 lerp(const V2& other, double alpha) const;  // Interpolación lineal de vectores
    V2 perpendicular() const;
    double radAngle() const;
    double degAngle() const;

    // Overload de operadores
    V2 operator+(const V2& other) const;
    V2& operator+=(const V2& other);
    V2 operator-(const V2& other) const;
    V2 operator-() const;
    V2& operator-=(const V2& other);
    V2 operator*(const double other) const;
    V2 operator/(const double scalar) const;
    bool operator==(const V2& other) const;
    bool operator!=(const V2& other) const;

    // Depuración
    friend std::ostream& operator<<(std::ostream& os, const V2& vec);

private:
    static constexpr double pi = 3.14159265358979323846; // Definición de PI
    static constexpr double PI_OVER_180 = pi / 180.0; // PI dividido por 180
    static constexpr double OVER_180_PI = 180.0 / pi;
};

// Función global lerp para doubles
inline double lerp(double a, double b, double alpha)
{
    return a + (b - a) * alpha;
}

void print(std::string message);

template <typename T>
T clamp(T value, T minVal, T maxVal) {
    if (value < minVal) return minVal;
    if (value > maxVal) return maxVal;
    return value;
}

V2 operator*(double scalar, const V2& vec);

double NormalizeAngle(double angle);
double ShortestAngleDifference(double angle1, double angle2);
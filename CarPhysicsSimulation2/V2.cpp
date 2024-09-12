#include "V2.h"
#include <cmath>

V2::V2(const double x, const double y) : x(x), y(y) {}

const V2 V2::ZeroVector(0.0, 0.0);

double V2::size() const
{
    return std::sqrt((x * x) + (y * y));
}

double V2::sizeSquared() const
{
    return (x * x) + (y * y);
}

V2 V2::safeNormal() const
{
    double magnitude = size();
    if (magnitude > 0.0001)
    {
        return V2(x / magnitude, y / magnitude);
    }
    else
    {
        return V2::ZeroVector;
    }
}

V2 V2::rotateVector(double angleDeg) const
{
    double rad = angleDeg * PI_OVER_180;
    double cosAngle = cos(rad);
    double sinAngle = sin(rad);
    return V2(x * cosAngle - y * sinAngle, x * sinAngle + y * cosAngle);
}

double V2::dot(const V2& other) const {
    return x * other.x + y * other.y;
}

// Nuevo: Producto cruzado
double V2::cross(const V2& other) const {
    return x * other.y - y * other.x;
}

// Nuevo: Proyección
V2 V2::projectOnto(const V2& other) const {
    double dotProduct = dot(other);
    double otherSizeSquared = other.sizeSquared();
    return other * (dotProduct / otherSizeSquared);
}

// Nuevo: Distancia entre vectores
double V2::distanceTo(const V2& other) const {
    return (*this - other).size();
}

// Nuevo: Reflejo
V2 V2::reflect(const V2& normal) const {
    return *this - normal * (2 * dot(normal));
}

// Nuevo: Interpolación lineal de vectores
V2 V2::lerp(const V2& other, double alpha) const {
    return V2(::lerp(x, other.x, alpha), ::lerp(y, other.y, alpha));
}

V2 V2::perpendicular() const
{
    return V2(-y, x);
}

double V2::radAngle() const
{
    return std::atan2(y, x);
}

double V2::degAngle() const
{
    return radAngle() * OVER_180_PI;
}

// Operadores
V2 V2::operator+(const V2& other) const
{
    return V2(x + other.x, y + other.y);
}

V2& V2::operator+=(const V2& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

V2 V2::operator-(const V2& other) const
{
    return V2(x - other.x, y - other.y);
}

V2 V2::operator-() const
{
    return V2(-x, -y);
}

V2& V2::operator-=(const V2& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

V2 V2::operator*(const double other) const
{
    return V2(x * other, y * other);
}

V2 V2::operator/(const double scalar) const
{
    return V2(x / scalar, y / scalar);
}

bool V2::operator==(const V2& other) const
{
    return x == other.x && y == other.y;
}

bool V2::operator!=(const V2& other) const
{
    return !(*this == other);
}

// Sobrecarga del operador << para depuración
std::ostream& operator<<(std::ostream& os, const V2& vec)
{
    os << "V2(" << vec.x << ", " << vec.y << ")";
    return os;
}

void print(std::string message)
{
    std::cout << message << std::endl;
}

double NormalizeAngle(double angle) {
    while (angle > 180.0) angle -= 360.0;
    while (angle < -180.0) angle += 360.0;
    return angle;
}

double ShortestAngleDifference(double angle1, double angle2) {
    double difference = angle1 - angle2;
    return NormalizeAngle(difference);
}

// Sobrecarga para double * V2
V2 operator*(double scalar, const V2& vec)
{
    return V2(vec.x * scalar, vec.y * scalar);
}
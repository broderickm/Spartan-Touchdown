/**
 * @file Vector.h
 * @author Annika Valaboju
 *
 *
 */

#ifndef PROJECT1_VECTOR_H
#define PROJECT1_VECTOR_H

/**
 * Simple vector class to represent 2D coordinates or velocity.
 */
class Vector
{
private:
    double mX;
    double mY;

public:
    /// Default constructor
    Vector() : mX(0), mY(0) {}

    /// Constructor with x and y values
    Vector(double x, double y) : mX(x), mY(y) {}

    /// Getters
    double X() const { return mX; }
    double Y() const { return mY; }

    /// Setters
    void SetX(double x) { mX = x; }
    void SetY(double y) { mY = y; }

    /// Add two vectors
    Vector operator+(const Vector& other) const
    {
        return Vector(mX + other.mX, mY + other.mY);
    }

    /// Subtract two vectors
    Vector operator-(const Vector& other) const
    {
        return Vector(mX - other.mX, mY - other.mY);
    }

    /// Multiply vector by scalar
    Vector operator*(double scalar) const
    {
        return Vector(mX * scalar, mY * scalar);
    }
};

#endif //PROJECT1_VECTOR_H
/**
 * @file Vector.h
 * @author Annika Valaboju
 *
 *
 */

#ifndef PROJECT1_VECTOR_H
#define PROJECT1_VECTOR_H

/**
 * Represents a 2D mathematical vector with X and Y components.
 * Provides basic arithmetic operations such as addition, subtraction,
 * and scalar multiplication.
 */
class Vector
{
private:
    /// X component of the vector
    double mX;

    /// Y component of the vector
    double mY;

public:
    /**
     * Default constructor.
     * Initializes the vector to (0, 0).
     */
    Vector() : mX(0), mY(0) {}

    /**
     * Construct a vector with given coordinates.
     * @param x The initial X component.
     * @param y The initial Y component.
     */
    Vector(double x, double y) : mX(x), mY(y) {}

    /**
     * Get the X coordinate.
     * @return The X component
     */
    double X() const { return mX; }

    /**
     * Get the Y coordinate.
     * @return The Y component
     */
    double Y() const { return mY; }

    /**
     * Set the X coordinate.
     * @param x The new X value
     */
    void SetX(double x) { mX = x; }

    /**
     * Set the Y coordinate.
     * @param y The new Y value
     */
    void SetY(double y) { mY = y; }

    /**
     * Add another vector to this vector.
     * @param other The vector to add.
     * @return A new vector representing the sum.
     */
    Vector operator+(const Vector& other) const
    {
        return Vector(mX + other.mX, mY + other.mY);
    }

    /**
     * Subtract another vector.
     * @param other The vector to subtract
     * @return Resulting vector from subtraction
     */
    Vector operator-(const Vector& other) const
    {
        return Vector(mX - other.mX, mY - other.mY);
    }

    /**
     * Multiply the vector by a scalar.
     * @param scalar The scalar multiplier
     * @return The scaled vector
     */
    Vector operator*(double scalar) const
    {
        return Vector(mX * scalar, mY * scalar);
    }
};

#endif //PROJECT1_VECTOR_H
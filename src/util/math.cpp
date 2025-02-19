#include "math.h"

bool nearlyEqual(float a, float b, float epsilon) {
    // Handle NaN cases
    if (std::isnan(a) || std::isnan(b)) {
        return false; // If either is NaN, they are not nearly equal
    }

    // Handle exact equality first
    if (a == b) {
        return true; // Handles infinities and identical values
    }

    // Calculate absolute values and difference
    float absA = std::fabs(a);
    float absB = std::fabs(b);
    float diff = std::fabs(a - b);

    // Handle cases where a or b is zero, or both are very small
    if (absA < epsilon && absB < epsilon) {
        // Both numbers are very close to zero
        return diff < epsilon; // Use absolute difference
    }

    // Use a relative error for general cases
    float minAbsSum = absA + absB;
    if (minAbsSum == 0.0f) {
        return diff < epsilon; // Handle the case where both are zero
    }

    return diff / minAbsSum < epsilon;
}

// Logarithm of any base
template<typename T>
T logBase(T x, T base) {
    return log(x) / log(base);
}

// Hyperbolic functions
template<typename T>
T csch(T x) {
    return 1.0 / sinh(x);
}

template<typename T>
T coth(T x) {
    return cosh(x) / sinh(x);
}

template<typename T>
T sech(T x) {
    return 1.0 / cosh(x);
}

// Inverse trigonometric functions
template<typename T>
T arcsin(T x) {
    return asin(x);
}

template<typename T>
T arccos(T x) {
    return acos(x);
}

template<typename T>
T arctan(T x) {
    return atan(x);
}

// Quadratic Bézier curve
template<typename T>
std::vector<T> bezierQuadratic(T t, const std::vector<T>& P0, const std::vector<T>& P1, const std::vector<T>& P2) {
    if (P0.size() != 2 || P1.size() != 2 || P2.size() != 2) {
        throw std::invalid_argument("Control points must be 2D vectors.");
    }

    T x = pow(1 - t, 2) * P0[0] + 2 * (1 - t) * t * P1[0] + pow(t, 2) * P2[0];
    T y = pow(1 - t, 2) * P0[1] + 2 * (1 - t) * t * P1[1] + pow(t, 2) * P2[1];
    return {x, y};
}

// Function to calculate secant
template<typename T>
T sec(T x) {
    return 1.0 / cos(x);
}

// Function to calculate cosecant
template<typename T>
T csc(T x) {
    return 1.0 / sin(x);
}

// Function to calculate cotangent
template<typename T>
T cot(T x) {
    return cos(x) / sin(x);
}

// Function to calculate inverse hyperbolic sine
template<typename T>
T arcsinh(T x) {
    return log(x + sqrt(x * x + 1));
}

// Function to calculate inverse hyperbolic cosine
template<typename T>
T arccosh(T x) {
    if (x < 1) {
        throw std::invalid_argument("arccosh is defined for x >= 1");
    }
    return log(x + sqrt(x * x - 1));
}

// Function to calculate inverse hyperbolic tangent
template<typename T>
T arctanh(T x) {
    if (x <= -1 || x >= 1) {
        throw std::invalid_argument("arctanh is defined for -1 < x < 1");
    }
    return 0.5 * log((1 + x) / (1 - x));
}

float clamp(float value, float min, float max) {
    return std::min(std::max(value, min), max);
}

float lerpF(float a, float b, float f) {
    return a + f * (b - a);
}
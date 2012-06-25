#ifndef WZY_UTILITIES_QUATERNION_FUNCTIONS_MATH_HPP
#define WZY_UTILITIES_QUATERNION_FUNCTIONS_MATH_HPP


namespace wzy {

template <class T>
const Quaternion<T> conjugate(const Quaternion<T>& quat)
{ return Quaternion<T>(quat.w(), -quat.x(), -quat.y(), -quat.z()); }

template <class T>
void identity(Quaternion<T>& quat) {
    quat.setW(1.0);
    quat.setX(0.0);
    quat.setY(0.0);
    quat.setZ(0.0);
}

template <class T>
void inverse(Quaternion<T>& quat) {
    float norm = quat.w() * quat.w() + quat.x() * quat.x() + quat.y() * quat.y() + quat.z() * quat.z();
    float invNorm = 1.0 / norm;
    quat.setW(quat.w() * invNorm);
    quat.setX(-quat.x() * invNorm);
    quat.setY(-quat.y() * invNorm);
    quat.setZ(-quat.z() * invNorm);
}

template <class T>
float magnitude(const Quaternion<T>& quat)
{ return std::sqrt(quat.w() * quat.w() + quat.x() * quat.x() + quat.y() * quat.y() + quat.z() * quat.z()); }

template <class T>
void normalise(Quaternion<T>& quat)
{ quat /= magnitude(quat); }

template <int rows, int cols, class Tm, class Tq>
void rotate(Matrix<rows, cols, Tm>& m, const Quaternion<Tq>& quat) {
    m *= Matrix<rows, cols, Tm>(getMatrix(quat));
}

}

#endif

#pragma once
#include <math.h>
#define PIE 3.141592653589793238

namespace glMath
{

    //-----------------------------------------------------------------
    // vec3 class
    //-----------------------------------------------------------------
    template <typename T>
    class vec3
    {
    public:
        vec3() : x(0), y(0), z(0) {}
        vec3(T xx) : x(xx), y(xx), z(xx) {}
        vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}

        // operator overloading
        // --------------------
        vec3 operator+(const vec3 &v) const
        {
            return vec3(x + v.x, y + v.y, z + v.z);
        }
        vec3 &operator+=(const vec3 &v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }
        vec3 &operator-=(const vec3 &v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }
        vec3 operator-(const vec3 v) const
        {
            return vec3(x - v.x, y - v.y, z - v.z);
        }
        vec3 operator*(const T r) const
        {
            return vec3(x * r, y * r, z * r);
        }

        T &operator[](uint8_t i)
        {
            return (&x)[i];
        }

        friend std::ostream &operator<<(std::ostream &s, const vec3<T> &v)
        {
            return s << '(' << v.x << ' ' << v.y << ' ' << v.z << ')';
        }

        // product
        // -------
        T dotProduct(const vec3<T> &v) const
        {
            return x * v.x + y * v.y + z * v.z;
        }
        T crossProduct(vec3<T> &v) const
        {
            return vec3<T>(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
        }

        // properties
        // ----------
        T norm() const
        {
            return x * x + y * y + z * z;
        }

        T length() const
        {
            return sqrt(norm());
        }

        vec3 &normalize()
        {
            T n = norm();
            if (n > 0)
            {
                T factor = 1 / sqrt(n);
                x *= factor;
                y *= factor;
                z *= factor;
            }

            return *this;
        }
        T x, y, z;
    };

    //-----------------------------------------------------------------
    // non member functions of vec3
    //-----------------------------------------------------------------

    template <typename T>
    struct triangle
    {
        glMath::vec3<T> p[3];
    };
    
    typedef triangle<float> trianglef;

    template <typename T>
    vec3<T> normalize(vec3<T> v)
    {
        vec3<T> temp = v;
        T n = v.norm();
        if (n > 0)
        {
            T factor = 1 / sqrt(n);
            temp.x *= factor;
            temp.y *= factor;
            temp.z *= factor;
        }
        return temp;
    }

    template <typename T>
    vec3<T> cross(vec3<T> v1, vec3<T> v)
    {
        return vec3<T>(v1.y * v.z - v1.z * v.y, v1.z * v.x - v1.x * v.z, v1.x * v.y - v1.y * v.x);
    }

    template <typename T>
    T dot(const vec3<T> &v, const vec3<T> &s)
    {
        return s.x * v.x + s.y * v.y + s.z * v.z;
    }

    typedef vec3<float> vec3f;
    typedef vec3<int> vec3i;

    //-----------------------------------------------------------------
    // vec4 class
    //-----------------------------------------------------------------

    template <typename T>
    class vec4
    {
    public:
        vec4() : x(0), y(0), z(0), w(0) {}
        vec4(T xx) : x(xx), y(xx), z(xx), w(xx) {}
        vec4(T xx, T yy, T zz, T ww) : x(xx), y(yy), z(zz), w(ww) {}

        // operator overloading
        // --------------------
        vec4 operator+(const vec4 &v) const
        {
            return vec4(x + v.x, y + v.y, z + v.z, w + v.w);
        }
        vec4 operator*(const vec4 &v) const
        {
            return vec4(x + v.x, y + v.y, z + v.z, w + v.w);
        } 

        vec4 &operator+=(const vec4 &v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            w += v.w;
            return *this;
        }

        vec4 &operator-=(const vec4 &v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            w -= v.w;
            return *this;
        }

        vec4 operator-(const vec4 v) const
        {
            return vec4(x - v.x, y - v.y, z - v.z, w - v.w);
        }

        vec4 operator*(const T r) const
        {
            return vec4(x * r, y * r, z * r, w * r);
        }

        T &operator[](uint8_t i)
        {
            return (&x)[i];
        }

        friend std::ostream &operator<<(std::ostream &s, const vec4<T> &v)
        {
            return s << '(' << v.x << ' ' << v.y << ' ' << v.z << v.w << ')';
        }

        // product
        // -------
        T dotProduct(const vec4<T> &v) const
        {
            return x * v.x + y * v.y + z * v.z + w * v.w;
        }

        // properties
        // ----------
        T norm() const
        {
            return x * x + y * y + z * z + w * w;
        }

        T length() const
        {
            return sqrt(norm());
        }

        vec4 &normalize()
        {
            T n = norm();
            if (n > 0)
            {
                T factor = 1 / sqrt(n);
                x *= factor;
                y *= factor;
                z *= factor;
                w *= factor;
            }

            return *this;
        }

        T x, y, z, w;
    };

    //-----------------------------------------------------------------
    // non member functions of vec4
    //-----------------------------------------------------------------

    template <typename T>
    vec4<T> normalize(vec4<T> v)
    {
        vec4<T> temp = v;
        T n = v.norm();
        if (n > 0)
        {
            T factor = 1 / sqrt(n);
            temp.x *= factor;
            temp.y *= factor;
            temp.z *= factor;
            temp.w *= factor;
        }
        return temp;
    }

    template <typename T>
    T dot(const vec4<T> &v, const vec4<T> &s)
    {
        return s.x * v.x + s.y * v.y + s.z * v.z + s.w * v.w;
    }

    typedef vec4<float> vec4f;

    // -------------
    // angle functions
    // -------------
    template <typename T>
    T degToRadians(T degree)
    {
        return degree * PIE / 180.0f;
    }

    //-----------------------------------------------------------------
    // mat4 class
    //-----------------------------------------------------------------

    template <typename T>
    class mat4
    {
    public:
        T x[4][4];
        mat4()
        {
            x[0][0] = 1;
            x[0][1] = 0;
            x[0][2] = 0;
            x[0][3] = 0;

            x[1][0] = 0;
            x[1][1] = 1;
            x[1][2] = 0;
            x[1][3] = 0;

            x[2][0] = 0;
            x[2][1] = 0;
            x[2][2] = 1;
            x[2][3] = 0;

            x[3][0] = 0;
            x[3][1] = 0;
            x[3][2] = 0;
            x[3][3] = 1;
        }

        mat4(T val)
        {
            x[0][0] = val;
            x[0][1] = 0;
            x[0][2] = 0;
            x[0][3] = 0;
            x[1][0] = 0;
            x[1][1] = val;
            x[1][2] = 0;
            x[1][3] = 0;
            x[2][0] = 0;
            x[2][1] = 0;
            x[2][2] = val;
            x[2][3] = 0;
            x[3][0] = 0;
            x[3][1] = 0;
            x[3][2] = 0;
            x[3][3] = val;
        }
        mat4(T a, T b, T c, T d, T e, T f, T g, T h,
             T i, T j, T k, T l, T m, T n, T o, T p)
        {
            x[0][0] = a;
            x[0][1] = b;
            x[0][2] = c;
            x[0][3] = d;
            x[1][0] = e;
            x[1][1] = f;
            x[1][2] = g;
            x[1][3] = h;
            x[2][0] = i;
            x[2][1] = j;
            x[2][2] = k;
            x[2][3] = l;
            x[3][0] = m;
            x[3][1] = n;
            x[3][2] = o;
            x[3][3] = p;
        }

        mat4(vec4<T> v1, vec4<T> v2, vec4<T> v3, vec4<T> v4)
        {
            x[0][0] = v1.x;
            x[0][1] = v1.y;
            x[0][2] = v1.z;
            x[0][3] = v1.w;
            x[1][0] = v2.x;
            x[1][1] = v2.y;
            x[1][2] = v2.z;
            x[1][3] = v2.w;
            x[2][0] = v3.x;
            x[2][1] = v3.y;
            x[2][2] = v3.z;
            x[2][3] = v3.w;
            x[3][0] = v4.x;
            x[3][1] = v4.y;
            x[3][2] = v4.z;
            x[3][3] = v4.w;
        }

        const T *operator[](uint8_t i) const
        {
            return x[i];
        }

        T *operator[](uint8_t i)
        {
            return x[i];
        }

        mat4<T> operator*(const mat4<T> &v) const
        {
            mat4<T> tmp(0.0f);
            multiply(*this, v, tmp);
            return tmp;
        }

        mat4<T> operator*(T v) const
        {
            mat4 tmp(
                x[0][0] * v,
                x[0][1] * v,
                x[0][2] * v,
                x[0][3] * v,
                x[1][0] * v,
                x[1][1] * v,
                x[1][2] * v,
                x[1][3] * v,
                x[2][0] * v,
                x[2][1] * v,
                x[2][2] * v,
                x[2][3] * v,
                x[3][0] * v,
                x[3][1] * v,
                x[3][2] * v,
                x[3][3] * v);
            return tmp;
        }

        glMath::vec3<T> operator*(const glMath::vec3<T> &v) const
        {
            glMath::vec3<T> temp;
            temp.x = x[0][0] * v.x + x[0][1] * v.y + x[0][2] * v.z + x[0][3] * 1;
            temp.y = x[1][0] * v.x + x[1][1] * v.y + x[1][2] * v.z + x[1][3] * 1;
            temp.z = x[2][0] * v.x + x[2][1] * v.y + x[2][2] * v.z + x[2][3] * 1;
            return temp;
        }

        glMath::vec4<T> operator*(const glMath::vec4<T> &v) const
        {
            glMath::vec4<T> temp;
            temp.x = x[0][0] * v.x + x[0][1] * v.y + x[0][2] * v.z + x[0][3] * v.w;
            temp.y = x[1][0] * v.x + x[1][1] * v.y + x[1][2] * v.z + x[1][3] * v.w;
            temp.z = x[2][0] * v.x + x[2][1] * v.y + x[2][2] * v.z + x[2][3] * v.w;
            temp.w = x[3][0] * v.x + x[3][1] * v.y + x[3][2] * v.z + x[3][3] * v.w;
            return temp;
        }

        static void multiply(const mat4<T> &a, const mat4<T> &b, mat4<T> &c)
        {
            for (uint8_t i = 0; i < 4; ++i)
            {
                for (uint8_t j = 0; j < 4; ++j)
                {
                    c[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] +
                              a[i][2] * b[2][j] + a[i][3] * b[3][j];
                }
            }
        }

        mat4<T> &transpose()
        {
            mat4 tmp(
                x[0][0],
                x[1][0],
                x[2][0],
                x[3][0],
                x[0][1],
                x[1][1],
                x[2][1],
                x[3][1],
                x[0][2],
                x[1][2],
                x[2][2],
                x[3][2],
                x[0][3],
                x[1][3],
                x[2][3],
                x[3][3]);
            *this = tmp;

            return *this;
        }

        friend std::ostream &operator<<(std::ostream &s, const mat4<T> &m)
        {
            return s << '\n'
                     << m[0][0] << ' ' << m[0][1] << ' ' << m[0][2] << ' ' << m[0][3] << '\n'
                     << m[1][0] << ' ' << m[1][1] << ' ' << m[1][2] << ' ' << m[1][3] << '\n'
                     << m[2][0] << ' ' << m[2][1] << ' ' << m[2][2] << ' ' << m[2][3] << '\n'
                     << m[3][0] << ' ' << m[3][1] << ' ' << m[3][2] << ' ' << m[3][3] << '\n';
        }
    };

    //-----------------------------------------------------------------
    // mat4 non member functions
    //-----------------------------------------------------------------

    template <typename T>
    mat4<T> transpose(mat4<T> &x)
    {
        mat4<T> tmp(x[0][0],
                    x[1][0],
                    x[2][0],
                    x[3][0],
                    x[0][1],
                    x[1][1],
                    x[2][1],
                    x[3][1],
                    x[0][2],
                    x[1][2],
                    x[2][2],
                    x[3][2],
                    x[0][3],
                    x[1][3],
                    x[2][3],
                    x[3][3]);
        return x;
    }

    template <typename T>
    mat4<T> translate(mat4<T> &m, vec3<T> v)
    {
        mat4<T> transMat(1.0f);
        transMat[0][3] = v[0];
        transMat[1][3] = v[1];
        transMat[2][3] = v[2];

        return (transMat * m);
    }

    template <typename T>
    mat4<T> rotate(mat4<T> &m, T angle, vec3<T> v)
    {
        T const a = angle;
        T const c = cos(a);
        T const s = sin(a);

        vec3<T> axis = normalize(v);
        // vec3<T> axis = (v);
        T X = axis.x;
        T Y = axis.y;
        T Z = axis.z;

        T t = (T(1) - c);

        mat4<T> Rotate(1.0f);
        Rotate[0][0] = (t * X * X + c);
        Rotate[0][1] = (t * X * Y - s * Z);
        Rotate[0][2] = (t * X * Z + s * Y);

        Rotate[1][0] = (t * X * Y + s * Z);
        Rotate[1][1] = (t * Y * Y + c);
        Rotate[1][2] = (t * Y * Z - s * X);

        Rotate[2][0] = (t * X * Z - s * Y);
        Rotate[2][1] = (t * Y * Z + s * X);
        Rotate[2][2] = (t * Z * Z + c);

        return (Rotate * m);
    }

    template <typename T>
    mat4<T> scale(mat4<T> &m, vec3<T> v)
    {
        mat4<T> scaleMat(1.0f);
        scaleMat[0][0] = v.x;
        scaleMat[1][1] = v.y;
        scaleMat[2][2] = v.z;
        return (scaleMat * m);
    }
    template <typename T>
    mat4<T> perspective(T fov, float screenWidth, float screenHeight, T nearZ, T farZ)
    {
        mat4<T> perspecMat(0.0f);
        fov = fov * (3.14f / 180.0f);
        T aspectRatio = screenWidth / screenHeight;
        T tangent = tan(fov / 2.0f);
        tangent = 1 / tangent;
        T val = tangent / aspectRatio;
        perspecMat[0][0] = val;
        perspecMat[1][1] = tangent;
        perspecMat[2][2] = -(nearZ - farZ) / (nearZ - farZ);
        perspecMat[2][3] = (2 * nearZ * farZ) / (nearZ - farZ);
        perspecMat[3][2] = -1;

        return perspecMat;
    }

    template <typename T>
    mat4<T> inverse(mat4<T> &m)
    {
        T Coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
        T Coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
        T Coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

        T Coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
        T Coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
        T Coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

        T Coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
        T Coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
        T Coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

        T Coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
        T Coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
        T Coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

        T Coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
        T Coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
        T Coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

        T Coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
        T Coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
        T Coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];
        vec4<T> Fac0(Coef00, Coef00, Coef02, Coef03);
        vec4<T> Fac1(Coef04, Coef04, Coef06, Coef07);
        vec4<T> Fac2(Coef08, Coef08, Coef10, Coef11);
        vec4<T> Fac3(Coef12, Coef12, Coef14, Coef15);
        vec4<T> Fac4(Coef16, Coef16, Coef18, Coef19);
        vec4<T> Fac5(Coef20, Coef20, Coef22, Coef23);
        vec4<T> Vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
        vec4<T> Vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
        vec4<T> Vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
        vec4<T> Vec3(m[1][3], m[0][3], m[0][3], m[0][3]);
        vec4<T> Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
        vec4<T> Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
        vec4<T> Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
        vec4<T> Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);
        vec4<T> SignA(+1, -1, +1, -1);
        vec4<T> SignB(-1, +1, -1, +1);
        mat4<T> Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);
        vec4<T> Row0(Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0]);
        vec4<T> Dot0(Row0 * glMath::vec4<T>(m[0][0], m[0][1], m[0][2], m[0][3]));
        T Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

        T OneOverDeterminant = static_cast<T>(1) / Dot1;

        glMath::mat4<T> temp(1.0f);
        temp = Inverse * OneOverDeterminant;
        temp = glMath::transpose(temp);

        return (temp);
    }

    template <typename T>
    mat4<T> lookAt(vec3<T> from, vec3<T> to, vec3<T> temp)
    {
        vec3<T> forward = glMath::normalize(to - from);
        vec3<T> right = glMath::normalize(glMath::cross(forward, glMath::normalize(temp)));
        vec3<T> up = glMath::cross(right, forward);

        mat4<T> Result(1.0f);

        Result[0][0] = right.x;
        Result[0][1] = right.y;
        Result[0][2] = right.z;
        Result[1][0] = up.x;
        Result[1][1] = up.y;
        Result[1][2] = up.z;
        Result[2][0] = -forward.x;
        Result[2][1] = -forward.y;
        Result[2][2] = -forward.z;
        Result[0][3] = -from.x;
        Result[1][3] = -from.y;
        Result[2][3] = -from.z;

        Result[3][3] = 1;
        
        return Result;
    }

    typedef mat4<float> mat4f;

    // template <typename T>
    // void mouseMovement(bool &fM, T &yaw, T &pitch, T &lastX, T &lastY, T xPosIn, T yPosIn)
    // {
    //     // TODO:  hide the cursor and capture mouse/cursor.
    //     // TODO: in processevent loop call these functions when needed.
    //     // maybe initialize yaw,pitch values before using
    //     // bool firstMouse = true;
    //     // float yaw = -90.0f;
    //     // float pitch = 0.0f;
    //     // float lastX = 800.0f / 2.0;
    //     // float lastY = 600.0 / 2.0;
    //     // also cameraFront

    //     // for camera i can have like this initially
    //     // camera
    //     // glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    //     // glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    //     // glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    //     float xpos = xposIn;
    //     float ypos = yposIn;

    //     if (firstMouse)
    //     {
    //         lastX = xpos;
    //         lastY = ypos;
    //         firstMouse = false;
    //     }

    //     float xoffset = xpos - lastX;
    //     float yoffset = ypos - lastY;
    //     lastX = xpos;
    //     lastY = ypos;

    //     float sensitivity = 0.1f;
    //     xoffset *= sensitivity;
    //     yoffset *= sensitivity;

    //     yaw += xoffset;
    //     pitch += yoffset;

    //     if (pitch > 89.0f)
    //         pitch = 89.0f;
    //     if (pitch < -89.0f)
    //         pitch = -89.0f;

    //     glMath::vec3f front;
    //     front.x = cos(glMath::degToRadians(yaw)) * cos(glMath::degToRadians(pitch));
    //     front.y = sin(glMath::degToRadians(pitch));
    //     front.z = sin(glMath::degToRadians(yaw)) * cos(glMath::degToRadians(pitch));
    //     cameraFront = glMath::normalize(front);
    // }
    // template <typename T>
    // void scrollMovement(T xoffset, T yoffset, T &fov)
    // {
    //     fov -= (float)yoffset;
    //     if (fov < 1.0f)
    //         fov = 1.0f;
    //     if (fov > 45.0f)
    //         fov = 45.0f;
    // }

    // // clipping parts:
    // vec3f linePlaneIntersection(vec3f &plane_p, vec3f &plane_n, vec3f &lineStart, vec3f &lineEnd)
    // {
    //     plane_n = glMath::normalize(plane_n);
    //     float plane_d = -plane_n.dotProduct(plane_p);
    //     float ad = lineStart.dotProduct(plane_n);
    //     float bd = lineEnd.dotProduct(plane_n);
    //     float t = (-plane_d - ad) / (bd - ad);
    //     vec3f lineStartToEnd = lineEnd - lineStart;
    //     vec3f lineToIntersect = lineStartToEnd * t;
    //     return lineStart + lineToIntersect;
    // }

    // int triangleNumClippedInPlane(vec3f plane_p, vec3f plane_n, trianglef &in_tri, trianglef &out_tri1, trianglef &out_tri2)
    // {
    //     plane_n = glMath::normalize(plane_n);

    //     // Return signed shortest distance from point to plane, plane normal must be normalised
    //     auto dist = [&](vec3f &p)
    //     {
    //         vec3f n = glMath::normalize(p);
    //         return (plane_n.x * p.x + plane_n.y * p.y + plane_n.z * p.z - plane_n.dotProduct(plane_p));
    //     };

    //     // Create two temporary storage arrays to classify points either side of plane
    //     // If distance sign is positive, point lies on "inside" of plane
    //     vec3f *inside_points[3];
    //     int nInsidePointCount = 0;
    //     vec3f *outside_points[3];
    //     int nOutsidePointCount = 0;

    //     // Get signed distance of each point in triangle to plane
    //     float d0 = dist(in_tri.p[0]);
    //     float d1 = dist(in_tri.p[1]);
    //     float d2 = dist(in_tri.p[2]);

    //     if (d0 >= 0)
    //     {
    //         inside_points[nInsidePointCount++] = &in_tri.p[0];
    //     }
    //     else
    //     {
    //         outside_points[nOutsidePointCount++] = &in_tri.p[0];
    //     }
    //     if (d1 >= 0)
    //     {
    //         inside_points[nInsidePointCount++] = &in_tri.p[1];
    //     }
    //     else
    //     {
    //         outside_points[nOutsidePointCount++] = &in_tri.p[1];
    //     }
    //     if (d2 >= 0)
    //     {
    //         inside_points[nInsidePointCount++] = &in_tri.p[2];
    //     }
    //     else
    //     {
    //         outside_points[nOutsidePointCount++] = &in_tri.p[2];
    //     }

    //     // Now break the input triangle into
    //     // smaller output triangles if required. There are four possible
    //     // outcomes

    //     if (nInsidePointCount == 0)
    //     {
    //         // All points lie on the outside of plane, so clip whole triangle
    //         // It ceases to exist

    //         return 0; // No returned triangles are valid
    //     }

    //     if (nInsidePointCount == 3)
    //     {
    //         // All points lie on the inside of plane, so do nothing
    //         // and allow the triangle to simply pass through
    //         out_tri1 = in_tri;
    //         return 1; // Just the one returned original triangle is valid
    //     }

    //     if (nInsidePointCount == 1 && nOutsidePointCount == 2)
    //     {
    //         // Triangle should be clipped. As two points lie outside
    //         // the plane, the triangle simply becomes a smaller triangle

    //         // Copy appearance info to new triangle
    //         // out_tri1.col = in_tri.col;
    //         // out_tri1.sym = in_tri.sym;

    //         // The inside point is valid, so keep that...
    //         out_tri1.p[0] = *inside_points[0];

    //         // but the two new points are at the locations where the
    //         // original sides of the triangle (lines) intersect with the plane
    //         out_tri1.p[1] = linePlaneIntersection(plane_p, plane_n, *inside_points[0], *outside_points[0]);
    //         out_tri1.p[2] = linePlaneIntersection(plane_p, plane_n, *inside_points[0], *outside_points[1]);

    //         return 1; // Return the newly formed single triangle
    //     }

    //     if (nInsidePointCount == 2 && nOutsidePointCount == 1)
    //     {
    //         // Triangle should be clipped. As two points lie inside the plane,
    //         // the clipped triangle becomes a "quad". Fortunately, we can
    //         // represent a quad with two new triangles

    //         // Copy appearance info to new triangles
    //         // out_tri1.col = in_tri.col;
    //         // out_tri1.sym = in_tri.sym;

    //         // out_tri2.col = in_tri.col;
    //         // out_tri2.sym = in_tri.sym;

    //         // The first triangle consists of the two inside points and a new
    //         // point determined by the location where one side of the triangle
    //         // intersects with the plane
    //         out_tri1.p[0] = *inside_points[0];
    //         out_tri1.p[1] = *inside_points[1];
    //         out_tri1.p[2] = linePlaneIntersection(plane_p, plane_n, *inside_points[0], *outside_points[0]);

    //         // The second triangle is composed of one of he inside points, a
    //         // new point determined by the intersection of the other side of the
    //         // triangle and the plane, and the newly created point above
    //         out_tri2.p[0] = *inside_points[1];
    //         out_tri2.p[1] = out_tri1.p[2];
    //         out_tri2.p[2] = linePlaneIntersection(plane_p, plane_n, *inside_points[1], *outside_points[0]);

    //         return 2; // Return two newly formed triangles which form a quad
    //     }
    // }

}

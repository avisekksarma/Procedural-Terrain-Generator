#pragma once
#include <math.h>
#define PIE 3.141592653589793238

namespace glMath {

    //-----------------------------------------------------------------
    // vec3 class
    //-----------------------------------------------------------------
    template<typename T> 
    class vec3 
    { 
    public: 
        vec3() : x(0), y(0), z(0) {} 
        vec3(T xx) : x(xx), y(xx), z(xx) {} 
        vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {} 

        // operator overloading
        // --------------------
        vec3 operator + (const vec3 &v) const 
        { 
            return vec3(x + v.x, y + v.y, z + v.z); 
        } 
        vec3& operator +=(const vec3 &v) 
        {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this; 
        } 
        vec3& operator -=(const vec3 &v) 
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this; 
        } 
        vec3 operator - (const vec3 v) const 
        { 
            return vec3(x - v.x, y - v.y, z - v.z);
        } 
        vec3 operator * (const T r) const 
        { 
            return vec3(x * r, y * r, z * r);
        } 

        T& operator [] (uint8_t i) 
        { 
            return (&x)[i];
        } 

        friend std::ostream& operator << (std::ostream &s, const vec3<T> &v) 
        { 
            return s << '(' << v.x << ' ' << v.y << ' ' << v.z << ')'; 
        } 

        // product
        // -------
        T dotProduct(const vec3<T> &v) const 
        { 
           return x * v.x + y * v.y + z * v.z;
        } 
        T crossProduct(vec3<T>& v) const
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

        vec3& normalize() 
        { 
            T n = norm(); 
            if (n > 0) { 
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
    vec3<T> normalize(vec3<T> v) 
    { 
        vec3<T> temp = v;
        T n = v.norm(); 
        if (n > 0) { 
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
        return vec3<T>(v1.y * v.z -v1.z * v.y,v1.z * v.x -v1.x * v.z,v1.x * v.y -v1.y * v.x); 
    } 

    template <typename T>
    T dot(const vec3<T> &v, const vec3<T>&s) 
    { 
        return s.x * v.x +s.y * v.y + s.z * v.z; 
    } 

    //-----------------------------------------------------------------
    // vec4 class
    //-----------------------------------------------------------------

    template<typename T> 
    class vec4 
    { 
    public: 
        vec4() : x(0), y(0), z(0), w(0) {} 
        vec4(T xx) : x(xx), y(xx), z(xx), w(xx) {} 
        vec4(T xx, T yy, T zz, T ww) : x(xx), y(yy), z(zz), w(ww) {} 

        // operator overloading
        // --------------------
        vec4 operator + (const vec4 &v) const 
        {
             return vec4(x + v.x, y + v.y, z + v.z, w + v.w);
        } 
        vec4 operator * (const vec4 &v) const 
        { 
            return vec4(x * v.x, y * v.y, z * v.z, w * v.w);
        } 

        vec4& operator +=(const vec4 &v) 
        {
            x += v.x;
            y += v.y;
            z += v.z;
            w += v.w;
            return *this; 
        } 

        vec4& operator -=(const vec4 &v) 
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            w -= v.w;
            return *this; 
        } 

        vec4 operator - (const vec4 v) const 
        { 
            return vec4(x - v.x, y - v.y, z - v.z, w - v.w);
        } 
        
        vec4 operator * (const T r) const 
        {
            return vec4(x * r, y * r, z * r, w * r); 
        } 

        T& operator [] (uint8_t i)
        { 
           return (&x)[i];
        } 

        friend std::ostream& operator << (std::ostream &s, const vec4<T> &v) 
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

        vec4& normalize() 
        { 
            T n = norm(); 
            if (n > 0) { 
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
        if (n > 0) { 
            T factor = 1 / sqrt(n); 
            temp.x *= factor;
            temp.y *= factor; 
            temp.z *= factor;
            temp.w *= factor; 
        } 
        return temp; 
    } 

    template <typename T>
    T dot(const vec4<T> &v, const vec4<T>&s) 
    { 
        return s.x * v.x +s.y * v.y + s.z * v.z + s.w * v.w; 
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

        mat4(vec4<T>v1,vec4<T>v2,vec4<T>v3,vec4<T>v4)
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

		const T* operator [] (uint8_t i) const
        { 
            return x[i]; 
        }

        T* operator [] (uint8_t i) 
        { 
            return x[i]; 
        }

        mat4<T> operator * (const mat4<T>& v) const
        {
            mat4<T> tmp(0.0f);
            multiply(*this, v, tmp);
            return tmp;
        }

        mat4<T> operator * (T v) const
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
                x[3][3] * v
            );
            return tmp;
        }

        glMath::vec3<T> operator * (const glMath::vec3<T>& v) const
        {
            glMath::vec3<T> temp;
            temp.x = x[0][0] * v.x + x[0][1] * v.y + x[0][2] * v.z + x[0][3]*1;
            temp.y = x[1][0] * v.x + x[1][1] * v.y + x[1][2] * v.z + x[1][3]*1;
            temp.z = x[2][0] * v.x + x[2][1] * v.y + x[2][2] * v.z + x[2][3]*1;
            return temp;
        }

        glMath::vec4<T> operator * (const glMath::vec4<T>& v) const
        {
            glMath::vec4<T> temp;
            temp.x = x[0][0] * v.x + x[0][1] * v.y + x[0][2] * v.z + x[0][3]*v.w;
            temp.y = x[1][0] * v.x + x[1][1] * v.y + x[1][2] * v.z + x[1][3]*v.w;
            temp.z = x[2][0] * v.x + x[2][1] * v.y + x[2][2] * v.z + x[2][3]*v.w;
            temp.w = x[3][0] * v.x + x[3][1] * v.y + x[3][2] * v.z + x[3][3]*v.w;
            return temp;
        }

        static void multiply(const mat4<T> &a, const mat4<T>& b, mat4<T> &c) 
        { 
            for (uint8_t i = 0; i < 4; ++i) { 
                for (uint8_t j = 0; j < 4; ++j) { 
                    c[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] + 
                        a[i][2] * b[2][j] + a[i][3] * b[3][j]; 
                } 
            } 
        } 

        mat4<T>& transpose()
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

        friend std::ostream& operator << (std::ostream& s, const mat4<T>& m)
        {
            return s << '\n' << m[0][0] << ' ' << m[0][1] << ' ' << m[0][2] << ' ' << m[0][3] << '\n'
                << m[1][0] << ' ' << m[1][1] << ' ' << m[1][2] << ' ' << m[1][3] << '\n'
                << m[2][0] << ' ' << m[2][1] << ' ' << m[2][2] << ' ' << m[2][3] << '\n'
                << m[3][0] << ' ' << m[3][1] << ' ' << m[3][2] << ' ' << m[3][3] << '\n';
        }
    };

    //-----------------------------------------------------------------
    // mat4 non member functions
    //-----------------------------------------------------------------

    template <typename T>
    mat4<T> transpose(mat4<T>& x)
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
    mat4<T> translate(mat4<T>& m, vec3<T> v)
    {
        mat4<T> transMat(1.0f);
        transMat[0][3] = v[0];
        transMat[1][3] = v[1];
        transMat[2][3] = v[2];

        return ( transMat*m );
    }

    template <typename T>
    mat4<T> rotate(mat4<T>& m, T angle, vec3<T> v)
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
        Rotate[0][1] = (t * X*Y - s*Z);
        Rotate[0][2] = ( t * X * Z + s * Y);

        Rotate[1][0] = ( t * X * Y + s*Z);
        Rotate[1][1] = ( t * Y * Y + c);
        Rotate[1][2] = (t * Y * Z - s * X);

        Rotate[2][0] = (t * X * Z - s * Y);
        Rotate[2][1] = (t * Y * Z + s * X);
        Rotate[2][2] = ( t * Z * Z + c);


        return (Rotate * m);
    }

    template <typename T>
    mat4<T> scale(mat4<T>& m, vec3<T> v)
    {
        mat4<T> scaleMat(1.0f);
        scaleMat[0][0] = v.x;
        scaleMat[1][1] = v.y;
        scaleMat[2][2] = v.z;
        return (m * scaleMat);
    }

    template <typename T>
    mat4<T> inverse(mat4<T>& m)
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

    //-----------------------------------------------------------------
    // type definitons 
    //-----------------------------------------------------------------

    typedef vec3<float> vec3f; 
    typedef vec4<float> vec4f; 
	typedef vec3<int> vec3i;
	typedef mat4<float> mat4f;

}

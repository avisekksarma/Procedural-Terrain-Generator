#include "../include/glMath.h"


template <typename T>
glMath::vec3<T> glMath::normalize(glMath::vec3<T> v) 
{ 
    glMath::vec3<T> temp = v;
    T n = v.norm(); 
    if (n > 0) { 
        T factor = 1 / sqrt(n); 
        temp.x *= factor, temp.y *= factor, temp.z *= factor; 
    } 
    return temp; 
} 

template <typename T>
glMath::vec3<T> glMath::cross(glMath::vec3<T> v1, glMath::vec3<T> v) 
{ return vec3<T>(v1.y * v.z -v1.z * v.y,v1.z * v.x -v1.x * v.z,v1.x * v.y -v1.y * v.x); } 


template <typename T>
T glMath::dot(const glMath::vec3<T> &v, const glMath::vec3<T>&s) 
{ return s.x * v.x +s.y * v.y + s.z * v.z; } 

template <typename T>
glMath::vec2<T> glMath::normalize(glMath::vec2<T> v) 
{ 
    glMath::vec3<T> temp = v;
    T n = v.norm(); 
    if (n > 0) { 
        T factor = 1 / sqrt(n); 
        temp.x *= factor, temp.y *= factor; 
    } 
    return temp; 
} 

template <typename T>
glMath::vec2<T> glMath::cross(glMath::vec2<T> v1, glMath::vec2<T> v) 
{ return vec2<T>(v1.x * v.y - v1.y * v.x); } 

template <typename T>
T glMath::dot(const glMath::vec2<T> &v, const glMath::vec2<T>&s) 
{ return s.x * v.x +s.y * v.y ; } 

template <typename T>
glMath::mat4<T> glMath::transpose(glMath::mat4<T>& x)
{
    glMath::mat4<T> tmp(x[0][0],
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
glMath::mat4<T> glMath::translate(glMath::mat4<T>& m, glMath::vec3<T> v)
{
    glMath::mat4<T> transMat(1.0f);
    //transMat[3][0] = v[0];
    //transMat[3][1] = v[1];
    //transMat[3][2] = v[2];
    
    transMat[0][3] = v[0];
    transMat[1][3] = v[1];
    transMat[2][3] = v[2];

    // transMat.transpose();
    return ( m * transMat   );
}

template <typename T>
glMath::mat4<T> glMath::rotate(glMath::mat4<T>& m, T angle, glMath::vec3<T> v)
{
    T const a = angle;
    T const c = cos(a);
    T const s = sin(a);

    glMath::vec3<T> axis = normalize(v);
    T X = axis.x;
    T Y = axis.y;
    T Z = axis.z;

    T t = (T(1) - c);

    glMath::mat4<T> Rotate(1.0f);
    Rotate[0][0] = (t * X * X + c);
    Rotate[0][1] = (t * X*Y - s*Z);
    Rotate[0][2] = ( t * X * Z + s * Y);

    Rotate[1][0] = ( t * X * Y + s*Z);
    Rotate[1][1] = ( t * Y * Y + c);
    Rotate[1][2] = (t * Y * Z - s * X);

    Rotate[2][0] = (t * X * Z - s * Y);
    Rotate[2][1] = (t * Y * Z + s * X);
    Rotate[2][2] = ( t * Z * Z + c);

    Rotate = glMath::transpose(Rotate);

    return (m * Rotate);
}

template <typename T>
glMath::mat4<T> glMath::scale(glMath::mat4<T>& m, glMath::vec3<T> v)
{
    glMath::mat4<T> scaleMat(1.0f);
    scaleMat[0][0] = v.x;
    scaleMat[1][1] = v.y;
    scaleMat[2][2] = v.z;


    return (m * scaleMat);
}

template <typename T>
glMath::mat4<T> glMath::ortho(const T b, const T t, const T l, const T r,
    const T n, const T f)
{
    glMath::mat4<T> orthoMat;
    orthoMat[0][0] = 2 / (r - l); 
    orthoMat[0][1] = 0; 
    orthoMat[0][2] = 0; 
    orthoMat[0][3] = 0; 
        
    orthoMat[1][0] = 0; 
    orthoMat[1][1] = 2 / (t - b); 
    orthoMat[1][2] = 0; 
    orthoMat[1][3] = 0; 
    
    orthoMat[2][0] = 0; 
    orthoMat[2][1] = 0; 
    orthoMat[2][2] = -2 / (f - n); 
    orthoMat[2][3] = 0; 
        
    orthoMat[3][0] = -(r + l) / (r - l); 
    orthoMat[3][1] = -(t + b) / (t - b); 
    orthoMat[3][2] = -(f + n) / (f - n); 
    orthoMat[3][3] = 1; 

    orthoMat.transpose();

    return orthoMat;
}

template <typename T>
glMath::mat4<T> glMath::perspective(T fovY, T aspectRatio,T front, T back)
{
    T tangent = tan(fovY/2);				  // tangent of half fovY
    T height = front * tangent;				 // half height of near plane
    T width = height * aspectRatio;			// half width of near plane

    T  r = width,  t = height, n = front, f = back;

    glMath::mat4<T> perspecMat(0.0f);

    // perspecMat[0][0] = n / r;
    // perspecMat[1][1] = n / t;
    // perspecMat[2][2] = -(f + n) / (f - n);
    // perspecMat[2][3] = -(2 * f * n) / (f - n);
    // perspecMat[3][2] = -1;
    // transpose

    perspecMat[0][0] = n / r;
    perspecMat[1][1] = n / t;
    perspecMat[2][2] = f / (f - n);
    perspecMat[3][2] = 1;
    perspecMat[2][3] = -(n * f)/(f - n);
    perspecMat[3][3] = 0;


    // perspecMat.transpose();
    
    return perspecMat;
}

template <typename T>
glMath::mat4<T> glMath::lookAt(glMath::vec3<T> from, glMath::vec3<T> to, glMath::vec3<T> temp)
{
    glMath::vec3<T> forward = glMath::normalize(to - from);
    glMath::vec3<T> right = glMath::cross(forward, glMath::normalize(temp));
    glMath::vec3<T> up = glMath::cross(right, forward);

    glMath::mat4<T> Result(1.0f);

    Result[0][0] = right.x;
    Result[0][1] = right.y;
    Result[0][2] = right.z;
    Result[1][0] = up.x;
    Result[1][1] = up.y;
    Result[1][2] = up.z;
    Result[2][0] = -forward.x;
    Result[2][1] = -forward.y;
    Result[2][2] = -forward.z;
    Result[0][3] = -glMath::dot(right, from);
    Result[1][3] = -glMath::dot(up, from);
    Result[2][3] = glMath::dot(forward, from);

    Result.transpose();

    return Result;
}

template <typename T>
T* glMath::value_ptr(glMath::mat4<T>& m)
{
    return &m[0][0];
}

float glMath::radians(float angle)
{
    return ((PIE / 180) * angle);
}


template<typename T>
void glMath::drawTriangle(glMath::vec3<T>p1, glMath::vec3<T>p2, glMath::vec3<T>p3, int color)
{
    BLA(p1.x,p1.y,p2.x,p2.y, color);
    BLA(p2.x,p2.y,p3.x,p3.y, color);
    BLA(p3.x,p3.y,p1.x,p1.y, color);
}
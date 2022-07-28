// #pragma once
// #include <ostream>
// #include <math.h>
// namespace glMath {

// #define PIE 3.141592653589793238

// 	// Vector classes
// 	//----------------------------------------------------------
// 	template<typename T> 
// 	class vec3 
// 	{ 
// 	public: 
// 		vec3() : x(0), y(0), z(0) {} 
// 		vec3(T xx) : x(xx), y(xx), z(xx) {} 
// 		vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {} 

// 		// operator overloading
// 		// --------------------
// 		vec3 operator + (const vec3 &v) const 
// 		{ return vec3(x + v.x, y + v.y, z + v.z); } 
// 		vec3& operator +=(const vec3 &v) 
// 		{
// 			x += v.x;
// 			y += v.y;
// 			z += v.z;
// 			return *this; 
// 		} 
// 		vec3& operator -=(const vec3 &v) 
// 		{
// 			x -= v.x;
// 			y -= v.y;
// 			z -= v.z;
// 			return *this; 
// 		} 

// 		vec3 operator - (const vec3 v) const 
// 		{ return vec3(x - v.x, y - v.y, z - v.z); } 
// 		vec3 operator * (const T r) const 
// 		{ return vec3(x * r, y * r, z * r); } 
// 		const T& operator [] (uint8_t i) const { return (&x)[i]; } 
// 		T& operator [] (uint8_t i) { return (&x)[i]; } 
// 		friend std::ostream& operator << (std::ostream &s, const vec3<T> &v) 
// 		{ 
// 			return s << '(' << v.x << ' ' << v.y << ' ' << v.z << ')'; 
// 		} 

// 		// product
// 		// -------
// 		T dotProduct(const vec3<T> &v) const 
// 		{ return x * v.x + y * v.y + z * v.z; } 
// 		T crossProduct(vec3<T>& v) const
// 		{ return vec3<T>(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); } 

// 		// properties
// 		// ----------
// 		T norm() const 
// 		{ return x * x + y * y + z * z; } 
// 		T length() const 
// 		{ return sqrt(norm()); } 
// 		vec3& normalize() 
// 		{ 
// 			T n = norm(); 
// 			if (n > 0) { 
// 				T factor = 1 / sqrt(n); 
// 				x *= factor, y *= factor, z *= factor; 
// 			} 
	 
// 			return *this; 
// 		} 
// 		T x, y, z; 
// 	}; 

// 	template<typename T> 
// 	class vec2 
// 	{ 
// 	public: 
// 		vec2() : x(0), y(0) {} 
// 		vec2(T xx) : x(xx), y(xx) {} 
// 		vec2(T xx, T yy) : x(xx), y(yy) {} 

// 		// operator overloading
// 		// --------------------
// 		vec2 operator + (const vec2 &v) const 
// 		{ return vec2(x + v.x, y + v.y); } 
// 		vec2& operator +=(const vec2 &v) 
// 		{
// 			x += v.x;
// 			y += v.y;
// 			return *this; 
// 		} 
// 		vec2& operator -=(const vec2 &v) 
// 		{
// 			x -= v.x;
// 			y -= v.y;
// 			return *this; 
// 		} 

// 		vec2 operator - (const vec2 v) const 
// 		{ return vec2(x - v.x, y - v.y); } 
// 		vec2 operator * (const T r) const 
// 		{ return vec2(x * r, y * r); } 
// 		const T& operator [] (uint8_t i) const { return (&x)[i]; } 
// 		T& operator [] (uint8_t i) { return (&x)[i]; } 
// 		// friend std::ostream& operator << (std::ostream &s, const vec3<T> &v) 
// 		// { 
// 		// 	return s << '(' << v.x << ' ' << v.y << ')'; 
// 		// } 

// 		// product
// 		// -------
// 		T dotProduct(const vec2<T> &v) const 
// 		{ return x * v.x + y * v.y ; } 
// 		T crossProduct(vec2<T>& v) const
// 		{return (x*v.y - y*v.x);} 

// 		// properties
// 		// ----------
// 		T norm() const 
// 		{ return x * x + y * y; } 
// 		T length() const 
// 		{ return sqrt(norm()); } 
// 		vec2& normalize() 
// 		{ 
// 			T n = norm(); 
// 			if (n > 0) { 
// 				T factor = 1 / sqrt(n); 
// 				x *= factor, y *= factor; 
// 			} 
// 			return *this; 
// 		} 
// 		T x, y; 
// 	}; 

// 	// Matrix classes 
// 	// ----------------------------------------------------------------------------------
// 	template <typename T>
// 	class mat4 
// 	{
// 	public:
// 		T x[4][4];
// 		mat4()
// 		{
// 			x[0][0] = 1;
// 			x[0][1] = 0;
// 			x[0][2] = 0;
// 			x[0][3] = 0;

// 			x[1][0] = 0;
// 			x[1][1] = 1;
// 			x[1][2] = 0;
// 			x[1][3] = 0;

// 			x[2][0] = 0;
// 			x[2][1] = 0;
// 			x[2][2] = 1;
// 			x[2][3] = 0;

// 			x[3][0] = 0;
// 			x[3][1] = 0;
// 			x[3][2] = 0;
// 			x[3][3] = 1;
// 		}

// 		mat4(T val)
// 		{
// 			x[0][0] = val;
// 			x[0][1] = 0;
// 			x[0][2] = 0;
// 			x[0][3] = 0;
// 			x[1][0] = 0;
// 			x[1][1] = val;
// 			x[1][2] = 0;
// 			x[1][3] = 0;
// 			x[2][0] = 0;
// 			x[2][1] = 0;
// 			x[2][2] = val;
// 			x[2][3] = 0;
// 			x[3][0] = 0;
// 			x[3][1] = 0;
// 			x[3][2] = 0;
// 			x[3][3] = val;
// 		}
// 		mat4(T a, T b, T c, T d, T e, T f, T g, T h,
// 			T i, T j, T k, T l, T m, T n, T o, T p)
// 		{
// 			x[0][0] = a;
// 			x[0][1] = b;
// 			x[0][2] = c;
// 			x[0][3] = d;
// 			x[1][0] = e;
// 			x[1][1] = f;
// 			x[1][2] = g;
// 			x[1][3] = h;
// 			x[2][0] = i;
// 			x[2][1] = j;
// 			x[2][2] = k;
// 			x[2][3] = l;
// 			x[3][0] = m;
// 			x[3][1] = n;
// 			x[3][2] = o;
// 			x[3][3] = p;
// 		}

// 		const T* operator [] (uint8_t i) const { return x[i]; }
// 		T* operator [] (uint8_t i) { return x[i]; }
// 		mat4<T> operator * (const mat4<T>& v) const
// 		{
// 			mat4<T> tmp(0.0f);
// 			multiply(*this, v, tmp);

// 			return tmp;
// 		}

// 		glMath::vec3<T> operator * (const glMath::vec3<T>& v) const
// 		{
// 			glMath::vec3<T> temp;
// 			temp.x = x[0][0] * v.x + x[0][1] * v.y + x[0][2] * v.z + x[0][3]*1;
// 			temp.y = x[1][0] * v.x + x[1][1] * v.y + x[1][2] * v.z + x[1][3]*1;
// 			temp.z = x[2][0] * v.x + x[2][1] * v.y + x[2][2] * v.z + x[2][3]*1;
// 			return temp;
// 		}

// 		static void multiply(const mat4<T> &a, const mat4<T>& b, mat4<T> &c) 
// 		{ 
// 			for (uint8_t i = 0; i < 4; ++i) { 
// 				for (uint8_t j = 0; j < 4; ++j) { 
// 					c[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] + 
// 						a[i][2] * b[2][j] + a[i][3] * b[3][j]; 
// 				} 
// 			} 

// 			//for (int I = 0; I < 4; ++I)
// 			//{
// 			//	for (int J = 0; J < 4; ++J)
// 			//	{
// 			//		float SumElements = 0.0f;
// 			//		for (int K = 0; K < 4; ++K)
// 			//		{
// 			//			SumElements += a[I][K] * b[K][J];
// 			//		}
// 			//		c[I][J] = SumElements;
// 			//	}
// 			//}

// 			// A restric qualified pointer (or reference) is basically a promise
// 			// to the compiler that for the scope of the pointer, the target of the
// 			// pointer will only be accessed through that pointer (and pointers
// 			// copied from it.
// 			//const T * __restrict ap = &a.x[0][0]; 
// 			//const T * __restrict bp = &b.x[0][0]; 
// 			//	  T * __restrict cp = &c.x[0][0]; 
	 
// 			//T a0, a1, a2, a3; 
	 
// 			//a0 = ap[0]; 
// 			//a1 = ap[1]; 
// 			//a2 = ap[2]; 
// 			//a3 = ap[3]; 
	 
// 			//cp[0]  = a0 * bp[0]  + a1 * bp[4]  + a2 * bp[8]  + a3 * bp[12]; 
// 			//cp[1]  = a0 * bp[1]  + a1 * bp[5]  + a2 * bp[9]  + a3 * bp[13]; 
// 			//cp[2]  = a0 * bp[2]  + a1 * bp[6]  + a2 * bp[10] + a3 * bp[14]; 
// 			//cp[3]  = a0 * bp[3]  + a1 * bp[7]  + a2 * bp[11] + a3 * bp[15]; 
	 
// 			//a0 = ap[4]; 
// 			//a1 = ap[5]; 
// 			//a2 = ap[6]; 
// 			//a3 = ap[7]; 
	 
// 			//cp[4]  = a0 * bp[0]  + a1 * bp[4]  + a2 * bp[8]  + a3 * bp[12]; 
// 			//cp[5]  = a0 * bp[1]  + a1 * bp[5]  + a2 * bp[9]  + a3 * bp[13]; 
// 			//cp[6]  = a0 * bp[2]  + a1 * bp[6]  + a2 * bp[10] + a3 * bp[14]; 
// 			//cp[7]  = a0 * bp[3]  + a1 * bp[7]  + a2 * bp[11] + a3 * bp[15]; 
	 
// 			//a0 = ap[8]; 
// 			//a1 = ap[9]; 
// 			//a2 = ap[10]; 
// 			//a3 = ap[11]; 
	 
// 			//cp[8]  = a0 * bp[0]  + a1 * bp[4]  + a2 * bp[8]  + a3 * bp[12]; 
// 			//cp[9]  = a0 * bp[1]  + a1 * bp[5]  + a2 * bp[9]  + a3 * bp[13]; 
// 			//cp[10] = a0 * bp[2]  + a1 * bp[6]  + a2 * bp[10] + a3 * bp[14]; 
// 			//cp[11] = a0 * bp[3]  + a1 * bp[7]  + a2 * bp[11] + a3 * bp[15]; 
	 
// 			//a0 = ap[12]; 
// 			//a1 = ap[13]; 
// 			//a2 = ap[14]; 
// 			//a3 = ap[15]; 
	 
// 			//cp[12] = a0 * bp[0]  + a1 * bp[4]  + a2 * bp[8]  + a3 * bp[12]; 
// 			//cp[13] = a0 * bp[1]  + a1 * bp[5]  + a2 * bp[9]  + a3 * bp[13]; 
// 			//cp[14] = a0 * bp[2]  + a1 * bp[6]  + a2 * bp[10] + a3 * bp[14]; 
// 			//cp[15] = a0 * bp[3]  + a1 * bp[7]  + a2 * bp[11] + a3 * bp[15]; 
// 		} 
// 		mat4<T>& transpose()
// 		{
// 			mat4 tmp(x[0][0],
// 				x[1][0],
// 				x[2][0],
// 				x[3][0],
// 				x[0][1],
// 				x[1][1],
// 				x[2][1],
// 				x[3][1],
// 				x[0][2],
// 				x[1][2],
// 				x[2][2],
// 				x[3][2],
// 				x[0][3],
// 				x[1][3],
// 				x[2][3],
// 				x[3][3]);
// 			*this = tmp;

// 			return *this;
// 		}

// 		friend std::ostream& operator << (std::ostream& s, const mat4<T>& m)
// 		{
// 			return s << '\n' << m[0][0] << ' ' << m[0][1] << ' ' << m[0][2] << ' ' << m[0][3] << '\n'
// 				<< m[1][0] << ' ' << m[1][1] << ' ' << m[1][2] << ' ' << m[1][3] << '\n'
// 				<< m[2][0] << ' ' << m[2][1] << ' ' << m[2][2] << ' ' << m[2][3] << '\n'
// 				<< m[3][0] << ' ' << m[3][1] << ' ' << m[3][2] << ' ' << m[3][3] << '\n';
// 		}
// 	};

// 	// non member functions
// 	template <typename T>
// 	vec3<T> normalize(vec3<T> v) ;

// 	template <typename T>
// 	vec3<T> cross(vec3<T> v1, vec3<T> v) ;

// 	template <typename T>
// 	T dot(const vec3<T> &v, const vec3<T>&s);

// 	template <typename T>
// 	vec2<T> normalize(vec2<T> v) ;

// 	template <typename T>
// 	vec2<T> cross(vec2<T> v1, vec2<T> v) ;

// 	template <typename T>
// 	T dot(const vec2<T> &v, const vec2<T>&s);

// 	template <typename T>
// 	mat4<T> transpose(mat4<T>& x);

// 	template <typename T>
// 	mat4<T> translate(mat4<T>& m, vec3<T> v);

// 	template <typename T>
// 	// mat4<T> rotate(mat4<T>& m, T angle, vec3<T> v);
// 	mat4<T> rotate(mat4<T>& m, T angle, vec3<T> v){
// 		T const a = angle;
// 		T const c = std::cos(a);
// 		T const s = std::sin(a);

// 		glMath::vec3<T> axis = normalize<float>(v);
// 		T X = axis.x;
// 		T Y = axis.y;
// 		T Z = axis.z;

// 		T t = (T(1) - c);

// 		glMath::mat4<T> Rotate(1.0f);
// 		Rotate[0][0] = (t * X * X + c);
// 		Rotate[0][1] = (t * X*Y - s*Z);
// 		Rotate[0][2] = ( t * X * Z + s * Y);

// 		Rotate[1][0] = ( t * X * Y + s*Z);
// 		Rotate[1][1] = ( t * Y * Y + c);
// 		Rotate[1][2] = (t * Y * Z - s * X);

// 		Rotate[2][0] = (t * X * Z - s * Y);
// 		Rotate[2][1] = (t * Y * Z + s * X);
// 		Rotate[2][2] = ( t * Z * Z + c);

// 		// Rotate = glMath::transpose(Rotate);

// 		return (m * Rotate);
// 	}

// 	template <typename T>
// 	mat4<T> scale(mat4<T>& m, vec3<T> v);

// 	template <typename T>
// 	mat4<T> ortho(const T b, const T t, const T l, const T r,
// 		const T n, const T f);

// 	template <typename T>
// 	mat4<T> perspective(T fovY, T aspectRatio,T front, T back);

// 	template <typename T>
// 	mat4<T> lookAt(vec3<T> from, vec3<T> to, vec3<T> temp);

// 	typedef vec3<float> vec3f; 
// 	typedef vec3<int> vec3i;
// 	typedef vec2<float> vec2f;
// 	typedef vec2<int> vec2i;

// 	typedef mat4<float> mat4f;
// }

	// template <typename T>
	// mat4<T> ortho(const T b, const T t, const T l, const T r,
	// 	const T n, const T f)
	// {
	// 	mat4<T> orthoMat;
	// 	orthoMat[0][0] = 2 / (r - l); 
	// 	orthoMat[0][1] = 0; 
	// 	orthoMat[0][2] = 0; 
	// 	orthoMat[0][3] = 0; 
		 
	// 	orthoMat[1][0] = 0; 
	// 	orthoMat[1][1] = 2 / (t - b); 
	// 	orthoMat[1][2] = 0; 
	// 	orthoMat[1][3] = 0; 
	 
	// 	orthoMat[2][0] = 0; 
	// 	orthoMat[2][1] = 0; 
	// 	orthoMat[2][2] = -2 / (f - n); 
	// 	orthoMat[2][3] = 0; 
		 
	// 	orthoMat[3][0] = -(r + l) / (r - l); 
	// 	orthoMat[3][1] = -(t + b) / (t - b); 
	// 	orthoMat[3][2] = -(f + n) / (f - n); 
	// 	orthoMat[3][3] = 1; 

	// 	orthoMat.transpose();

	// 	return orthoMat;
	// }

	// template <typename T>
	// mat4<T> perspective(T fovY, T aspectRatio,T front, T back)
	// {
	// 	T tangent = tan(fovY/2);				  // tangent of half fovY
	// 	T height = front * tangent;				 // half height of near plane
	// 	T width = height * aspectRatio;			// half width of near plane

	// 	T  r = width,  t = height, n = front, f = back;

	// 	mat4<T> perspecMat(0.0f);

	// 	perspecMat[0][0] = n / r;
	// 	perspecMat[1][1] = n / t;
	// 	perspecMat[2][2] = -(f + n) / (f - n);
	// 	perspecMat[2][3] = -(2 * f * n) / (f - n);
	// 	perspecMat[3][2] = -1;

	// 	perspecMat.transpose();
		

	// 	return perspecMat;
	// }

	// template <typename T>
	// mat4<T> lookAt(vec3<T> from, vec3<T> to, vec3<T> temp)
	// {
	// 	vec3<T> forward = glMath::normalize(to - from);
	// 	vec3<T> right = glMath::cross(forward, glMath::normalize(temp));
	// 	vec3<T> up = glMath::cross(right, forward);

	// 	mat4<T> Result(1.0f);

	// 	Result[0][0] = right.x;
	// 	Result[0][1] = right.y;
	// 	Result[0][2] = right.z;
	// 	Result[1][0] = up.x;
	// 	Result[1][1] = up.y;
	// 	Result[1][2] = up.z;
	// 	Result[2][0] = -forward.x;
	// 	Result[2][1] = -forward.y;
	// 	Result[2][2] = -forward.z;
	// 	Result[0][3] = -glMath::dot(right, from);
	// 	Result[1][3] = -glMath::dot(up, from);
	// 	Result[2][3] = glMath::dot(forward, from);

	// 	Result.transpose();

	// 	return Result;
	// }

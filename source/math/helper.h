#ifndef _H_HELPER_MATH
#define _H_HELPER_MATH

#include <vector>
#include "../config.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"
#include "mat3.h"
#include "smart_matrix.h"
#include "quat.h"

namespace Punk {
	namespace Engine {
		namespace Math
		{
			float DegToRad(float value);
			float RadToDeg(float value);

			//PUNK_ENGINE_API const mat4 ProjectionMatrix(float fov, float aspect, float zNear, float zFar);
			//	PUNK_ENGINE_API const mat4 OrthoMatrix(float width, float height, float bottom, float top);
			//	PUNK_ENGINE_API const mat4 Rotate(vec4 v);
			//	PUNK_ENGINE_API const mat4 Translate(vec3 pos);
			//	PUNK_ENGINE_API const mat4 Scale(vec3 scale);
			//	PUNK_ENGINE_API const mat4 TargetCamera(vec3 eye, vec3 pos, vec3 up);
			//	PUNK_ENGINE_API const mat4 FreeCamera(vec3 pos, vec3 dir, vec3 up);
			PUNK_ENGINE_API const mat3 NormalMatrixFromWorldView(const mat4& worldView);

			//	used to find ceter of the mass of the object
			PUNK_ENGINE_API bool YawPitchRollToUpDirection(float yaw, float pitch, float roll, vec3& up, vec3& dir);

			template<class T>
			inline int Sign(T x)
			{
				return (x == T(0) ? 0 : ((x < 0) ? -1 : 1));
			}			

			template<class T>
			inline T Floor(T x)
			{
				return floor(x);
			}

			template<class T>
			inline T Fract(T x)
			{
				return x - Floor(x);
			}

			template<class T>
			inline T Mod(T x, T y)
			{
				return x - y*Floor(x / y);
			}

			template<class T>
			inline T Step(T edge, T x)
			{
				if (x < edge)
					return T(0);
				return T(1);
			}

			template<class T>
			T SmoothStep(T edge0, T edge1, T x)
			{
				T t = Clamp((x - edge0) / (edge1 - edge0), T(0), T(1));
				return t*t*(T(3) - T(2)*t);
			}

			template<class T>
			T RoundUp(T value, T ratio)
			{
				T rest = value % ratio;
				if (rest == 0)
					return value;
				else
					return value + ratio - rest;
			}

			template<class T>
			T Clamp(T min_val, T max_val, T x)
			{
				return Min(Max(x, min_val), max_val);
			}

			template<class T>
			inline T Refract(T I, T N, float eta)
			{
				float k = 1.0f - eta*eta*(1.0f - N.Dot(I) * N.Dot(I));
				if (k < 0.0f)
					return T(0.0f);
				else
					return eta*I - (eta*N.Dot(I) + sqrt(k))*N;
			}

			template<class T>
			inline T Reflect(T I, T N)
			{
				return I - N.Dot(N, I) * N;
			}

			template<class T>
			inline T FaceForward(T N, T I, T Nref)
			{
				if (Nref.Dot(I) < 0)
					return N;
				return -N;
			}
			template<class T>
			inline T Mix(T x, T y, float a)
			{
				return x*(1 - a) + y*a;
			}

			PUNK_ENGINE_API const vec3 CalculateNormal(const vec3& p1, const vec3& p2, const vec3& p3);
			PUNK_ENGINE_API void CalculateTBN(const vec3& p1, const vec3& p2, const vec3& p3,
				const vec2& tex1, const vec2& tex2, const vec2& tex3,
				vec3& tng, vec3& btn, vec3& nrm, float& mm);
		}
	}
}

#endif

#ifndef _H_PUNK_MATH_POLYGON_3D
#define _H_PUNK_MATH_POLYGON_3D

#include <vector>
#include "config.h"
#include "tuple.h"
#include "plane.h"

PUNK_ENGINE_BEGIN
namespace Math {

	template<class T, int Dim> class Polygon;

    template<class T, int Dim>
    struct PolygonData {
        std::vector<Tuple<T, 3, tagPoint>> m_points;
    };

    template<class T>
    struct PolygonData<T, 3> {
        std::vector<Tuple<T, 3, tagPoint>> m_points;
        bool m_is_planar{true};
    };

    template<class T, int Dim>
    struct PolygonAccessorBase : public PolygonData<T, Dim> {
        using PolygonData<T, Dim>::PolygonData;

		PolygonAccessorBase() {}

		PolygonAccessorBase(const PolygonData<T, Dim>& value) 
			: PolygonData<T, Dim>(value) {}

        std::uint32_t GetCount() const {
            return (std::uint32_t)this->m_points.size();
        }

        const Tuple<T, Dim, tagPoint>& operator [] (std::uint32_t index) const {
            return this->m_points[index];
        }

        Tuple<T, Dim, tagPoint>& operator [] (std::uint32_t index) {
            return this->m_points[index];
        }

        const Tuple<T, Dim, tagPoint>* GetPoints() const {
            return this->m_points.data();
        }

        bool IsTriangle() const {
            return this->m_points.size() == 3;
        }
    };

    template<class T, int Dim>
    struct PolygonAccessor : public PolygonAccessorBase<T, Dim> {
        using PolygonAccessorBase<T, Dim>::PolygonAccessorBase;

		PolygonAccessor() {}

		PolygonAccessor(const PolygonData<T, Dim>& value)
			: PolygonAccessorBase<T, Dim>(value) {}
    };

    template<class T>
    struct PolygonAccessor<T, 3> : public PolygonAccessorBase<T, 3> {
        using PolygonAccessorBase<T, 3>::PolygonAccessorBase;

		PolygonAccessor() {}

		PolygonAccessor(const PolygonData<T, 3>& value)
			: PolygonAccessorBase<T, 3>(value) {}

        bool IsPlanar() const {
            return this->m_is_planar;
        }
    };

    template<class T, int Dim>
    struct PolygonOperationsBase : public PolygonAccessor<T, Dim> {
        using PolygonAccessor<T, Dim>::PolygonAccessor;

		PolygonOperationsBase() {}

		PolygonOperationsBase(const PolygonData<T, Dim>& value)
			: PolygonAccessor<T, Dim>(value) {}
    };

    template<class T, int Dim>
    struct PolygonOperations : public PolygonOperationsBase<T, Dim> {

        using PolygonOperationsBase<T, Dim>::PolygonOperationsBase;

		PolygonOperations() {}

		PolygonOperations(const PolygonData<T, Dim>& value)
			: PolygonOperationsBase<T, Dim>(value) {}
    };

    template<class T>
    struct PolygonOperations<T, 3> : public PolygonOperationsBase<T, 3> {
        using PolygonOperationsBase<T, 3>::PolygonOperationsBase;

        void MakePlanar() {
            return *this;
        }

		PolygonOperations() {}

		PolygonOperations(const PolygonData<T, 3>& value)
			: PolygonOperationsBase<T, 3>(value) {}

		Relation CrossPlane(const TPlane<T>& plane, Polygon<T, 3>& front, Polygon<T, 3>& back)
		{
            (void)plane; (void)front; (void)back;
		}

    };

    template<class T, int Dim>
    class Polygon : public PolygonOperations<T, Dim> {
    public:
        using PolygonOperations<T, Dim>::PolygonOperations;

		Polygon() {}

		Polygon(const PolygonData<T, Dim>& value)
			: PolygonOperations<T, Dim>(value) {}
    };
}
PUNK_ENGINE_END

#endif

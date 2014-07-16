#include "tuple.h"

PUNK_ENGINE_BEGIN
namespace Math {

	void f() {
		TupleData<float, 3, tagVector> tuple{ 1, 2, 3 };
		tuple.m_v[0] = 1;

		TupleComponentAccessorBase<float, 3, tagVector> component_base{ 1, 2, 3 };
		component_base[0] = 2;

		{
			TupleComponentAccessor<float, 2, tagVector> component{ 1, 2 };
			component[0] = 3;
			component.X();
		}
		
		{
			TupleComponentAccessor<float, 3, tagVector> component{ 1, 2, 3 };
			component[0] = 3;
			component.XZY();
		}
	}
}
PUNK_ENGINE_END

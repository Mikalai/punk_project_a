#include "tuple.h"

PUNK_ENGINE_BEGIN
namespace Math {

	void f() {
		TupleData<float, 3, tagVector> tuple{ { 1, 2, 3 } };	
        tuple.m_v[0] = 1;

        TupleComponentAccessorBase<float, 3, tagVector> component_base{tuple};
        component_base[0] = 2;

        {
            TupleComponentAccessor<float, 2, tagVector> component{ 1, 2 };
            component[0] = 3;
            component.X();
        }
		
        {
            TupleComponentAccessor<float, 3, tagVector> component{ tuple };
            component[0] = 3;
            component.XZY();
        }

        {
            TupleComponentAccessor<float, 4, tagVector> component{ tuple };
            component[0] = 3;
            Tuple<float, 4, tagVector> v = component.XZYW();
        }
        {
            Tuple<float, 4, tagVector> c{1, 2, 3, 4};
            c.X();
        }
	}
}
PUNK_ENGINE_END

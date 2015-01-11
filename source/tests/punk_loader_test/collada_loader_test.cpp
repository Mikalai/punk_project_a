#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <loader/module.h>
#include <system/factory/module.h>
#include <attributes/data_flow/module.h>
#include <string/buffer.h>
#include <math/absolute_value.h>

using namespace Punk::Engine;
using namespace IoModule;
using namespace Attributes;

class ColladaLoaderTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(ColladaLoaderTest);
	CPPUNIT_TEST(testFloatArray);
	CPPUNIT_TEST(testAccessor);
	CPPUNIT_TEST(testParam);
	CPPUNIT_TEST(testSource);
	CPPUNIT_TEST(testInput);
	CPPUNIT_TEST_SUITE_END();
public:

	void testFloatArray() {
		try {
			//auto system = System::LoadPunkModule("punk_system");
			auto loader = System::LoadPunkModule("punk_loader");

			auto reader = NewColladaReader();

			Core::Buffer buffer;
			buffer.WriteString("<float_array id=\"Cube - mesh - normals - array\" count=\"36\">0 0 -1 0 0 1 1 -5.66244e-7 -2.38419e-7 -4.76837e-7 -1 -2.98023e-7 -1 2.08616e-7 -1.49012e-7 2.08616e-7 1 1.78814e-7 0 0 -1 0 0 1 1 0 3.27826e-7 0 -1 0 -1 2.38419e-7 -1.19209e-7 2.68221e-7 1 2.38419e-7</float_array>");
			buffer.SetPosition(0);

			auto o = reader->Read(buffer);

			auto float_array = Core::QueryInterfacePtr<Attributes::IFloatArray>(o, Attributes::IID_IFloatArray);
			CPPUNIT_ASSERT(float_array->GetId() == "Cube - mesh - normals - array");
			CPPUNIT_ASSERT(float_array->GetCount() == 36);

			float res[] = { 0, 0, -1, 0, 0, 1, 1, -5.66244e-7, -2.38419e-7, -4.76837e-7, -1, -2.98023e-7, -1, 2.08616e-7, -1.49012e-7
				, 2.08616e-7, 1, 1.78814e-7, 0, 0, -1, 0, 0, 1, 1, 0, 3.27826e-7, 0, -1, 0, -1, 2.38419e-7, -1.19209e-7, 2.68221e-7, 1, 2.38419e-7 };

			for (int i = 0, max_i = float_array->GetCount(); i < max_i; ++i) {
				CPPUNIT_ASSERT(Math::Abs(res[i] - float_array->GetValue(i)) < 1e-6);
			}
		}
		catch (System::Error::SystemException& e) {
			System::GetDefaultLogger()->Error(e.Message());
			CPPUNIT_ASSERT(false);
		}
	}

	void testAccessor() {
		try {
			//auto system = System::LoadPunkModule("punk_system");
			auto loader = System::LoadPunkModule("punk_loader");

			auto reader = NewColladaReader();

			Core::Buffer buffer;
			buffer.WriteString("<accessor source = \"#Cube - mesh - positions - array\" count = \"8\" stride = \"3\">\
				<param name=\"X\" type=\"float\" />\
				<param name=\"Y\" type=\"float\" />\
				<param name=\"Z\" type=\"float\" />\
				</accessor>");
			buffer.SetPosition(0);

			auto o = reader->Read(buffer);

			auto accessor = Core::QueryInterfacePtr<Attributes::IAccessor>(o, Attributes::IID_IAccessor);
			CPPUNIT_ASSERT(accessor->GetSource() == "#Cube - mesh - positions - array");
			CPPUNIT_ASSERT(accessor->GetCount() == 8);
			CPPUNIT_ASSERT(accessor->GetOffset() == 0);
			CPPUNIT_ASSERT(accessor->GetStride() == 3);
			CPPUNIT_ASSERT(accessor->GetParamsCount() == 3);

			for (int i = 0, max_i = accessor->GetParamsCount(); i < max_i; ++i) {
				auto p = accessor->GetParam(i);
				if (i == 0) {
					CPPUNIT_ASSERT(p->GetName() == "X");
				}
				else if (i == 1) {
					CPPUNIT_ASSERT(p->GetName() == "Y");
				}
				else if (i == 2) {
					CPPUNIT_ASSERT(p->GetName() == "Z");
				}
				CPPUNIT_ASSERT(p->GetType() == Attributes::ParamType::Float);
			}
		}
		catch (System::Error::SystemException& e) {
			System::GetDefaultLogger()->Error(e.Message());
			CPPUNIT_ASSERT(false);
		}			
	}

	void testParam() {		
		try {
			//auto system = System::LoadPunkModule("punk_system");
			auto loader = System::LoadPunkModule("punk_loader");

			auto reader = NewColladaReader(); 

			Core::Buffer buffer;
			buffer.WriteString("<param name=\"X\" type=\"float\" />");
			buffer.SetPosition(0);

			auto o = reader->Read(buffer);

			auto param = Core::QueryInterfacePtr<Attributes::IParam>(o, Attributes::IID_IParam);
			CPPUNIT_ASSERT(param->GetName() == "X");
			CPPUNIT_ASSERT(param->GetType() == Attributes::ParamType::Float);
		}
		catch (System::Error::SystemException& e) {
			System::GetDefaultLogger()->Error(e.Message());
			CPPUNIT_ASSERT(false);
		}
	}

	void testSource() {
		using namespace IoModule;
		try {
			auto loader = System::LoadPunkModule("punk_loader");

			auto reader = NewColladaReader();

			Core::Buffer buffer;
			buffer.WriteString("<source id=\"Cube-mesh-positions\">\
				<float_array id = \"Cube-mesh-positions-array\" count = \"24\">1 1 -1 1 -1 -1 -1 -0.9999998 -1 -0.9999997 1 -1 1 0.9999995 1 0.9999994 -1.000001 1 -1 -0.9999997 1 -1 1 1 </float_array>\
				<technique_common>\
				<accessor source = \"#Cube-mesh-positions-array\" count = \"8\" stride = \"3\">\
				<param name = \"X\" type = \"float\" />\
				<param name = \"Y\" type = \"float\" />\
				<param name = \"Z\" type = \"float\" />\
				</accessor>\
				</technique_common>\
				</source>");
			buffer.SetPosition(0);

			auto o = reader->Read(buffer);

			auto source = Core::QueryInterfacePtr<Attributes::ISource>(o, Attributes::IID_ISource);
			CPPUNIT_ASSERT(source);
			auto accessor = source->GetAccessor();
			CPPUNIT_ASSERT(accessor);
			CPPUNIT_ASSERT(source->GetId() == "Cube-mesh-positions");
			
			auto float_array = Core::QueryInterfacePtr<IFloatArray>(source->GetArray(), IID_IFloatArray);

			CPPUNIT_ASSERT(float_array->GetId() == "Cube-mesh-positions-array");
			CPPUNIT_ASSERT(float_array->GetCount() == 24);

			float res[] = { 1, 1, -1, 1, -1, -1, -1, -0.9999998, -1, -0.9999997, 1, -1, 1, 0.9999995, 1, 0.9999994, -1.000001, 1, -1, -0.9999997, 1, -1, 1, 1 };

			for (int i = 0, max_i = float_array->GetCount(); i < max_i; ++i) {
				CPPUNIT_ASSERT(Math::Abs(res[i] - float_array->GetValue(i)) < 1e-6);
			}
			
			CPPUNIT_ASSERT(accessor->GetSource() == "#Cube-mesh-positions-array");
			CPPUNIT_ASSERT(accessor->GetCount() == 8);
			CPPUNIT_ASSERT(accessor->GetOffset() == 0);
			CPPUNIT_ASSERT(accessor->GetStride() == 3);
			CPPUNIT_ASSERT(accessor->GetParamsCount() == 3);

			for (int i = 0, max_i = accessor->GetParamsCount(); i < max_i; ++i) {
				auto p = accessor->GetParam(i);
				if (i == 0) {
					CPPUNIT_ASSERT(p->GetName() == "X");
				}
				else if (i == 1) {
					CPPUNIT_ASSERT(p->GetName() == "Y");
				}
				else if (i == 2) {
					CPPUNIT_ASSERT(p->GetName() == "Z");
				}
				CPPUNIT_ASSERT(p->GetType() == Attributes::ParamType::Float);
			}
		}
		catch (System::Error::SystemException& e) {
			System::GetDefaultLogger()->Error(e.Message());
			CPPUNIT_ASSERT(false);
		}
	}

	void testInput() {
		try {
			//auto system = System::LoadPunkModule("punk_system");
			auto loader = System::LoadPunkModule("punk_loader");

			auto reader = NewColladaReader();

			Core::Buffer buffer;
			buffer.WriteString("<input semantic=\"POSITION\" source=\"#Cube-mesh-positions\"/>");
			buffer.SetPosition(0);

			auto o = reader->Read(buffer);

			auto input = Core::QueryInterfacePtr<Attributes::IInput>(o, Attributes::IID_IInput);
			CPPUNIT_ASSERT(input);
			CPPUNIT_ASSERT(input->GetSemantic() == InputSemantic::Position);
			CPPUNIT_ASSERT(input->GetSourceRef() == "#Cube-mesh-positions");
		}
		catch (System::Error::SystemException& e) {
			System::GetDefaultLogger()->Error(e.Message());
			CPPUNIT_ASSERT(false);
		}
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(ColladaLoaderTest);

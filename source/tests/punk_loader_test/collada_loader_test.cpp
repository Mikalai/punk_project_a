#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <loader/module.h>
#include <system/factory/module.h>
#include <attributes/data_flow/module.h>
#include <string/buffer.h>
#include <math/absolute_value.h>

using namespace Punk::Engine;

class ColladaLoaderTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(ColladaLoaderTest);
	CPPUNIT_TEST(test1);
	CPPUNIT_TEST(test2);
	CPPUNIT_TEST(test3);
	CPPUNIT_TEST_SUITE_END();
public:

	void test1() {
		try {
			//auto system = System::LoadPunkModule("punk_system");
			auto loader = System::LoadPunkModule("punk_loader");

			auto reader = System::CreateInstancePtr<IoModule::IReader>(IoModule::CLSID_ColladaReader, IoModule::IID_IReader);

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

	void test2() {
		try {
			//auto system = System::LoadPunkModule("punk_system");
			auto loader = System::LoadPunkModule("punk_loader");

			auto reader = System::CreateInstancePtr<IoModule::IReader>(IoModule::CLSID_ColladaReader, IoModule::IID_IReader);

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

	void test3() {
		try {
			//auto system = System::LoadPunkModule("punk_system");
			auto loader = System::LoadPunkModule("punk_loader");

			auto reader = System::CreateInstancePtr<IoModule::IReader>(IoModule::CLSID_ColladaReader, IoModule::IID_IReader);

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
};

CPPUNIT_TEST_SUITE_REGISTRATION(ColladaLoaderTest);

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <loader/module.h>
#include <system/factory/module.h>
#include <attributes/data_flow/module.h>
#include <attributes/geometry/module.h>
#include <attributes/camera/module.h>
#include <string/buffer.h>
#include <math/absolute_value.h>

using namespace Punk::Engine;
using namespace Math;
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
	CPPUNIT_TEST(testVertices);
	CPPUNIT_TEST(testInputShared);
	CPPUNIT_TEST(testVertexCountList);
	CPPUNIT_TEST(testPrimitivesList);
	CPPUNIT_TEST(testPolylist);
	CPPUNIT_TEST(testMesh);
	CPPUNIT_TEST(testGeometry);
	CPPUNIT_TEST(testLibraryGeometries);
	CPPUNIT_TEST(testPerspective);
	CPPUNIT_TEST(testOptics);
	CPPUNIT_TEST(testCamera);
	CPPUNIT_TEST(testLibraryCameras);
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

	void testInputShared() {
		try {
			//auto system = System::LoadPunkModule("punk_system");
			auto loader = System::LoadPunkModule("punk_loader");

			auto reader = NewColladaReader();

			Core::Buffer buffer;
			buffer.WriteString("<input semantic=\"VERTEX\" source=\"#Cube-mesh-vertices\" offset=\"1\"/>");
			buffer.SetPosition(0);

			auto o = reader->Read(buffer);

			auto input = Core::QueryInterfacePtr<Attributes::IInputShared>(o, Attributes::IID_IInputShared);
			CPPUNIT_ASSERT(input);
			CPPUNIT_ASSERT(input->GetSemantic() == InputSemantic::Vertex);
			CPPUNIT_ASSERT(input->GetSourceRef() == "#Cube-mesh-vertices");
			CPPUNIT_ASSERT(input->GetOffset() == 1);
		}
		catch (System::Error::SystemException& e) {
			System::GetDefaultLogger()->Error(e.Message());
			CPPUNIT_ASSERT(false);
		}
	}

	void testVertices() {
		try {
			//auto system = System::LoadPunkModule("punk_system");
			auto loader = System::LoadPunkModule("punk_loader");

			auto reader = NewColladaReader();

			Core::Buffer buffer;
			buffer.WriteString("<vertices id=\"Cube-mesh-vertices\">\
							   				<input semantic=\"POSITION\" source=\"#Cube-mesh-positions\"/>\
															</vertices>");
			buffer.SetPosition(0);

			auto o = reader->Read(buffer);

			auto vertices = Core::QueryInterfacePtr<Attributes::IVertices>(o, Attributes::IID_IVertices);
			CPPUNIT_ASSERT(vertices);
			CPPUNIT_ASSERT(vertices->GetId() == "Cube-mesh-vertices");
			CPPUNIT_ASSERT(vertices->GetInputsCount() == 1);
			auto input = vertices->GetInput(0);
			CPPUNIT_ASSERT(input);
			CPPUNIT_ASSERT(input->GetSemantic() == InputSemantic::Position);
			CPPUNIT_ASSERT(input->GetSourceRef() == "#Cube-mesh-positions");
		}
		catch (System::Error::SystemException& e) {
			System::GetDefaultLogger()->Error(e.Message());
			CPPUNIT_ASSERT(false);
		}
	}

	void testVertexCountList() {
		try {
			//auto system = System::LoadPunkModule("punk_system");
			auto loader = System::LoadPunkModule("punk_loader");

			auto reader = NewColladaReader();

			Core::Buffer buffer;
			buffer.WriteString("<vcount>3 3 3 3 3 3 3 3 3 3 3 3 </vcount>");
			buffer.SetPosition(0);

			auto o = reader->Read(buffer);

			auto vcount = Core::QueryInterfacePtr<Attributes::IVertexCountList>(o, Attributes::IID_IVertexCountList);
			CPPUNIT_ASSERT(vcount);
			CPPUNIT_ASSERT(vcount->GetSize() == 12);
			for (int i = 0; i < (int)vcount->GetSize(); ++i) {
				auto v = vcount->GetValue(i);
				CPPUNIT_ASSERT(v == 3);
			}
		}
		catch (System::Error::SystemException& e) {
			System::GetDefaultLogger()->Error(e.Message());
			CPPUNIT_ASSERT(false);
		}
	}

	void testPrimitivesList() {
		try {
			//auto system = System::LoadPunkModule("punk_system");
			auto loader = System::LoadPunkModule("punk_loader");

			auto reader = NewColladaReader();

			Core::Buffer buffer;
			buffer.WriteString("<p>1 0 2 0 3 0 7 1 6 1 5 1 0 2 4 2 5 2 1 3 5 3 6 3 6 4 7 4 3 4 0 5 3 5 7 5 0 6 1 6 3 6 4 7 7 7 5 7 1 8 0 8 5 8 2 9 1 9 6 9 2 10 6 10 3 10 4 11 0 11 7 11</p>");
			buffer.SetPosition(0);

			auto o = reader->Read(buffer);

			auto p = Core::QueryInterfacePtr<Attributes::IPrimitivesList>(o, Attributes::IID_IPrimitivesList);
			CPPUNIT_ASSERT(p);
			CPPUNIT_ASSERT(p->GetSize() == 72);

			int res[] = { 1, 0, 2, 0, 3, 0, 7, 1, 6, 1, 5, 1, 0, 2, 4, 2, 5, 2, 1, 3, 5, 3, 6, 3, 6, 4, 7, 4, 3, 4, 0, 5, 3, 5, 7, 5, 0, 6, 1, 6, 3, 6, 4, 7, 7, 7, 5, 7, 1, 8, 0, 8, 5, 8, 2, 9, 1, 9, 6, 9, 2, 10, 6, 10, 3, 10, 4, 11, 0, 11, 7, 11 };
			for (int i = 0; i < (int)p->GetSize(); ++i) {
				auto v = p->GetValue(i);
				CPPUNIT_ASSERT(v == res[i]);
			}
		}
		catch (System::Error::SystemException& e) {
			System::GetDefaultLogger()->Error(e.Message());
			CPPUNIT_ASSERT(false);
		}
	}

	void testPolylist() {
		try {
			//auto system = System::LoadPunkModule("punk_system");
			auto loader = System::LoadPunkModule("punk_loader");

			auto reader = NewColladaReader();

			Core::Buffer buffer;
			buffer.WriteString("<polylist material=\"Material-material\" count=\"12\">\
							   				<input semantic=\"VERTEX\" source=\"#Cube-mesh-vertices\" offset=\"0\"/> \
															<input semantic=\"NORMAL\" source=\"#Cube-mesh-normals\" offset=\"1\"/> \
																			<vcount>3 3 3 3 3 3 3 3 3 3 3 3 </vcount>\
																							<p>1 0 2 0 3 0 7 1 6 1 5 1 0 2 4 2 5 2 1 3 5 3 6 3 6 4 7 4 3 4 0 5 3 5 7 5 0 6 1 6 3 6 4 7 7 7 5 7 1 8 0 8 5 8 2 9 1 9 6 9 2 10 6 10 3 10 4 11 0 11 7 11</p>\
																											</polylist>\
																															");

			buffer.SetPosition(0);

			auto o = reader->Read(buffer);

			auto p = Core::QueryInterfacePtr<Attributes::IPolyList>(o, Attributes::IID_IPolyList);

			CPPUNIT_ASSERT(p);
			CPPUNIT_ASSERT(p->GetSize() == 12);
			CPPUNIT_ASSERT(p->GetMaterialRef() == "Material-material");
			auto input_count = p->GetInputsCount();
			CPPUNIT_ASSERT(input_count == 2);

			for (int i = 0; i < input_count; ++i) {
				auto input = p->GetInput(i);
				CPPUNIT_ASSERT(input);
				if (i == 0) {
					CPPUNIT_ASSERT(input->GetSemantic() == Attributes::InputSemantic::Vertex);
					CPPUNIT_ASSERT(input->GetSourceRef() == "#Cube-mesh-vertices");
					CPPUNIT_ASSERT(input->GetOffset() == 0);
				}
				else if (i == 1) {
					CPPUNIT_ASSERT(input->GetSemantic() == Attributes::InputSemantic::Normal);
					CPPUNIT_ASSERT(input->GetSourceRef() == "#Cube-mesh-normals");
					CPPUNIT_ASSERT(input->GetOffset() == 1);
				}
			}

			auto vcount = p->GetVertexCountList();
			CPPUNIT_ASSERT(vcount);
			CPPUNIT_ASSERT(vcount->GetSize() == 12);
			for (int i = 0; i < (int)vcount->GetSize(); ++i) {
				auto v = vcount->GetValue(i);
				CPPUNIT_ASSERT(v == 3);
			}

			auto primitives = p->GetPrimitivesList();
			CPPUNIT_ASSERT(primitives);
			CPPUNIT_ASSERT(primitives->GetSize() == 72);

			int res[] = { 1, 0, 2, 0, 3, 0, 7, 1, 6, 1, 5, 1, 0, 2, 4, 2, 5, 2, 1, 3, 5, 3, 6, 3, 6, 4, 7, 4, 3, 4, 0, 5, 3, 5, 7, 5, 0, 6, 1, 6, 3, 6, 4, 7, 7, 7, 5, 7, 1, 8, 0, 8, 5, 8, 2, 9, 1, 9, 6, 9, 2, 10, 6, 10, 3, 10, 4, 11, 0, 11, 7, 11 };
			for (int i = 0; i < (int)p->GetSize(); ++i) {
				auto v = primitives->GetValue(i);
				CPPUNIT_ASSERT(v == res[i]);
			}

		}
		catch (System::Error::SystemException& e) {
			System::GetDefaultLogger()->Error(e.Message());
			CPPUNIT_ASSERT(false);
		}
	}

	void testMesh() {
		try {
			//auto system = System::LoadPunkModule("punk_system");
			auto loader = System::LoadPunkModule("punk_loader");

			auto reader = NewColladaReader();

			Core::Buffer buffer;
			buffer.WriteString("<mesh>\
							   				<source id=\"Cube-mesh-positions\">\
															<float_array id=\"Cube-mesh-positions-array\" count=\"24\">1 1 -1 1 -1 -1 -1 -0.9999998 -1 -0.9999997 1 -1 1 0.9999995 1 0.9999994 -1.000001 1 -1 -0.9999997 1 -1 1 1</float_array>\
																			<technique_common>\
																							<accessor source=\"#Cube-mesh-positions-array\" count=\"8\" stride=\"3\">\
																											<param name=\"X\" type=\"float\" />\
																															<param name=\"Y\" type=\"float\" />\
																																			<param name=\"Z\" type=\"float\" />\
																																							</accessor></technique_common></source>\
																																											<source id=\"Cube-mesh-normals\">\
																																															<float_array id=\"Cube-mesh-normals-array\" count=\"36\">0 0 -1 0 0 1 1 -5.66244e-7 -2.38419e-7 -4.76837e-7 -1 -2.98023e-7 -1 2.08616e-7 -1.49012e-7 2.08616e-7 1 1.78814e-7 0 0 -1 0 0 1 1 0 3.27826e-7 0 -1 0 -1 2.38419e-7 -1.19209e-7 2.68221e-7 1 2.38419e-7</float_array>\
																																																			<technique_common>\
																																																							<accessor source=\"#Cube-mesh-normals-array\" count=\"12\" stride=\"3\">\
																																																											<param name=\"X\" type=\"float\" />\
																																																															<param name=\"Y\" type=\"float\" />\
																																																																			<param name=\"Z\" type=\"float\" />\
																																																																							</accessor></technique_common></source>\
																																																																											<vertices id=\"Cube-mesh-vertices\">\
																																																																															<input semantic=\"POSITION\" source=\"#Cube-mesh-positions\" />\
																																																																																			</vertices>\
																																																																																							<polylist material=\"Material-material\" count=\"12\">\
																																																																																											<input semantic=\"VERTEX\" source=\"#Cube-mesh-vertices\" offset=\"0\" />\
																																																																																															<input semantic=\"NORMAL\" source=\"#Cube-mesh-normals\" offset=\"1\" />\
																																																																																																			<vcount>3 3 3 3 3 3 3 3 3 3 3 3 </vcount>\
																																																																																																							<p>1 0 2 0 3 0 7 1 6 1 5 1 0 2 4 2 5 2 1 3 5 3 6 3 6 4 7 4 3 4 0 5 3 5 7 5 0 6 1 6 3 6 4 7 7 7 5 7 1 8 0 8 5 8 2 9 1 9 6 9 2 10 6 10 3 10 4 11 0 11 7 11</p>\
																																																																																																											</polylist></mesh>");

			buffer.SetPosition(0);

			auto o = reader->Read(buffer);

			auto p = Core::QueryInterfacePtr<Attributes::IMesh>(o, Attributes::IID_IMesh);

			CPPUNIT_ASSERT(p);
			auto vertices = p->GetVerices();
			CPPUNIT_ASSERT(vertices);
			CPPUNIT_ASSERT(vertices->GetId() == "Cube-mesh-vertices");
			CPPUNIT_ASSERT(vertices->GetInputsCount() == 1);
			for (int i = 0; i < vertices->GetInputsCount(); ++i) {
				auto input = vertices->GetInput(i);
				CPPUNIT_ASSERT(input);
				CPPUNIT_ASSERT(input->GetSemantic() == Attributes::InputSemantic::Position);
				CPPUNIT_ASSERT(input->GetSourceRef() == "#Cube-mesh-positions");
			}

		}
		catch (System::Error::SystemException& e) {
			System::GetDefaultLogger()->Error(e.Message());
			CPPUNIT_ASSERT(false);
		}
	}

	void testGeometry() {
		try {
			//auto system = System::LoadPunkModule("punk_system");
			auto loader = System::LoadPunkModule("punk_loader");

			auto reader = NewColladaReader();

			Core::Buffer buffer;
			buffer.WriteString("<geometry id=\"Cube-mesh\" name=\"Cube\">\
							   	<mesh>\
										<source id=\"Cube-mesh-positions\">\
													<float_array id=\"Cube-mesh-positions-array\" count=\"24\">1 1 -1 1 -1 -1 -1 -0.9999998 -1 -0.9999997 1 -1 1 0.9999995 1 0.9999994 -1.000001 1 -1 -0.9999997 1 -1 1 1</float_array>\
																<technique_common>\
																				<accessor source=\"#Cube-mesh-positions-array\" count=\"8\" stride=\"3\">\
																									<param name=\"X\" type=\"float\"/>\
																														<param name=\"Y\" type=\"float\"/>\
																																			<param name=\"Z\" type=\"float\"/>\
																																							</accessor>\
																																										</technique_common>\
																																												</source>\
																																														<source id=\"Cube-mesh-normals\">\
																																																	<float_array id=\"Cube-mesh-normals-array\" count=\"36\">0 0 -1 0 0 1 1 -5.66244e-7 -2.38419e-7 -4.76837e-7 -1 -2.98023e-7 -1 2.08616e-7 -1.49012e-7 2.08616e-7 1 1.78814e-7 0 0 -1 0 0 1 1 0 3.27826e-7 0 -1 0 -1 2.38419e-7 -1.19209e-7 2.68221e-7 1 2.38419e-7</float_array>\
																																																				<technique_common>\
																																																								<accessor source=\"#Cube-mesh-normals-array\" count=\"12\" stride=\"3\">\
																																																													<param name=\"X\" type=\"float\"/>\
																																																																		<param name=\"Y\" type=\"float\"/>\
																																																																							<param name=\"Z\" type=\"float\"/>\
																																																																											</accessor>\
																																																																														</technique_common>\
																																																																																</source>\
																																																																																		<vertices id=\"Cube-mesh-vertices\">\
																																																																																					<input semantic=\"POSITION\" source=\"#Cube-mesh-positions\"/>\
																																																																																							</vertices>\
																																																																																									<polylist material=\"Material-material\" count=\"12\">\
																																																																																												<input semantic=\"VERTEX\" source=\"#Cube-mesh-vertices\" offset=\"0\"/>\
																																																																																															<input semantic=\"NORMAL\" source=\"#Cube-mesh-normals\" offset=\"1\"/>\
																																																																																																		<vcount>3 3 3 3 3 3 3 3 3 3 3 3 </vcount>\
																																																																																																					<p>1 0 2 0 3 0 7 1 6 1 5 1 0 2 4 2 5 2 1 3 5 3 6 3 6 4 7 4 3 4 0 5 3 5 7 5 0 6 1 6 3 6 4 7 7 7 5 7 1 8 0 8 5 8 2 9 1 9 6 9 2 10 6 10 3 10 4 11 0 11 7 11</p>\
																																																																																																							</polylist>\
																																																																																																								</mesh>\
																																																																																																								</geometry>");

			buffer.SetPosition(0);

			auto o = reader->Read(buffer);

			auto p = Core::QueryInterfacePtr<Attributes::IGeometry2>(o, Attributes::IID_IGeometry2);

			CPPUNIT_ASSERT(p);
			CPPUNIT_ASSERT(p->GetId() == "Cube-mesh");
			CPPUNIT_ASSERT(p->GetName() == "Cube");

		}
		catch (System::Error::SystemException& e) {
			System::GetDefaultLogger()->Error(e.Message());
			CPPUNIT_ASSERT(false);
		}
	}

	void testLibraryGeometries() {
		try {
			//auto system = System::LoadPunkModule("punk_system");
			auto loader = System::LoadPunkModule("punk_loader");

			auto reader = NewColladaReader();

			Core::Buffer buffer;
			buffer.WriteString("<library_geometries>\
							   	<geometry id=\"Cube-mesh\" name=\"Cube\">\
										<mesh>\
													<source id=\"Cube-mesh-positions\">\
																	<float_array id=\"Cube-mesh-positions-array\" count=\"24\">1 1 -1 1 -1 -1 -1 -0.9999998 -1 -0.9999997 1 -1 1 0.9999995 1 0.9999994 -1.000001 1 -1 -0.9999997 1 -1 1 1</float_array>\
																					<technique_common>\
																										<accessor source=\"#Cube-mesh-positions-array\" count=\"8\" stride=\"3\">\
																																<param name=\"X\" type=\"float\"/>\
																																						<param name=\"Y\" type=\"float\"/>\
																																												<param name=\"Z\" type=\"float\"/>\
																																																	</accessor>\
																																																					</technique_common>\
																																																								</source>\
																																																											<source id=\"Cube-mesh-normals\">\
																																																															<float_array id=\"Cube-mesh-normals-array\" count=\"36\">0 0 -1 0 0 1 1 -5.66244e-7 -2.38419e-7 -4.76837e-7 -1 -2.98023e-7 -1 2.08616e-7 -1.49012e-7 2.08616e-7 1 1.78814e-7 0 0 -1 0 0 1 1 0 3.27826e-7 0 -1 0 -1 2.38419e-7 -1.19209e-7 2.68221e-7 1 2.38419e-7</float_array>\
																																																																			<technique_common>\
																																																																								<accessor source=\"#Cube-mesh-normals-array\" count=\"12\" stride=\"3\">\
																																																																														<param name=\"X\" type=\"float\"/>\
																																																																																				<param name=\"Y\" type=\"float\"/>\
																																																																																										<param name=\"Z\" type=\"float\"/>\
																																																																																															</accessor>\
																																																																																																			</technique_common>\
																																																																																																						</source>\
																																																																																																									<vertices id=\"Cube-mesh-vertices\">\
																																																																																																													<input semantic=\"POSITION\" source=\"#Cube-mesh-positions\"/>\
																																																																																																																</vertices>\
																																																																																																																			<polylist material=\"Material-material\" count=\"12\">\
																																																																																																																							<input semantic=\"VERTEX\" source=\"#Cube-mesh-vertices\" offset=\"0\"/>\
																																																																																																																											<input semantic=\"NORMAL\" source=\"#Cube-mesh-normals\" offset=\"1\"/>\
																																																																																																																															<vcount>3 3 3 3 3 3 3 3 3 3 3 3 </vcount>\
																																																																																																																																			<p>1 0 2 0 3 0 7 1 6 1 5 1 0 2 4 2 5 2 1 3 5 3 6 3 6 4 7 4 3 4 0 5 3 5 7 5 0 6 1 6 3 6 4 7 7 7 5 7 1 8 0 8 5 8 2 9 1 9 6 9 2 10 6 10 3 10 4 11 0 11 7 11</p>\
																																																																																																																																						</polylist>\
																																																																																																																																								</mesh>\
																																																																																																																																									</geometry>\
																																																																																																																																									</library_geometries>");

			buffer.SetPosition(0);

			auto o = reader->Read(buffer);

			auto p = Core::QueryInterfacePtr<Attributes::ILibraryGeometries>(o, Attributes::IID_ILibraryGeometries);

			CPPUNIT_ASSERT(p);
			CPPUNIT_ASSERT(p->GetGeometriesCount() == 1);

		}
		catch (System::Error::SystemException& e) {
			System::GetDefaultLogger()->Error(e.Message());
			CPPUNIT_ASSERT(false);
		}
	}

	void testPerspective() {
		try {
			//auto system = System::LoadPunkModule("punk_system");
			auto loader = System::LoadPunkModule("punk_loader");

			auto reader = NewColladaReader();

			Core::Buffer buffer;
			buffer.WriteString("<perspective>\
							   	<xfov sid=\"xfov\">49.13434</xfov>\
									<aspect_ratio>1.777778</aspect_ratio>\
										<znear sid=\"znear\">0.1</znear>\
											<zfar sid=\"zfar\">100</zfar>\
											</perspective>");

			buffer.SetPosition(0);

			auto o = reader->Read(buffer);

			auto p = Core::QueryInterfacePtr<Attributes::IPerspective>(o, Attributes::IID_IPerspective);

			CPPUNIT_ASSERT(p);
			CPPUNIT_ASSERT(AreEqual(p->GetFovX().GetValue(), DegToRad(degf{ 49.13434f }).GetValue()));
			CPPUNIT_ASSERT(AreEqual(p->GetAspectRatio().GetValue(), 1.777778f));
			CPPUNIT_ASSERT(AreEqual(p->GetZNear().GetValue(), 0.1f));
			CPPUNIT_ASSERT(AreEqual(p->GetZFar().GetValue(), 100.0f));

		}
		catch (System::Error::SystemException& e) {
			System::GetDefaultLogger()->Error(e.Message());
			CPPUNIT_ASSERT(false);
		}
	}

	void testOptics() {
		try {
			//auto system = System::LoadPunkModule("punk_system");
			auto loader = System::LoadPunkModule("punk_loader");

			auto reader = NewColladaReader();

			Core::Buffer buffer;
			buffer.WriteString("<optics><perspective>\
							   							   	<xfov sid=\"xfov\">49.13434</xfov>\
																								<aspect_ratio>1.777778</aspect_ratio>\
																																		<znear sid=\"znear\">0.1</znear>\
																																													<zfar sid=\"zfar\">100</zfar>\
																																																								</perspective></optics>");

			buffer.SetPosition(0);

			auto o = reader->Read(buffer);

			auto p = Core::QueryInterfacePtr<Attributes::IOptics>(o, Attributes::IID_IOptics);

			CPPUNIT_ASSERT(p);
			CPPUNIT_ASSERT(p->GetProjection());

		}
		catch (System::Error::SystemException& e) {
			System::GetDefaultLogger()->Error(e.Message());
			CPPUNIT_ASSERT(false);
		}
	}

	void testCamera() {
		try {
			//auto system = System::LoadPunkModule("punk_system");
			auto loader = System::LoadPunkModule("punk_loader");

			auto reader = NewColladaReader();

			Core::Buffer buffer;
			buffer.WriteString("<camera id=\"Camera-camera\" name=\"Camera\">\
							   	<optics>\
										<technique_common>\
													<perspective>\
																	<xfov sid=\"xfov\">49.13434</xfov>\
																					<aspect_ratio>1.777778</aspect_ratio>\
																									<znear sid=\"znear\">0.1</znear>\
																													<zfar sid=\"zfar\">100</zfar>\
																																</perspective>\
																																		</technique_common>\
																																			</optics>\
																																				<extra>\
																																						<technique profile=\"blender\">\
																																									<YF_dofdist>0</YF_dofdist>\
																																												<shiftx>0</shiftx>\
																																															<shifty>0</shifty>\
																																																	</technique>\
																																																		</extra>\
																																																		</camera>");

			buffer.SetPosition(0);

			auto o = reader->Read(buffer);

			auto p = Core::QueryInterfacePtr<Attributes::ICamera2>(o, Attributes::IID_ICamera2);

			CPPUNIT_ASSERT(p);
			CPPUNIT_ASSERT(p->GetOptics());
			CPPUNIT_ASSERT(p->GetId() == "Camera-camera");
			CPPUNIT_ASSERT(p->GetName() == "Camera");

		}
		catch (System::Error::SystemException& e) {
			System::GetDefaultLogger()->Error(e.Message());
			CPPUNIT_ASSERT(false);
		}
	}

	void testLibraryCameras() {
		try {
			//auto system = System::LoadPunkModule("punk_system");
			auto loader = System::LoadPunkModule("punk_loader");

			auto reader = NewColladaReader();

			Core::Buffer buffer;
			buffer.WriteString("<library_cameras id=\"id\" name=\"name\">\
    <camera id=\"Camera-camera\" name=\"Camera\">\
      <optics>\
        <technique_common>\
          <perspective>\
            <xfov sid=\"xfov\">49.13434</xfov>\
            <aspect_ratio>1.777778</aspect_ratio>\
            <znear sid=\"znear\">0.1</znear>\
            <zfar sid=\"zfar\">100</zfar>\
          </perspective>\
        </technique_common>\
      </optics>\
      <extra>\
        <technique profile=\"blender\">\
          <YF_dofdist>0</YF_dofdist>\
          <shiftx>0</shiftx>\
          <shifty>0</shifty>\
        </technique>\
      </extra>\
    </camera>\
  </library_cameras>");

			buffer.SetPosition(0);

			auto o = reader->Read(buffer);

			auto p = Core::QueryInterfacePtr<Attributes::ILibraryCameras>(o, Attributes::IID_ILibraryCameras);

			CPPUNIT_ASSERT(p);
			CPPUNIT_ASSERT(p->GetCamerasCount() == 1);
			CPPUNIT_ASSERT(p->GetId() == "id");
			CPPUNIT_ASSERT(p->GetName() == "name");

		}
		catch (System::Error::SystemException& e) {
			System::GetDefaultLogger()->Error(e.Message());
			CPPUNIT_ASSERT(false);
		}
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(ColladaLoaderTest);

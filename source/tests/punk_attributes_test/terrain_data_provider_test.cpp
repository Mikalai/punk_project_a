#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <images/module.h>
#include <system/factory/module.h>
#include <attributes/terrain/iterrain_data_provider.h>

using namespace Punk::Engine;

class TerrainDataProviderTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TerrainDataProviderTest);
	CPPUNIT_TEST(testGeneratedTerrainDataProvider);
	CPPUNIT_TEST_SUITE_END();
public:

	void testGeneratedTerrainDataProvider() {
		auto data_provider = System::CreateInstancePtr<Attributes::ITerrainDataProvider>(Attributes::CLSID_GeneratedTerrainDataProvider, Attributes::IID_ITerrainDataProvider);
		auto image = System::CreateInstancePtr<ImageModule::IImage>(ImageModule::CLSID_FloatR32Image, ImageModule::IID_IFloatR32Image);
		const int size = 2048;
		image->SetSize(size, size);
		data_provider->SetDestinationBuffer(size, size, (float*)image->GetData());
		data_provider->SetVisibleRange(0, 0, 20., 20.1);
		data_provider->SetDetailsLevel(10);
		data_provider->UpdateBuffer();

		
		ImageModule::ImageAccessor<ImageModule::ImageFormat::FloatR16> accessor{ image.get() };
		
		auto image_writer = System::CreateInstancePtr<ImageModule::IImageWriter>(ImageModule::CLSID_ImageWriter, ImageModule::IID_IImageWriter);

		image_writer->Write(image.get(), "image.tiff", ImageModule::ImageFileType::Tiff);

		/*auto image_reader = System::CreateInstancePtr<ImageModule::IImageReader>(ImageModule::CLSID_ImageReader,
			ImageModule::IID_IImageReader);*/
		
		//auto image2 = image_reader->Read("image.tiff");
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION(TerrainDataProviderTest);

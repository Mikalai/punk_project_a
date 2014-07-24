#include <memory>
#include <system/factory/module.h>
#include <images/module.h>
#include <system/logger/module.h>
#include <system/environment.h>
#include <core/iserializable.h>
#include <config.h>
#include <math/tuple.h>
#include <string/string.h>
#include "itexture_slot.h"
#include "inormal_texture_slot.h"
#include "idiffuse_texture_slot.h"
#include "ispecular_intensity_texture_slot.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class PUNK_ENGINE_LOCAL TextureSlot
		: public IDiffuseTextureSlot
		, public INormalTextureSlot
		, public ISpecularIntensityTextureSlot
		, public Core::ISerializable {
	public:

		/**
		* @brief TextureSlot Create texture slot as part of the specified material
		* @param owner Material that owns this slot. Material is responsible for deleting the texture slot.
		*/
		TextureSlot()
		{}

		~TextureSlot() {
			System::GetDefaultLogger()->Debug("TextureSlot destroyed");
		}

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) {
			if (!object)
				return;

			*object = nullptr;

			if (type == Core::IID_IObject) {
				*object = (Core::IObject*)(IDiffuseTextureSlot*)this;
				AddRef();
			}
			else if (type == IID_ITextureSlot) {
				*object = (ITextureSlot*)(IDiffuseTextureSlot*)this;
				AddRef();
			}
			else if (type == IID_IDiffuseTextureSlot) {
				*object = (IDiffuseTextureSlot*)this;
				AddRef();
			}
			else if (type == IID_INormalTextureSlot) {
				*object = (INormalTextureSlot*)this;
				AddRef();
			}
			else if (type == IID_ISpecularIntensityTextureSlot) {
				*object = (ISpecularIntensityTextureSlot*)this;
				AddRef();
			}
			else if (type == Core::IID_ISerializable) {
				*object = (Core::ISerializable*)this;
				AddRef();
			}				
		}

		std::uint32_t AddRef() {
			return m_ref_count.fetch_add(1);
		}

		std::uint32_t Release() {
			auto v = m_ref_count.fetch_sub(1) - 1;
			if (!v) {
				delete this;
			}
			return v;
		}

		//	ITextureSlot
		void SetScale(const Math::vec3& value) {
			m_scale = value;
		}

		const Math::vec3& GetScale() const {
			return m_scale;
		}

		void SetFilename(const Core::String& value) {
			m_image_filename = value;
		}

		const Core::String& GetFilename() const {
			return m_image_filename;
		}

		void SetFactor(float value) {
			m_factor = value;
		}

		float GetFactor() const {
			return m_factor;
		}

		void SetTexture(Graphics::ITexture2D* value) {
			value->AddRef();
			m_texture_2d.reset(value);
		}

		Graphics::ITexture2D* GetTexture() {
			return m_texture_2d.get();
		}

		//	ISerializable
		void Serialize(Core::Buffer& buffer) override {
			//	IObject
			buffer.WritePod(CLSID_TextureSlot);

			//	ITextureSlot
			buffer.WritePod(m_scale);
			buffer.WriteReal32(m_factor);
			buffer.WriteString(m_image_filename);			
		}

		void Deserialize(Core::Buffer& buffer) override {
			//	ITextureSlot
			buffer.ReadPod(m_scale);
			m_factor = buffer.ReadReal32();
			m_image_filename = buffer.ReadString();
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		Math::vec3 m_scale;
		Core::String m_image_filename;
		float m_factor{ 1.0f };
		Core::Pointer<Graphics::ITexture2D> m_texture_2d{ nullptr, Core::DestroyObject };		
	};

	PUNK_REGISTER_CREATOR(CLSID_TextureSlot, (System::CreateInstance<TextureSlot, IDiffuseTextureSlot>));
}
PUNK_ENGINE_END

#include <sstream>
#include <stdio.h>
#include <stdexcept>
#include <vector>
#include <string.h>
#include <core/iobject_impl.h>
#include <system/factory/module.h>
#include <map>
#include <config.h>
#include <string/module.h>
#include <graphics/texture/module.h>
#include "istyle.h"

PUNK_ENGINE_BEGIN
namespace Gui
{
	/**
	*	Holds data, that influence widgets visual representation.
	*	It has a set of colors and textures for different widget states:
	*	- Default state;
	*	- Mouse over widget;
	*	- Mouse clicked widget;
	*	- Widget focused;
	*/
	class Style : public IStyle
	{
	public:

		Style() {			
			for (int i = 0; i < 4; ++i) { 
				m_image.push_back(Core::Pointer < Graphics::ITexture2D > {nullptr, Core::DestroyObject});
			}
			m_back_color[GetIndex(StylePart::BACK_COLOR)].Set(0.6f, 0.6f, 0.6f, 0.4f);
			m_back_color[GetIndex(StylePart::BACK_COLOR_FOCUSED)].Set(0.6f, 0.6f, 0.6f, 0.9f);
			m_back_color[GetIndex(StylePart::BACK_COLOR_MOUSE_OVER)].Set(0.6f, 0.6f, 0.6f, 0.5f);
			m_back_color[GetIndex(StylePart::BACK_COLOR_MOUSE_PRESSED)].Set(0.3f, 0.3f, 0.3f, 1.0f);
		}

		~Style() { }

		void QueryInterface(const Core::Guid& type, void** object) override {
			Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IStyle });
		}

		std::uint32_t AddRef() override {
			return m_ref_count.fetch_add(1);
		}

		std::uint32_t Release() override {
			auto v = m_ref_count.fetch_sub(1) - 1;
			if (!v)
				delete this;
			return v;
		}

		Core::Pointer<Graphics::ITexture2D> GetBackTexture(StylePart part) const override {
			return m_image[GetIndex(part)];
		}

		const Math::vec4& GetBackColor(StylePart part) const override {
			return m_back_color[GetIndex(part)];
		}

		void EnableTextures(bool value) override {
			m_use_textures = value;
		}

		bool IsEnabledTextures() const override {
			return m_use_textures;
		}

		void SetBackColor(StylePart part, float r, float g, float b, float a) override {
			m_back_color[GetIndex(part)].Set(r, g, b, a);
		}

		void SetFontColor(StylePart part, float r, float g, float b, float a) override {
			m_font_color[GetIndex(part)].Set(r, g, b, a);
		}

		void SetBackTexture(StylePart part, Core::Pointer<Graphics::ITexture2D> value) override {
			m_image[GetIndex(part)] = value;
		}

		void SetType(const Core::String& value) override {
			m_type = value;
		}

		const Core::String& GetType() const override {
			return m_type;
		}

		void SetFont(const Core::String& value) override {
			m_font = value;
		}

		const Core::String& GetFont() const override {
			return m_font;
		}

		void SetCursor(Core::Pointer<Graphics::ITexture2D> value) override {
			m_cursor = value;
		}

		const Core::Pointer<Graphics::ITexture2D> GetCursor() const override {
			return m_cursor;
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		Core::String m_font;
		Core::Pointer<Graphics::ITexture2D> m_cursor{ nullptr, Core::DestroyObject };
		Core::String m_type;
		bool m_use_textures;
		
		Math::vec4 m_back_color[4];
		Math::vec4 m_font_color[4];
		std::vector<Core::Pointer<Graphics::ITexture2D>> m_image;
	};

	PUNK_REGISTER_CREATOR(IID_IStyle, (System::CreateInstance<Style, IStyle>));
}
PUNK_ENGINE_END

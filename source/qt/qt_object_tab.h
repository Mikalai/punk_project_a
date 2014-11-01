#include <cstdint>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlabel.h>
#include "forms/qt_iobject_tab.ui.h"
#include <core/iobject.h>
#include <core/pointer.h>
#include <config.h>
#include "iobject_tab.h"

namespace Punk {
	namespace Engine {
		namespace Qt {

			class QtIObjectTab : public QWidget, public Gui::IObjectTab {
				Q_OBJECT
			public:
				QtIObjectTab(QWidget* widget)
					: QWidget(widget)
				{
					ui = new Ui::IObjectTab();
					ui->setupUi(this);
				}

				//	IObject
				void QueryInterface(const Core::Guid& type, void** object) override {
					if (!object)
						return;

					*object = nullptr;
					if (type == Core::IID_IObject) {
						*object = (Core::IObject*)this;
						AddRef();
					}
					else if (type == Gui::IID_IObjectTab) {
						*object = (Gui::IObjectTab*)this;
						AddRef();
					}
					else if (type == Gui::IID_ITab) {
						*object = (Gui::ITab*)this;
						AddRef();
					}
				}

				std::uint32_t AddRef() override {
					return m_ref_count.fetch_add(1);
				}

				std::uint32_t Release() override {
					auto v = m_ref_count.fetch_sub(1) - 1;
					if (!v) {
						delete this;
					}
					return v;
				}

				//	IWidget
				void Show() override {
					show();
				}

				void Hide() override {
					hide();
				}

				bool IsVisible() override {
					return isVisible();
				}

				//	IObjectTab
				void SetObject(Core::Pointer<Core::IObject> value) override {
					m_object = value;
					ui->m_address->setText(QString::number((std::uint64_t)m_object.get()));
				}

			private:
				std::atomic<std::uint32_t> m_ref_count{ 0 };
				Ui::IObjectTab* ui;
				Core::Pointer<Core::IObject> m_object{ nullptr, Core::DestroyObject };
			};

			extern "C" PUNK_ENGINE_API Gui::IObjectTab* CreateIObjectTab() {
				return new QtIObjectTab(nullptr);
			}
		}
	}
}

#include <cstdint>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlabel.h>
#include "forms/qt_icollection_tab.ui.h"
#include <core/iobject.h>
#include <core/pointer.h>
#include <config.h>
#include "icollection_tab.h"

namespace Punk {
	namespace Engine {
		namespace Qt {

			class QtCollectionTab : public QWidget, public Gui::ICollectionTab {
				Q_OBJECT
			public:
				QtCollectionTab(QWidget* widget)
					: QWidget(widget)
				{
					ui = new Ui::CollectionWidget();
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
					else if (type == Gui::IID_ICollectionTab) {
						*object = (Gui::ICollectionTab*)this;
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
				void SetObject(Core::Pointer<Attributes::ICollection> value) override {
					m_object = value;
					for (int i = 0; i < value->Size(); ++i) {
						ui->m_objects->addItem(QString::number(i));
					}
				}

			private:
				std::atomic<std::uint32_t> m_ref_count{ 0 };
				Ui::CollectionWidget* ui;
				Core::Pointer<Attributes::ICollection> m_object{ nullptr, Core::DestroyObject };
			};

			extern "C" PUNK_ENGINE_API Gui::ICollectionTab* CreateCollectionTab() {
				return new QtCollectionTab(nullptr);
			}
		}
	}
}

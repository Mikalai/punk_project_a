#include <cstdint>
#include <QtCore/qstring.h>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlabel.h>
#include "forms/qt_tab_holder.ui.h"
#include <core/iobject.h>
#include <core/pointer.h>
#include <config.h>
#include "itab.h"
#include "itab_holder.h"

namespace Punk {
	namespace Engine {
		namespace Qt {

			class QtTabHolder : public QWidget, public Gui::ITabHolder {
				Q_OBJECT
			public:
				QtTabHolder(QWidget* widget)
					: QWidget(widget)
				{
					ui = new Ui::QtTabHolder();
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
					else if (type == Gui::IID_ITabHolder) {
						*object = (Gui::ITabHolder*)this;
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
				void AddTab(const Core::String& name, Core::Pointer<Gui::ITab> value) override {
					m_tabs.push_back(value);
					QWidget* w = dynamic_cast<QWidget*>(value.get());
					QString s("Some tab");
					ui->tabWidget->addTab(w, s);
				}

				void RemoveTab(const Core::String& name) override {

				}

				void RemoveTab(Core::Pointer<Gui::ITab> value) override {
					auto it = std::find_if(m_tabs.begin(), m_tabs.end(), [&value](Core::Pointer<Gui::ITab>& v) {
						return value == v;
					});

					if (it == m_tabs.end())
						return;
					m_tabs.erase(it);
				}

			private:
				std::atomic<std::uint32_t> m_ref_count{ 0 };
				Ui::QtTabHolder* ui;
				Core::Pointer<Core::IObject> m_object{ nullptr, Core::DestroyObject };
				std::vector<Core::Pointer<Gui::ITab>> m_tabs;
			};

			extern "C" PUNK_ENGINE_API Gui::ITabHolder* CreateTabHolder() {
				auto w = new QtTabHolder(nullptr);
				w->show();
				return w;
			}
		}
	}
}

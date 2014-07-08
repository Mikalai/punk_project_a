#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <vector>
#include <config.h>
#include "ivertex_array.h"
#include "vertex.h"

PUNK_ENGINE_BEGIN
namespace Graphics {

    template<typename VertexType> class VertexArray : public IVertexArray {
    public:

        VertexArray(const std::vector<VertexType>& array)
            : m_array(array) {}

        VertexArray(VertexType* buffer, std::uint64_t size) {
            m_array.resize(size);
            for (auto i = 0; i < size; ++i) {
                m_array.push_back(*((VertexType*)buffer+i));
            }
        }

        virtual ~VertexArray() {}

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) {
			Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IVertexArray });
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

		//	IVertexArray
        std::uint64_t GetVertexType() const override {
            return VertexType::Value();
        }

        std::uint64_t GetVertexSize() const override {
            return sizeof(VertexType);
        }

        std::uint64_t GetVertexCount() const override {
            return m_array.size();
        }

        std::uint64_t GetMemoryUsage() const override {
            return GetVertexCount()*GetVertexSize();
        }

        VertexType* GetVertexBuffer() {
            return &m_array[0];
        }

		const VertexType* GetVertexBuffer() const {
            return &m_array[0];
        }
    private:
		
		void* GetBuffer() override {
			return (void*)&m_array[0];
		}

		const void* GetBuffer() const override {
			return (const void*)&m_array[0];
		}

		std::atomic<std::uint32_t> m_ref_count{ 0 };
        std::vector<VertexType> m_array;
    };
}
PUNK_ENGINE_END

#endif // VERTEX_ARRAY_H

#ifndef _H_PUNK_ENGINE_SYSTEM_ACTION
#define _H_PUNK_ENGINE_SYSTEM_ACTION

#include <algorithm>
#include <vector>
#include <cstdint>
#include <atomic>
#include "config.h"
#include "iobject_impl.h"
//#include <core/atomicint.h>

PUNK_ENGINE_BEGIN
namespace Core {
	/**
			*	A set of template classes that represent one action.
			*	Action can encapsulate method and object, or be just
			*	a simple function.
			*	When action is activated it is possible to provide
			*	several parameters.
			*
			*   Can be viewed as a command (action) pattern
			*/
	class MetaAction : public Core::IObject
	{
	public:

		void QueryInterface(const Core::Guid& type, void** o) override {
			if (!o)
				return;
			Core::QueryInterface(this, type, o, { Core::IID_IObject });
		}

		std::uint32_t AddRef() override
		{
			return m_ref_count.fetch_add(1);
		}

		std::uint32_t Release() override
		{
			auto v = m_ref_count.fetch_sub(1) - 1;
			if (!v)
				delete this;
			return v;
		}

		virtual ~MetaAction() {}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
	};

	template<typename... Types>
	class ActionBase : public MetaAction
	{
	public:
		virtual void operator () (Types...) = 0;
		virtual bool IsOwner(void* o) const = 0;
	};

	template<>
	class ActionBase<void> : public MetaAction
	{
	public:
		virtual void operator () () = 0;
		virtual bool IsOwner(void* o) const = 0;
	};

	template<class O, typename... Types>
	class Action : public ActionBase < Types... >
	{
	public:
		Action(O* object, void (O::*method)(Types...))
			: m_object(object),
			m_method(method)
		{}

		virtual void operator() (Types... value)
		{
			if (m_object && m_method)
			{
				(m_object->*m_method)(value...);
			}
		}

		bool IsOwner(void* o) const override {
			return (void*)m_object == o;
		}

	private:
		O* m_object;
		void (O::*m_method)(Types...);
	};

	template<typename... T>
	using ActionBasePtr = Core::Pointer<ActionBase<T...>>;

	template<class O>
	class Action<O, void> : public ActionBase < void >
	{
	public:
		Action(O* object, void (O::*method)())
			: m_object(object),
			m_method(method)
		{}

		virtual void operator() ()
		{
			if (m_object && m_method)
			{
				(m_object->*m_method)();
			}
		}

		bool IsOwner(void* o) const override {
			return (void*)m_object == o;
		}

	private:
		O* m_object;
		void (O::*m_method)();
	};

	template<typename... Types>
	class ActionSlot
	{
	public:
		typedef ActionBase<Types...> Action;
		typedef void(*Function)(Types...);

	private:


		typedef std::vector<Core::Pointer<Action>> MethodCollection;
		typedef std::vector<Function> FunctionCollection;

	public:

		void operator () (Types... value)
		{
			for (typename FunctionCollection::iterator it = m_functions.begin(); it != m_functions.end(); ++it)
			{
				(*it)(value...);
			}

			for (typename MethodCollection::iterator it = m_methods.begin(); it != m_methods.end(); ++it)
			{
				(*(*(*it)))(value...);
			}
		}

		void Add(Core::Pointer<Action> action)
		{
			m_methods.push_back(action);
		}

		void Add(Function f)
		{
			m_functions.push_back(f);
		}

		void Remove(Core::Pointer<Action> action)
		{
			typename MethodCollection::iterator it = std::find_if(
				m_methods.begin(),
				m_methods.end(),
				[&action](const Core::Pointer<Action>& slot) -> bool
			{
				return slot == action;
			});

			if (it == m_methods.end())
				return;
			m_methods.erase(it);
		}

		void Remove(Function f)
		{
			typename FunctionCollection::iterator it = std::find(m_functions.begin(), m_functions.end(), f);
			if (it == m_functions.end())
				return;
			m_functions.erase(it);
		}

		void RemoveOwnerActions(void* o) {
			auto it = std::find_if(m_methods.begin(), m_methods.end(), [&o](const Core::Pointer<Action>& action) -> bool {
				return action->IsOwner(o);
			});
			while (it != m_methods.end()) {
				m_methods.erase(it);
				it = std::find_if(m_methods.begin(), m_methods.end(), [&o](const Core::Pointer<Action>& action) -> bool {
					return action->IsOwner(o);
				});
			}
		}

		~ActionSlot()
		{
			while (!m_methods.empty())
			{
				m_methods.pop_back();
			}
		}

	private:

		MethodCollection m_methods;
		FunctionCollection m_functions;
	};

	template<>
	class ActionSlot < void >
	{
	public:
		typedef ActionBase<void> Action;
		typedef void(*Function)();

	private:
		typedef std::vector<Core::Pointer<Action>> MethodCollection;
		typedef std::vector<Function> FunctionCollection;

	public:

		void operator () ()
		{
			for (auto it = m_functions.begin(); it != m_functions.end(); ++it)
			{
				(*it)();
			}

			for (auto it = m_methods.begin(); it != m_methods.end(); ++it)
			{
				(*(*(*it)))();
			}
		}

		void Add(Core::Pointer<Action> action)
		{
			m_methods.push_back(action);
			//action->AddRef();
		}

		void Add(Function f)
		{
			m_functions.push_back(f);
		}

		void Remove(Core::Pointer<Action> action)
		{
			auto it = std::find(m_methods.begin(), m_methods.end(), action);
			if (it == m_methods.end())
				return;
			m_methods.erase(it);
			//action->Release();
		}

		void Remove(Function f)
		{
			auto it = std::find(m_functions.begin(), m_functions.end(), f);
			if (it == m_functions.end())
				return;
			m_functions.erase(it);
		}

		~ActionSlot()
		{
			while (!m_methods.empty())
			{
				//  m_methods.back()->Release();
				m_methods.pop_back();
			}
		}

	private:

		MethodCollection m_methods;
		FunctionCollection m_functions;
	};

	template<class O, typename... Types>
	using ActionPtr = Action<O, Types...>*;
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_ENGINE_SYSTEM_ACTION

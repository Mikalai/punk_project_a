#ifndef _H_SCENE_COMMAND
#define _H_SCENE_COMMAND

#include <config.h>
#include <typeinfo>
#include <cstdint>

PUNK_ENGINE_BEGIN
namespace Scene {

	class PUNK_ENGINE_API CommandBase {
	public:
		virtual ~CommandBase() {}
		union
		{
			struct {
				std::uint32_t index : 24;
				std::uint32_t domain : 8;				
			};
			std::uint32_t code;
		};		
	};

	template<int Domain, int Index>
	class Command : public CommandBase {
	public:
		Command() {
			domain = Domain;
			index = Index;
		}

		virtual ~Command() {}
		
		virtual std::uint64_t GetType() {
			return typeid(Command<Domain,Index>).hash_code();
		}

		static std::uint64_t Type() {
			return typeid(Command).hash_code();
		}		
	};
}
PUNK_ENGINE_END

#endif	//	_H_SCENE_COMMAND
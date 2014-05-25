#ifndef _H_SCENE_COMMAND
#define _H_SCENE_COMMAND

#include <config.h>
#include <typeinfo>
#include <cstdint>

PUNK_ENGINE_BEGIN
namespace SceneModule {

	class ISceneManager;

	static const int SceneDomain = 0;

	enum class SceneCommands {
		CmdSetSceneManager,
	};

	class PUNK_ENGINE_API CommandBase {
	public:
		virtual ~CommandBase() {}
		virtual CommandBase* Clone() { return new CommandBase(*this); }

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

		virtual Command<Domain, Index>* Clone() { return new Command<Domain, Index>(*this); }
	};

	class CmdSceneSetManager : public Command < SceneDomain, (int)SceneCommands::CmdSetSceneManager > {
	public:
		ISceneManager* manager;
		CmdSceneSetManager* Clone() { return new CmdSceneSetManager; }
	};
}
PUNK_ENGINE_END

#endif	//	_H_SCENE_COMMAND
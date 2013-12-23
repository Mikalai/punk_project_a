#ifndef _H_PUNK_ENVIRONMENT
#define _H_PUNK_ENVIRONMENT

#include <memory>
#include "config.h"

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace System
{
	class PUNK_ENGINE_API Environment
	{
	public:		
		Environment();
        void SetCurrentFolder(const Core::String& dir);
        const Core::String GetCurrentFolder();
        const Core::String GetFontFolder();
        const Core::String GetModelFolder();
        const Core::String GetTextureFolder();
        const Core::String GetMapFolder();
        const Core::String GetSaveFolder();
        const Core::String GetQuestFolder();
        const Core::String GetSoundFolder();
        const Core::String GetShaderFolder();
        const Core::String GetArmatureFolder();
        const Core::String GetWeaponFolder();
        const Core::String GetOpenCLFolder();

		static Environment* Instance();
		static void Destroy();
	private:
		static Environment* m_instance;

	};
}
PUNK_ENGINE_END

#endif

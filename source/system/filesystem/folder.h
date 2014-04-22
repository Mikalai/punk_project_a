#ifndef H_PUNK_SYSTEM_FOLDER
#define H_PUNK_SYSTEM_FOLDER

#include <config.h>
#include <String/String.h>

PUNK_ENGINE_BEGIN
namespace System
{
	class PUNK_ENGINE_API Folder
	{    
		Folder(const Folder&);
		Folder& operator = (const Folder&);
        Core::String m_folder_name;
        Core::String m_prev_folder_name;
	public:
		Folder();
		~Folder();
        bool IsContain(const Core::String&) const;
        const Core::StringList ListAllItems();
        bool Open(const Core::String& name);
		void Close();
        const Core::StringList Find(const Core::String& name) const;
        const Core::String& Name() const;

        static void DeleteFile(const Core::String& filename);
        static const Core::String GetCurrentFolder();
        static void SetCurrentFolder(const Core::String& value);
	};
}
PUNK_ENGINE_END

#endif // H_PUNK_SYSTEM_FOLDER

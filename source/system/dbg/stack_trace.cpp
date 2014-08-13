#include <string/module.h>
#include <ostream>

#ifdef _MSC_VER
#ifndef NOMINMAX
#define NOMINMAX
#endif	//	NOMINMAX
#include <Windows.h>
#ifdef _MSC_VER
#include <DbgHelp.h>
#pragma comment(lib, "dbghelp.lib")
#endif
#endif	//	MSVS
#ifdef __gnu_linux__
#include <execinfo.h>
#endif  //  __gnu_linux__

#include "stack_trace.h"
#include <system/errors/exceptions.h>

namespace Punk {
	namespace Engine {
		namespace System {

			Stack::Stack()
			{
#ifdef _MSC_VER
				if (!SymInitialize(GetCurrentProcess(), NULL, TRUE))
					throw Core::Error::CoreException(L"Unable to find initialize debug info");
#endif	//	MSVS
			}

			Stack::~Stack()
			{
#ifdef _MSC_VER
				SymCleanup(GetCurrentProcess());
#endif	//	MSVS
			}

			Core::String Stack::GetStackTrace()
			{
                Core::StringList list;

#ifdef _MSC_VER
				CONTEXT c;
				memset(&c, 0, sizeof(c));
				RtlCaptureContext(&c);

#ifdef _M_AMD64
				STACKFRAME64 stack_frame;
				memset(&stack_frame, 0, sizeof(stack_frame));
				//stack_frame.AddrPC.Offset = c.Rip;
				//stack_frame.AddrPC.Mode = AddrModeFlat;
				//stack_frame.AddrFrame.Offset = c.Rbp;
				//stack_frame.AddrFrame.Mode = AddrModeFlat;
				//stack_frame.AddrStack.Offset = c.Rsp;
				//stack_frame.AddrStack.Mode = AddrModeFlat;

				IMAGEHLP_SYMBOL64* pSym = (IMAGEHLP_SYMBOL64*)malloc(sizeof(IMAGEHLP_SYMBOL64) + 1024);
				memset(pSym, 0, sizeof(IMAGEHLP_SYMBOL64) + 1024);
				pSym->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
				pSym->MaxNameLength = 1024;

				IMAGEHLP_LINE64 line;
				memset(&line, 0, sizeof(line));
				line.SizeOfStruct = sizeof(line);				

				for (int i = 0;; i++)
				{	
					Core::String module_name;
					Core::String function;
					Core::String line_number;
					Core::String file;

					if (!StackWalk64(IMAGE_FILE_MACHINE_AMD64,
						GetCurrentProcess(),
						GetCurrentThread(),
						&stack_frame,
						&c,
						0,
						SymFunctionTableAccess64,
						SymGetModuleBase64,
						0))
					{
						list.Push(L"Can't make stack trace");
						break;
					}

					if (stack_frame.AddrPC.Offset != 0)
					{

						DWORD64 displacement;
						if (SymGetSymFromAddr64(GetCurrentProcess(), stack_frame.AddrPC.Offset, &displacement, pSym))
						{
							char buf[1024];
							/*result += Core::String(pSym->Name) + L" ";
							UnDecorateSymbolName(pSym->Name, buf, 1024, UNDNAME_NAME_ONLY);*/
							//result += Core::String(buf) + L" ";
							UnDecorateSymbolName(pSym->Name, buf, 1024, UNDNAME_COMPLETE);
							function = Core::String(buf);
						}
	
						DWORD displ = 0;
						if (SymGetLineFromAddr64(GetCurrentProcess(), stack_frame.AddrPC.Offset, &displ, &line))
						{
							line_number = Core::String::Convert((int)line.LineNumber, 10);
							file = Core::String(line.FileName);
						}

						IMAGEHLP_MODULE64 module;
						memset(&module, 0, sizeof(module));
						module.SizeOfStruct = sizeof(module);

						if (SymGetModuleInfo64(GetCurrentProcess(), stack_frame.AddrPC.Offset, &module))
						{							
							module_name = Core::String(module.ModuleName);
						}
					}

					list.Push(module_name + "!" + function + " in " + file + ":" + line_number + "\n");

					if (stack_frame.AddrReturn.Offset == 0)
						break;


				}

				free(pSym);
#endif	//	_M_AMD64
#ifdef _M_IX86
				
				STACKFRAME64 stack_frame;
				memset(&stack_frame, 0, sizeof(stack_frame));
				stack_frame.AddrPC.Offset = c.Eip;
				stack_frame.AddrPC.Mode = AddrModeFlat;
				stack_frame.AddrFrame.Offset = c.Ebp;
				stack_frame.AddrFrame.Mode = AddrModeFlat;
				stack_frame.AddrStack.Offset = c.Esp;
				stack_frame.AddrStack.Mode = AddrModeFlat;


				IMAGEHLP_SYMBOL64* pSym = (IMAGEHLP_SYMBOL64*)malloc(sizeof(IMAGEHLP_SYMBOL64)+1024);
				memset(pSym, 0, sizeof(IMAGEHLP_SYMBOL64) + 1024);
				pSym->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
				pSym->MaxNameLength = 1024;

				IMAGEHLP_LINE64 line;
				memset(&line, 0, sizeof(line));
				line.SizeOfStruct = sizeof(line);

				for (int i = 0; ; i++)
				{
					Core::String module_name;
					Core::String function;
					Core::String line_number;
					Core::String file;
					
					if (!StackWalk64(IMAGE_FILE_MACHINE_I386,
						GetCurrentProcess(),
						GetCurrentThread(),
						&stack_frame,
						&c,
						0,
						SymFunctionTableAccess64,
						SymGetModuleBase64,
						0))
					{
						list.Push(L"Can't make stack trace");
						break;
					}

					if (stack_frame.AddrPC.Offset != 0)
					{

						DWORD64 displacement;
						if (SymGetSymFromAddr64(GetCurrentProcess(), stack_frame.AddrPC.Offset, &displacement, pSym))
						{
							char buf[1024];
							/*result += Core::String(pSym->Name) + L" ";
							UnDecorateSymbolName(pSym->Name, buf, 1024, UNDNAME_NAME_ONLY);*/
							//result += Core::String(buf) + L" ";
							UnDecorateSymbolName(pSym->Name, buf, 1024, UNDNAME_COMPLETE);
							function = Core::String(buf);
						}


						DWORD displ = 0;
						if (SymGetLineFromAddr64(GetCurrentProcess(), stack_frame.AddrPC.Offset, &displ, &line))
						{
							line_number = Core::String::Convert((int)line.LineNumber, 10);
							file = Core::String(line.FileName);
						}

						IMAGEHLP_MODULE64 module;
						memset(&module, 0, sizeof(module));
						module.SizeOfStruct = sizeof(module);

						if (SymGetModuleInfo64(GetCurrentProcess(), stack_frame.AddrPC.Offset, &module))
						{
							module_name = Core::String(module.ModuleName);
						}
					}

					list.Push(module_name + "!" + function + " in " + file + ":" + line_number + "\n");

					if (stack_frame.AddrReturn.Offset == 0)
						break;


				}

				free(pSym);				

#endif	//	_M_IX86
#endif //	_MSC_VER

				return list.ToString("");
			}

		}
	}
}

#include <ostream>

#ifdef MSVS
#ifndef NOMINMAX
#define NOMINMAX
#endif	//	NOMINMAX
#include <Windows.h>
#ifdef MSVS
#include <DbgHelp.h>
#endif
#endif	//	MSVS
#ifdef __gnu_linux__
#include <execinfo.h>
#endif  //  __gnu_linux__

#include "stack_trace.h"
#include "exceptions.h"

namespace Punk {
    namespace Engine {
        namespace System {

            Stack::Stack()
            {
#ifdef MSVS
                if (!SymInitialize(GetCurrentProcess(), NULL, TRUE))
                    throw PunkException(L"Unable to find initialize debug info");
#endif	//	MSVS
            }

            Stack::~Stack()
            {
#ifdef MSVS
                SymCleanup(GetCurrentProcess());
#endif	//	MSVS
            }

            Core::String Stack::GetStackTrace()
            {
                Core::String result;
#ifdef MSVS
                CONTEXT c;
                memset(&c, 0, sizeof(c));
                RtlCaptureContext(&c);
                STACKFRAME64 stack_frame;
                memset(&stack_frame, 0, sizeof(stack_frame));
                stack_frame.AddrPC.Offset = c.Eip;
                stack_frame.AddrPC.Mode = AddrModeFlat;
                stack_frame.AddrFrame.Offset = c.Ebp;
                stack_frame.AddrFrame.Mode = AddrModeFlat;
                stack_frame.AddrStack.Offset = c.Esp;
                stack_frame.AddrStack.Mode = AddrModeFlat;



#ifdef _M_AMD64
                StackWalk64();
#endif	//	_M_AMD64
#ifdef _M_IX86
                IMAGEHLP_SYMBOL64* pSym = (IMAGEHLP_SYMBOL64*)malloc(sizeof(IMAGEHLP_SYMBOL64)+1024);
                memset(pSym, 0, sizeof(IMAGEHLP_SYMBOL64) + 1024);
                pSym->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
                pSym->MaxNameLength = 1024;

                IMAGEHLP_LINE64 line;
                memset(&line, 0, sizeof(line));
                line.SizeOfStruct = sizeof(line);

                for (int i = 0; ; i++)
                {
                    result += L"\n";
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
                        result += String(L"Can't make stack trace");
                        break;
                    }

                    if (stack_frame.AddrPC.Offset != 0)
                    {

                        DWORD64 displacement;
                        if (SymGetSymFromAddr64(GetCurrentProcess(), stack_frame.AddrPC.Offset, &displacement, pSym))
                        {
                            char buf[1024];
                            result += String(pSym->Name) + L" ";
                            UnDecorateSymbolName(pSym->Name, buf, 1024, UNDNAME_NAME_ONLY);
                            result += String(buf) + L" ";
                            UnDecorateSymbolName(pSym->Name, buf, 1024, UNDNAME_COMPLETE);
                            result += String(buf) + L" ";
                        }
                        else
                        {
                            result += String(L"Error in SymGetSymFromAddr64");
                        }

                        DWORD displ override;
                        if (SymGetLineFromAddr64(GetCurrentProcess(), stack_frame.AddrPC.Offset, &displ, &line))
                        {
                            result += String::Convert((int)line.LineNumber, 10) + L" ";
                            result += String(line.FileName) + L" ";
                        }
                        else
                        {
                            result += String(L"Error in SymGetLineFromAddr64");
                        }

                        IMAGEHLP_MODULE64 module;
                        memset(&module, 0, sizeof(module));
                        module.SizeOfStruct = sizeof(module);

                        if (SymGetModuleInfo64(GetCurrentProcess(), stack_frame.AddrPC.Offset, &module))
                        {
                            result += String(module.ModuleName) + L" ";
                            result += String(module.LoadedImageName) + L"\n";
                        }
                    }

                    if (stack_frame.AddrReturn.Offset == 0)
                        break;


                }

                free(pSym);

#endif	//	_M_IX86
#endif //	MSVS

                return result;
            }

            /// Using ILogger interface StackWalker
            Core::String Print()
            {
                Core::String res;
#ifdef MSVS
                CONTEXT c;
                memset(&c, 0, sizeof(c));
                RtlCaptureContext(&c);
                STACKFRAME64 stack_frame;
                memset(&stack_frame, 0, sizeof(stack_frame));
                stack_frame.AddrPC.Offset = c.Eip;
                stack_frame.AddrPC.Mode = AddrModeFlat;
                stack_frame.AddrFrame.Offset = c.Ebp;
                stack_frame.AddrFrame.Mode = AddrModeFlat;
                stack_frame.AddrStack.Offset = c.Esp;
                stack_frame.AddrStack.Mode = AddrModeFlat;
#ifdef _M_AMD64
                StackWalk64();
#endif
#ifdef _M_IX86

                IMAGEHLP_SYMBOL64* pSym = (IMAGEHLP_SYMBOL64*)malloc(sizeof(IMAGEHLP_SYMBOL64)+1024);
                memset(pSym, 0, sizeof(IMAGEHLP_SYMBOL64) + 1024);
                pSym->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
                pSym->MaxNameLength = 1024;

                IMAGEHLP_LINE64 line;
                memset(&line, 0, sizeof(line));
                line.SizeOfStruct = sizeof(line);
                stream << "Call stack:" << std::endl;
                for (int i = 0; ; i++)
                {
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
                        break;
                    }

                    if (stack_frame.AddrPC.Offset != 0)
                    {

                        DWORD64 displacement;
                        SymGetSymFromAddr64(GetCurrentProcess(), stack_frame.AddrPC.Offset, &displacement, pSym);
                        DWORD displ override;
                        line.FileName override;
                        line.LineNumber = -1;
                        SymGetLineFromAddr64(GetCurrentProcess(), stack_frame.AddrPC.Offset, &displ, &line);

                        IMAGEHLP_MODULE64 module;
                        memset(&module, 0, sizeof(module));
                        module.SizeOfStruct = sizeof(module);

                        SymGetModuleInfo64(GetCurrentProcess(), stack_frame.AddrPC.Offset, &module);
                        if (i != 0)
                            stream << "[" << i << "] " << module.ModuleName << "->" << ((line.FileName != 0) ? line.FileName : "NULL") << "(" <<  (int)line.LineNumber << ") : " << pSym->Name << std::endl;
                    }
                    if (stack_frame.AddrReturn.Offset == 0)
                        break;
                }
                free(pSym);
#endif	//	_M_IX86
#endif	//	MSVS
#ifdef __gnu_linux__
                const int s = 100;
                void *array[s];
                size_t size;
                char **strings;
                size_t i;

                size = backtrace (array, s);
                strings = backtrace_symbols (array, size);

                res += Core::String(L"Obtained {0} stack frames.\n").arg(size);

                for (i = 0; i < size; i++)
                {
                    res += Core::String(strings[i]) + L"\n";
                }

                free (strings);
#endif  //    __gnu_linux__
                return res;
            }
        }
    }
}

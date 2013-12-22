env = Environment()
env['CPPDEFINES'] = ['PUNK_ENGINE_EXPORTS', '_WIN32', 'NDEBUG', 'WIN32']
env['CPPPATH'] = './source'
env['CCFLAGS'] = '-std=c++11'

debug = ARGUMENTS.get('debug', 0)
if env['PLATFORM'] == 'win32':
	if int(debug):
		env.Append(CCFLAGS = ' -O0 ')
	else:
		env.Append(CCFLAGS = ' -O3 ')
					
VariantDir('build/error', 'source/error', duplicate = 0)
punk_error_env = env.Clone();
punk_error = 'bin/punk_error'
flag = ARGUMENTS.get('punk_error', 0)
if int(flag):
	punk_error_env.SharedLibrary(punk_error, Glob('build/error/*.cpp'))

VariantDir('build/string', 'source/string', duplicate = 0)
punk_string_env = env.Clone();
punk_string = 'bin/punk_string'
punk_string_env['LIBS'] = ['punk_error']
punk_string_env['LIBPATH'] = ['./bin/']
flag = ARGUMENTS.get('punk_string', 0)
if int(flag):
	punk_string_env.SharedLibrary(punk_string, Glob('build/string/*.cpp'))


punk_math_env = env.Clone();
punk_math = 'bin/punk_math'
VariantDir('build/math', 'source/math', duplicate = 0)
punk_math_env['LIBS'] = ['punk_error', 'punk_string']
punk_math_env['LIBPATH'] = ['./bin/']
flag = ARGUMENTS.get('punk_math', 0)
if int(flag):
	punk_math_env.SharedLibrary(punk_math, Glob('build/math/*.cpp'))

punk_core_env = env.Clone();
punk_core = 'bin/punk_core'
VariantDir('build/core', 'source/core', duplicate = 0)
punk_core_env['LIBS'] = ['punk_error', 'punk_string']
punk_core_env['LIBPATH'] = ['./bin/']
flag = ARGUMENTS.get('punk_core', 0)
if int(flag):
	punk_core_env.SharedLibrary(punk_core, Glob('build/core/*.cpp'))

punk_terminal_env = env.Clone();
punk_terminal = 'bin/punk_terminal'
VariantDir('build/terminal', 'source/terminal', duplicate = 0)
punk_terminal_env['LIBS'] = ['punk_error', 'punk_string', 'punk_core']
punk_terminal_env['LIBPATH'] = ['./bin/']
flag = ARGUMENTS.get('punk_terminal', 0)
if int(flag):
	punk_terminal_env.SharedLibrary(punk_terminal, Glob('build/terminal/*.cpp'))


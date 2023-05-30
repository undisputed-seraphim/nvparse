#include <string>
#include <GL/glew.h>

#if defined(_WIN32)
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#elif defined(__DARWIN_OSX__)
#  include <string>
#  include <mach-o/dyld.h>
#else
#  include <dlfcn.h>
#endif

#include "nvparse_extensions.h"

namespace {

void *getGLExtensionFuncPtr(const char *funcName) {
#if defined(_WIN32)
	return (void *)wglGetProcAddress(funcName);
#elif defined(__DARWIN_OSX__)
	std::string temp("_");
	temp += funcName;
	if (NSIsSymbolNameDefined(temp.c_str())) {
		NSSymbol symbol = NSLookupAndBindSymbol(temp.c_str());
		return NSAddressOfSymbol(symbol);
	}
	return 0;
#else
	return dlsym(0, funcName);
#endif
}

}

#define NVPARSE_LOADEXT(xtype, var)	var = (xtype)(getGLExtensionFuncPtr(#var))

Extensions::Extension_map Extensions::xmap_;

Extensions::Extensions() {
	// create a list of extension names
	const char *glextlist = reinterpret_cast<const char *>(glGetString(GL_EXTENSIONS));
	if (glextlist) {
		const char *lastptr = glextlist;
		while (*glextlist != 0) {
			if (*glextlist == ' ') {
				ext_names_.push_back(std::string(lastptr, glextlist));
				lastptr = glextlist + 1;
			}
			++glextlist;
		}
	}

	// multitexture
	NVPARSE_LOADEXT(PFNGLACTIVETEXTUREARBPROC, glActiveTextureARB);

	// GL_NV_register_combiners
	NVPARSE_LOADEXT(PFNGLCOMBINERPARAMETERFVNVPROC, glCombinerParameterfvNV);
	NVPARSE_LOADEXT(PFNGLCOMBINERPARAMETERINVPROC, glCombinerParameteriNV);
	NVPARSE_LOADEXT(PFNGLCOMBINERINPUTNVPROC, glCombinerInputNV);
	NVPARSE_LOADEXT(PFNGLCOMBINEROUTPUTNVPROC, glCombinerOutputNV);
	NVPARSE_LOADEXT(PFNGLFINALCOMBINERINPUTNVPROC, glFinalCombinerInputNV);

	// GL_NV_register_combiners2
	NVPARSE_LOADEXT(PFNGLCOMBINERSTAGEPARAMETERFVNVPROC, glCombinerStageParameterfvNV);

	// GL_NV_vertex_program
	NVPARSE_LOADEXT(PFNGLPROGRAMPARAMETER4FVNVPROC, glProgramParameter4fvNV);
	NVPARSE_LOADEXT(PFNGLTRACKMATRIXNVPROC, glTrackMatrixNV);
	NVPARSE_LOADEXT(PFNGLLOADPROGRAMNVPROC, glLoadProgramNV);
}
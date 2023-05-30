#ifndef NVPARSE_EXTENSIONS_
#define NVPARSE_EXTENSIONS_

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GL/glx.h>

class Extensions {
public:
	/** Returns an instance of the Extensions record for the current GL context.
	Do not call this method if there isn't a valid OpenGL context active!    */
	inline static const Extensions *instance();

	/** Returns true if the specified extension is supported.
	Do not call this method if there isn't a valid OpenGL context active! */
	inline bool isExtensionSupported(const char *ext) const;

	// multitexture
#ifdef GL_VERSION_1_2
	//typedef void (APIENTRY * PFNGLACTIVETEXTUREARBPROC) (GLenum texture);
#endif
	PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;

	// vertex program
	//typedef void (APIENTRY * PFNGLPROGRAMPARAMETER4FNVPROC) (GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	//typedef void (APIENTRY * PFNGLTRACKMATRIXNVPROC) (GLenum target, GLuint address, GLenum matrix, GLenum transform);
	//typedef void (APIENTRY * PFNGLLOADPROGRAMNVPROC) (GLenum target, GLuint id, GLsizei len, const GLubyte *program);

	PFNGLPROGRAMPARAMETER4FVNVPROC glProgramParameter4fvNV;
	PFNGLTRACKMATRIXNVPROC glTrackMatrixNV;
	PFNGLLOADPROGRAMNVPROC glLoadProgramNV;

	// register combiners
	//typedef void (APIENTRY * PFNGLCOMBINERPARAMETERFVNVPROC) (GLenum pname, const GLfloat *params);
	//typedef void (APIENTRY * PFNGLCOMBINERPARAMETERINVPROC) (GLenum pname, GLint param);
	//typedef void (APIENTRY * PFNGLCOMBINERSTAGEPARAMETERFVNVPROC) (GLenum stage, GLenum pname, const GLfloat *params);
	//typedef void (APIENTRY * PFNGLCOMBINERINPUTNVPROC) (GLenum stage, GLenum portion, GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage);
	//typedef void (APIENTRY * PFNGLCOMBINEROUTPUTNVPROC) (GLenum stage, GLenum portion, GLenum abOutput, GLenum cdOutput, GLenum sumOutput, GLenum scale, GLenum bias, GLboolean abDotProduct, GLboolean cdDotProduct, GLboolean muxSum);
	//typedef void (APIENTRY * PFNGLFINALCOMBINERINPUTNVPROC) (GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage);

	PFNGLCOMBINERPARAMETERFVNVPROC glCombinerParameterfvNV;
	PFNGLCOMBINERPARAMETERINVPROC glCombinerParameteriNV;
	PFNGLCOMBINERSTAGEPARAMETERFVNVPROC glCombinerStageParameterfvNV;
	PFNGLCOMBINERINPUTNVPROC glCombinerInputNV;
	PFNGLCOMBINEROUTPUTNVPROC glCombinerOutputNV;
	PFNGLFINALCOMBINERINPUTNVPROC glFinalCombinerInputNV;

protected:
	Extensions();

private:
#ifdef _WIN32
	typedef HGLRC Context_type;
#else
	typedef GLXContext Context_type;
#endif
	typedef std::map<Context_type, const Extensions *> Extension_map;
	static Extension_map xmap_;

	typedef std::vector<std::string> Extension_name_list;
	Extension_name_list ext_names_;
};

// INLINE METHODS

inline const Extensions *Extensions::instance() {
#ifdef _WIN32
	Context_type context = wglGetCurrentContext();
#else
	Context_type context = glXGetCurrentContext();
#endif
	const Extensions *xobj = xmap_[context];
	if (!xobj) {
		xobj = new Extensions;
		xmap_[context] = xobj;
	}
	return xobj;
}

inline bool Extensions::isExtensionSupported(const char *name) const {
	Extension_name_list::const_iterator i =
		std::find(ext_names_.begin(), ext_names_.end(), std::string(name));
	return i != ext_names_.end();
}

#endif
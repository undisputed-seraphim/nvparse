#include "nvparse_extensions.h"

#include "rc1.0_combiners.h"
#include "nvparse_errors.h"
#include "nvparse_externs.h"

#include <cstring>

void CombinersStruct::Validate()
{
	if (2 == numConsts &&
		cc[0].reg.bits.name == cc[1].reg.bits.name)
		errors.set("global constant set twice");

	generals.Validate(numConsts, &cc[0]);

	final.Validate();
}

void CombinersStruct::Invoke()
{
	for (int i = 0; i < numConsts; i++)
		Extensions::instance()->glCombinerParameterfvNV(cc[i].reg.bits.name, &(cc[i].v[0]));

	generals.Invoke();

	final.Invoke();
}

bool is_rc10(const char * s)
{
	return ! strncmp(s, "!!RC1.0", 7);
}


bool rc10_init_more()
{
	bool rcinit = false;
	if(rcinit == false)
	{
		if(!Extensions::instance()->isExtensionSupported("GL_NV_register_combiners"))
		{
			errors.set("unable to initialize GL_NV_register_combiners\n");
			return false;
		}
		else
		{
			rcinit = true;
		}
	}

	errors.reset();
	line_number = 1;

	return true;
}
/*
    else if(!strncmp(instring, "!!RC1.0", 7))
    {
        if(Extensions::instance()->glCombinerParameterfvNV == 0)
        {
            if(! glh_init_extensions("GL_NV_register_combiners"))
            {
                errors.set("unable to initialize GL_NV_register_combiners\n");
                free(instring);
                return;
            }
        }
        if(Extensions::instance()->glCombinerStageParameterfvNV == 0)
        {
            glh_init_extensions("GL_NV_register_combiners2");
            // Don't fail if this doesn't initialize.
            // We will run even if it doesn't exist.
        }
        errors.reset();
        line_number = 1;
        rc10_init(instring+7);
        rc10_parse();
    }
*/

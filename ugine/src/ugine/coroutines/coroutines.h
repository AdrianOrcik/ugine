#pragma once

#include "ugine/log.h"

#define CAT(X,Y) CAT2(X,Y)
#define CAT2(X,Y) X##Y

#define USABLE_LINE int(CAT(__LINE__,U)) 

#define ccrContParam void **ccrParam

#define ccrBeginContext struct ccrContextTag {int ccrLine
#define ccrEndContext(x) } *x = (struct ccrContextTag*)*ccrParam

#define ccrBegin(x)		if(!x) { *ccrParam=malloc(sizeof(*x));  x = (struct ccrContextTag*)*ccrParam;  x->ccrLine=0;}\
						if(x) switch(x->ccrLine){case 0:;

#define ccrFinish(z)	} free(*ccrParam); *ccrParam=0; return(z)
#define ccrFinishV		} free(*ccrParam); *ccrParam=0; return

#define ccrReturn(z)	\
		do{\
			((struct ccrContextTag*)*ccrParam)->ccrLine=USABLE_LINE;\
			return(z); case USABLE_LINE:;\
		}while(0)

#define ccrReturnV		\
		do{\
			((struct ccrContextTag*)*ccrParam)->ccrLine=USABLE_LINE;\
		return; case USABLE_LINE:;\
		} while(0)

#define ccrStop(z)	do{ free(*ccrParam); *ccrParam=0; return(z); }while(0)
#define ccrStopV	do{ free(*ccrParam); *ccrParam=0; return; } while(0)

#define ccrContext	void*
#define ccrAbort(ctx) do { free(ctx); ctx=0; } while(0)


class Coro
{
public:
	void macro_routine(ccrContParam)
	{
		ccrBeginContext;
		int i;
		ccrEndContext(foo);

		ccrBegin(foo);
		for (foo->i = 0; foo->i < 5; foo->i++) {
			ccrReturnV;
		}
		ccrFinishV;
	}
};

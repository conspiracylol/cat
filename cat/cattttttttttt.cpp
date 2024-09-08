#include "catcatcatcatcatcat.h"
#include "catcatcatcatcatcatcatcat.h"
#include "catcatcatcat.h"



#define DBG_MODE 0

#if DBG_MODE
void cat::catctatttttttttttttttttttttttttttt(const char* cat, ...)
{
	va_list(args);
	va_start(args, cat);

	vDbgPrintExWithPrefix("[cat] ", 0, 0, cat, args);

	va_end(args);
}
#else
void cat::catctatttttttttttttttttttttttttttt(const char* cat, ...) { return; };
#endif
#ifndef TEXT_BASED_ENGINE_ENGINE_PRINT_LINE_DEBUG_H
#define TEXT_BASED_ENGINE_ENGINE_PRINT_LINE_DEBUG_H

#include <dep/print_line.h>

namespace tbe {

template <class T>
void printLineDebug(T const & value) {
#if defined(_DEBUG) && defined(_DEBUG_OUTPUT)
	dep::printErr(value);
#endif
}

}

#endif

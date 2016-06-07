#include "check_file_exists.h"

#include <sys/stat.h>

namespace dep {

bool
checkFileExists(com::StringRef fileName)
{
	struct stat buffer;
	return (stat(fileName.c_str(), &buffer) == 0);
}



}
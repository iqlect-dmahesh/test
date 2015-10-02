#ifndef __UTILS_H__
#define __UTILS_H__

#include <iostream>

// Prints the <file : function : line> of invocation!
#define FFL {std::cout << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << std::endl;}

#endif // __UTILS_H__

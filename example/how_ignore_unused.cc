#ifndef IGNORE_UNUSED_H_
#	include "superflame/ignore_unused.h"
#endif

#include <string>

void test(std::string const & a, int b, bool c, float d) {
	superflame::ignore_unused(a, b, c, d);
}

int main() {
	test("1", 2, 3, 4.);
	return 0;
}

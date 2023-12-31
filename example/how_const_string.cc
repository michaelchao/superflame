#include <superflame/const_string.h>

void showcase_01() {
    auto s = superflame::make_constexpr_str("michaelma");
}

void showcase_02() {
    CXX_MAKE_TYPED_LITERNAL(s, "zhangfei");
}

int main() {
    showcase_01();
    return 0;
}

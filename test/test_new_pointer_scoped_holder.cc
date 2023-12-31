#include "superflame/new_pointer_scoped_holder.h"
#include <string>
#include <cassert>

struct Test {
    std::string str;
};

void testcase_01() {
    auto f = []() {
        auto * s = new Test();
        s->str = "longfei";
        return s;
    };

    DEFINE_NEW_POINTER_SCOPED_HOLDER(holder, f());
    assert(!!holder.get());
    assert(holder.get()->str == "longfei");
}

void testcase_02() {
    DEFINE_NEW_POINTER_SCOPED_HOLDER(holder, new Test());
    holder.get()->str = "michaelma";
    assert(!!holder.get());
    assert(holder.get()->str == "michaelma");
}

void testcase_03() {
    DEFINE_NEW_POINTER_SCOPED_HOLDER(holder, new Test());
    holder.get()->str = "zhangfei";
    assert(!!holder.get());
    assert(holder.get()->str == "zhangfei");
    Test * tmp = new Test();
    holder = tmp;
    assert(holder.get() == tmp);
}

int main() {
    testcase_01();
    testcase_02();
    testcase_03();
    return 0;
}
#include "superflame/attribute.h"
#include <vector>
#include <string>
#include <cassert>

void testcase_01() {
    superflame::attr::Attribute invalidAttr;
    assert(!invalidAttr.has());
}

void testcase_02() {
    std::vector<superflame::attr::Attribute> vec;
    vec.emplace_back(7);
    vec.emplace_back(std::string("michaelma"));
    assert(vec[0].has());
    assert(vec[0].as_mutable().get<int>() == 7);
    assert(vec[1].as_mutable().get<std::string>() == "michaelma");
}

void testcase_03() {
    superflame::attr::Attribute constAttr {true, superflame::attr::Attribute::RO{}};
    assert(constAttr.has());
    assert(constAttr.as_const().get<bool>() == true);
}

void testcase_04() {
    using VecString = std::vector<std::string>;
    std::vector<superflame::attr::Attribute> vec;
    vec.emplace_back(VecString{});
    assert(vec[0].as_mutable().get<VecString>().size() == 0);
    auto & vv = vec[0].as_mutable().get<VecString>();
    vv.emplace_back("liubei");
    vv.emplace_back("guanyu");
    vv.emplace_back("zhangfei");
    assert(vec[0].as_mutable().get<VecString>().size() == 3);
    int i = 0;
    auto & vv2 = vec[0].as_mutable().get<VecString>();
    for (auto & item : vv2) {
        if (0 == i) {
            assert(item == "liubei");
        } else if (1 == i) {
            assert(item == "guanyu");
        } else if (2 == i) {
            assert(item == "zhangfei");
        } else {}
        ++i;
    }

}

int main() {
    testcase_01();
    testcase_02();
    testcase_03();
    testcase_04();
    return 0;
}
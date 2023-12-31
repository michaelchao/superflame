#include "superflame/attribute.h"
#include <vector>
#include <string>
#include <cassert>

void testcase_01() {
    using VecString = std::vector<std::string>;
    superflame::attr::AttributeGroup ag;
    ag.emplace("1", superflame::attr::make_const_attribute(std::string("liubei")));
    ag.emplace("2", superflame::attr::make_const_attribute(std::string("guanyu")));
    ag.emplace("3", superflame::attr::make_const_attribute(std::string("zhangfei")));
    ag.emplace("4", superflame::attr::make_const_attribute(std::string("zhaoyun")));
    ag.emplace("5", superflame::attr::make_const_attribute(11));
    ag.emplace("6", superflame::attr::make_const_attribute(22));
    ag.emplace("7", superflame::attr::make_const_attribute(33));
    ag.emplace("8", superflame::attr::make_mutable_attribute(VecString{}));
    superflame::attr::get_mutable_value<VecString>(ag["8"]).emplace_back("weiyan");
    superflame::attr::get_mutable_value<VecString>(ag["8"]).emplace_back("huangzhong");
    superflame::attr::get_mutable_value<VecString>(ag["8"]).emplace_back("machao");

    assert(superflame::attr::get_const_value<std::string>(ag["1"]) == "liubei");
    assert(superflame::attr::get_const_value<std::string>(ag["2"]) == "guanyu");
    assert(superflame::attr::get_const_value<std::string>(ag["3"]) == "zhangfei");
    assert(superflame::attr::get_const_value<std::string>(ag["4"]) == "zhaoyun");
    assert(superflame::attr::get_const_value<int>(ag["5"]) == 11);
    assert(superflame::attr::get_const_value<int>(ag["6"]) == 22);
    assert(superflame::attr::get_const_value<int>(ag["7"]) == 33);
    assert(ag["8"].as_mutable().get<VecString>().size() == 3);
    assert(ag["8"].as_mutable().get<VecString>()[0] == "weiyan");
    assert(ag["8"].as_mutable().get<VecString>()[1] == "huangzhong");
    assert(ag["8"].as_mutable().get<VecString>()[2] == "machao");
}

int main() {
    testcase_01();
    return 0;
}

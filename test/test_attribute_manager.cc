#include "superflame/attribute_manager.h"
#include <vector>
#include <string>
#include <cassert>

void testcase_01() {
    auto domainBody = superflame::make_constexpr_str("car_body");
    superflame::AttributeManager::singleton().add_mutable_attr(domainBody, "left_window_status", 1);
    superflame::AttributeManager::singleton().add_mutable_attr(domainBody, "right_window_status", 2);
    superflame::AttributeManager::singleton().add_mutable_attr(domainBody, "up_window_status", 3);
    superflame::AttributeManager::singleton().add_mutable_attr(domainBody, "down_window_status", 4);

    auto vinCode = superflame::make_constexpr_str("vin_info");
    superflame::AttributeManager::singleton().add_const_attr(vinCode, "vin", "20231124");

    assert(superflame::AttributeManager::singleton().has_attr(domainBody, "left_window_status"));
    assert(superflame::AttributeManager::singleton().has_attr(domainBody, "right_window_status"));
    assert(superflame::AttributeManager::singleton().has_attr(domainBody, "up_window_status"));
    assert(superflame::AttributeManager::singleton().has_attr(domainBody, "down_window_status"));
    assert(superflame::AttributeManager::singleton().has_attr(vinCode, "vin"));

    assert(!superflame::AttributeManager::singleton().has_attr(domainBody, "vin"));
    assert(!superflame::AttributeManager::singleton().has_attr(vinCode, "left_window_status"));

    assert(superflame::AttributeManager::singleton().get_mutable_attr<int>(domainBody, "left_window_status") == 1);
    assert(superflame::AttributeManager::singleton().get_mutable_attr<int>(domainBody, "right_window_status") == 2);
    assert(superflame::AttributeManager::singleton().get_mutable_attr<int>(domainBody, "up_window_status") == 3);
    assert(superflame::AttributeManager::singleton().get_mutable_attr<int>(domainBody, "down_window_status") == 4);
    assert(superflame::AttributeManager::singleton().get_const_attr<std::string>(vinCode, "vin") == "20231124");
}

int main() {
    testcase_01();
    return 0;
}
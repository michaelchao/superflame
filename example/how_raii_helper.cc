#include <superflame/raii_helper.h>

void showcase_01() {
    superflame::RaiiHelper rh {[]() {
        return 0;
    }};
}

void showcase_02() {
    superflame::RaiiHelper rh {[]() {
        // This is init
    }, [](){
        // This is deinit
    }};
}

int main() {
    showcase_01();
    showcase_02();
    return 0;
}
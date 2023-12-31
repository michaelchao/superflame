#include <superflame/static_initializer.h>
#include <iostream>

class Test01 {
public:
    static superflame::StaticInitializer<Test01> si;

    static bool static_res_init() {
        std::cout << "Test01::" << __func__ << std::endl;
        return true;
    }
};

superflame::StaticInitializer<Test01> Test01::si;

class Test02 {
public:
    static superflame::StaticInitializer<Test02> si;

    static std::string static_res_init() {
        std::cout << "Test02::" << __func__ << std::endl;
        return "michaelma";
    }
};

superflame::StaticInitializer<Test02> Test02::si;

int main() {
    return 0;
}

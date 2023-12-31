#pragma once
#ifndef STATIC_INITIALIZER_H_
#define STATIC_INITIALIZER_H_

namespace superflame {
template<typename OWNER>
class StaticInitializer {
public:
    StaticInitializer() {
        OWNER::static_res_init();
    }
};
}  // namespace superflame

#endif  // STATIC_INITIALIZER_H_

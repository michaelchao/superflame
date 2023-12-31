#pragma once
#ifndef NEW_POINTER_SCOPED_HOLDER_H_
#define NEW_POINTER_SCOPED_HOLDER_H_
#include <type_traits>

namespace superflame {
template<typename T>
class NewPointerScopedHolder {
private:
    T * raw_ {nullptr};

private:
    void destroy() {
        if (raw_) {
            delete raw_;
        }
    }

public:
    NewPointerScopedHolder() = default;

    explicit NewPointerScopedHolder(T * raw)
    :raw_(raw) {
    }

    ~NewPointerScopedHolder() {
        destroy();
    }

    NewPointerScopedHolder& operator=(T * raw) noexcept {
        destroy();

        raw_ = raw;
        return *this;
    }

    T * get() noexcept {
        return raw_;
    }

};

}  // namespace superflame

#define DEFINE_NEW_POINTER_SCOPED_HOLDER(varibale, operation) \
    superflame::NewPointerScopedHolder<std::remove_pointer<decltype((operation))>::type> varibale {operation}

#endif  // NEW_POINTER_SCOPED_HOLDER_H_

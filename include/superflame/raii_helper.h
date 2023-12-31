#pragma once
#ifndef RAII_HELPER_H_
#define RAII_HELPER_H_
#include <functional>

namespace superflame {

class RaiiHelper {
  public:
    explicit RaiiHelper(const std::function<void()>& cleanup) noexcept
    :RaiiHelper(std::function<void()>(), cleanup) {
    }

    RaiiHelper(const std::function<void()>& init,
                const std::function<void()>& cleanup) noexcept
    : cleanup_(cleanup) {
        if (init) {
            init();
        }
    }

    ~RaiiHelper() noexcept { destroy(); }

    RaiiHelper(const RaiiHelper&) = delete;
    RaiiHelper& operator=(const RaiiHelper&) = delete;

    RaiiHelper(RaiiHelper&& rhs) noexcept { *this = std::move(rhs); }

    RaiiHelper& operator=(RaiiHelper&& rhs) noexcept {
        if (this != &rhs) {
            destroy();
            cleanup_ = rhs.cleanup_;
            rhs.cleanup_ = std::function<void()>();
        }
        return *this;
    }

  private:
    void destroy() noexcept {
        if (cleanup_) {
            cleanup_();
            cleanup_ = std::function<void()>();
        }
    }

  private:
    std::function<void()> cleanup_;
};

}

#endif  // RAII_HELPER_H_

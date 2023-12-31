#pragma once
#ifndef ATTRIBUTE_SYSTEM_H_
#define ATTRIBUTE_SYSTEM_H_
#include "attribute.h"
#include "const_string.h"

namespace superflame {

class AttributeManager {
    public:
        static AttributeManager & singleton() {
            static AttributeManager sobj;
            return sobj;
        }

    public:
        template<size_t D>
        bool has_attr(const superflame::constexpr_str<D> & domain, const std::string & key) const {
            auto agi = attrs_.find(domain.str);
            if (agi == attrs_.cend()) {
                return false;
            }

            auto ai = agi->second.find(key);
            if (ai == agi->second.cend()) {
                return false;
            }

            return true;
        }

        template<typename T, size_t D>
        void add_mutable_attr(const superflame::constexpr_str<D> & domain, const std::string & key, T && value) {
            if (attrs_.find(domain.str) == attrs_.end()) {
                attr::AttributeGroup ag;
                ag.emplace(key, attr::make_mutable_attribute(std::forward<T>(value)));
                attrs_[domain.str] = std::move(ag);
            } else {
                auto & ag = attrs_[domain.str];
                ag[key] = attr::make_mutable_attribute(std::forward<T>(value));
            }
        }

        template<typename T, size_t D>
        T & get_mutable_attr(const superflame::constexpr_str<D> & domain, const std::string & key) {
            auto agi = attrs_.find(domain.str);
            auto ai = agi->second.find(key);
            return attr::get_mutable_value<T>(ai->second);
        }

        template<typename T, size_t D>
        void add_const_attr(const superflame::constexpr_str<D> & domain, const std::string & key, T && value) {
            if (attrs_.find(domain.str) == attrs_.end()) {
                attr::AttributeGroup ag;
                ag.emplace(key, attr::make_const_attribute(std::forward<T>(value)));
                attrs_[domain.str] = std::move(ag);
            } else {
                auto & ag = attrs_[domain.str];
                ag[key] = attr::make_const_attribute(std::forward<T>(value));
            }
        }

        template<size_t D>
        void add_const_attr(const superflame::constexpr_str<D> & domain, const std::string & key, char const * value) {
            if (attrs_.find(domain.str) == attrs_.end()) {
                attr::AttributeGroup ag;
                ag.emplace(key, attr::make_const_attribute(std::string(value)));
                attrs_[domain.str] = std::move(ag);
            } else {
                auto & ag = attrs_[domain.str];
                ag[key] = attr::make_const_attribute(std::string(value));
            }
        }

        template<typename T, size_t D>
        const T & get_const_attr(const superflame::constexpr_str<D> & domain, const std::string & key) {
            auto agi = attrs_.find(domain.str);
            auto ai = agi->second.find(key);
            return attr::get_const_value<T>(ai->second);
        }

    public:
        ~AttributeManager() = default;

    private:
        AttributeManager() = default;

    private:
        std::map<std::string, attr::AttributeGroup> attrs_;
};

}  // namespace superflame

#endif // ATTRIBUTE_SYSTEM_H_

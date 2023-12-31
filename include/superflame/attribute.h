#pragma once
#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_
#include <memory>
#include <cassert>
#include <map>

namespace superflame {
namespace attr {

class Attribute;

// AccessorBase
//
// Offer generic container
class AccessorBase {
protected:
    struct ContainerBase {
        virtual ~ContainerBase() = default;
    };

    template<typename T>
    struct Container : public ContainerBase {
        T value_;
        Container(T && v)
        :value_(std::move(v)) {}

        T & get() {
            return value_;
        }
    };
};

// Accessor
//
// This is an mutable accessor
class Accessor final : private AccessorBase {
    friend class Attribute;

    Accessor() = default;

    template<typename M>
    Accessor(M v)
    : base_{new Container<M>(std::move(v))} {
    }

    bool has() const {
        return !!base_;
    }

public:
    template<typename T>
    T & get() {
        auto derived = dynamic_cast<Container<T>*>(base_.get());
        assert(derived);

        return derived->get();
    }

private:
    std::unique_ptr<ContainerBase> base_;
};

// Accessor
//
// This is an const accessor
class ConstAccessor final : private AccessorBase {
    friend class Attribute;

    ConstAccessor() = default;

    template<typename M>
    ConstAccessor(M v)
    : base_{new Container<M>(std::move(v))} {
    }

    bool has() const {
        return !!base_;
    }

public:
    template<typename T>
    const T & get() const {
        auto derived = dynamic_cast<Container<T>*>(base_.get());
        assert(derived);

        return derived->get();
    }

private:
    std::unique_ptr<ContainerBase> base_;
};

// Attribute
//
// Attribute used by user
class Attribute {
    struct AttributeConcept {
        virtual ~AttributeConcept() = default;

        virtual Accessor & as_mutable() = 0;
        virtual ConstAccessor & as_const() = 0;
        virtual bool has() const = 0;
    };

    template<typename T>
    struct AttributeImpl : public AttributeConcept {
        Accessor accessor_;
        ConstAccessor const_accessor_;

        AttributeImpl(T x)
        : accessor_{std::move(x)} {
        }

        virtual ~AttributeImpl() = default;

        virtual Accessor & as_mutable() {
            return accessor_;
        };

        virtual ConstAccessor & as_const() {
            return const_accessor_;
        };

        virtual bool has() const {
            return accessor_.has();
        }
    };

    template<typename T>
    struct ConstAttributeImpl : public AttributeConcept {
        Accessor accessor_;
        ConstAccessor const_accessor_;

        ConstAttributeImpl(T x)
        : const_accessor_{std::move(x)} {
        }

        virtual ~ConstAttributeImpl() = default;

        virtual Accessor & as_mutable() {
            return accessor_;
        };

        virtual ConstAccessor & as_const() {
            return const_accessor_;
        };

        virtual bool has() const {
            return const_accessor_.has();
        }
    };

    std::unique_ptr<AttributeConcept> attr_;

public:
    Attribute() = default;

#if 0 // Activing this will make AttributeManager compiling fail
    Attribute(Attribute && other) {
        if (this == &other) { return; }
        attr_ = std::move(other.attr_);
    }
#endif

    // Constuct mutable attribute
    template<typename N>
    Attribute(N && v)
    :attr_(new AttributeImpl<N>(std::move(v))) {
    }

    struct RO {};

    // Constuct const attribute
    template<typename N>
    Attribute(N && v, RO)
    :attr_(new ConstAttributeImpl<N>(std::move(v))) {
    }

    // Access to mutable attribute
    Accessor & as_mutable() {
        return attr_->as_mutable();
    }

    // Access to const attribute
    ConstAccessor & as_const() {
        return attr_->as_const();
    }

    bool has() const {
        return !!attr_ && attr_->has();
    }
};

// I design this for you
using AttributeGroup = std::map<std::string, Attribute>;

// Make a mutbale attribute with type `T`
template<typename T>
Attribute make_mutable_attribute(T && v) {
    return Attribute(std::forward<T>(v));
}

// Make a constant attribute with type `T`
template<typename T>
Attribute make_const_attribute(T && v) {
    return Attribute(std::forward<T>(v), Attribute::RO{});
}

// Get mutable value from attribute by type `T`.
// Assert will fail when `T` is not same as type of value in attribute
template<typename T>
T & get_mutable_value(Attribute & attr) {
    return attr.as_mutable().get<T>();
}

// Get constant value from attribute by type `T`.
// Assert will fail when `T` is not same as type of value in attribute
template<typename T>
const T & get_const_value(Attribute & attr) {
    return attr.as_const().get<T>();
}

}  // namespace attr
}  // namespace superflame

#endif  // ATTRIBUTE_H_

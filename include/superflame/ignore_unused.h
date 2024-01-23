#ifndef IGNORE_UNUSED_H_
#define IGNORE_UNUSED_H_

namespace superflame {

template<typename T>
inline void ignore_unused(T const & arg) {
	static_cast<void>(arg);
}

template<typename First, typename... Rest>
inline void ignore_unused(First const & first, Rest const & ...rest) {
	static_cast<void>(first);
	ignore_unused(rest...);
}

}  // namespace superflame

#endif  // IGNORE_UNUSED_H_


#ifndef RDF4CPP_REGISTRY_UTIL_CONSTEXPRSTRING_HPP
#define RDF4CPP_REGISTRY_UTIL_CONSTEXPRSTRING_HPP

#include <algorithm>
#include <cstddef>
#include <string>
#include <string_view>
#include <format>

namespace rdf4cpp::rdf::datatypes::registry::util {
/**
 * Literal class type that wraps a constant expression string.
 *
 * Uses implicit conversion to allow templates to *seemingly* accept constant strings.
 *
 * Extended version of https://ctrpeach.io/posts/cpp20-string-literal-template-parameters/.
 */
template<size_t N>
struct ConstexprString {
    char value[N];
    constexpr ConstexprString(const char (&str)[N]) noexcept {
        std::copy_n(str, N, value);
    }

    constexpr operator std::string_view() const noexcept {
        return std::string_view{value};
    }

    template<size_t M>
    constexpr std::strong_ordering operator<=>(ConstexprString<M> const &other) const noexcept {
        auto min = std::min(M, N);
        for (size_t i = 0; i < min; ++i) {
            std::strong_ordering cmp = this->value[i] <=> other.value[i];
            if (cmp != std::strong_ordering::equal)
                return cmp;
        }
        std::strong_ordering cmp = N <=> M;
        return cmp;
    }

    template<size_t M>
    constexpr bool operator==(ConstexprString<M> const &other) const noexcept {
        if (M == N) {
            return (*this <=> other == std::strong_ordering::equal);
        } else {
            return false;
        }
    }

    [[nodiscard]] constexpr size_t size() const noexcept {
        return N;
    }
};

}  // namespace rdf4cpp::rdf::datatypes::registry::util

template<size_t N>
struct std::formatter<rdf4cpp::rdf::datatypes::registry::util::ConstexprString<N>> : std::formatter<std::string_view> {
    auto format(rdf4cpp::rdf::datatypes::registry::util::ConstexprString<N> const &s, format_context& ctx) const {
        return formatter<string_view>::format(static_cast<std::string_view>(s), ctx);
    }
};

#endif  //RDF4CPP_REGISTRY_UTIL_CONSTEXPRSTRING_HPP

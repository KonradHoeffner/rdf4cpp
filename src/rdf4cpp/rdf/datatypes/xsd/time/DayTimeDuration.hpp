#ifndef RDF4CPP_DAYTIMEDURATION_HPP
#define RDF4CPP_DAYTIMEDURATION_HPP

#include <chrono>

#include <rdf4cpp/rdf/datatypes/registry/DatatypeMapping.hpp>
#include <rdf4cpp/rdf/datatypes/registry/FixedIdMappings.hpp>
#include <rdf4cpp/rdf/datatypes/registry/LiteralDatatypeImpl.hpp>
#include <rdf4cpp/rdf/util/Timezone.hpp>
#include <rdf4cpp/rdf/datatypes/xsd/time/Duration.hpp>

namespace rdf4cpp::rdf::datatypes::registry {

template<>
struct DatatypeMapping<xsd_dayTimeDuration> {
    using cpp_datatype = std::chrono::milliseconds;
};
template<>
struct DatatypeSupertypeMapping<xsd_dayTimeDuration> {
    using supertype = xsd::Duration;
};


template<>
capabilities::Default<xsd_dayTimeDuration>::cpp_type capabilities::Default<xsd_dayTimeDuration>::from_string(std::string_view s);

template<>
std::string capabilities::Default<xsd_dayTimeDuration>::to_canonical_string(const cpp_type &value) noexcept;

template<>
std::optional<storage::node::identifier::LiteralID> capabilities::Inlineable<xsd_dayTimeDuration>::try_into_inlined(cpp_type const &value) noexcept;

template<>
capabilities::Inlineable<xsd_dayTimeDuration>::cpp_type capabilities::Inlineable<xsd_dayTimeDuration>::from_inlined(storage::node::identifier::LiteralID inlined) noexcept;

template<>
std::partial_ordering capabilities::Comparable<xsd_dayTimeDuration>::compare(cpp_type const &lhs, cpp_type const &rhs) noexcept;

template<>
template<>
capabilities::Subtype<xsd_dayTimeDuration>::super_cpp_type<0> capabilities::Subtype<xsd_dayTimeDuration>::into_supertype<0>(cpp_type const &value) noexcept;

template<>
template<>
nonstd::expected<capabilities::Subtype<xsd_dayTimeDuration>::cpp_type, DynamicError> capabilities::Subtype<xsd_dayTimeDuration>::from_supertype<0>(super_cpp_type<0> const &value) noexcept;

extern template struct LiteralDatatypeImpl<xsd_dayTimeDuration,
                                           capabilities::Comparable,
                                           capabilities::FixedId,
                                           capabilities::Inlineable,
                                           capabilities::Subtype>;

}  // namespace rdf4cpp::rdf::datatypes::registry

namespace rdf4cpp::rdf::datatypes::xsd {

struct DayTimeDuration : registry::LiteralDatatypeImpl<registry::xsd_dayTimeDuration,
                                                       registry::capabilities::Comparable,
                                                       registry::capabilities::FixedId,
                                                       registry::capabilities::Inlineable,
                                                       registry::capabilities::Subtype> {};

}  // namespace rdf4cpp::rdf::datatypes::xsd


namespace rdf4cpp::rdf::datatypes::registry::instantiation_detail {

[[maybe_unused]] inline xsd::DayTimeDuration const xsd_DaysTimeDuration_instance;

}  // namespace rdf4cpp::rdf::datatypes::registry::instantiation_detail

#endif  //RDF4CPP_DAYTIMEDURATION_HPP

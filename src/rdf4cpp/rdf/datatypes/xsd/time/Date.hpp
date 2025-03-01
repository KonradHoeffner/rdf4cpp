#ifndef RDF4CPP_DATE_HPP
#define RDF4CPP_DATE_HPP

#include <chrono>

#include <rdf4cpp/rdf/datatypes/registry/DatatypeMapping.hpp>
#include <rdf4cpp/rdf/datatypes/registry/FixedIdMappings.hpp>
#include <rdf4cpp/rdf/datatypes/registry/LiteralDatatypeImpl.hpp>
#include <rdf4cpp/rdf/util/Timezone.hpp>
#include <rdf4cpp/rdf/datatypes/xsd/time/DateTime.hpp>
#include <dice/hash.hpp>

namespace rdf4cpp::rdf::datatypes::registry {

template<>
struct DatatypeMapping<xsd_date> {
    using cpp_datatype = std::pair<std::chrono::year_month_day, rdf::util::OptionalTimezone>;
};
template<>
struct DatatypeSupertypeMapping<xsd_date> {
    using supertype = xsd::DateTime;
};

template<>
capabilities::Default<xsd_date>::cpp_type capabilities::Default<xsd_date>::from_string(std::string_view s);

template<>
std::string capabilities::Default<xsd_date>::to_canonical_string(const cpp_type &value) noexcept;


template<>
std::partial_ordering capabilities::Comparable<xsd_date>::compare(cpp_type const &lhs, cpp_type const &rhs) noexcept;

template<>
std::optional<storage::node::identifier::LiteralID> capabilities::Inlineable<xsd_date>::try_into_inlined(cpp_type const &value) noexcept;

template<>
capabilities::Inlineable<xsd_date>::cpp_type capabilities::Inlineable<xsd_date>::from_inlined(storage::node::identifier::LiteralID inlined) noexcept;

template<>
template<>
capabilities::Subtype<xsd_date>::super_cpp_type<0> capabilities::Subtype<xsd_date>::into_supertype<0>(cpp_type const &value) noexcept;

template<>
template<>
nonstd::expected<capabilities::Subtype<xsd_date>::cpp_type, DynamicError> capabilities::Subtype<xsd_date>::from_supertype<0>(super_cpp_type<0> const &value) noexcept;

extern template struct LiteralDatatypeImpl<xsd_date,
                                           capabilities::Comparable,
                                           capabilities::FixedId,
                                           capabilities::Inlineable,
                                           capabilities::Subtype>;

}  // namespace rdf4cpp::rdf::datatypes::registry

namespace rdf4cpp::rdf::datatypes::xsd {

struct Date : registry::LiteralDatatypeImpl<registry::xsd_date,
                                            registry::capabilities::Comparable,
                                            registry::capabilities::FixedId,
                                            registry::capabilities::Inlineable,
                                            registry::capabilities::Subtype> {};

}  // namespace rdf4cpp::rdf::datatypes::xsd


namespace rdf4cpp::rdf::datatypes::registry::instantiation_detail {

[[maybe_unused]] inline xsd::Date const xsd_Date_instance;

}  // namespace rdf4cpp::rdf::datatypes::registry::instantiation_detail

template<typename Policy>
struct dice::hash::dice_hash_overload<Policy, std::chrono::year_month_day> {
    static size_t dice_hash(std::chrono::year_month_day const &x) noexcept {
        auto year = static_cast<int>(x.year());
        auto month = static_cast<unsigned int>(x.month());
        auto day = static_cast<unsigned int>(x.day());
        return dice::hash::dice_hash_templates<Policy>::dice_hash(std::tie(year, month, day));
    }
};

#endif  //RDF4CPP_DATE_HPP

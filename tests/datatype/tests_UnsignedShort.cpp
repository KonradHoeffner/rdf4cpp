#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>
#include <rdf4cpp/rdf.hpp>

using namespace rdf4cpp::rdf;

TEST_CASE("Datatype UnsignedShort") {

    constexpr auto correct_type_iri_cstr = "http://www.w3.org/2001/XMLSchema#unsignedShort";

    CHECK(std::string(datatypes::xsd::UnsignedShort::identifier) == correct_type_iri_cstr);

    auto type_iri = IRI(datatypes::xsd::UnsignedShort::identifier);
    CHECK(type_iri.identifier() == correct_type_iri_cstr);

    using type = datatypes::xsd::UnsignedShort::cpp_type;

    CHECK(std::is_same_v<type, uint16_t>);

    uint16_t value = 1;
    auto lit1 = Literal::make_typed_from_value<datatypes::xsd::UnsignedShort>(value);
    CHECK(lit1.value<datatypes::xsd::UnsignedShort>() == value);
    CHECK(lit1.lexical_form() == std::to_string(value));

    value = 0;
    auto lit2 = Literal::make_typed_from_value<datatypes::xsd::UnsignedShort>(value);
    CHECK(lit2.value<datatypes::xsd::UnsignedShort>() == value);
    CHECK(lit2.lexical_form() == std::to_string(value));

    value = std::numeric_limits<uint16_t>::max();
    auto lit3 = Literal::make_typed_from_value<datatypes::xsd::UnsignedShort>(value);
    CHECK(lit3.value<datatypes::xsd::UnsignedShort>() == value);
    CHECK(lit3.lexical_form() == std::to_string(value));

    value = 1;
    auto lit4 = Literal::make_typed(std::to_string(value), type_iri);
    CHECK(lit4.value<datatypes::xsd::UnsignedShort>() == value);

    value = 0;
    auto lit5 = Literal::make_typed(std::to_string(value), type_iri);
    CHECK(lit5.value<datatypes::xsd::UnsignedShort>() == value);

    value = std::numeric_limits<uint16_t>::min();
    auto lit6 = Literal::make_typed_from_value<datatypes::xsd::UnsignedShort>(value);
    CHECK(lit6.value<datatypes::xsd::UnsignedShort>() == value);
    CHECK(lit6.lexical_form() == std::to_string(value));

    CHECK(lit1 != lit2);
    CHECK(lit2 != lit3);
    CHECK(lit1 == lit4);
    CHECK(lit2 == lit6);
    CHECK(lit5 == lit6);

    // suppress warnings regarding attribute ‘nodiscard’
    Literal no_discard_dummy;

    CHECK_THROWS(no_discard_dummy = Literal::make_typed("-1", type_iri));

    CHECK_THROWS(no_discard_dummy = Literal::make_typed("65536", type_iri));

    CHECK_THROWS(no_discard_dummy = Literal::make_typed("a23dg.59566", type_iri));

    CHECK_THROWS(no_discard_dummy = Literal::make_typed("-0.01", type_iri));
}

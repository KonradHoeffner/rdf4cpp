#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>
#include <rdf4cpp/rdf.hpp>

using namespace rdf4cpp::rdf;

TEST_CASE("Datatype Decimal") {

    constexpr auto correct_type_iri_cstr = "http://www.w3.org/2001/XMLSchema#decimal";

    CHECK(std::string(datatypes::xsd::Decimal::identifier) == correct_type_iri_cstr);

    auto type_iri = IRI(datatypes::xsd::Decimal::identifier);
    CHECK(type_iri.identifier() == correct_type_iri_cstr);

    using type = datatypes::xsd::Decimal::cpp_type;

    CHECK(std::is_same_v<type, double>);

    double value = 1.00;
    auto lit1 = Literal::make<datatypes::xsd::Decimal>(value);
    CHECK(lit1.value<datatypes::xsd::Decimal>() == value);
    CHECK(lit1.lexical_form() == std::to_string(value));

    value = 64582165456988.235046;
    auto lit2 = Literal::make<datatypes::xsd::Decimal>(value);
    CHECK(lit2.value<datatypes::xsd::Decimal>() == value);
    CHECK(lit2.lexical_form() == std::to_string(value));

    value = -64524654389.2345650;
    auto lit3 = Literal::make<datatypes::xsd::Decimal>(value);
    CHECK(lit3.value<datatypes::xsd::Decimal>() == value);
    CHECK(lit3.lexical_form() == std::to_string(value));

    value = 1.0;
    auto lit4 = Literal{std::to_string(value), type_iri};
    CHECK(lit4.value<datatypes::xsd::Decimal>() == value);

    value = 64582165456988.235046;
    auto lit5 = Literal{std::to_string(value), type_iri};
    CHECK(lit5.value<datatypes::xsd::Decimal>() == value);

    value = 1;
    auto lit6 = Literal{"1", type_iri};
    CHECK(lit6.value<datatypes::xsd::Decimal>() == value);

    auto lit7 = Literal{"1.0", type_iri};
    CHECK(lit7.value<datatypes::xsd::Decimal>() == value);

    auto lit8 = Literal{"1.00", type_iri};
    CHECK(lit8.value<datatypes::xsd::Decimal>() == value);

    value = std::numeric_limits<double>::max();
    auto lit9 = Literal{std::to_string(value), type_iri};
    CHECK(lit9.value<datatypes::xsd::Decimal>() == value);

    CHECK(lit1 != lit2);
    CHECK(lit2 != lit3);
    CHECK(lit1 == lit4);
    CHECK(lit2 == lit5);
    CHECK(lit6 == lit7);  //This CHECK fails because the string representation of xsd:decimal is not in canonical form yet.
    CHECK(lit6 == lit8);  //This CHECK fails because the string representation of xsd:decimal is not in canonical form yet.
    CHECK(lit7 == lit8);  //This CHECK fails because the string representation of xsd:decimal is not in canonical form yet.
    CHECK(lit6.value<datatypes::xsd::Decimal>() == lit7.value<datatypes::xsd::Decimal>());
    CHECK(lit6.value<datatypes::xsd::Decimal>() == lit8.value<datatypes::xsd::Decimal>());
    CHECK(lit7.value<datatypes::xsd::Decimal>() == lit7.value<datatypes::xsd::Decimal>());

    // suppress warnings regarding attribute ‘nodiscard’
    std::any no_discard_dummy = false;

    auto lit10 = Literal{"NAN", type_iri};
    CHECK_THROWS_WITH_AS(no_discard_dummy = lit10.value(), "XSD Parsing Error", std::runtime_error);

    auto lit11 = Literal{"INF", type_iri};
    CHECK_THROWS_WITH_AS(no_discard_dummy = lit11.value(), "XSD Parsing Error", std::runtime_error);

    value = INFINITY;
    auto lit12 = Literal{std::to_string(value), type_iri};
    CHECK_THROWS_WITH_AS(no_discard_dummy = lit12.value(), "XSD Parsing Error", std::runtime_error);

    value = NAN;
    auto lit13 = Literal{std::to_string(value), type_iri};
    CHECK_THROWS_WITH_AS(no_discard_dummy = lit13.value(), "XSD Parsing Error", std::runtime_error);

    auto lit14 = Literal{"454sdsd", type_iri};
    CHECK_THROWS_WITH_AS(no_discard_dummy = lit14.value(), "XSD Parsing Error", std::runtime_error);

    auto lit15 = Literal{"2.225E-307", type_iri};
    CHECK_THROWS_WITH_AS(no_discard_dummy = lit15.value(), "XSD Parsing Error", std::runtime_error);
}
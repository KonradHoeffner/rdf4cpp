#include <rdf4cpp/rdf.hpp>
#include <rdf4cpp/rdf/parser/RDFFileParser.hpp>

int main() {
    // read file
    for (const auto &v : rdf4cpp::rdf::parser::RDFFileParser{"./RDFFileParser_simple.ttl"}) {
        if (v.has_value())  // check if parser returns a successful read value
            std::cout << v.value() << "\n";
        else  // or an error
            std::cout << v.error() << "\n";
    }
    return 0;
}
#ifndef RDF4CPP_PARSER_ISTREAMQUADITERATOR_HPP
#define RDF4CPP_PARSER_ISTREAMQUADITERATOR_HPP

#include <iterator>
#include <memory>

#include <nonstd/expected.hpp>

#include <rdf4cpp/rdf/Quad.hpp>
#include <rdf4cpp/rdf/parser/ParsingError.hpp>
#include <rdf4cpp/rdf/parser/ParsingFlags.hpp>

#include <dice/hash.hpp>
#include <dice/sparse-map/sparse_map.hpp>

namespace rdf4cpp::rdf::parser {

/**
 * Similar to std::istream_iterator<>.
 * Parses the given istream and tries to extract Quads given in TURTLE format.
 *
 * @note the iterator _starts on_ the first Quad
 * @note An exhausted iterator becomes the end-of-stream iterator.
 * @warning The value pointed to by an end-of-stream iterator is undefined
 *
 * @example
 * @code
 * std::ifstream ifs{"triples.nt"};
 *
 * for (auto qit = IStreamQuadIterator{ifs}; qit != IStreamQuadIterator{}; ++qit) {
 *      if (qit->has_value()) {
 *          std::cout << qit->value() << std::endl;
 *      } else {
 *          std::cerr << qit->error() << std::endl;
 *      }
 * }
 * @endcode
 */
struct IStreamQuadIterator {
    using value_type = nonstd::expected<Quad, ParsingError>;
    using reference = value_type const &;
    using pointer = value_type const *;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::input_iterator_tag;
    using istream_type = std::istream;

    using prefix_storage_type = dice::sparse_map::sparse_map<std::string,
                                                             std::string,
                                                             dice::hash::DiceHashwyhash<std::string_view>,
                                                             std::equal_to<>>;

private:
    struct Impl;

    std::unique_ptr<Impl> impl;
    nonstd::expected<Quad, ParsingError> cur = nonstd::make_unexpected(ParsingError{.error_type = ParsingError::Type::EofReached, .line = 0, .col = 0, .message = "eof reached"});

    [[nodiscard]] bool is_at_end() const noexcept;

public:
    /**
     * Constructs the end-of-stream iterator
     */
    IStreamQuadIterator() noexcept;

    /**
     * Constructs the end-of-stream iterator
     */
    IStreamQuadIterator(std::default_sentinel_t) noexcept;

    IStreamQuadIterator(IStreamQuadIterator const &) = delete;
    IStreamQuadIterator(IStreamQuadIterator &&) noexcept;

    IStreamQuadIterator &operator=(IStreamQuadIterator &&) noexcept = default;

    explicit IStreamQuadIterator(std::istream &istream, ParsingFlags flags = ParsingFlags::none(),
                                 prefix_storage_type prefixes = {},
                                 storage::node::NodeStorage node_storage = storage::node::NodeStorage::default_instance()) noexcept;
    ~IStreamQuadIterator() noexcept;

    reference operator*() const noexcept;
    pointer operator->() const noexcept;
    IStreamQuadIterator &operator++();

    bool operator==(IStreamQuadIterator const &) const noexcept;
    bool operator!=(IStreamQuadIterator const &) const noexcept;
};

}  // namespace rdf4cpp::rdf::parser

#endif  //RDF4CPP_PARSER_ISTREAMQUADITERATOR_HPP

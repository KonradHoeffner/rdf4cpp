#ifndef RDF4CPP_NAMESPACE_HPP
#define RDF4CPP_NAMESPACE_HPP

#include <rdf4cpp/rdf/IRI.hpp>

#include <dice/hash.hpp>
#include <dice/sparse-map/sparse_map.hpp>

#include <string>
#include <string_view>

namespace rdf4cpp::rdf {

/**
 * Namespace provides a simple tool to create IRIs from a certain namespace and vocabulary. Each Namespace instance maintains an internal cache to save roundtrip to storage::node::NodeStorage.<br/>
 * Example:
 *  @code
 *  Namespace ex("http://example.com/);
 *  IRI me = ex + "me";
 *  @endcode
 */
class Namespace {
public:
    using NodeStorage = storage::node::NodeStorage;
    using WeakNodeStorage = storage::node::WeakNodeStorage;

protected:
    /**
     * The IRI string of the namespace.
     */
    std::string namespace_iri_;

    /**
     * NodeStorage from which IRI objects are created.
     */
    WeakNodeStorage node_storage_;

    // TODO: a faster, less memory efficient map would be better.
    /**
     * Cache storing the <div>NodeBackendHandle</div> for prefixes. This saves roundtrips to NodeStorage.
     */
    mutable dice::sparse_map::sparse_map<std::string, storage::node::identifier::NodeBackendHandle,
                                         dice::hash::DiceHashwyhash<std::string_view>, std::equal_to<>> cache_;

public:
    /**
     * Namespace Constructor
     * @param namespace_iri namespace IRI string. This will be used as prefix. IRI must not be encapsulated in <..>.
     * @param node_storage where the IRIs will live
     */
    explicit Namespace(std::string_view namespace_iri,
                       NodeStorage &node_storage = NodeStorage::default_instance());

    /**
     * @return IRI string of the Namespace
     */
    std::string_view name_space() const noexcept;

    /**
     * @return NodeStorage used to create <div>IRI</div>s from this Namespace.
     */
    WeakNodeStorage node_storage() const;

    /**
     * Create an IRI with the suffix added to the
     * @return
     */
    /**
      *
      * @return
      */

    /**
     * Create an IRI with the suffix added to the Namespace.
     * @param suffix suffix that is appended
     * @return the constructed IRI
     */
    virtual IRI operator+(std::string_view suffix) const;

    /**
     * Clears the cache.
     */
    virtual void clear() const;
};
}  // namespace rdf4cpp::rdf

#endif  //RDF4CPP_NAMESPACE_HPP

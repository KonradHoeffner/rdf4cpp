#ifndef RDF4CPP_RDF_BNODEMANAGEMENT_INODEFACADE
#define RDF4CPP_RDF_BNODEMANAGEMENT_INODEFACADE

#include <rdf4cpp/rdf/bnode_management/IIdGenerator.hpp>
#include <rdf4cpp/rdf/storage/node/NodeStorage.hpp>

namespace rdf4cpp::rdf::util {

/**
 * A factory for nodes. Any kind of node. That given a generator
 * produces a node that somehow incorporates the generated id of the generator.
 */
struct INodeFactory {
    virtual ~INodeFactory() = default;

    [[nodiscard]] virtual storage::node::identifier::NodeBackendHandle make_null_node() const noexcept = 0;
    [[nodiscard]] virtual storage::node::identifier::NodeBackendHandle make_node(IIdGenerator &generator, storage::node::NodeStorage &node_storage) = 0;
};

}  //namespace rdf4cpp::rdf::util

#endif  //RDF4CPP_RDF_BNODEMANAGEMENT_INODEFACADE

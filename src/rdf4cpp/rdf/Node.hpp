#ifndef RDF4CPP_NODE_HPP
#define RDF4CPP_NODE_HPP

/** @file
 * @brief RDFNode
 * Long
 */

#include <rdf4cpp/rdf/storage/node/NodeStorage.hpp>
#include <rdf4cpp/rdf/util/TriBool.hpp>

#include <memory>
#include <optional>
#include <string>

namespace rdf4cpp::rdf {
class Literal;
class BlankNode;
class IRI;
namespace query {
class Variable;
};
/**
 * @brief Models a node in RDF <span>Dataset</span>s, RDF <span>Graphs</span>s or pattern matching tuples like <span>QuadPattern</span>s or <span>TriplePattern</span>s.
 * <p><b>Please note:</b> The edges of an RDF Graph, dubbed <span>Predicate</span>s, are <span>IRI</span>s. As such the same resource can also be used as a node.
 * For the sake of simplicity, we decided to have no separate class for edges in an RDF graph.
 * You can determine if a Node is an edge by the the fact that it is used as predicate in a Dataset, Graph, Quad, Statement, QuadPattern or TriplePattern.</p>
 *
 * @warning This type is a POD.
 */
class Node {
protected:
    using NodeBackendHandle = rdf4cpp::rdf::storage::node::identifier::NodeBackendHandle;
    using NodeID = rdf4cpp::rdf::storage::node::identifier::NodeID;
    using NodeStorage = rdf4cpp::rdf::storage::node::NodeStorage;
    using RDFNodeType = rdf4cpp::rdf::storage::node::identifier::RDFNodeType;
    NodeBackendHandle handle_;

    explicit Node(NodeBackendHandle id) noexcept;

public:
    /**
     * Registers this node in the given node storage (if it does not already exist)
     * @param node_storage node storage to register this node in
     * @return this node but in node storage
     */
    Node to_node_storage(NodeStorage &node_storage) const noexcept;

    /**
     * Tries to retrieve this nodes equivalent node in the given node storage
     * @param node_storage node storage to try to retrieve the node from
     * @return this node but in node storage, or the null node if it does not exist in node_storage
     */
    [[nodiscard]] Node try_get_in_node_storage(NodeStorage const &node_storage) const noexcept;

    // TODO: revisit comparison implementation
    // TODO: support comparison between NodeStorages
    /**
     * Default construction produces null() const Node. This node models an unset or invalid Node.
     * null() const <span>Node</span>s should only be used as temporary placeholders. They cannot be inserted into a Graph or Dataset.
     *
     * @warning This type is POD. The constructor needs to be invoked explicitly. Alternatively: call Node::make_null()
     */
    Node() noexcept = default;

    /**
     * Construct the null-node
     */
    [[nodiscard]] static Node make_null() noexcept;

    /**
     * Returns a string representation of the given node in N-format as defined by <a href="https://www.w3.org/TR/n-triples/">N-Triples</a> and <a href="https://www.w3.org/TR/n-quads/">N-Quads</a>.
     * @return string representation in N-format
     */
    [[nodiscard]] explicit operator std::string() const noexcept;

    /**
     * @see operator std::string() const
     */
    friend std::ostream &operator<<(std::ostream &os, const Node &node);

    /**
     * Checks weather the node is a Literal. If yes, it is safe to convert it with `auto literal = (Literal) rdf_node;`
     * @return if this is a Literal
     */
    [[nodiscard]] bool is_literal() const noexcept;

    /**
     * Checks weather the node is a Variable. If yes, it is safe to convert it with `auto variable = (Variable) rdf_node;`
     * @return if this is a Variable
     */
    [[nodiscard]] bool is_variable() const noexcept;

    /**
     * Checks weather the node is a BlankNode. If yes, it is safe to convert it with `auto bnode = (BlankNode) rdf_node;`
     * @return if this is a BlankNode
     */
    [[nodiscard]] bool is_blank_node() const noexcept;

    /**
     * Checks weather the node is a IRI. If yes, it is safe to convert it with `auto iri = (Literal) rdf_node;`
     * @return if this is a IRI
     */
    [[nodiscard]] bool is_iri() const noexcept;

    /**
     * @return if the current value of this node is stored inside the handle instead of the node storage
     */
    [[nodiscard]] bool is_inlined() const noexcept;

    bool operator==(const Node &other) const noexcept;

    std::weak_ordering operator<=>(const Node &other) const noexcept;

    /**
     * @return the effective boolean value of this
     */
    [[nodiscard]] util::TriBool ebv() const noexcept;

    /**
     * @return the effective boolean value of this as xsd:boolean (or null literal in case of Err)
     */
    [[nodiscard]] Literal as_ebv(NodeStorage &node_storage = NodeStorage::default_instance()) const noexcept;


    /**
     * Casts this Node into a BlankNode if it is one, otherwise returns the null BlankNode.
     * @return a copy of this as BlankNode if it is one, else null BlankNode
     */
    [[nodiscard]] BlankNode as_blank_node() const noexcept;

    /**
     * Casts this Node into a IRI if it is one, otherwise returns the null IRI.
     * @return a copy of this as IRI if it is one, else null IRI
     */
    [[nodiscard]] IRI as_iri() const noexcept;

    /**
     * Casts this Node into a Literal if it is one, otherwise returns the null Literal.
     * @return a copy of this as Literal if it is one, else null Literal
     */
    [[nodiscard]] Literal as_literal() const noexcept;

    /**
     * Casts this Node into a Variable if it is one, otherwise returns the null Variable.
     * @return a copy of this as Variable if it is one, else null Variable
     */
    [[nodiscard]] query::Variable as_variable() const noexcept;


    /**
     * Check whether the Node has no value or an invalid value.
     * @return if value is unset or invalid
     */
    [[nodiscard]] bool null() const noexcept;

    /**
     * Exposes the const NodeBackendHandle.
     *
     * This function is unsafe! Make sure this is not null() const.
     * @return its NodeBackendHandle.
     */
    [[nodiscard]] const NodeBackendHandle &backend_handle() const noexcept;

    /**
     * Exposes the NodeBackendHandle.
     *
     * This function is unsafe! Make sure this is not null() const.
     * @return its NodeBackendHandle.
     */
    [[nodiscard]] NodeBackendHandle &backend_handle() noexcept;
};
}  // namespace rdf4cpp::rdf

template<>
struct std::hash<rdf4cpp::rdf::Node> {
    inline size_t operator()(rdf4cpp::rdf::Node const &v) const noexcept {
        return std::hash<rdf4cpp::rdf::storage::node::identifier::NodeBackendHandle>()(v.backend_handle());
    }
};

#include <ostream>
#include <rdf4cpp/rdf/BlankNode.hpp>
#include <rdf4cpp/rdf/IRI.hpp>
#include <rdf4cpp/rdf/Literal.hpp>
#include <rdf4cpp/rdf/query/Variable.hpp>

#endif  //RDF4CPP_NODE_HPP

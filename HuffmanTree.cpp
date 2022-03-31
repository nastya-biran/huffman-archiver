#include "HuffmanTree.h"
#include "PriorityQueue.h"
#include <memory>

template <>
struct std::less<std::shared_ptr<HuffmanTree::Node>> {
    bool operator()(std::shared_ptr<HuffmanTree::Node> node1, std::shared_ptr<HuffmanTree::Node> node2) {
        return std::tie(node1->fr, node1->c) < std::tie(node2->fr, node2->c);
    }
};

void HuffmanTree::DFS(std::shared_ptr<HuffmanTree::Node> current_node, int32_t depth) {
    if (current_node->l != nullptr) {
        DFS(std::move(current_node->l), depth + 1);
        DFS(std::move(current_node->r), depth + 1);
    } else {
        symbols_code_length_[current_node->c] = depth;
        return;
    }
}

std::unordered_map<int32_t, int32_t> HuffmanTree::GetSymbolsCodeSize() {
    PriorityQueue<std::shared_ptr<HuffmanTree::Node>, std::less<std::shared_ptr<HuffmanTree::Node>>> q;
    auto symbol = symbols_frequency.begin();
    while (symbol != symbols_frequency.end()) {
        std::shared_ptr<Node> new_node_ptr = std::make_shared<Node>(nullptr, nullptr, symbol->first, symbol->second);
        q.Push(std::move(new_node_ptr));
        ++symbol;
    }
    while (q.Size() > 1) {
        std::shared_ptr<Node> child1 = q.Pop();
        std::shared_ptr<Node> child2 = q.Pop();
        std::shared_ptr<Node> new_node_ptr =
            std::make_shared<Node>(std::move(child1), std::move(child2), NO_CHAR_, child1->fr + child2->fr);
        q.Push(std::move(new_node_ptr));
    }
    std::shared_ptr<Node> leaf = q.Pop();
    DFS(std::move(leaf), 0);
    return symbols_code_length_;
}

#pragma once

#include <unordered_map>
#include <memory>

class HuffmanTree {
public:
    class Node {
    public:
        Node(std::shared_ptr<Node> l1, std::shared_ptr<Node> r1, int32_t c1, int32_t fr1) : l(l1), r(r1), c(c1),
                                                                                            fr(fr1) {};
        std::shared_ptr<Node> l;
        std::shared_ptr<Node> r;
        int32_t c;
        int32_t fr;
    };


    std::unordered_map<int32_t, int32_t> GetSymbolsCodeSize();

    std::unordered_map<int32_t, int32_t> symbols_frequency;
private:
    void DFS(std::shared_ptr<HuffmanTree::Node> current_node, int32_t depth);

    const char NO_CHAR_ = '\0';
    std::unordered_map<int32_t, int32_t> symbols_code_length_;
};


#include <vector>
#include <iostream>

template <typename T, class Compare = std::less<T>>
class PriorityQueue {
public:
    PriorityQueue() = default;

    void Push(T pushing_node) {
        storage_.push_back(pushing_node);
        PushUp(storage_.size() - 1);
    }

    T Pop() {
        T upper_node = storage_[0];
        std::swap(storage_.back(), storage_[0]);
        storage_.pop_back();
        PushDown(0);
        return upper_node;
    }

    size_t Size() {
        return storage_.size();
    }

private:
    size_t Parent(size_t x) {
        return (x - 1) / 2;
    }

    size_t LeftChild(size_t x) {
        return 2 * x + 1;
    }

    size_t RightChild(size_t x) {
        return 2 * x + 2;
    }

    void PushUp(size_t pos) {
        while (pos != 0 && compare_symbols_(storage_[pos], storage_[Parent(pos)])) {
            std::swap(storage_[pos], storage_[Parent(pos)]);
            pos = Parent(pos);
        }
    }

    void PushDown(size_t pos) {
        while (pos < storage_.size() / 2) {
            size_t max_child = LeftChild(pos);
            if (RightChild(pos) < storage_.size() &&
                compare_symbols_(storage_[RightChild(pos)], storage_[LeftChild(pos)])) {
                max_child = RightChild(pos);
            }
            if (compare_symbols_(storage_[pos], storage_[max_child])) {
                return;
            }
            std::swap(storage_[pos], storage_[max_child]);
            pos = max_child;
        }
    }

    Compare compare_symbols_;
    std::vector<T> storage_;
};
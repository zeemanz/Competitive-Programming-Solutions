template <class T, class Cmp = std::less<T>> struct ErasableHeap {
    std::priority_queue<T, std::vector<T>, Cmp> heap, trash;
    ErasableHeap() {}
    ErasableHeap(const std::vector<T> &data) : heap{data.begin(), data.end()} {}
    void push(const T &x) {
        heap.push(x);
    }
    void pop() {
        doErase();
        heap.pop();
    }
    const T &top() {
        doErase();
        return heap.top();
    }
    void erase(const T &x) {
        trash.push(x);
    }
    void doErase() {
        while (!heap.empty() && !trash.empty() && heap.top() == trash.top()) {
            heap.pop();
            trash.pop();
        }
    }
    bool empty() const {
        return heap.size() == trash.size();
    }
};

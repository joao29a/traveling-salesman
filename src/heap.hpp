#ifndef HEAP
#define HEAP

/* E type of elem of a container; D type of container */
template<typename E, template<typename, typename> class D, typename F>
struct Heap{
    void build(D<E, allocator<E>>& vt){
        make_heap(vt.begin(), vt.end(), F());
    }
    
    E pop(D<E, allocator<E>>& vt){
        E node = vt.front();
        pop_heap(vt.begin(), vt.end(), F());
        vt.pop_back();
        return node;
    }

    void push(D<E, allocator<E>>& vt, E elem){
        vt.push_back(elem);
        push_heap(vt.begin(), vt.end(), F());
    }
};

#endif

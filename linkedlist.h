/*
implements a single linked list with a tiny interface and iter like protocol.
*/
#ifndef tiny_linked_list_h
#define tiny_linked_list_h


template<class K>
class LoopingIterator;

template <class C>
class Node{
    public:
        C data;
        Node<C> *next=nullptr;
};

template <typename T>
class TinyLinkedList{
    friend class LoopingIterator<T>;
    public:
        TinyLinkedList()
        : iter{*this}
        {};
        ~TinyLinkedList(){_free();};
        LoopingIterator<T> iter;

        void append(T v){
            Node<T> *newNode = new Node<T>();
            newNode->data =v;
            if (_root){
                // old end
                _end->next = newNode;
            } else {
                _root = newNode;
                iter._reset();
            }
            _end = newNode;
            _size++;
        };

        signed int index(T element){
            Node<T> *current{_root};
            for(size_t idx=0; idx<=_size; idx++){
                if (current->data == element){
                    return idx;
                }
                current = current->next;
            }
            return -1;
        };

        T remove(size_t index){
            Node<T> *pred = _get(index - 1);
            Node<T> *res = pred->next;
            pred->next = pred->next->next;
            return res->data;
        }

        T get(size_t index){
            return _get(index)->data;
        }

        T pop(){
            if (not _size) return T();
            T resData;
            if (_size >=2){
                 resData = _end->data;
                delete(_end);
                _end = _get(_size - 2);
                _end->next = nullptr;
                _size--;
            } else {
                resData = _root->data;
                _root = nullptr;
                _end = nullptr;
                _size = 0;
            }
            return resData;
        }

        size_t size(){return _size;};

    private:
        size_t _size {0};
        Node<T> *_root{nullptr};
        Node<T> *_end{nullptr};
        Node<T> *_next{nullptr};

        Node<T> *_get(size_t index){
            Node<T> *recent = _root;
            for (size_t idx = 0; idx < index; idx++){
                recent = recent->next;
            }
            return recent;
        }

        void _free(){
            while(_root){
                Node<T> *recent = _root;
                delete _root;
                _root = recent->next;
            }
        }

};

template<class K>
class LoopingIterator{
    friend class TinyLinkedList<K>;
    public:
        LoopingIterator(TinyLinkedList<K> &instance)
           : _instance{instance}
        {};
        // once we iterated all elements we reset and return false.
        bool operator()(){
            bool res = _iter;
            if (not _iter) _reset();
            return res;
        }
    
        K next(){
            K data = _next->data;
            _next = _next->next;
            if (not _next){
               _iter = false;
            }
            return data;
        }

        K loopNext(){
            K data = next();
            if (not _iter)
                _reset();
            return data;
        }

    private:

        TinyLinkedList<K> &_instance ;
        Node<K> *_next{nullptr};
        bool _iter = true;

        void _reset(){
            _next = _instance._root;
            _iter = true;
        }
};


#endif

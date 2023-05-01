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
            _size++;
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
                delete(_root);
                _root = nullptr;
                _end = nullptr;
                _size = 0;
                iter._reset();
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
            bool res = _canIter;
            if (not _canIter) _reset();
            return res;
        }
    
        K next(){
            if (_instance.size()){
                K data = _next->data;
                _next = _next->next;
                if (not _next){
                    _canIter = false;
                } 
                return data;
            } else {
                return K();
            }
        }

        /*
        Loops infentily. When end is reached it will start with zero element again
        */
        K loopNext(){
            if (not _canIter)
                _reset();
            K data = next();
            return data;
        }

        /*
        Resets the iterator and starts than from zero element again.
        */
       void reset(){
        _reset();
       }


    private:

        TinyLinkedList<K> &_instance ;
        Node<K> *_next{nullptr};
        bool _canIter{false};

        void _reset(){
            if (_instance.size()){
                _next = _instance._root;
                _canIter = true;
            } else {
                _next = nullptr;
                _canIter = false;
            }
        }
};


#endif

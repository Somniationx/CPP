#ifndef LIST_ITERATOR_H
#define LIST_ITERATOR_H

template<class Iterator, class Ref, class Ptr>
class reverseIterator {
    typedef reverseIterator<Iterator, Ref, Ptr> Self;
private:
    Iterator _it;
public:
    explicit reverseIterator(Iterator it) : _it(it) {}

    Self &operator++() {
        --_it;
        return *this;
    }

    Self &operator--() {
        ++_it;
        return *this;
    }

    bool operator!=(const Self &other) const {
        return _it != other._it;
    }

    Iterator &operator*() {
        Iterator tmp = _it;
        return *--tmp;
    }

    Ptr operator->() {
        return &(operator*());
    }
};

#endif //LIST_ITERATOR_H

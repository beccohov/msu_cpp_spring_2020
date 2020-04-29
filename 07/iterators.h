#pragma once
template <typename EType>
class riterator {
public:
    riterator(EType* p) {
        _curr = p;
    }
    riterator& operator++() {
        _curr--;
        return *this;
    }
    EType& operator*() {
        return *_curr;
    }
    bool operator==(const riterator& b) const {
        return _curr == b._curr;
    }

    bool operator!=(const riterator& b) const {
        return _curr != b._curr;
    }
    riterator& next() {
        _curr--;
        return *this;
    }
private:
    EType * _curr;
};

template <typename EType>
class iterator_ {

public:
    iterator_(EType* p) :_curr(p) {}
    iterator_ & operator++() {
        _curr++;
        return *this;
    }
    iterator_& operator--() {
        _curr--;
        return *this;
    }
    EType& operator*() {
        return *_curr;
    }
    bool operator==(const iterator_& b) const {
        return _curr == b._curr;
    }

    bool operator!=(const iterator_& b) const {
        return _curr != b._curr;
    }
private:
    EType * _curr;
};
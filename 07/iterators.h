#pragma once
template <typename EType>
class riterator {
public:
    riterator(EType* p, EType* min) {
        _curr = p;
        _min = min;
    }
    riterator& operator++() {
        if (_curr > _min) _curr--;
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
        if (_curr > _min) _curr--;
        return *this;
    }
private:
    EType * _curr;
    EType* _min;
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
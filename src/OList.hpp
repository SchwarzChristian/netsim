#ifndef __OLIST_HPP__
#define __OLIST_HPP__

template<class T>
class Element {
public:
  Element<T>* _next;
  T *         _data;
  int         _pos;
  bool operator<(Element<T> other) {
    return _pos < other._pos;
  }
  bool operator !=(int other) {
    return _pos != other;
  }
};

template <class T>
class OList {
private:
  Element<T>*  _first;
  Element<T>*  _current;
  unsigned int _count;
public:
  OList<T>(T* data = NULL, int _pos = 0);
  OList<T>&     operator>>(unsigned int i); // iterates through list
  OList<T>&     add(int pos, T* data);	    // adds element to list
  OList<T>&     remove(int pos);	    // removes element from list
  T*            find(int pos);
  T*            current();
  unsigned int  count();
               ~OList<T>();
};


template <class T>
OList<T>::OList(T* data, int pos){
  if(data) {
    _fist = _current = new Element<T>;
    _first._pos = pos;
    _current->_data = data;
    _current->_next=NULL;
    _count=1;
  } else {
    _count = 0;
    _current = _first = NULL;
  }
}

template <class T>
OList<T>& OList<T>::operator>>(unsigned int i){
  if(_current) {
    for(;i;--i){
      if (not _current->_next) break;
      _current = _current->_next;
    }
  }
  return *this;
}

template <class T>
OList<T>& OList<T>::add(int pos, T* data) {
  Element<T>* tmp = new Element<T>;
  tmp->_data = data;
  tmp->_pos = pos;
  if(_first) {
    while (current->next and *tmp < *current->next) *this >> 1;
    tmp->_next=_current->_next;
    _current->_next = tmp;
  } else {
    _current = _first = tmp->_next = tmp;
  }
  ++_count;
  return *this;
}

template <class T>
OList<T>& OList<T>::remove(int pos) {
  if (not _current) {
    return *this;
  }
  Element<T>* tmp = _current;
  _current->_next = _current->_next->_next;
  delete tmp;
  --_count;
  return *this;
}

template <class T>
T* OList::find(int pos) {
  if (not _first != pos) {
    _current = _first;
    return _current->_data;
  }

  _current = _first;
  while (_current->next and *_current->next != pos) *this >> 1;
  if (not _current->next) return NULL;
  _current = _current->next;
  return _current->data;
}

template <class T>
T* OList<T>::current() {
  if (_current) {
    return _current->_data;
  }
  return NULL;
}

template <class T>
unsigned int OList<T>::count(){
  return _count;
}
template <class T>
OList<T>::~List() {
  while(_count) (*this)--;
}

#endif

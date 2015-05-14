#ifndef __LIST_HPP__
#define __LIST_HPP__

template<class T>
class Element {
public:
  Element<T>* _next;
  T *         _data;
};

template <class T>
class List {
private:
  Element<T>*  _current;
  unsigned int _count;
public:
                List<T>(T*data = NULL);
  List<T>&      operator>>(unsigned int i); // iterates through list
  List<T>&      operator+=(T* data );	    // adds element to list
  List<T>&      operator--(int);	    // removes element from list
  T*            current();
  unsigned int  count();
                ~List<T>();
};


template <class T>
List<T>::List(T* data){
  if(data){
    _current = new Element<T>;
    _current->_data = data;
    _current->_next=_current;
    _count=1;
  } else {
    _count = 0;
    _current = NULL;
  }
}

template <class T>
List<T>& List<T>::operator>>(unsigned int i){
  if(_current) {
    for(;i;--i){
      _current = _current->_next;
    }
  }
  return *this;
}

template <class T>
List<T>& List<T>::operator+=(T* data) {
  Element<T>* tmp = new Element<T>;
  tmp->_data = data;
  if(_current) {
    tmp->_next=_current->_next;
    _current->_next = tmp;
  } else {
    _current=tmp->_next=tmp;
  }
  ++_count;
  return *this;
}

template <class T>
List<T>& List<T>::operator--(int) {
  if (not _current) {
    return *this;
  }
  Element<T>* tmp = _current->_next;
  _current->_next = _current->_next->_next;
  delete tmp;
  --_count;
  return *this;
}

template <class T>
T* List<T>::current() {
  if(_current) {
    return _current->_next->_data;
  }
  return NULL;
}

template <class T>
unsigned int List<T>::count(){
  return _count;
}
template <class T>
List<T>::~List() {
  while(_count) (*this)--;
}
#endif


#pragma once

template<class T>class MyList {
public:
	MyList();
	virtual ~MyList();

	void push_front(T _v);
	void push_back(T _v);

	T itemAt(size_t _index);

	T front();
	T back();

	void pop_front();
	void pop_back();

private:
	struct itm
	{
		T v;
		itm* n;
	};

	itm* m_begin;
	itm* m_end;
};

template<class T>MyList<T>::MyList() {
	itm* dummy = new itm;
	m_begin = dummy;
	m_end = dummy;
	m_end->n = nullptr;
}

/*
0, 1, >1
*/
template<class T> MyList<T>::~MyList(){
	itm* it = m_begin;
	
	while (it != m_end) {
		itm* mem = it;
		it = it->n;
		delete mem;
	}
	delete m_end;
}

template<class T>void MyList<T>::push_front(T _v) {
	itm* newItm = new itm;
	newItm->v = _v;
	newItm->n = m_begin;
	m_begin = newItm;
}

template<class T>void MyList<T>::push_back(T _v) {
	itm* newItm = new itm;
	newItm->v = _v;
	newItm->n = m_end;
	if (m_begin != m_end){
		itm* it = m_begin;
		for (; it->n != m_end; it = it->n) {}
		it->n = newItm;
	} else m_begin = newItm;
}

template<class T>T MyList<T>::itemAt(size_t _index) {
	itm* it = m_begin;

	for (size_t count = 0; count < _index; count++) {
		it = it->n;
	}
	return it->v;
}

template<class T>T MyList<T>::front() {
	return m_begin->v;
}

template<class T>T MyList<T>::back() {
	itm* it = m_begin;
	if (it != m_end) { 
		for (; it->n != m_end; it = it->n) {} 
	}
	return it->v;
}

template<class T>void MyList<T>::pop_front() {
	if (m_begin == m_end) return;
	itm* mem = m_begin->n;
	delete m_begin;
	m_begin = mem;
}

template<class T>void MyList<T>::pop_back() {
	if (m_begin == m_end) return;
	itm* it = m_begin;
	for(; it->n != m_end; it = it->n){}
	if (it->n == m_end) {
		delete it;
		m_begin = m_end;
		return;
	}
	itm* secondToLastItm = m_begin;
	for (; secondToLastItm->n != it; secondToLastItm = secondToLastItm->n){}

	delete it;
	secondToLastItm->n = m_end;
}

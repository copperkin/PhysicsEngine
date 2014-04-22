#ifndef __LIST_H__
#define __LIST_H__

template <class T, int max_length>
class List
{
public:
	List() : _length(0){}
	int length() { return _length; }
	T operator[](int index)
	{
		return _items[index];
	}

	void append(T item)
	{
		if(_length < max_length)
			_items[_length++] = item;
	}
private:
	T _items[max_length];
	int _length;
};

#endif // __LIST_H__

#ifndef mystack_h
#define mystack_h

//#include <cstdef>
#include <cstdlib>

class mystack {

	private:
		char* stackArray;
		size_t stackCapacity;
		size_t stackSize;

	public:
		mystack();
		mystack(const mystack&);
		~mystack();
		mystack& operator=(const mystack&);
		size_t capacity() const;
		size_t size() const;
		bool empty() const;
		void clear();
		void reserve(size_t);
		const char& top() const;
		void push(char);
		void pop();

};

#endif

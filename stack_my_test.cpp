// Writed by wgaunt (wgaunt@student.21-school.ru) in 11.01.2022

#include "Stack.hpp"
#include "Vector.hpp"
#include <iostream>

#define BLACK "\033[30m" << 
#define RED "\033[31m" << 
#define GREEN "\033[32m" << 
#define YELLOW "\033[33m" << 
#define BLUE "\033[34m" << 
#define MAGENTA "\033[35m" << 
#define CYAN "\033[36m" << 
#define WHITE "\033[37m" << 
#define RESET  << "\033[0m"

#include <string>
#include <deque>
#if 0 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include <Map.hpp>
	#include <Stack.hpp>
	#include <Vector.hpp>
	#include <utility.hpp>
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::Stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::Stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

int main(int argc, char** argv)
{
	{
		if (argc != 2)
		{
			std::cerr << "Usage: ./test seed" << std::endl;
			std::cerr << "Provide a seed please" << std::endl;
			std::cerr << "Count value:" << COUNT << std::endl;
			return 1;
		}
		const int seed = atoi(argv[1]);
		srand(seed);

		ft::Vector<std::string> vector_str;
		ft::Vector<int> vector_int;
		ft::Stack<int> stack_int;
		ft::Vector<Buffer> vector_buffer;
		ft::Stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
		ft::map<int, int> map_int;

		for (int i = 0; i < COUNT; i++)
		{
			vector_buffer.push_back(Buffer());
		}

		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer[idx].idx = 5;
		}
		ft::Vector<Buffer>().swap(vector_buffer);

		try
		{
			for (int i = 0; i < COUNT; i++)
			{
				const int idx = rand() % COUNT;
				vector_buffer.at(idx);
				std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
			}
		}
		catch(const std::exception& e)
		{
			//NORMAL ! :P
		}

		for (int i = 0; i < COUNT; ++i)
		{
			map_int.insert(ft::make_pair(rand(), rand()));
		}

		int sum = 0;
		for (int i = 0; i < 10000; i++)
		{
			int access = rand();
			sum += map_int[access];
		}
		std::cout << "should be constant with the same seed: " << sum << std::endl;

		{
			ft::map<int, int> copy = map_int;
		}
		MutantStack<char> iterable_stack;
		for (char letter = 'a'; letter <= 'z'; letter++)
			iterable_stack.push(letter);
		for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
		{
			std::cout << *it;
		}
		std::cout << std::endl;
	}
	{
		ft::Stack<int>	a, b;

		std::cout << std::endl;
		a.push(10);
		a.push(11);
		std::cout << "Stack a <- 10, 11" << std::endl;
		b = a;
		std::cout << "Stack b = Stack a" << std::endl;
		std::cout << std::endl;

		std::cout << std::boolalpha;
		std::cout << YELLOW "Bool operations:" RESET << std::endl << std::endl;
		std::cout << "(a == b) = " << (a == b) << std::endl;
		std::cout << "(a > b)  = " << (a > b) << std::endl;
		a.push(11);
		std::cout << "Stack a <- 11" << std::endl;
		std::cout << "(a != b) = " << (a != b) << std::endl;
		std::cout << "(a <= b) = " << (a <= b) << std::endl;

		std::cout << std::endl << YELLOW "Output all elements in Stack b:" RESET << std::endl << std::endl;

		std::cout << "Stack b.size = " << b.size() << std::endl;
		while (!b.empty())
		{
			std::cout << MAGENTA b.top() RESET << std::endl;
			b.pop();
			std::cout << "Stack b ->" << std::endl;
		}
		std::cout << "Stack b.size = " << b.size() << std::endl;

		a.pop();
		std::cout << std::endl;
		std::cout << "Stack a ->" << std::endl;

		std::cout << std::endl << YELLOW "Copy costructor:" RESET << std::endl << std::endl;

		{
			ft::Stack<int>	c(a);

			std::cout << MAGENTA c.top() RESET << std::endl;
			c.pop();
			std::cout << "Stack c ->" << std::endl;
			std::cout << MAGENTA c.top() RESET << std::endl;
		}
	}
	return 0;
}
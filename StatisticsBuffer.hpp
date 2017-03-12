#ifndef STATISTICS_BUFFER
#define STATISTICS_BUFFER

#include "DataContainer.hpp"

/*
Class definition for StatisticsBuffer.
template args:
	N 		-- the length of the buffer
	T_width -- the width of each element in the buffer
*/
template<size_t N, size_t T_width>
class StatisticsBuffer {
public:
	StatisticsBuffer();
	~StatisticsBuffer();
	void add(const DataContainer<T_width>& dc);

	//getters
	double getStandardDeviationI(int index) const;
	double getMeanI(int index) const;

	double getStandardDeviationAll() const;
	double getMeanAll() const;

	friend std::ostream& operator<<(std::ostream&, const StatisticsBuffer<N, T_width>&);
private:
	DataContainer<T_width>* buffer[N];
	//"zeroIndex" tracks the index of the oldest element in the buffer
	int zeroIndex;
	
	//"currIndex" tracks the index of the next open location in the buffer
	int currIndex;

	bool isEmpty;

	void popOldestElement();
	std::ostream& printSB(std::ostream& os) const;
};

//CLASS METHOD DEFINITIONS////////////////////////////////////////////////

/*default constructor*/
template<size_t N, size_t T_width>
StatisticsBuffer<N,T_width>::StatisticsBuffer() {
	for (int i=0; i<N; i++) {
		buffer[i] = NULL;
	}
	zeroIndex = 0;
	currIndex = 0;
	isEmpty = true;
}

/*destructor*/
template<size_t N, size_t T_width>
StatisticsBuffer<N, T_width>::~StatisticsBuffer() {
	for (int i=0; i<N; i++) {
		delete buffer[i];
	}
}

/*
void Add()
Add a new element to the next open spot in the buffer.
This buffer is implemented as a circular array to avoid unnecessary copying
of the internal DataContainers upon adding, which would be expensive.
*/
template<size_t N, size_t T_width>
void StatisticsBuffer<N, T_width>::add(const DataContainer<T_width>& dc) {
	//if we need to overwrite the oldest element, pop it
	if(!isEmpty && currIndex == zeroIndex) popOldestElement();
	buffer[++currIndex] = new DataContainer<T_width>(dc);
	isEmpty = false;
}

/*
void PopOldestElement()
Deallocates the oldest element in the buffer, and then updates 
zeroIndex to reflect the new location
of the buffer in the circular array.
*/
template<size_t N, size_t T_width>
void StatisticsBuffer<N, T_width>::popOldestElement() {
	delete buffer[zeroIndex];
	buffer[zeroIndex] = NULL;
	zeroIndex = (zeroIndex+1)%N;
}

//GETTERS//
template<size_t N, size_t T_width>
double StatisticsBuffer<N, T_width>::getStandardDeviationI(int index) const {
	return 5.0;
}

template<size_t N, size_t T_width>
double StatisticsBuffer<N, T_width>::getMeanI(int index) const {
	return 5.0;
}

template<size_t N, size_t T_width>
double StatisticsBuffer<N, T_width>::getStandardDeviationAll() const {
	return 5.0;
}

template<size_t N, size_t T_width>
double StatisticsBuffer<N, T_width>::getMeanAll() const {
	return 5.0;
}

//printer functions
template<size_t N, size_t T_width>
std::ostream& StatisticsBuffer<N, T_width>::printSB(std::ostream& os) const {
	if (isEmpty) std::cout << "--buffer is empty--\n";
	else {
		std::cout << "From oldest to newest:\n" << buffer[zeroIndex];
		for (int i=zeroIndex+1; i!=currIndex; i=(i+1)%N) {
			std::cout << buffer[i];
		}
	}
	return os;
}

template<size_t N, size_t T_width>
std::ostream& operator<<(std::ostream& os, const StatisticsBuffer<N, T_width>& sb) {
	return sb.printSB(os);
}

#endif
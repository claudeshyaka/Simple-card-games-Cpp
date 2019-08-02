#ifndef NULLBUFFER_H
#define NULLBUFFER_H

// Defining a null buffer for debugging purposes.
class NullBuffer : public std::streambuf
{
public:
	int overflow(int c);
};




#endif // NULLBUFFER_H
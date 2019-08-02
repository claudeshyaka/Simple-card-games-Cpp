#include "stdafx.h"
#include <iostream>

using namespace std;
#include "nullbuffer.h"

int NullBuffer::overflow(int c) {
	return c;
}
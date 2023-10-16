#include "unistd.h"

int main()
{
	write(1, "123\n123", 8);
}
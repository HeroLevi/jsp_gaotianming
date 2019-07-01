#include "mysql.h"
#include "TCPNet.h"
#include "TCPKernel.h"

int main(void)
{
	TCPKernel tk;
	tk.Open();
	return 0;
}

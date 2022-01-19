#include "stdafx.h"
#include "FA_API.h"
int main()
{
	//Assign and open the COM port
	char iPort = 5;
	FA_ComOpen(iPort);
	//Draw a triangle
	for (int i = 0; i < 3; i++)
	{
		FA_Forwards(iPort, 500);
		FA_Left(iPort, 120);
	}
	//Close the COM port
	FA_ComClose(iPort);
	return 0;
}
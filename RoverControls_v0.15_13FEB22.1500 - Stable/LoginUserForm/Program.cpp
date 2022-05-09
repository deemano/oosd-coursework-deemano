#include "MyForm.h"
#include "stdafx.h"
#include <stdlib.h>
#include < cstdlib >




using namespace System;
using namespace System::Windows::Forms;

void main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	LoginUserForm::MyForm myForm;

 
	

	myForm.ShowDialog();
	User^ user = myForm.userLog;

	if (user != nullptr) {
		MessageBox::Show("Succesfull authentication "+ user->name,
			"Authetication", MessageBoxButtons::OK);
		   int result = system("start D:\\RoverC\\Debug\\RoverControlConsole.exe");
	}
	else {
		MessageBox::Show("Authentication Canceled",
			"Authetication", MessageBoxButtons::OK);
	}


	

	
}


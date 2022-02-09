#include "MyForm.h"
//#include "MainForm.h"

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
			"Program.cpp", MessageBoxButtons::OK);
	}
	else {
		MessageBox::Show("Authentication Canceled",
			"Program.cpp", MessageBoxButtons::OK);
	}
}

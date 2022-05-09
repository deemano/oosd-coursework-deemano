#include "RecPass.h"
//#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;

void main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	LoginUserForm::RecPass recPassForm;

	recPassForm.ShowDialog();
	User^ user = recPassForm.userRec;

	if (user != nullptr) {
		MessageBox::Show("The information " + user->name,
			"Go forward", MessageBoxButtons::OK);
	}
	else {
		MessageBox::Show("Authentication Canceled",
			"Try again", MessageBoxButtons::OK);
	}
}

#pragma once
#include "User.h"
#include "AddUserForm.h"
#include "RecPass.h"


namespace LoginUserForm {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::SqlClient;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ labelUser;
	protected:
	private: System::Windows::Forms::Label^ labelPass;
	private: System::Windows::Forms::TextBox^ inputUser;
	private: System::Windows::Forms::TextBox^ inputPass;
	private: System::Windows::Forms::Button^ btnOk;
	private: System::Windows::Forms::Button^ btnCl;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ btnAddU;
	private: System::Windows::Forms::Label^ forgetPassL;

	private: System::Windows::Forms::Button^ btnRecPass;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->labelUser = (gcnew System::Windows::Forms::Label());
			this->labelPass = (gcnew System::Windows::Forms::Label());
			this->inputUser = (gcnew System::Windows::Forms::TextBox());
			this->inputPass = (gcnew System::Windows::Forms::TextBox());
			this->btnOk = (gcnew System::Windows::Forms::Button());
			this->btnCl = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->btnAddU = (gcnew System::Windows::Forms::Button());
			this->forgetPassL = (gcnew System::Windows::Forms::Label());
			this->btnRecPass = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// labelUser
			// 
			this->labelUser->AutoSize = true;
			this->labelUser->Location = System::Drawing::Point(54, 39);
			this->labelUser->Name = L"labelUser";
			this->labelUser->Size = System::Drawing::Size(36, 16);
			this->labelUser->TabIndex = 0;
			this->labelUser->Text = L"User";
			// 
			// labelPass
			// 
			this->labelPass->AutoSize = true;
			this->labelPass->Location = System::Drawing::Point(54, 76);
			this->labelPass->Name = L"labelPass";
			this->labelPass->Size = System::Drawing::Size(67, 16);
			this->labelPass->TabIndex = 1;
			this->labelPass->Text = L"Password";
			// 
			// inputUser
			// 
			this->inputUser->Location = System::Drawing::Point(173, 37);
			this->inputUser->Name = L"inputUser";
			this->inputUser->Size = System::Drawing::Size(195, 22);
			this->inputUser->TabIndex = 2;
			// 
			// inputPass
			// 
			this->inputPass->Location = System::Drawing::Point(174, 73);
			this->inputPass->Name = L"inputPass";
			this->inputPass->PasswordChar = '*';
			this->inputPass->Size = System::Drawing::Size(193, 22);
			this->inputPass->TabIndex = 3;
			// 
			// btnOk
			// 
			this->btnOk->Location = System::Drawing::Point(73, 179);
			this->btnOk->Name = L"btnOk";
			this->btnOk->Size = System::Drawing::Size(136, 47);
			this->btnOk->TabIndex = 4;
			this->btnOk->Text = L"OK";
			this->btnOk->UseVisualStyleBackColor = true;
			this->btnOk->Click += gcnew System::EventHandler(this, &MyForm::btnOk_Click);
			// 
			// btnCl
			// 
			this->btnCl->Location = System::Drawing::Point(277, 180);
			this->btnCl->Name = L"btnCl";
			this->btnCl->Size = System::Drawing::Size(156, 46);
			this->btnCl->TabIndex = 5;
			this->btnCl->Text = L"Cancel";
			this->btnCl->UseVisualStyleBackColor = true;
			this->btnCl->Click += gcnew System::EventHandler(this, &MyForm::btnCl_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(54, 276);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(127, 16);
			this->label1->TabIndex = 6;
			this->label1->Text = L"Are you a new user\?";
			// 
			// btnAddU
			// 
			this->btnAddU->Location = System::Drawing::Point(249, 273);
			this->btnAddU->Name = L"btnAddU";
			this->btnAddU->Size = System::Drawing::Size(184, 23);
			this->btnAddU->TabIndex = 7;
			this->btnAddU->Text = L"Create new user";
			this->btnAddU->UseVisualStyleBackColor = true;
			this->btnAddU->Click += gcnew System::EventHandler(this, &MyForm::btnAddU_Click);
			// 
			// forgetPassL
			// 
			this->forgetPassL->AutoSize = true;
			this->forgetPassL->Location = System::Drawing::Point(54, 137);
			this->forgetPassL->Name = L"forgetPassL";
			this->forgetPassL->Size = System::Drawing::Size(188, 16);
			this->forgetPassL->TabIndex = 8;
			this->forgetPassL->Text = L"Did you forget your password\?";
			// 
			// btnRecPass
			// 
			this->btnRecPass->Location = System::Drawing::Point(250, 137);
			this->btnRecPass->Name = L"btnRecPass";
			this->btnRecPass->Size = System::Drawing::Size(183, 23);
			this->btnRecPass->TabIndex = 10;
			this->btnRecPass->Text = L"Recover password";
			this->btnRecPass->UseVisualStyleBackColor = true;
			this->btnRecPass->Click += gcnew System::EventHandler(this, &MyForm::btnRecPass_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(569, 323);
			this->Controls->Add(this->btnRecPass);
			this->Controls->Add(this->forgetPassL);
			this->Controls->Add(this->btnAddU);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->btnCl);
			this->Controls->Add(this->btnOk);
			this->Controls->Add(this->inputPass);
			this->Controls->Add(this->inputUser);
			this->Controls->Add(this->labelPass);
			this->Controls->Add(this->labelUser);
			this->Name = L"MyForm";
			this->Text = L"Login User";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btnCl_Click(System::Object^ sender, System::EventArgs^ e) {

		this->Close();
	}
	public:User^ userLog=nullptr;

	private: System::Void btnAddU_Click(System::Object^ sender, System::EventArgs^ e) {
			
			
			LoginUserForm::AddUserForm addUserForm;

			addUserForm.ShowDialog();

				
			return;

		  }
	private: System::Void btnOk_Click(System::Object^ sender, System::EventArgs^ e) {

	String^ user = this->inputUser->Text;
	String^ password = this->inputPass->Text;

	if (user->Length == 0 || password->Length == 0) {
		MessageBox::Show("Please enter user and password",
			"User or Password Empty", MessageBoxButtons::OK);
		return;
	}
	try {
		String^ connString = "Data Source=localhost\\hammada;Initial Catalog=login_user;Integrated Security=True";
		SqlConnection sqlConn(connString);
		sqlConn.Open();

		String^ sqlQuery = "SELECT * FROM users WHERE name=@user AND password=@password;";
		SqlCommand command(sqlQuery, % sqlConn);
		command.Parameters->AddWithValue("@user", user);
		command.Parameters->AddWithValue("@password", password);

		
		SqlDataReader^ reader = command.ExecuteReader();
		if (reader->Read()) {
			userLog = gcnew User;
			userLog->id = reader->GetInt32(0);
			userLog->name = reader->GetString(1);
			userLog->password = reader->GetString(2);

			this->Close();
		}
		else {
			MessageBox::Show("User or password is incorrect",
				"User or Password wrong", MessageBoxButtons::OK);
		}
	}
	catch (Exception^ e) {
		MessageBox::Show("Failed to connect to database",
			"Database Connection Error", MessageBoxButtons::OK);
	}
}

private: System::Void btnRecPass_Click(System::Object^ sender, System::EventArgs^ e) {
	
	LoginUserForm::RecPass recPass;

	recPass.ShowDialog();


	return;

}
};
}

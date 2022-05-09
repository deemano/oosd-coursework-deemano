#pragma once
#include "RecPass.h"

namespace LoginUserForm {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for NewPassForm
	/// </summary>
	public ref class NewPassForm : public System::Windows::Forms::Form
	{
	
	

	public:


		NewPassForm(void)
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
		~NewPassForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ helloL;
	protected:
	private: System::Windows::Forms::Label^ enterNewPL;
	private: System::Windows::Forms::TextBox^ entNewP;
	private: System::Windows::Forms::Button^ btnOk;
	private: System::Windows::Forms::Button^ btnCl;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->helloL = (gcnew System::Windows::Forms::Label());
			this->enterNewPL = (gcnew System::Windows::Forms::Label());
			this->entNewP = (gcnew System::Windows::Forms::TextBox());
			this->btnOk = (gcnew System::Windows::Forms::Button());
			this->btnCl = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// helloL
			// 
			this->helloL->AutoSize = true;
			this->helloL->Location = System::Drawing::Point(39, 48);
			this->helloL->Name = L"helloL";
			this->helloL->Size = System::Drawing::Size(37, 13);
			this->helloL->TabIndex = 0;
			this->helloL->Text = L"Welecome back " ;
			// 
			// enterNewPL
			// 
			this->enterNewPL->AutoSize = true;
			this->enterNewPL->Location = System::Drawing::Point(42, 94);
			this->enterNewPL->Name = L"enterNewPL";
			this->enterNewPL->Size = System::Drawing::Size(126, 13);
			this->enterNewPL->TabIndex = 1;
			this->enterNewPL->Text = L"Enter your new password";
			// 
			// entNewP
			// 
			this->entNewP->Location = System::Drawing::Point(42, 125);
			this->entNewP->Name = L"entNewP";
			this->entNewP->PasswordChar = '*';
			this->entNewP->Size = System::Drawing::Size(167, 20);
			this->entNewP->TabIndex = 2;
			// 
			// btnOk
			// 
			this->btnOk->Location = System::Drawing::Point(42, 211);
			this->btnOk->Name = L"btnOk";
			this->btnOk->Size = System::Drawing::Size(75, 23);
			this->btnOk->TabIndex = 3;
			this->btnOk->Text = L"OK";
			this->btnOk->UseVisualStyleBackColor = true;
			this->btnOk->Click += gcnew System::EventHandler(this, &NewPassForm::btnOk_Click);
			// 
			// btnCl
			// 
			this->btnCl->Location = System::Drawing::Point(134, 211);
			this->btnCl->Name = L"btnCl";
			this->btnCl->Size = System::Drawing::Size(75, 23);
			this->btnCl->TabIndex = 4;
			this->btnCl->Text = L"Cancel";
			this->btnCl->UseVisualStyleBackColor = true;
			this->btnCl->Click += gcnew System::EventHandler(this, &NewPassForm::btnCl_Click);
			// 
			// NewPassForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->btnCl);
			this->Controls->Add(this->btnOk);
			this->Controls->Add(this->entNewP);
			this->Controls->Add(this->enterNewPL);
			this->Controls->Add(this->helloL);
			this->Name = L"NewPassForm";
			this->Text = L"NewPassForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btnCl_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
	private: User^ userRec = nullptr;

	private: System::Void btnOk_Click(System::Object^ sender, System::EventArgs^ e) {

		
	}

	

	
};
}

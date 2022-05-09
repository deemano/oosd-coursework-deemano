#pragma once
#include "User.h"

namespace LoginUserForm {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::SqlClient;

	/// <summary>
	/// Summary for AddUserForm
	/// </summary>
	public ref class AddUserForm : public System::Windows::Forms::Form
	{
	public:
		AddUserForm(void)
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
		~AddUserForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ newU;
	private: System::Windows::Forms::TextBox^ newP;


	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::ComboBox^ selectQ;


	private: System::Windows::Forms::Button^ btnOkAdd;
	private: System::Windows::Forms::Button^ btnClAdd;
	private: System::Windows::Forms::Label^ secretAL;
	private: System::Windows::Forms::TextBox^ secretA;


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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(AddUserForm::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->newU = (gcnew System::Windows::Forms::TextBox());
			this->newP = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->selectQ = (gcnew System::Windows::Forms::ComboBox());
			this->btnOkAdd = (gcnew System::Windows::Forms::Button());
			this->btnClAdd = (gcnew System::Windows::Forms::Button());
			this->secretAL = (gcnew System::Windows::Forms::Label());
			this->secretA = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(75, 39);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(70, 16);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Enter User";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(75, 91);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(101, 16);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Enter Password";
			// 
			// newU
			// 
			this->newU->Location = System::Drawing::Point(223, 39);
			this->newU->Name = L"newU";
			this->newU->Size = System::Drawing::Size(244, 22);
			this->newU->TabIndex = 2;
			// 
			// newP
			// 
			this->newP->Location = System::Drawing::Point(223, 91);
			this->newP->Name = L"newP";
			this->newP->Size = System::Drawing::Size(244, 22);
			this->newP->TabIndex = 3;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(75, 144);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(102, 16);
			this->label3->TabIndex = 4;
			this->label3->Text = L"Secret Question";
			this->label3->Click += gcnew System::EventHandler(this, &AddUserForm::label3_Click);
			// 
			// selectQ
			// 
			this->selectQ->FormattingEnabled = true;
			this->selectQ->Items->AddRange(gcnew cli::array< System::Object^  >(3) {
				L"What is your mother\'s name\?", L"Where did you get your fist job\?",
					L"Who is your favourite hero\?"
			});
			this->selectQ->Location = System::Drawing::Point(223, 144);
			this->selectQ->Name = L"selectQ";
			this->selectQ->Size = System::Drawing::Size(244, 24);
			this->selectQ->TabIndex = 5;
			this->selectQ->Text = L"Chose a question";
			this->selectQ->SelectedIndexChanged += gcnew System::EventHandler(this, &AddUserForm::selectQ_SelectedIndexChanged);
			// 
			// btnOkAdd
			// 
			this->btnOkAdd->Location = System::Drawing::Point(78, 261);
			this->btnOkAdd->Name = L"btnOkAdd";
			this->btnOkAdd->Size = System::Drawing::Size(185, 30);
			this->btnOkAdd->TabIndex = 6;
			this->btnOkAdd->Text = L"OK";
			this->btnOkAdd->UseVisualStyleBackColor = true;
			this->btnOkAdd->Click += gcnew System::EventHandler(this, &AddUserForm::btnOkAdd_Click);
			// 
			// btnClAdd
			// 
			this->btnClAdd->Location = System::Drawing::Point(292, 261);
			this->btnClAdd->Name = L"btnClAdd";
			this->btnClAdd->Size = System::Drawing::Size(175, 30);
			this->btnClAdd->TabIndex = 7;
			this->btnClAdd->Text = L"Cancel";
			this->btnClAdd->UseVisualStyleBackColor = true;
			this->btnClAdd->Click += gcnew System::EventHandler(this, &AddUserForm::btnClAdd_Click);
			// 
			// secretAL
			// 
			this->secretAL->AutoSize = true;
			this->secretAL->Location = System::Drawing::Point(75, 194);
			this->secretAL->Name = L"secretAL";
			this->secretAL->Size = System::Drawing::Size(93, 16);
			this->secretAL->TabIndex = 8;
			this->secretAL->Text = L"Secret Answer";
			// 
			// secretA
			// 
			this->secretA->Location = System::Drawing::Point(223, 194);
			this->secretA->Name = L"secretA";
			this->secretA->Size = System::Drawing::Size(244, 22);
			this->secretA->TabIndex = 9;
			// 
			// AddUserForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(521, 336);
			this->Controls->Add(this->secretA);
			this->Controls->Add(this->secretAL);
			this->Controls->Add(this->btnClAdd);
			this->Controls->Add(this->btnOkAdd);
			this->Controls->Add(this->selectQ);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->newP);
			this->Controls->Add(this->newU);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"AddUserForm";
			this->Text = L"AddUserForm";
			this->Load += gcnew System::EventHandler(this, &AddUserForm::AddUserForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void vScrollBar1_Scroll(System::Object^ sender, System::Windows::Forms::ScrollEventArgs^ e) {
	}
private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void AddUserForm_Load(System::Object^ sender, System::EventArgs^ e) {
}

public: User^ user = nullptr;

private: System::Void btnOkAdd_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ newUser = this->newU->Text;
	String^ newPassword = this->newP->Text;
	String^ newSecretQ = this->selectQ->Text;
	String^ newSecretA = this->secretA->Text;

	if (newUser->Length == 0 || newPassword->Length == 0 || newSecretQ->Length == 0 || newSecretA->Length == 0) {
		MessageBox::Show("Please fill all the fields",
			"Fields Empty", MessageBoxButtons::OK);
		return;
	}
	try {
	
	
		String^ connString = "Data Source=localhost\\hammada;Initial Catalog=login_user;Integrated Security=True";
		SqlConnection sqlConn(connString);
		sqlConn.Open();

		String^ sqlQuery ="INSERT INTO Users(name, password, secretQ, secretA) VALUES(@newUser, @newPassword, @newSecretQ, @newSecretA);";
		SqlCommand command(sqlQuery, % sqlConn);
		command.Parameters->AddWithValue("@newUser", newUser);
		command.Parameters->AddWithValue("@newPassword", newPassword);
		command.Parameters->AddWithValue("@newSecretQ", newSecretQ);
		command.Parameters->AddWithValue("@newSecretA", newSecretA);
		
		command.ExecuteNonQuery();
		user = gcnew User;
		user->name = newUser;
		user->password = newPassword;
		user->secretQ = newSecretQ;
		user->secretA = newSecretA;
		

		this->Close();
	}
	catch (Exception^ e) {
		MessageBox::Show("Failed to connect to database",
			"Database Connection Error", MessageBoxButtons::OK);
	}

}
private: System::Void selectQ_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void btnClAdd_Click(System::Object^ sender, System::EventArgs^ e) {

	this->Close();
}
};
} 


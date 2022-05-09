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
	/// Summary for RecPass
	/// </summary>
	public ref class RecPass : public System::Windows::Forms::Form
	{

	
	public:
		RecPass(void)
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
		~RecPass()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ recEnterUser;
	protected:
	private: System::Windows::Forms::Label^ recEnterQ;
	private: System::Windows::Forms::Label^ recEnterA;
	private: System::Windows::Forms::TextBox^ recU;

	private: System::Windows::Forms::TextBox^ recSecretA;


	private: System::Windows::Forms::ComboBox^ recSelectQ;
	private: System::Windows::Forms::Button^ recOk;
	private: System::Windows::Forms::Button^ btnRecCl;
	private: System::Windows::Forms::Label^ enterNewPL;
	private: System::Windows::Forms::TextBox^ enterNewP;



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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(RecPass::typeid));
			this->recEnterUser = (gcnew System::Windows::Forms::Label());
			this->recEnterQ = (gcnew System::Windows::Forms::Label());
			this->recEnterA = (gcnew System::Windows::Forms::Label());
			this->recU = (gcnew System::Windows::Forms::TextBox());
			this->recSecretA = (gcnew System::Windows::Forms::TextBox());
			this->recSelectQ = (gcnew System::Windows::Forms::ComboBox());
			this->recOk = (gcnew System::Windows::Forms::Button());
			this->btnRecCl = (gcnew System::Windows::Forms::Button());
			this->enterNewPL = (gcnew System::Windows::Forms::Label());
			this->enterNewP = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// recEnterUser
			// 
			this->recEnterUser->AutoSize = true;
			this->recEnterUser->Location = System::Drawing::Point(57, 78);
			this->recEnterUser->Name = L"recEnterUser";
			this->recEnterUser->Size = System::Drawing::Size(67, 16);
			this->recEnterUser->TabIndex = 0;
			this->recEnterUser->Text = L"Enter user";
			// 
			// recEnterQ
			// 
			this->recEnterQ->AutoSize = true;
			this->recEnterQ->Location = System::Drawing::Point(57, 135);
			this->recEnterQ->Name = L"recEnterQ";
			this->recEnterQ->Size = System::Drawing::Size(140, 16);
			this->recEnterQ->TabIndex = 1;
			this->recEnterQ->Text = L"Chose secret question";
			// 
			// recEnterA
			// 
			this->recEnterA->AutoSize = true;
			this->recEnterA->Location = System::Drawing::Point(57, 196);
			this->recEnterA->Name = L"recEnterA";
			this->recEnterA->Size = System::Drawing::Size(124, 16);
			this->recEnterA->TabIndex = 2;
			this->recEnterA->Text = L"Enter secret answer";
			// 
			// recU
			// 
			this->recU->Location = System::Drawing::Point(236, 78);
			this->recU->Name = L"recU";
			this->recU->Size = System::Drawing::Size(160, 22);
			this->recU->TabIndex = 3;
			this->recU->TextChanged += gcnew System::EventHandler(this, &RecPass::recU_TextChanged);
			// 
			// recSecretA
			// 
			this->recSecretA->Location = System::Drawing::Point(236, 190);
			this->recSecretA->Name = L"recSecretA";
			this->recSecretA->Size = System::Drawing::Size(160, 22);
			this->recSecretA->TabIndex = 4;
			// 
			// recSelectQ
			// 
			this->recSelectQ->FormattingEnabled = true;
			this->recSelectQ->Items->AddRange(gcnew cli::array< System::Object^  >(3) {
				L"What is your mother\'s name\?", L"Where did you get your fist job\?",
					L"Who is your favourite hero\?"
			});
			this->recSelectQ->Location = System::Drawing::Point(236, 138);
			this->recSelectQ->Name = L"recSelectQ";
			this->recSelectQ->Size = System::Drawing::Size(159, 24);
			this->recSelectQ->TabIndex = 5;
			this->recSelectQ->Text = L"Select a question";
			this->recSelectQ->SelectedIndexChanged += gcnew System::EventHandler(this, &RecPass::recSelectQ_SelectedIndexChanged);
			// 
			// recOk
			// 
			this->recOk->Location = System::Drawing::Point(106, 318);
			this->recOk->Name = L"recOk";
			this->recOk->Size = System::Drawing::Size(130, 29);
			this->recOk->TabIndex = 6;
			this->recOk->Text = L"Ok";
			this->recOk->UseVisualStyleBackColor = true;
			this->recOk->Click += gcnew System::EventHandler(this, &RecPass::recOk_Click);
			// 
			// btnRecCl
			// 
			this->btnRecCl->Location = System::Drawing::Point(275, 318);
			this->btnRecCl->Name = L"btnRecCl";
			this->btnRecCl->Size = System::Drawing::Size(121, 29);
			this->btnRecCl->TabIndex = 7;
			this->btnRecCl->Text = L"Cancel";
			this->btnRecCl->UseVisualStyleBackColor = true;
			this->btnRecCl->Click += gcnew System::EventHandler(this, &RecPass::btnRecCl_Click);
			// 
			// enterNewPL
			// 
			this->enterNewPL->AutoSize = true;
			this->enterNewPL->Location = System::Drawing::Point(57, 251);
			this->enterNewPL->Name = L"enterNewPL";
			this->enterNewPL->Size = System::Drawing::Size(127, 16);
			this->enterNewPL->TabIndex = 8;
			this->enterNewPL->Text = L"Enter new password";
			// 
			// enterNewP
			// 
			this->enterNewP->Location = System::Drawing::Point(235, 248);
			this->enterNewP->Name = L"enterNewP";
			this->enterNewP->Size = System::Drawing::Size(160, 22);
			this->enterNewP->TabIndex = 9;
			// 
			// RecPass
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(465, 403);
			this->Controls->Add(this->enterNewP);
			this->Controls->Add(this->enterNewPL);
			this->Controls->Add(this->btnRecCl);
			this->Controls->Add(this->recOk);
			this->Controls->Add(this->recSelectQ);
			this->Controls->Add(this->recSecretA);
			this->Controls->Add(this->recU);
			this->Controls->Add(this->recEnterA);
			this->Controls->Add(this->recEnterQ);
			this->Controls->Add(this->recEnterUser);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"RecPass";
			this->Text = L"RecPass";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void recSelectQ_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	}
private: User^ userRec = nullptr;

private: System::Void recOk_Click(System::Object^ sender, System::EventArgs^ e) {

	String^ recUserF = this->recU->Text;
	String^ recSecretQ = this->recSelectQ->Text;
	String^ recSecretA = this->recSecretA->Text;
	String^ enterNewP = this->enterNewP->Text;


	if (recUserF->Length == 0 || recSecretQ->Length == 0 || recSecretQ->Length == 0 || enterNewP->Length==0 ) {
		MessageBox::Show("Please fill all the fields",
			"Fields empty", MessageBoxButtons::OK);
		return;
	}

	try {
		String^ connString = "Data Source=localhost\\hammada;Initial Catalog=login_user;Integrated Security=True";
		SqlConnection sqlConn(connString);
		sqlConn.Open();

		String^ sqlQuery = "SELECT * FROM users WHERE name=@recUserF AND secretQ=@recSecretQ AND secretA=@recSecretA;";
		SqlCommand command(sqlQuery, % sqlConn);
		command.Parameters->AddWithValue("@recUserF", recUserF);
		command.Parameters->AddWithValue("@recSecretQ", recSecretQ);
		command.Parameters->AddWithValue("@recSecretA", recSecretA);


		SqlDataReader^ reader = command.ExecuteReader();
		if (reader->Read()) {
			userRec = gcnew User;
			userRec->id = reader->GetInt32(0);
			userRec->name = reader->GetString(1);
			userRec->secretQ = reader->GetString(3);
			userRec->secretQ = reader->GetString(4);

			
			this->Close();
			
		}
		else {
			MessageBox::Show("The information you entered is not correct",
				"Please, try again", MessageBoxButtons::OK);
		}
		

		if (userRec != nullptr) {

			String^ connString = "Data Source=localhost\\hammada;Initial Catalog=login_user;Integrated Security=True";
			SqlConnection sqlConn(connString);
			sqlConn.Open();

			String^ sqlQuery = "UPDATE users SET password=@enterNewP WHERE name=@recUserF;";
			SqlCommand command(sqlQuery, % sqlConn);
			command.Parameters->AddWithValue("@recUserF", recUserF);
			command.Parameters->AddWithValue("@enterNewP", enterNewP);

			command.ExecuteNonQuery();
			userRec = gcnew User;
			userRec->password = enterNewP;
			

			this->Close();

			MessageBox::Show("Well done",
				"Your password has been changed", MessageBoxButtons::OK);

			
			return;
			
		}
		
	}
		catch (Exception^ e) {
			MessageBox::Show("Failed to connect to database",
				"Database Connection Error", MessageBoxButtons::OK);
		}
	}
private: System::Void btnRecCl_Click(System::Object^ sender, System::EventArgs^ e) {

	this->Close();
}
private: System::Void recU_TextChanged(System::Object^ sender, System::EventArgs^ e) {


}
};
}

#pragma once

namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;

	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;
		Bitmap^ imgData;
		System::Windows::Forms::RadioButton^ NormalRadio;
		System::Windows::Forms::RadioButton^ GrayScaleRadio;
		System::Windows::Forms::RadioButton^ BlackWhiteRadio;
		System::Windows::Forms::Button^ OpenImageButton;
		System::Windows::Forms::TextBox^ textBox1;
		System::Windows::Forms::PictureBox^ pictureBox1;
		System::Windows::Forms::OpenFileDialog^ openFileDialog1;
		String^ Filename;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->NormalRadio = (gcnew System::Windows::Forms::RadioButton());
			this->GrayScaleRadio = (gcnew System::Windows::Forms::RadioButton());
			this->BlackWhiteRadio = (gcnew System::Windows::Forms::RadioButton());
			this->OpenImageButton = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// NormalRadio
			// 
			this->NormalRadio->AutoSize = true;
			this->NormalRadio->Location = System::Drawing::Point(12, 12);
			this->NormalRadio->Name = L"NormalRadio";
			this->NormalRadio->Size = System::Drawing::Size(58, 17);
			this->NormalRadio->TabIndex = 0;
			this->NormalRadio->TabStop = true;
			this->NormalRadio->Text = L"Normal";
			this->NormalRadio->UseVisualStyleBackColor = true;
			// 
			// GrayScaleRadio
			// 
			this->GrayScaleRadio->AutoSize = true;
			this->GrayScaleRadio->Location = System::Drawing::Point(12, 35);
			this->GrayScaleRadio->Name = L"GrayScaleRadio";
			this->GrayScaleRadio->Size = System::Drawing::Size(77, 17);
			this->GrayScaleRadio->TabIndex = 1;
			this->GrayScaleRadio->TabStop = true;
			this->GrayScaleRadio->Text = L"Grey Scale";
			this->GrayScaleRadio->UseVisualStyleBackColor = true;
			// 
			// BlackWhiteRadio
			// 
			this->BlackWhiteRadio->AutoSize = true;
			this->BlackWhiteRadio->Location = System::Drawing::Point(12, 58);
			this->BlackWhiteRadio->Name = L"BlackWhiteRadio";
			this->BlackWhiteRadio->Size = System::Drawing::Size(83, 17);
			this->BlackWhiteRadio->TabIndex = 2;
			this->BlackWhiteRadio->TabStop = true;
			this->BlackWhiteRadio->Text = L"Black White";
			this->BlackWhiteRadio->UseVisualStyleBackColor = true;
			// 
			// OpenImageButton
			// 
			this->OpenImageButton->Location = System::Drawing::Point(167, 207);
			this->OpenImageButton->Name = L"OpenImageButton";
			this->OpenImageButton->Size = System::Drawing::Size(105, 42);
			this->OpenImageButton->TabIndex = 3;
			this->OpenImageButton->Text = L"Open Image";
			this->OpenImageButton->UseVisualStyleBackColor = true;
			this->OpenImageButton->Click += gcnew EventHandler(this, &MyForm::OpenImageButton_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(148, 57);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 4;
			// 
			// MyForm
			// 
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->OpenImageButton);
			this->Controls->Add(this->BlackWhiteRadio);
			this->Controls->Add(this->GrayScaleRadio);
			this->Controls->Add(this->NormalRadio);
			this->Name = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		Void OpenImageButton_Click(Object^ sender, EventArgs^ e)
		{
			if (BlackWhiteRadio->Checked)
			{
				if (textBox1->Text->Length <= 0)
				{
					MessageBox::Show("You Must enter threshhold for black & white mode", "", MessageBoxButtons::OK);
					this->Close();
					return;
				}
			}

			BlackWhiteRadio->Visible = false;
			GrayScaleRadio->Visible = false;
			NormalRadio->Visible = false;
			OpenImageButton->Visible = false;
			textBox1->Visible = false;

			openFileDialog1 = gcnew OpenFileDialog;
			openFileDialog1->InitialDirectory = "c:\\";
			openFileDialog1->Filter = "Image Files(*.BMP;*.JPG;*.GIF)|*.BMP;*.JPG;*.GIF|All files (*.*)|*.*";
			openFileDialog1->FilterIndex = 1;
			openFileDialog1->RestoreDirectory = true;
			openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog1_FileOk);

			openFileDialog1->ShowDialog();

			if (Filename->Length <= 0)
			{
				MessageBox::Show("You Must choose file", "", MessageBoxButtons::OK);
				this->Close();
				return;
			}

			imgData = gcnew Bitmap(Filename);

			pictureBox1 = gcnew PictureBox();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			pictureBox1->Location = Drawing::Point(0, 0);
			pictureBox1->Name = L"pictureBox1";
			pictureBox1->Size = Drawing::Size(imgData->Width, imgData->Height);
			pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;

			this->Controls->Add(this->pictureBox1);

			this->ClientSize = System::Drawing::Size(imgData->Width, imgData->Height);

			if (NormalRadio->Checked)
			{
				pictureBox1->Image = imgData;
			}
			else if (GrayScaleRadio->Checked)
			{
				pictureBox1->Image = ToGreyScale(imgData);
			}
			else
			{
				float threshold = (float)Convert::ToDouble(textBox1->Text);
				pictureBox1->Image = ToBlackNWhite(imgData, threshold);
			}
		}

		Void openFileDialog1_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) 
		{
			Filename = openFileDialog1->FileName;
		}

		Bitmap^ ToGreyScale(Bitmap^ input)
		{
			Bitmap^ result = gcnew Bitmap(input->Width, input->Height);
			
			for (int x = 0; x < input->Width; x++)
			{
				for (int y = 0; y < input->Height; y++)
				{
					Color newColor = input->GetPixel(x, y);
					int avg = (newColor.R + newColor.G + newColor.B) / 3;
					newColor = Color::FromArgb(avg, avg, avg);
					result->SetPixel(x, y, newColor);
				}
			}

			return result;
		}

		Bitmap^ ToBlackNWhite(Bitmap^ input, float threshold)
		{
			Bitmap^ result = gcnew Bitmap(input->Width, input->Height);

			for (int x = 0; x < input->Width; x++)
			{
				for (int y = 0; y < input->Height; y++)
				{
					Color newColor = input->GetPixel(x, y);
					int avg = (newColor.R + newColor.G + newColor.B) / 3;

					if (avg < threshold * 255)
					{
						newColor = Color::FromArgb(0, 0, 0);
					}
					else
					{
						newColor = Color::FromArgb(255, 255, 255);
					}
					result->SetPixel(x, y, newColor);
				}
			}
			return result;
		}
	};
}

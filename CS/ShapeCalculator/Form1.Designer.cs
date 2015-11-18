namespace ShapeCalculator
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.shapeLabel = new System.Windows.Forms.Label();
            this.shapeComboBox = new System.Windows.Forms.ComboBox();
            this.formula = new System.Windows.Forms.Label();
            this.input1TextBox = new System.Windows.Forms.TextBox();
            this.input2TextBox = new System.Windows.Forms.TextBox();
            this.input1Label = new System.Windows.Forms.Label();
            this.input2Label = new System.Windows.Forms.Label();
            this.calculateButton = new System.Windows.Forms.Button();
            this.areaTextBox = new System.Windows.Forms.TextBox();
            this.areaLabel = new System.Windows.Forms.Label();
            this.perimeterTextBox = new System.Windows.Forms.TextBox();
            this.perimeterLabel = new System.Windows.Forms.Label();
            this.volumeTextBox = new System.Windows.Forms.TextBox();
            this.volumeLabel = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(106, 31);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(256, 256);
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // shapeLabel
            // 
            this.shapeLabel.AutoSize = true;
            this.shapeLabel.Location = new System.Drawing.Point(22, 417);
            this.shapeLabel.Name = "shapeLabel";
            this.shapeLabel.Size = new System.Drawing.Size(38, 13);
            this.shapeLabel.TabIndex = 1;
            this.shapeLabel.Text = "Shape";
            // 
            // shapeComboBox
            // 
            this.shapeComboBox.FormattingEnabled = true;
            this.shapeComboBox.Items.AddRange(new object[] {
            "Circle",
            "Rectangle",
            "Square",
            "Triangle (Right)",
            "Sphere"});
            this.shapeComboBox.Location = new System.Drawing.Point(106, 414);
            this.shapeComboBox.Name = "shapeComboBox";
            this.shapeComboBox.Size = new System.Drawing.Size(256, 21);
            this.shapeComboBox.TabIndex = 2;
            this.shapeComboBox.SelectedIndexChanged += new System.EventHandler(this.shapeComboBox_SelectionChangeCommitted);
            // 
            // formula
            // 
            this.formula.AutoSize = true;
            this.formula.Font = new System.Drawing.Font("Times New Roman", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.formula.Location = new System.Drawing.Point(103, 313);
            this.formula.Name = "formula";
            this.formula.Size = new System.Drawing.Size(74, 22);
            this.formula.TabIndex = 3;
            this.formula.Text = "formula";
            // 
            // input1TextBox
            // 
            this.input1TextBox.Location = new System.Drawing.Point(106, 446);
            this.input1TextBox.Name = "input1TextBox";
            this.input1TextBox.Size = new System.Drawing.Size(256, 20);
            this.input1TextBox.TabIndex = 4;
            // 
            // input2TextBox
            // 
            this.input2TextBox.Location = new System.Drawing.Point(106, 472);
            this.input2TextBox.Name = "input2TextBox";
            this.input2TextBox.Size = new System.Drawing.Size(256, 20);
            this.input2TextBox.TabIndex = 5;
            // 
            // input1Label
            // 
            this.input1Label.AutoSize = true;
            this.input1Label.Location = new System.Drawing.Point(22, 449);
            this.input1Label.Name = "input1Label";
            this.input1Label.Size = new System.Drawing.Size(39, 13);
            this.input1Label.TabIndex = 6;
            this.input1Label.Text = "input 1";
            // 
            // input2Label
            // 
            this.input2Label.AutoSize = true;
            this.input2Label.Location = new System.Drawing.Point(22, 475);
            this.input2Label.Name = "input2Label";
            this.input2Label.Size = new System.Drawing.Size(39, 13);
            this.input2Label.TabIndex = 7;
            this.input2Label.Text = "input 2";
            // 
            // calculateButton
            // 
            this.calculateButton.Location = new System.Drawing.Point(107, 509);
            this.calculateButton.Name = "calculateButton";
            this.calculateButton.Size = new System.Drawing.Size(255, 29);
            this.calculateButton.TabIndex = 10;
            this.calculateButton.Text = "Calculate";
            this.calculateButton.UseVisualStyleBackColor = true;
            this.calculateButton.Click += new System.EventHandler(this.calculateButton_Click);
            // 
            // areaTextBox
            // 
            this.areaTextBox.Location = new System.Drawing.Point(106, 560);
            this.areaTextBox.Name = "areaTextBox";
            this.areaTextBox.Size = new System.Drawing.Size(256, 20);
            this.areaTextBox.TabIndex = 12;
            // 
            // areaLabel
            // 
            this.areaLabel.AutoSize = true;
            this.areaLabel.Location = new System.Drawing.Point(21, 563);
            this.areaLabel.Name = "areaLabel";
            this.areaLabel.Size = new System.Drawing.Size(29, 13);
            this.areaLabel.TabIndex = 11;
            this.areaLabel.Text = "Area";
            // 
            // perimeterTextBox
            // 
            this.perimeterTextBox.Location = new System.Drawing.Point(106, 586);
            this.perimeterTextBox.Name = "perimeterTextBox";
            this.perimeterTextBox.Size = new System.Drawing.Size(256, 20);
            this.perimeterTextBox.TabIndex = 14;
            // 
            // perimeterLabel
            // 
            this.perimeterLabel.AutoSize = true;
            this.perimeterLabel.Location = new System.Drawing.Point(21, 589);
            this.perimeterLabel.Name = "perimeterLabel";
            this.perimeterLabel.Size = new System.Drawing.Size(51, 13);
            this.perimeterLabel.TabIndex = 13;
            this.perimeterLabel.Text = "Perimeter";
            // 
            // volumeTextBox
            // 
            this.volumeTextBox.Location = new System.Drawing.Point(107, 612);
            this.volumeTextBox.Name = "volumeTextBox";
            this.volumeTextBox.Size = new System.Drawing.Size(256, 20);
            this.volumeTextBox.TabIndex = 15;
            // 
            // volumeLabel
            // 
            this.volumeLabel.AutoSize = true;
            this.volumeLabel.Location = new System.Drawing.Point(21, 615);
            this.volumeLabel.Name = "volumeLabel";
            this.volumeLabel.Size = new System.Drawing.Size(42, 13);
            this.volumeLabel.TabIndex = 16;
            this.volumeLabel.Text = "Volume";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(412, 666);
            this.Controls.Add(this.volumeLabel);
            this.Controls.Add(this.volumeTextBox);
            this.Controls.Add(this.perimeterTextBox);
            this.Controls.Add(this.perimeterLabel);
            this.Controls.Add(this.areaTextBox);
            this.Controls.Add(this.areaLabel);
            this.Controls.Add(this.calculateButton);
            this.Controls.Add(this.input2Label);
            this.Controls.Add(this.input1Label);
            this.Controls.Add(this.input2TextBox);
            this.Controls.Add(this.input1TextBox);
            this.Controls.Add(this.formula);
            this.Controls.Add(this.shapeComboBox);
            this.Controls.Add(this.shapeLabel);
            this.Controls.Add(this.pictureBox1);
            this.Name = "Form1";
            this.Text = "Shape Calculator by Josh Fong";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label shapeLabel;
        private System.Windows.Forms.ComboBox shapeComboBox;
        private System.Windows.Forms.Label formula;
        private System.Windows.Forms.TextBox input1TextBox;
        private System.Windows.Forms.TextBox input2TextBox;
        private System.Windows.Forms.Label input1Label;
        private System.Windows.Forms.Label input2Label;
        private System.Windows.Forms.Button calculateButton;
        private System.Windows.Forms.TextBox areaTextBox;
        private System.Windows.Forms.Label areaLabel;
        private System.Windows.Forms.TextBox perimeterTextBox;
        private System.Windows.Forms.Label perimeterLabel;
        private System.Windows.Forms.TextBox volumeTextBox;
        private System.Windows.Forms.Label volumeLabel;
    }
}


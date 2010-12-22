namespace QuickEncodeCSharp
{
    partial class formMain
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(formMain));
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.textBoxSrc = new System.Windows.Forms.TextBox();
            this.textBoxTgt = new System.Windows.Forms.TextBox();
            this.buttonBrowseSrc = new System.Windows.Forms.Button();
            this.buttonBrowseTgt = new System.Windows.Forms.Button();
            this.buttonStart = new System.Windows.Forms.Button();
            this.timerProgress = new System.Windows.Forms.Timer(this.components);
            this.labelProgress = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(238)))), ((int)(((byte)(243)))), ((int)(((byte)(250)))));
            this.pictureBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBox1.Image = global::QuickEncodeCSharp.Properties.Resources.smalllogo;
            this.pictureBox1.Location = new System.Drawing.Point(7, 6);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(296, 84);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // textBoxSrc
            // 
            this.textBoxSrc.Location = new System.Drawing.Point(7, 117);
            this.textBoxSrc.Name = "textBoxSrc";
            this.textBoxSrc.Size = new System.Drawing.Size(196, 20);
            this.textBoxSrc.TabIndex = 1;
            // 
            // textBoxTgt
            // 
            this.textBoxTgt.Location = new System.Drawing.Point(7, 152);
            this.textBoxTgt.Name = "textBoxTgt";
            this.textBoxTgt.Size = new System.Drawing.Size(196, 20);
            this.textBoxTgt.TabIndex = 2;
            // 
            // buttonBrowseSrc
            // 
            this.buttonBrowseSrc.Location = new System.Drawing.Point(217, 117);
            this.buttonBrowseSrc.Name = "buttonBrowseSrc";
            this.buttonBrowseSrc.Size = new System.Drawing.Size(68, 20);
            this.buttonBrowseSrc.TabIndex = 4;
            this.buttonBrowseSrc.Text = "Browse...";
            this.buttonBrowseSrc.UseVisualStyleBackColor = true;
            this.buttonBrowseSrc.Click += new System.EventHandler(this.buttonBrowseSrc_Click);
            // 
            // buttonBrowseTgt
            // 
            this.buttonBrowseTgt.Location = new System.Drawing.Point(217, 151);
            this.buttonBrowseTgt.Name = "buttonBrowseTgt";
            this.buttonBrowseTgt.Size = new System.Drawing.Size(68, 20);
            this.buttonBrowseTgt.TabIndex = 5;
            this.buttonBrowseTgt.Text = "Browse...";
            this.buttonBrowseTgt.UseVisualStyleBackColor = true;
            this.buttonBrowseTgt.Click += new System.EventHandler(this.buttonBrowseTgt_Click);
            // 
            // buttonStart
            // 
            this.buttonStart.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonStart.Location = new System.Drawing.Point(218, 189);
            this.buttonStart.Name = "buttonStart";
            this.buttonStart.Size = new System.Drawing.Size(68, 20);
            this.buttonStart.TabIndex = 6;
            this.buttonStart.Text = "Start";
            this.buttonStart.UseVisualStyleBackColor = true;
            this.buttonStart.Click += new System.EventHandler(this.buttonStart_Click);
            // 
            // timerProgress
            // 
            this.timerProgress.Enabled = true;
            this.timerProgress.Interval = 1000;
            this.timerProgress.Tick += new System.EventHandler(this.timerProgress_Tick);
            // 
            // labelProgress
            // 
            this.labelProgress.AutoSize = true;
            this.labelProgress.Location = new System.Drawing.Point(10, 187);
            this.labelProgress.Name = "labelProgress";
            this.labelProgress.Size = new System.Drawing.Size(24, 13);
            this.labelProgress.TabIndex = 7;
            this.labelProgress.Text = "Idle";
            // 
            // formMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(310, 241);
            this.Controls.Add(this.labelProgress);
            this.Controls.Add(this.buttonStart);
            this.Controls.Add(this.buttonBrowseTgt);
            this.Controls.Add(this.buttonBrowseSrc);
            this.Controls.Add(this.textBoxTgt);
            this.Controls.Add(this.textBoxSrc);
            this.Controls.Add(this.pictureBox1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "formMain";
            this.Text = "Standard MPEG QuickConvert C#";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.TextBox textBoxSrc;
        private System.Windows.Forms.TextBox textBoxTgt;
        private System.Windows.Forms.Button buttonBrowseSrc;
        private System.Windows.Forms.Button buttonBrowseTgt;
        private System.Windows.Forms.Button buttonStart;
        private System.Windows.Forms.Timer timerProgress;
        private System.Windows.Forms.Label labelProgress;
    }
}


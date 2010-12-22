namespace CSharpDirectAccess
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.label1 = new System.Windows.Forms.Label();
            this.linkLabel1 = new System.Windows.Forms.LinkLabel();
            this.btnStart = new System.Windows.Forms.Button();
            this.buttonBrowseSrc = new System.Windows.Forms.Button();
            this.textBoxSource = new System.Windows.Forms.TextBox();
            this.labelSource = new System.Windows.Forms.Label();
            this.folderBrowserDialog = new System.Windows.Forms.FolderBrowserDialog();
            this.comboBoxFormat = new System.Windows.Forms.ComboBox();
            this.groupBoxFormat = new System.Windows.Forms.GroupBox();
            this.buttonBrowseTarget = new System.Windows.Forms.Button();
            this.textBoxTarget = new System.Windows.Forms.TextBox();
            this.labelTarget = new System.Windows.Forms.Label();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripProgress = new System.Windows.Forms.ToolStripStatusLabel();
            this.groupBoxFormat.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(79, 20);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(313, 67);
            this.label1.TabIndex = 0;
            this.label1.Text = "This sample will load images from a disk and render them to MPEG using the Standa" +
                "rd MPEG Encoder DirectAccess Interface. The images are loaded as bitmaps in memo" +
                "ry, then sent to the encoder directly.";
            // 
            // linkLabel1
            // 
            this.linkLabel1.AutoSize = true;
            this.linkLabel1.Location = new System.Drawing.Point(168, 335);
            this.linkLabel1.Name = "linkLabel1";
            this.linkLabel1.Size = new System.Drawing.Size(124, 13);
            this.linkLabel1.TabIndex = 1;
            this.linkLabel1.TabStop = true;
            this.linkLabel1.Text = "www.standardmpeg.com";
            // 
            // btnStart
            // 
            this.btnStart.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnStart.Location = new System.Drawing.Point(72, 263);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(320, 42);
            this.btnStart.TabIndex = 20;
            this.btnStart.Text = "Start Processing";
            this.btnStart.UseVisualStyleBackColor = true;
            this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
            // 
            // buttonBrowseSrc
            // 
            this.buttonBrowseSrc.Location = new System.Drawing.Point(320, 101);
            this.buttonBrowseSrc.Name = "buttonBrowseSrc";
            this.buttonBrowseSrc.Size = new System.Drawing.Size(72, 24);
            this.buttonBrowseSrc.TabIndex = 23;
            this.buttonBrowseSrc.Text = "Browse...";
            this.buttonBrowseSrc.Click += new System.EventHandler(this.buttonBrowseSrc_Click);
            // 
            // textBoxSource
            // 
            this.textBoxSource.Location = new System.Drawing.Point(72, 103);
            this.textBoxSource.Name = "textBoxSource";
            this.textBoxSource.Size = new System.Drawing.Size(240, 20);
            this.textBoxSource.TabIndex = 22;
            this.textBoxSource.Text = "c:\\";
            // 
            // labelSource
            // 
            this.labelSource.Location = new System.Drawing.Point(7, 97);
            this.labelSource.Name = "labelSource";
            this.labelSource.Size = new System.Drawing.Size(53, 33);
            this.labelSource.TabIndex = 21;
            this.labelSource.Text = "Source Folder:";
            this.labelSource.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // comboBoxFormat
            // 
            this.comboBoxFormat.Items.AddRange(new object[] {
            "MPEG-1",
            "MPEG-2",
            "MPEG-4"});
            this.comboBoxFormat.Location = new System.Drawing.Point(16, 26);
            this.comboBoxFormat.Name = "comboBoxFormat";
            this.comboBoxFormat.Size = new System.Drawing.Size(288, 21);
            this.comboBoxFormat.TabIndex = 0;
            this.comboBoxFormat.Text = "MPEG-1";
            // 
            // groupBoxFormat
            // 
            this.groupBoxFormat.Controls.Add(this.comboBoxFormat);
            this.groupBoxFormat.Location = new System.Drawing.Point(72, 184);
            this.groupBoxFormat.Name = "groupBoxFormat";
            this.groupBoxFormat.Size = new System.Drawing.Size(320, 64);
            this.groupBoxFormat.TabIndex = 27;
            this.groupBoxFormat.TabStop = false;
            this.groupBoxFormat.Text = "Output Format";
            // 
            // buttonBrowseTarget
            // 
            this.buttonBrowseTarget.Location = new System.Drawing.Point(320, 138);
            this.buttonBrowseTarget.Name = "buttonBrowseTarget";
            this.buttonBrowseTarget.Size = new System.Drawing.Size(72, 24);
            this.buttonBrowseTarget.TabIndex = 26;
            this.buttonBrowseTarget.Text = "Browse...";
            // 
            // textBoxTarget
            // 
            this.textBoxTarget.Location = new System.Drawing.Point(72, 138);
            this.textBoxTarget.Name = "textBoxTarget";
            this.textBoxTarget.Size = new System.Drawing.Size(240, 20);
            this.textBoxTarget.TabIndex = 25;
            this.textBoxTarget.Text = "c:\\test_out_direct.mpg";
            // 
            // labelTarget
            // 
            this.labelTarget.Location = new System.Drawing.Point(4, 131);
            this.labelTarget.Name = "labelTarget";
            this.labelTarget.Size = new System.Drawing.Size(56, 38);
            this.labelTarget.TabIndex = 24;
            this.labelTarget.Text = "Target File:";
            this.labelTarget.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripProgress});
            this.statusStrip1.Location = new System.Drawing.Point(0, 365);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(420, 22);
            this.statusStrip1.TabIndex = 28;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripProgress
            // 
            this.toolStripProgress.Name = "toolStripProgress";
            this.toolStripProgress.Size = new System.Drawing.Size(39, 17);
            this.toolStripProgress.Text = "Ready";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(420, 387);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.groupBoxFormat);
            this.Controls.Add(this.buttonBrowseTarget);
            this.Controls.Add(this.textBoxTarget);
            this.Controls.Add(this.labelTarget);
            this.Controls.Add(this.buttonBrowseSrc);
            this.Controls.Add(this.textBoxSource);
            this.Controls.Add(this.labelSource);
            this.Controls.Add(this.btnStart);
            this.Controls.Add(this.linkLabel1);
            this.Controls.Add(this.label1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form1";
            this.Text = "Standard MPEG DirectAccess MPEG Encode";
            this.groupBoxFormat.ResumeLayout(false);
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.LinkLabel linkLabel1;
        private System.Windows.Forms.Button btnStart;
        private System.Windows.Forms.Button buttonBrowseSrc;
        private System.Windows.Forms.TextBox textBoxSource;
        private System.Windows.Forms.Label labelSource;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog;
        private System.Windows.Forms.ComboBox comboBoxFormat;
        private System.Windows.Forms.GroupBox groupBoxFormat;
        private System.Windows.Forms.Button buttonBrowseTarget;
        private System.Windows.Forms.TextBox textBoxTarget;
        private System.Windows.Forms.Label labelTarget;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripProgress;
    }
}


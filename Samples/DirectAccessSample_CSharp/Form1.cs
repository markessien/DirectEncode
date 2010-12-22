using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO; // DirectoryInfo

namespace CSharpDirectAccess
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void buttonBrowseSrc_Click(object sender, EventArgs e)
        {
            if (folderBrowserDialog.ShowDialog() == DialogResult.OK)
            {
                textBoxSource.Text = folderBrowserDialog.SelectedPath ;
            }
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            btnStart.Enabled = false;
            btnStart.Text = "Processing...";

            // Create a new MPEG File
            MpegManager mpegManager = new MpegManager(textBoxTarget.Text, comboBoxFormat.SelectedIndex, 320, 240);

            // Walk through all image files in the directory
             DirectoryInfo di = new DirectoryInfo(textBoxSource.Text);
             FileInfo[] rgFiles = di.GetFiles("*.jpg");

             int i = 0;
             foreach(FileInfo fi in rgFiles)
             {
                 // We load the file from the file into a C# Bitmap.
                 System.Drawing.Bitmap image = new System.Drawing.Bitmap(fi.FullName);

                 // add the file as a frame to the directaccess dll
                 mpegManager.AddFrame(image);
                 image.Dispose();
                 image = null;

                 toolStripProgress.Text = i.ToString() + " of " + rgFiles.Length.ToString();
                 Application.DoEvents();
                 i++;
             }

             toolStripProgress.Text = "Ready";

             // shut down the file.
             mpegManager.CloseFile();

             btnStart.Enabled = true;
             btnStart.Text = "Start Processing";

        }

    }
}
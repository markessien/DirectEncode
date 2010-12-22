using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Threading;
using System.Runtime.InteropServices;

// You will need to reference DirectShowNet
// Download DirectShowNET from http://directshownet.sourceforge.net/. Right click on
// 'References' and browse to the file 'DirectShowLib-2005. Additionally, add the
// .NET wrapper for the mpeg encoder by referencing the file "DirectEncodeNET.dll"

using DirectShowLib;
using DirectShowLib.DES;
using DirectEncodeNET;

namespace Transcode
{
	public class formMain : System.Windows.Forms.Form
	{
        // Form controls
		private System.Windows.Forms.PictureBox pictureBoxLogo;
		private System.Windows.Forms.Label labelSource;
		private System.Windows.Forms.Label labelTarget;
		private System.Windows.Forms.TextBox textBoxSource;
		private System.Windows.Forms.TextBox textBoxTarget;
		private System.Windows.Forms.Button buttonBrowseSrc;
		private System.Windows.Forms.Button buttonBrowseTarget;
		private System.Windows.Forms.GroupBox groupBoxFormat;
		private System.Windows.Forms.ComboBox comboBoxFormat;
		private System.Windows.Forms.Button buttonStart;

		// dshow filters
		private IGraphBuilder m_pGraph;
		private IMediaEventEx m_pEvent;
		private IMediaSeeking m_pSeeking;
		private IMediaControl m_pMediaControl;
		private ICaptureGraphBuilder2 m_pBuilder;

		// DES filters
		private IRenderEngine m_pRenderEngine;
		private IAMTimeline m_pTimeline;
		private IAMTimelineObj m_pVideoGroupObj;
		private IAMTimelineObj m_pAudioGroupObj;

		// mpeg objects (from directencode)
		private IBaseFilter m_pMPEGWriter;
		private IStandardMpegEncoder m_pIMPEGEncoder;
		private StandardMpegEncoderProfile m_pIMPEGEncoderProfile;
	
        // running object table
		private DsROTEntry m_rot;

        // files we will convert
		string m_strSourceFile;
		string m_strTargetFile;

        // output formats
		DirectEncodeNET.SystemsOutputFormat m_systemsFormat;
        DirectEncodeNET.Constraint m_constraint;
        private System.Windows.Forms.Timer timerProgress;
        private StatusStrip statusStrip1;
        private ToolStripStatusLabel toolStripStatusLabel1;
        private IContainer components;

		public formMain()
		{
			// Required for Windows Form Designer support
			InitializeComponent();
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
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
            this.pictureBoxLogo = new System.Windows.Forms.PictureBox();
            this.labelSource = new System.Windows.Forms.Label();
            this.labelTarget = new System.Windows.Forms.Label();
            this.textBoxSource = new System.Windows.Forms.TextBox();
            this.textBoxTarget = new System.Windows.Forms.TextBox();
            this.buttonBrowseSrc = new System.Windows.Forms.Button();
            this.buttonBrowseTarget = new System.Windows.Forms.Button();
            this.groupBoxFormat = new System.Windows.Forms.GroupBox();
            this.comboBoxFormat = new System.Windows.Forms.ComboBox();
            this.buttonStart = new System.Windows.Forms.Button();
            this.timerProgress = new System.Windows.Forms.Timer(this.components);
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxLogo)).BeginInit();
            this.groupBoxFormat.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // pictureBoxLogo
            // 
            this.pictureBoxLogo.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.pictureBoxLogo.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(238)))), ((int)(((byte)(243)))), ((int)(((byte)(250)))));
            this.pictureBoxLogo.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBoxLogo.Image = ((System.Drawing.Image)(resources.GetObject("pictureBoxLogo.Image")));
            this.pictureBoxLogo.Location = new System.Drawing.Point(0, 1);
            this.pictureBoxLogo.Name = "pictureBoxLogo";
            this.pictureBoxLogo.Size = new System.Drawing.Size(344, 88);
            this.pictureBoxLogo.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.pictureBoxLogo.TabIndex = 0;
            this.pictureBoxLogo.TabStop = false;
            // 
            // labelSource
            // 
            this.labelSource.Location = new System.Drawing.Point(8, 104);
            this.labelSource.Name = "labelSource";
            this.labelSource.Size = new System.Drawing.Size(72, 16);
            this.labelSource.TabIndex = 1;
            this.labelSource.Text = "Source File:";
            this.labelSource.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // labelTarget
            // 
            this.labelTarget.Location = new System.Drawing.Point(-2, 136);
            this.labelTarget.Name = "labelTarget";
            this.labelTarget.Size = new System.Drawing.Size(80, 16);
            this.labelTarget.TabIndex = 2;
            this.labelTarget.Text = "Target File:";
            this.labelTarget.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // textBoxSource
            // 
            this.textBoxSource.Location = new System.Drawing.Point(88, 103);
            this.textBoxSource.Name = "textBoxSource";
            this.textBoxSource.Size = new System.Drawing.Size(168, 20);
            this.textBoxSource.TabIndex = 3;
            // 
            // textBoxTarget
            // 
            this.textBoxTarget.Location = new System.Drawing.Point(88, 136);
            this.textBoxTarget.Name = "textBoxTarget";
            this.textBoxTarget.Size = new System.Drawing.Size(168, 20);
            this.textBoxTarget.TabIndex = 4;
            // 
            // buttonBrowseSrc
            // 
            this.buttonBrowseSrc.Location = new System.Drawing.Point(264, 101);
            this.buttonBrowseSrc.Name = "buttonBrowseSrc";
            this.buttonBrowseSrc.Size = new System.Drawing.Size(72, 24);
            this.buttonBrowseSrc.TabIndex = 5;
            this.buttonBrowseSrc.Text = "Browse...";
            this.buttonBrowseSrc.Click += new System.EventHandler(this.buttonBrowseSrc_Click);
            // 
            // buttonBrowseTarget
            // 
            this.buttonBrowseTarget.Location = new System.Drawing.Point(264, 134);
            this.buttonBrowseTarget.Name = "buttonBrowseTarget";
            this.buttonBrowseTarget.Size = new System.Drawing.Size(72, 24);
            this.buttonBrowseTarget.TabIndex = 6;
            this.buttonBrowseTarget.Text = "Browse...";
            this.buttonBrowseTarget.Click += new System.EventHandler(this.buttonBrowseTarget_Click);
            // 
            // groupBoxFormat
            // 
            this.groupBoxFormat.Controls.Add(this.comboBoxFormat);
            this.groupBoxFormat.Location = new System.Drawing.Point(16, 176);
            this.groupBoxFormat.Name = "groupBoxFormat";
            this.groupBoxFormat.Size = new System.Drawing.Size(320, 64);
            this.groupBoxFormat.TabIndex = 7;
            this.groupBoxFormat.TabStop = false;
            this.groupBoxFormat.Text = "Output Format";
            // 
            // comboBoxFormat
            // 
            this.comboBoxFormat.Items.AddRange(new object[] {
            "MPEG-1",
            "MPEG-2"});
            this.comboBoxFormat.Location = new System.Drawing.Point(16, 26);
            this.comboBoxFormat.Name = "comboBoxFormat";
            this.comboBoxFormat.Size = new System.Drawing.Size(288, 21);
            this.comboBoxFormat.TabIndex = 0;
            this.comboBoxFormat.Text = "MPEG-1";
            // 
            // buttonStart
            // 
            this.buttonStart.Location = new System.Drawing.Point(200, 256);
            this.buttonStart.Name = "buttonStart";
            this.buttonStart.Size = new System.Drawing.Size(136, 32);
            this.buttonStart.TabIndex = 8;
            this.buttonStart.Text = "Start Conversion";
            this.buttonStart.Click += new System.EventHandler(this.buttonStart_Click);
            // 
            // timerProgress
            // 
            this.timerProgress.Enabled = true;
            this.timerProgress.Interval = 1000;
            this.timerProgress.Tick += new System.EventHandler(this.timerProgress_Tick);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1});
            this.statusStrip1.Location = new System.Drawing.Point(0, 301);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(344, 22);
            this.statusStrip1.TabIndex = 9;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(0, 17);
            // 
            // formMain
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.ClientSize = new System.Drawing.Size(344, 323);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.buttonStart);
            this.Controls.Add(this.groupBoxFormat);
            this.Controls.Add(this.buttonBrowseTarget);
            this.Controls.Add(this.buttonBrowseSrc);
            this.Controls.Add(this.textBoxTarget);
            this.Controls.Add(this.textBoxSource);
            this.Controls.Add(this.labelTarget);
            this.Controls.Add(this.labelSource);
            this.Controls.Add(this.pictureBoxLogo);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "formMain";
            this.Text = "Standard MPEG C# Sample";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxLogo)).EndInit();
            this.groupBoxFormat.ResumeLayout(false);
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new formMain());
		}


		/// <summary>
		/// Return the length of the media file
		/// </summary>
		/// <returns>Length in 100NS</returns>
		private void GetFileInfo(string filepath, ref double framerate, ref double dLength,
                                 ref int nWidth, ref int nHeight)
		{
			int hr;
			double d;

			IMediaDet imd = (IMediaDet)new MediaDet();

			// Set the name
			hr = imd.put_Filename(filepath);
			DESError.ThrowExceptionForHR(hr);

			// Read from stream zero
			int nStreams;
			imd.get_OutputStreams(out nStreams);
			for (int i=0;i<nStreams;i++)
			{
				hr = imd.put_CurrentStream(i);
				DESError.ThrowExceptionForHR(hr);

				// Get the length in seconds
				hr = imd.get_StreamLength(out d);
				DESError.ThrowExceptionForHR(hr);
				
				dLength = d;

				DirectShowLib.AMMediaType mt = new DirectShowLib.AMMediaType();
				imd.get_StreamMediaType(mt);
				
				if (mt.formatType == FormatType.VideoInfo)
				{
					VideoInfoHeader vif = new VideoInfoHeader();
					Marshal.PtrToStructure(mt.formatPtr, vif);
					nWidth = vif.BmiHeader.Width;
					nHeight = vif.BmiHeader.Height;
					imd.get_FrameRate(out framerate);
				}
			}
			
			Marshal.ReleaseComObject(imd);
		}

		private int LoadMPEGCodec()
		{
            Guid guid = new Guid("CFD87339-C61F-46ca-B6A1-F87D6B96243E");
			Type comtype = Type.GetTypeFromCLSID(guid);
			m_pMPEGWriter = (IBaseFilter)Activator.CreateInstance(comtype);
	      
			m_pIMPEGEncoder = (IStandardMpegEncoder)m_pMPEGWriter;

			// make the mpeg encoder select one of the pre-defined
			// profile objects that it stores internally. For audio
			// you will need to create your own profile.
			
			m_pIMPEGEncoder.SelectFormat(m_systemsFormat, m_constraint);
			m_pIMPEGEncoder.GetSelectedProfile(out m_pIMPEGEncoderProfile);

			return 0;
		}

		private int AddVideo(double dSourceLength, double dSourceFramerate, int nSourceWidth, int nSourceHeight)
		{
			// make the root video group/composition
			int hr;
			hr = m_pTimeline.CreateEmptyNode( out m_pVideoGroupObj, TimelineMajorType.Group);
			DESError.ThrowExceptionForHR(hr);

			IAMTimelineGroup pVideoGroup = (IAMTimelineGroup)m_pVideoGroupObj;
		
			//// Set Media Type
			AMMediaType VideoGroupType = new AMMediaType();
			VideoGroupType.majorType  = MediaType.Video;

			// our filter wants rgb24
			VideoGroupType.subType = MediaSubType.RGB24;
			VideoGroupType.formatType = FormatType.VideoInfo;
			VideoGroupType.formatSize = Marshal.SizeOf(typeof(VideoInfoHeader));

			VideoInfoHeader vif = new VideoInfoHeader();
			vif.BmiHeader = new BitmapInfoHeader();

			vif.BmiHeader.Size        = Marshal.SizeOf(typeof(BitmapInfoHeader));
			vif.BmiHeader.Compression = 0;
			vif.BmiHeader.BitCount    = 24;
			vif.BmiHeader.Width       = nSourceWidth;
			vif.BmiHeader.Height      = nSourceHeight;
			vif.BmiHeader.Planes      = 1;
			
			int iSampleSize = vif.BmiHeader.Width * vif.BmiHeader.Height * (vif.BmiHeader.BitCount / 8);
			vif.BmiHeader.ImageSize   = iSampleSize;
			VideoGroupType.sampleSize = iSampleSize;
			VideoGroupType.formatPtr = Marshal.AllocCoTaskMem(Marshal.SizeOf(vif));

			Marshal.StructureToPtr(vif, VideoGroupType.formatPtr, false);

			hr = pVideoGroup.SetMediaType(VideoGroupType);
			DESError.ThrowExceptionForHR(hr);

			// the framerate is a different issue. This has to be managed by DES

	//		double dRequiredInputFramerate = 0;
	//		m_pIMPEGEncoder.SetSourceFramerate(dSourceFramerate, out dRequiredInputFramerate);
	//		hr = pVideoGroup.SetOutputFPS(dRequiredInputFramerate);

			hr = m_pTimeline.AddGroup(m_pVideoGroupObj);
			DESError.ThrowExceptionForHR(hr);

			IAMTimelineComp pRootComp = (IAMTimelineComp)m_pVideoGroupObj;

			IAMTimelineObj pTrackVideoObj;
			hr = m_pTimeline.CreateEmptyNode(out pTrackVideoObj, TimelineMajorType.Track);

			hr = pRootComp.VTrackInsBefore(pTrackVideoObj, -1 );
			DESError.ThrowExceptionForHR(hr);

			IAMTimelineObj pSourceVideoObj;
			hr = m_pTimeline.CreateEmptyNode( out pSourceVideoObj, TimelineMajorType.Source);
			DESError.ThrowExceptionForHR(hr);

			hr = pSourceVideoObj.SetStartStop2(0, dSourceLength);
			DESError.ThrowExceptionForHR(hr);

			IAMTimelineSrc pSourceVideoSrc = (IAMTimelineSrc)pSourceVideoObj;

			hr = pSourceVideoSrc.SetMediaTimes2(0, dSourceLength);
			DESError.ThrowExceptionForHR(hr);

			hr = pSourceVideoSrc.SetMediaName(m_strSourceFile);
			DESError.ThrowExceptionForHR(hr);

			// add the source to the track
			IAMTimelineObj pVideoTrackObj;
			pRootComp.GetVTrack( out pVideoTrackObj, 0);

			IAMTimelineTrack pTrackVideo = (IAMTimelineTrack)pVideoTrackObj;
			hr = pTrackVideo.SrcAdd(pSourceVideoObj);
			DESError.ThrowExceptionForHR(hr);

			return hr;
		}

		private int AddAudio(double dSourceLength)
		{
			// This function adds an audio group to the DES
			int hr = 0;
			hr = m_pTimeline.CreateEmptyNode(out m_pAudioGroupObj, TimelineMajorType.Group);
			DESError.ThrowExceptionForHR(hr);

			IAMTimelineGroup pAudioGroup = (IAMTimelineGroup)m_pAudioGroupObj;

			AMMediaType AudioGroupType = new AMMediaType();
			AudioGroupType.majorType = MediaType.Audio;

			hr = pAudioGroup.SetMediaType(AudioGroupType);
			DESError.ThrowExceptionForHR(hr);
	
			hr = m_pTimeline.AddGroup(m_pAudioGroupObj);
			DESError.ThrowExceptionForHR(hr);
	
			IAMTimelineObj pTrackAudioObj;
			hr = m_pTimeline.CreateEmptyNode( out pTrackAudioObj, TimelineMajorType.Track );
			DESError.ThrowExceptionForHR(hr);

			IAMTimelineComp pRootComp = (IAMTimelineComp)(m_pAudioGroupObj);
			hr = pRootComp.VTrackInsBefore(pTrackAudioObj, -1);
			DESError.ThrowExceptionForHR(hr);
			
			IAMTimelineObj pSourceAudioObj;	
			hr = m_pTimeline.CreateEmptyNode( out pSourceAudioObj, TimelineMajorType.Source);
			DESError.ThrowExceptionForHR(hr);

			hr = pSourceAudioObj.SetStartStop2(0, dSourceLength);		

			IAMTimelineSrc pSourceAudioSrc = (IAMTimelineSrc)(pSourceAudioObj);
			hr = pSourceAudioSrc.SetMediaTimes2(0, dSourceLength);
			hr = pSourceAudioSrc.SetMediaName(m_strSourceFile);
			DESError.ThrowExceptionForHR(hr);
			
			IAMTimelineObj pAudioTrackObj;
			pRootComp.GetVTrack( out pAudioTrackObj, 0);

			IAMTimelineTrack pTrackAudio = (IAMTimelineTrack)(pAudioTrackObj);
			hr = pTrackAudio.SrcAdd(pSourceAudioObj);

			return hr;
		}

		private void Transcode(string strSource, string strTarget, string strFormat)
		{
			// store the settings we want to use
			m_strSourceFile = strSource;
			m_strTargetFile = strTarget;
            m_systemsFormat = DirectEncodeNET.SystemsOutputFormat.SYSTEMSFORMAT_MPEG1;
            m_constraint = DirectEncodeNET.Constraint.CONSTRAINT_NONE;

			// Create the capture graph builder.
			m_pBuilder = (ICaptureGraphBuilder2)new CaptureGraphBuilder2();
			
			// Create the timline.
			m_pTimeline = (IAMTimeline)new AMTimeline();

			// get the length, dimensions, fps of the file
			double dLength = 0;
			int nWidth = 0, nHeight = 0;
			double framerate = 0;
			GetFileInfo(strSource, ref framerate, ref dLength, ref nWidth, ref nHeight);

			int hr = 0;

			// Load MPEG Codec
			hr = LoadMPEGCodec();
			DESError.ThrowExceptionForHR(hr);

			// Add the video group and files
			hr = AddVideo(dLength, framerate, nWidth, nHeight);
			DESError.ThrowExceptionForHR(hr);

			hr = AddAudio(dLength);
			DESError.ThrowExceptionForHR(hr);

			// create the render engine
			m_pRenderEngine = (IRenderEngine)new RenderEngine();

			// tell the render engine about the timeline it should use
			hr = m_pRenderEngine.SetTimelineObject( m_pTimeline );
			DESError.ThrowExceptionForHR(hr);

			// connect up the front end
			hr = m_pRenderEngine.ConnectFrontEnd( );
			DESError.ThrowExceptionForHR(hr);

			// Get the filtergraph
			hr = m_pRenderEngine.GetFilterGraph( out m_pGraph );
			DESError.ThrowExceptionForHR(hr);

			// set the filtergraph to the graph builder
			hr = m_pBuilder.SetFiltergraph(m_pGraph);
			DESError.ThrowExceptionForHR(hr);

			IPin pVideoOutPin, pAudioOutPin;
			hr = m_pRenderEngine.GetGroupOutputPin(0, out pVideoOutPin);
			hr = m_pRenderEngine.GetGroupOutputPin(1, out pAudioOutPin);
			DESError.ThrowExceptionForHR(hr);

			hr = RenderOutput(m_pBuilder, m_pGraph, m_pRenderEngine, null, pVideoOutPin, pAudioOutPin, null);
			DESError.ThrowExceptionForHR(hr);

			// get the control interfaces
			m_pEvent = (IMediaEventEx)m_pGraph;
			m_pMediaControl = (IMediaControl)m_pGraph;

#if DEBUG
            // Allow the graph to be connected to from GraphEdit
            m_rot = null;
            m_rot = new DsROTEntry(m_pGraph);
#endif

			// Start the conversion
			hr = m_pMediaControl.Run();

            // Alternative method of getting info
			// EventLoop();

		}

		private void EventLoop()
		{
			const int E_ABORT = unchecked((int)0x80004004);

			IMediaEvent pEvent = (IMediaEvent)m_pGraph;

			int hr = 0;
			EventCode evCode = 0;
			do
			{
				hr = pEvent.WaitForCompletion(1000, out evCode);

				if (evCode == EventCode.Complete ||
					evCode == EventCode.ErrorAbort  ||
					evCode ==  EventCode.UserAbort)
				{
					StopConversion();
					break;
				}
			}
			while (hr == E_ABORT);

		}


	int RenderOutput(ICaptureGraphBuilder2 pBuilder, IGraphBuilder pGraph, IRenderEngine pEngine, 
                     IBaseFilter pVideoGrabber, IPin pVideoPin, IPin pAudioPin, IBaseFilter pSourceFilter)
	{
		int hr;
        IBaseFilter fileWriter = (IBaseFilter)new FileWriter();
        IFileSinkFilter fs = (IFileSinkFilter)fileWriter;
        hr = fs.SetFileName(m_strTargetFile, null);
        hr = pGraph.AddFilter(fileWriter, "File Writer Filter");
		DESError.ThrowExceptionForHR(hr);

		hr = pGraph.AddFilter(m_pMPEGWriter, "Standard MPEG Encoder");
		DESError.ThrowExceptionForHR(hr);

		m_pSeeking = (IMediaSeeking)m_pMPEGWriter;

		hr = pBuilder.RenderStream(null, null, pVideoPin, null, m_pMPEGWriter);
		DESError.ThrowExceptionForHR(hr);

		hr = pBuilder.RenderStream(null, DirectShowLib.MediaType.Audio, pAudioPin, null, m_pMPEGWriter);
		DESError.ThrowExceptionForHR(hr);

        hr = pBuilder.RenderStream(null, null, m_pMPEGWriter, null, fileWriter);
        DESError.ThrowExceptionForHR(hr);

   //     PromptForGraph(

		return hr;
	}

		private void StopConversion()
		{
			// stop graph
			m_pMediaControl.Stop();

			// destroy all objects
			m_pEvent = null;
			m_pSeeking = null;
			m_pMediaControl = null;

			m_pRenderEngine.ScrapIt();

			m_pRenderEngine = null;
			m_pTimeline = null;
			m_pVideoGroupObj = null;
			m_pAudioGroupObj = null;
			m_pIMPEGEncoderProfile = null;
			m_pIMPEGEncoder = null;
			m_pMPEGWriter = null;
			m_pGraph = null;
			m_pBuilder = null;
		}

		private void buttonBrowseSrc_Click(object sender, System.EventArgs e)
		{
			// Browse for source file
			string filename = null;
			OpenFileDialog fdlg = new OpenFileDialog();
			// fdlg.InitialDirectory = "c:\\"; // Environment.GetFolderPath(Environment.SpecialFolder.Desktop);
			if (fdlg.ShowDialog() == DialogResult.OK) 
			{
				filename = fdlg.FileName;
				textBoxSource.Text = filename;
			}
		}

		private void buttonBrowseTarget_Click(object sender, System.EventArgs e)
		{
			// Browse for target file
			string filename = null;
            SaveFileDialog fdlg = new SaveFileDialog();
			// fdlg.InitialDirectory = "c:\\"; // Environment.GetFolderPath(Environment.SpecialFolder.Desktop);
			if (fdlg.ShowDialog() == DialogResult.OK) 
			{
				filename = fdlg.FileName;
				textBoxTarget.Text = filename;
			}
		}

		private void buttonStart_Click(object sender, System.EventArgs e)
		{
			Transcode(textBoxSource.Text, textBoxTarget.Text, "");
		}

        private void timerProgress_Tick(object sender, EventArgs e)
        {
            if (m_pSeeking != null)
            {
                long duration = 0;
                long pos = 0;
                m_pSeeking.GetCurrentPosition(out pos);
                m_pSeeking.GetDuration(out duration);
                toolStripStatusLabel1.Text = pos.ToString() + " of " + duration.ToString();
            }
            else
            {
                toolStripStatusLabel1.Text = "Idle";
            }
            
        }

	}
}

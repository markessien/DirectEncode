using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

// You will need to add references to the DirectEncode library by referencing
// the DirectEncodeNET.dll file. Additionally, you will need to reference DirectShowNet,
// This is an open project that allows DirectShow to be used in C#. Download it here:
// http://directshownet.sourceforge.net/. To reference these items, right click on the
// references under "solution explorer", and select the .dll files.

using System.Runtime.InteropServices; // for 'marshal' support
using DirectShowLib;
using DirectShowLib.DES;
using DirectEncodeNET;

namespace QuickEncodeCSharp
{
    public partial class formMain : Form
    {
        const int WM_GRAPHNOTIFY = 0x00008001;
        private FilterGraph _filterGraph = null;
        private IGraphBuilder _graphBuilder = null;
        private IMediaControl _mediaControl = null;
        private IMediaEventEx _mediaEvent = null;
        private IMediaSeeking _mediaSeeking = null;
        private IBaseFilter _mpegFilter = null;

        public formMain()
        {
            InitializeComponent();
        }

        private void buttonBrowseSrc_Click(object sender, EventArgs e)
        {
            OpenFileDialog fdlg = new OpenFileDialog();
            fdlg.Filter = "All Files|*.*";
            if (fdlg.ShowDialog() == DialogResult.OK)
            {
                textBoxSrc.Text = fdlg.FileName;
            }
        }

        private void buttonBrowseTgt_Click(object sender, EventArgs e)
        {
            SaveFileDialog fdlg = new SaveFileDialog();
            fdlg.Filter = "All Files|*.*";
            if (fdlg.ShowDialog() == DialogResult.OK)
            {
                textBoxTgt.Text = fdlg.FileName;
            }
        }

        private void buttonStart_Click(object sender, EventArgs e)
        {
            StartConversion();
        }

        private void StartConversion()
        {
            // build directshow graph
            _filterGraph = new FilterGraph();
            _graphBuilder = (IGraphBuilder)_filterGraph;
            
            // Create Standard MPEG Filter
            Guid guid = new Guid("CFD87339-C61F-46ca-B6A1-F87D6B96243E");
            Type comtype = Type.GetTypeFromCLSID(guid);
            _mpegFilter = (IBaseFilter)Activator.CreateInstance(comtype);
            SetFilterParams();

            // Set the output file
            IBaseFilter fileWriter = (IBaseFilter)new FileWriter();
            IFileSinkFilter fs = (IFileSinkFilter)fileWriter;
            int hr = fs.SetFileName(textBoxTgt.Text, null);
            hr = _graphBuilder.AddFilter(fileWriter, "File Writer Filter");
            DsError.ThrowExceptionForHR(hr);

            // Add the encoder filter to the graph
            hr = _graphBuilder.AddFilter(_mpegFilter, "MPEG Filter");
            DsError.ThrowExceptionForHR(hr);

            // use Intelligent connect to build the rest of the graph
            hr = _graphBuilder.RenderFile(textBoxSrc.Text, null);
            DsError.ThrowExceptionForHR(hr);

            // get the interfaces we need for info and control
            _mediaControl = (IMediaControl)_filterGraph;
            _mediaEvent = (IMediaEventEx)_filterGraph;
            _mediaSeeking = (IMediaSeeking)_mpegFilter;

            hr = _mediaEvent.SetNotifyWindow(this.Handle, WM_GRAPHNOTIFY, IntPtr.Zero);
            DsError.ThrowExceptionForHR(hr); 
            
            // we are ready to convert
            hr = _mediaControl.Run();
            DsError.ThrowExceptionForHR(hr);
        }

        private void StopConversion()
        {
            if (_mediaEvent != null)
            {
                _mediaControl.Stop();
                _mediaEvent.SetNotifyWindow(IntPtr.Zero, WM_GRAPHNOTIFY, IntPtr.Zero);
            }

            _mediaSeeking = null;
            _mediaControl = null;
            _mediaEvent = null;
            _graphBuilder = null;
            if (_mpegFilter != null)
                Marshal.ReleaseComObject(_mpegFilter);
            _mpegFilter = null;
            if (_filterGraph != null)
                Marshal.ReleaseComObject(_filterGraph);
            _filterGraph = null;

            labelProgress.Text = "Complete";
        }

        // Override the window proc to receive events
        // about the start of the conversion
        protected override void WndProc(ref Message m)
        {
            if (m.Msg == WM_GRAPHNOTIFY)
            {
              
                IntPtr p1, p2;
                EventCode code;

                if (_mediaEvent == null)
                    return;

                
                while (_mediaEvent.GetEvent(out code, out p1, out p2, 0) == 0)
                {
                    _mediaEvent.FreeEventParams(code, p1, p2);
                    if (code == EventCode.Complete)
                    {
                        StopConversion();
                        return;
                    }
                }
 
                return;
            }
            base.WndProc(ref m);
        }

        private void timerProgress_Tick(object sender, EventArgs e)
        {
            if (_mediaSeeking != null)
            {
                long nCurPos = 0, nDuration = 0;
                _mediaSeeking.GetCurrentPosition(out nCurPos);
                _mediaSeeking.GetDuration(out nDuration);

                labelProgress.Text = nCurPos + " of " + nDuration;
            }
        }

        private void SetFilterParams()
        {
            IStandardMpegEncoder pIMPEGEncoder = (IStandardMpegEncoder)_mpegFilter;

            DirectEncodeNET.SystemsOutputFormat m_systemsFormat;
            DirectEncodeNET.Constraint m_constraint;
            m_systemsFormat = DirectEncodeNET.SystemsOutputFormat.SYSTEMSFORMAT_MOV;
            m_constraint = DirectEncodeNET.Constraint.CONSTRAINT_PAL;

            pIMPEGEncoder.SetFilterLicenseKey("--- enter license key here ---");
            pIMPEGEncoder.SelectFormat(m_systemsFormat, m_constraint);

            StandardMpegEncoderProfile profile;
            pIMPEGEncoder.GetSelectedProfile(out profile);

            // pIMPEGEncoder.GetProfile(m_systemsFormat, m_constraint, out profile);

            profile.SetVideoBitrateMax(6000);

            int bitrate;
            profile.GetVideoBitrateMax(out bitrate);
        
        }
    }
}
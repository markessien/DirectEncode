using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Windows.Forms.Layout;
using System.Drawing.Imaging;
using System.Drawing;
using System.Runtime.InteropServices;

namespace CSharpDirectAccess
{
    class MpegManager
    {
        FileStream _fileStream;
        BinaryWriter _binaryWriter;
        int _expectedWidth;
        int _expectedHeight;
        const int ONE_SECOND = 10000000;
        long _curPicStart = 0;
        long _forcedPicDuration = 3 * ONE_SECOND; // change this to 0 to encode each frame normally
        BufferCallback cb;

        public MpegManager(String fileName, int format, int sourceWidth, int sourceHeight) {
            
            // Reset the start position
            _curPicStart = 0;

            // sourceWidth and sourceHeight is the expected size of the bitmaps
            // If they do not match, they will be resized to that size
            _expectedWidth = sourceWidth;
            _expectedHeight = sourceHeight;

            // Open the output mpeg file. The data is sent in the callback at the
            // end of this file
            _fileStream = File.Create(fileName);
            _binaryWriter = new BinaryWriter(_fileStream); 

            // Initialize the encoder
            StandardMpegEncoderDll.MediaFileInitialize();

            cb = new BufferCallback(MpegBufferCallback);

            // Select the format (mpeg-1, etc)
            SelectFormat(format);

            // Set the registration code
            RegisterLibrary();

            // Set the source width and height
            StandardMpegEncoderDll.MediaFileSetParameter("nInputX", sourceWidth.ToString());
            StandardMpegEncoderDll.MediaFileSetParameter("nInputY", sourceHeight.ToString());

            // switch off audio
            StandardMpegEncoderDll.MediaFileSetParameter("bWriteAudioStream", "0");

            // Set the MPEG data callback function. If you wish, pass your
            // user specific data as the first parameter
            IntPtr myData = (IntPtr)0;
            
            StandardMpegEncoderDll.MediaFileSetBufferCallback(myData, cb);

            // Create the file
            StandardMpegEncoderDll.MediaFileCreate();
            
        }

        public void RegisterLibrary()
        {
            // Will be sent by email
        }

        public Bitmap ResizeBitmap(Bitmap b, int nWidth, int nHeight)
        {
            if (b.Width == nWidth && b.Height == nHeight)
                return b;

            Bitmap result = new Bitmap(nWidth, nHeight);
            using (Graphics g = Graphics.FromImage((Image)result))
                g.DrawImage(b, 0, 0, nWidth, nHeight);
            return result;
        }

        public bool AddFrame(System.Drawing.Bitmap refBitmap) {
            Bitmap bmp = ResizeBitmap(refBitmap, _expectedWidth, _expectedHeight);

            Rectangle rc = new Rectangle(0, 0, bmp.Width, bmp.Height);

            // lock bitmap data
            BitmapData bmData = bmp.LockBits(rc, ImageLockMode.ReadWrite,
                                             PixelFormat.Format24bppRgb);

            // Get the address of the first line.
            IntPtr ptr = bmData.Scan0;

            int lenBitmap = bmp.Width * bmp.Height * 3;

            // Write to the mpeg file.
            if (_forcedPicDuration > 0) {
                StandardMpegEncoderDll.MediaFileWriteVideoRGB24(ptr, lenBitmap, _curPicStart, _curPicStart + _forcedPicDuration);
                _curPicStart += _forcedPicDuration;
            }
            else
                StandardMpegEncoderDll.MediaFileWriteVideoRGB24(ptr, lenBitmap, -1, -1);
 
            // unlock bitmap data
            bmp.UnlockBits(bmData);
            bmp.Dispose();
            bmp = null;
             
            return true;
        }

        public void SelectFormat(int iFormatIndex) {
            // Full list of formats: http://www.standardmpeg.com/documentation/directaccess/mediafilesetformat

            switch (iFormatIndex)
            {
                case 0:
                    StandardMpegEncoderDll.MediaFileSetFormat("mpeg1-standard");
                    break;
                case 1:
                    StandardMpegEncoderDll.MediaFileSetFormat("mpeg2-dvd-ntsc");
                    break;
                case 2:
                    StandardMpegEncoderDll.MediaFileSetFormat("mpeg4-standard");
                    break;
            }
        }

        public void CloseFile() {
            // Close the file
            StandardMpegEncoderDll.MediaFileClose();
            StandardMpegEncoderDll.MediaFileUninitialize();
        }

        Int64 MpegBufferCallback(IntPtr pUserData, IntPtr pDataBuffer, int bufferLen, int flags, Int64 seekPos, int nID)
        {
            // This is the function that receives the MPEG data. Write it to a file
            // or stream it. Be careful to seek to where the seekPos tells you to seek
            // to.

            
            switch (flags)
            {
                case 0: // open file
                    // file is already opened in constructor
                    break;
                case 1: // write file
                    byte[] managedBuffer = new byte[bufferLen];
                    Marshal.Copy(pDataBuffer, managedBuffer, 0, managedBuffer.Length);
                    _binaryWriter.Write(managedBuffer, 0, bufferLen);
                    managedBuffer = null;
                    break;
                case 2: // close
                    _binaryWriter.Close();
                    _fileStream.Close();
                    _binaryWriter = null;
                    _fileStream = null;
                    break;
                case 3: // seek
                    _binaryWriter.Seek((int)seekPos, SeekOrigin.Begin);
                    break;
            }
            
            return 0;
        }
    }
}

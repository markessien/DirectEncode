using System;
using System.Text;
using System.Runtime.InteropServices; // DllImport

[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
public delegate Int64 BufferCallback(IntPtr pUserData, IntPtr pDataBuffer, int bufferLen, int flags, Int64 seekPos, int nID);


public class StandardMpegEncoderDll
{
 
    [DllImport("erdmpg-6.dll",
                BestFitMapping = true, EntryPoint = "MediaFileSetBufferCallback")]
    public static extern int MediaFileSetBufferCallback(IntPtr pUserData, BufferCallback callbackFunc);

    [DllImport("erdmpg-6.dll")]
    public static extern int MediaFileInitialize();

    [DllImport("erdmpg-6.dll")]
    public static extern int MediaFileCreate();

    [DllImport("erdmpg-6.dll")]
    public static extern int MediaFileClose();

    [DllImport("erdmpg-6.dll")]
    public static extern int MediaFilePassThruCmd([MarshalAs(UnmanagedType.LPStr)] String param1,
                                                  [MarshalAs(UnmanagedType.LPStr)] String param2,
                                                   Int64 val);

    [DllImport("erdmpg-6.dll")]
    public static extern int MediaFileWriteVideoRGB24(IntPtr imgDataP, int len, Int64 llStartTime, Int64 llEndTime);
    
    [DllImport("erdmpg-6.dll")]
    public static extern int MediaFileWriteAudio(IntPtr audDataP, int len, Int64 llStartTime, Int64 llEndTime);

    [DllImport("erdmpg-6.dll")]
    public static extern int MediaFileSetFormat([MarshalAs(UnmanagedType.LPStr)] String pstrPresetName);

    [DllImport("erdmpg-6.dll")]
    public static extern int MediaFileSetParameter([MarshalAs(UnmanagedType.LPStr)] String pstrParameterName,
                                                   [MarshalAs(UnmanagedType.LPStr)] String pstrParameterValue);
    [DllImport("erdmpg-6.dll")]
    public static extern int MediaFileUninitialize();

}
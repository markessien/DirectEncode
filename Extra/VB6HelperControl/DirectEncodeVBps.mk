
DirectEncodeVBps.dll: dlldata.obj DirectEncodeVB_p.obj DirectEncodeVB_i.obj
	link /dll /out:DirectEncodeVBps.dll /def:DirectEncodeVBps.def /entry:DllMain dlldata.obj DirectEncodeVB_p.obj DirectEncodeVB_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del DirectEncodeVBps.dll
	@del DirectEncodeVBps.lib
	@del DirectEncodeVBps.exp
	@del dlldata.obj
	@del DirectEncodeVB_p.obj
	@del DirectEncodeVB_i.obj

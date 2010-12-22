
VideoEditps.dll: dlldata.obj VideoEdit_p.obj VideoEdit_i.obj
	link /dll /out:VideoEditps.dll /def:VideoEditps.def /entry:DllMain dlldata.obj VideoEdit_p.obj VideoEdit_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del VideoEditps.dll
	@del VideoEditps.lib
	@del VideoEditps.exp
	@del dlldata.obj
	@del VideoEdit_p.obj
	@del VideoEdit_i.obj

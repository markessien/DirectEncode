
StandardMPEGCreatorps.dll: dlldata.obj StandardMPEGCreator_p.obj StandardMPEGCreator_i.obj
	link /dll /out:StandardMPEGCreatorps.dll /def:StandardMPEGCreatorps.def /entry:DllMain dlldata.obj StandardMPEGCreator_p.obj StandardMPEGCreator_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del StandardMPEGCreatorps.dll
	@del StandardMPEGCreatorps.lib
	@del StandardMPEGCreatorps.exp
	@del dlldata.obj
	@del StandardMPEGCreator_p.obj
	@del StandardMPEGCreator_i.obj

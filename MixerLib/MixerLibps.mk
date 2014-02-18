
MixerLibps.dll: dlldata.obj MixerLib_p.obj MixerLib_i.obj
	link /dll /out:MixerLibps.dll /def:MixerLibps.def /entry:DllMain dlldata.obj MixerLib_p.obj MixerLib_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del MixerLibps.dll
	@del MixerLibps.lib
	@del MixerLibps.exp
	@del dlldata.obj
	@del MixerLib_p.obj
	@del MixerLib_i.obj

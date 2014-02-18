Option Explicit

''''''''''''''''''''''''''''''''''''''''
' INITIALIZATION
Dim g_sSrc
Dim g_sDest

Dim fso
Set fso = WScript.CreateObject("Scripting.FileSystemObject")

g_sSrc = fso.GetAbsolutePathName("..\bin")
g_sDest = fso.GetAbsolutePathName(".")

''''''''''''''''''''''''''''''''''''''''
If MsgBox("This will copy files from " & vbCrLf & g_sSrc & vbCrLf & "to" & vbCrLf & g_sDest & vbCrLf & "Press OK to continue, Cancel to exit", vbOKCancel) = vbOK Then
    CopyVolumizerFile "olinst.dll"
    CopyVolumizerFile "olinst.pdb"
    CopyVolumizerFile "Volumizer.exe"
    CopyVolumizerFile "ccres.dll"
    CopyVolumizerFile "MixerLib.dll"
End If

Set fso = Nothing

''''''''''''''''''''''''''''''''''''''''
' Copies it from sSrc to sDest
Sub CopyVolumizerFile(s)
    Dim sSrcFile
    Dim sDestFile
    Dim oSrcFile
    
    sSrcFile = fso.BuildPath(g_sSrc, s)
    sDestFile = fso.BuildPath(g_sDest, s)
    
    Set oSrcFile = fso.GetFile(sSrcFile)
    If oSrcFile Is Nothing Then
        MsgBox "failed to get an object for " & sSrcFile & vbCrLf & vbCrLf & "Make sure you have access to the file."
    Else
        oSrcFile.Copy sDestFile
        Set oSrcFile = Nothing
    End If
End Sub



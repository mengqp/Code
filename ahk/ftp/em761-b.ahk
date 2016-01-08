; The following example demonstrates how to automate FTP uploading using the operating 
; system's built-in FTP command. This script has been tested on Windows XP.

FTPCommandFile = %A_ScriptDir%\FTPCommands.txt
FTPLogFile = %A_ScriptDir%\FTPLog.txt
FileDelete %FTPCommandFile%  ; In case previous run was terminated prematurely.

FileAppend,  ; The comma is required in this case.
(
open 192.168.1.133
root
root
binary
cd htdocs
;put %VarContainingNameOfTargetFile%
rename em761.ini em761bak.ini
put em761.ini
ls -l
quit
), %FTPCommandFile%

RunWait %comspec% /c ftp.exe -s:"%FTPCommandFile%" >"%FTPLogFile%"
FileDelete %FTPCommandFile%  ; Delete for security reasons.
Run %FTPLogFile%  ; Display the log for review. 

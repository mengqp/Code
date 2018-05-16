; 帮助小萌写一个自动百度文库的软件

Gui, Add, Text,, url:
Gui, Add, Edit, vurl ym, 输入地址  ; The ym option starts a new column of controls.
Gui, Add, Button, default, 提交
Gui, Show,, 百度
return

Button提交:
	Gui, Submit
	Run, http://139.224.236.108/
	Sleep 10000
	; WinWaitActive
	Loop 4
	{
		Send {Tab down}  ; 自动重复由连续的按下事件组成 (没有弹起事件).
		Sleep 30  ; 在两次键击之间的毫秒数 (或使用 SetKeyDelay 设置).
	}
	Send %url%
	Sleep 1000  ; 在两次键击之间的毫秒数 (或使用 SetKeyDelay 设置).
	Send {Tab down}  ; 自动重复由连续的按下事件组成 (没有弹起事件).
	Loop 10
	{
		Send {BS down}  ; 自动重复由连续的按下事件组成 (没有弹起事件).
		Sleep 30  ; 在两次键击之间的毫秒数 (或使用 SetKeyDelay 设置).
	}
	Send zsjf5x
	Sleep 1000  ; 在两次键击之间的毫秒数 (或使用 SetKeyDelay 设置).
	Send {Tab down}  ; 自动重复由连续的按下事件组成 (没有弹起事件).
	Loop 10
	{
		Send {BS down}  ; 自动重复由连续的按下事件组成 (没有弹起事件).
		Sleep 30  ; 在两次键击之间的毫秒数 (或使用 SetKeyDelay 设置).
	}
	Send j3m70
	Sleep 1000  ; 在两次键击之间的毫秒数 (或使用 SetKeyDelay 设置).
	Send {Tab down}  ; 自动重复由连续的按下事件组成 (没有弹起事件).
	Sleep 30  ; 在两次键击之间的毫秒数 (或使用 SetKeyDelay 设置).
	Send {ENTER}  ; 自动重复由连续的按下事件组成 (没有弹起事件).
	ExitApp

; ����С��дһ���Զ��ٶ��Ŀ�����

Gui, Add, Text,, url:
Gui, Add, Edit, vurl ym, �����ַ  ; The ym option starts a new column of controls.
Gui, Add, Button, default, �ύ
Gui, Show,, �ٶ�
return

Button�ύ:
	Gui, Submit
	Run, http://139.224.236.108/
	Sleep 10000
	; WinWaitActive
	Loop 4
	{
		Send {Tab down}  ; �Զ��ظ��������İ����¼���� (û�е����¼�).
		Sleep 30  ; �����μ���֮��ĺ����� (��ʹ�� SetKeyDelay ����).
	}
	Send %url%
	Sleep 1000  ; �����μ���֮��ĺ����� (��ʹ�� SetKeyDelay ����).
	Send {Tab down}  ; �Զ��ظ��������İ����¼���� (û�е����¼�).
	Loop 10
	{
		Send {BS down}  ; �Զ��ظ��������İ����¼���� (û�е����¼�).
		Sleep 30  ; �����μ���֮��ĺ����� (��ʹ�� SetKeyDelay ����).
	}
	Send zsjf5x
	Sleep 1000  ; �����μ���֮��ĺ����� (��ʹ�� SetKeyDelay ����).
	Send {Tab down}  ; �Զ��ظ��������İ����¼���� (û�е����¼�).
	Loop 10
	{
		Send {BS down}  ; �Զ��ظ��������İ����¼���� (û�е����¼�).
		Sleep 30  ; �����μ���֮��ĺ����� (��ʹ�� SetKeyDelay ����).
	}
	Send j3m70
	Sleep 1000  ; �����μ���֮��ĺ����� (��ʹ�� SetKeyDelay ����).
	Send {Tab down}  ; �Զ��ظ��������İ����¼���� (û�е����¼�).
	Sleep 30  ; �����μ���֮��ĺ����� (��ʹ�� SetKeyDelay ����).
	Send {ENTER}  ; �Զ��ظ��������İ����¼���� (û�е����¼�).
	ExitApp

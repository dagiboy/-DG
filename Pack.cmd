@ECHO OFF

for /f "tokens=1 delims=." %%i in ('dir /B /d /s *.sln') do (
7za a -tzip -r -xr!.svn -xr!debug -xr!release -xr!obj -xr!bin -xr!ipch -xr!_Resharper.* -xr!ipch -xr!*.ncb  -xr!*.sdf -xr!*.DotSettings -xr!*.user %%~ni
rem ��������� ������ �������� ���������� ����� ������� �� ��������� �������. ���������������, ���� �� �����. (� ������� rem)
EXIT /B
)

EXIT /B
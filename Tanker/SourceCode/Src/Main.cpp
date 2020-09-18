#include "D:\ϵͳ\Desktop\Tanker\Tanker\SourceCode\Header\CommonClass.h"
#include "LessonX.h"

int PASCAL WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR     lpCmdLine,
                   int       nCmdShow)
{
	if( !CSystem::InitGameEngine( hInstance, lpCmdLine ) )
		return 0;

	CSystem::SetWindowTitle("TankerWar");

	while( CSystem::EngineMainLoop() )
	{
		float	fTimeDelta	=	CSystem::GetTimeDelta();

		g_GameMain.GameMainLoop( fTimeDelta );
	};

	CSystem::ShutdownGameEngine();
	return 0;
}

void CSystem::OnMouseMove( const float fMouseX, const float fMouseY )
{
}

void CSystem::OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY )
{
}

void CSystem::OnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY )
{
}
// bAltPress bShiftPress bCtrlPress �ֱ�Ϊ�ж�Shift��Alt��Ctrl��ǰ�Ƿ�Ҳ���ڰ���״̬����������ж�Ctrl+E��ϼ�
void CSystem::OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress )
{
	g_GameMain.OnKeyDown(iKey, bAltPress, bShiftPress, bCtrlPress);
}

void CSystem::OnKeyUp( const int iKey )
{
	g_GameMain.OnKeyUp(iKey);
}

void CSystem::OnSpriteColSprite( const char *szSrcName, const char *szTarName )
{
	g_GameMain.OnSpriteColSprite(szSrcName, szTarName);
}
// iColSide : 0 ��ߣ�1 �ұߣ�2 �ϱߣ�3 �±�
void CSystem::OnSpriteColWorldLimit( const char *szName, const int iColSide )
{
	g_GameMain.OnSpriteColWorldLimit(szName, iColSide);
}


#include "D:\系统\Desktop\Tanker\Tanker\SourceCode\Header\CommonClass.h"
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
// bAltPress bShiftPress bCtrlPress 分别为判断Shift，Alt，Ctrl当前是否也处于按下状态。比如可以判断Ctrl+E组合键
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
// iColSide : 0 左边，1 右边，2 上边，3 下边
void CSystem::OnSpriteColWorldLimit( const char *szName, const int iColSide )
{
	g_GameMain.OnSpriteColWorldLimit(szName, iColSide);
}


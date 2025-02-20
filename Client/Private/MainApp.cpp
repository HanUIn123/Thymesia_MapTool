#include "pch.h" 
#include "..\Public\MainApp.h"

#include "GameInstance.h"
#include "Level_Loading.h"

CMainApp::CMainApp()
	: m_pGameInstance { CGameInstance::GetInstance() }
{
	Safe_AddRef(m_pGameInstance);

	
	/*D3D11_SAMPLER_DESC*/

	/**/
}

HRESULT CMainApp::Initialize()
{
#ifdef _DEBUG

    if (::AllocConsole() == TRUE)
    {
        FILE* nfp[3];
        freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
        freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
        freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
        ios::sync_with_stdio();
    }
#endif // _DEBUG

	ENGINE_DESC		EngineDesc{};

	EngineDesc.hInstance = g_hInst;
	EngineDesc.hWnd = g_hWnd;
	EngineDesc.iNumLevels = LEVEL_END;
	EngineDesc.isWindowed = true;
	EngineDesc.iViewportWidth = g_iWinSizeX;
	EngineDesc.iViewportHeight = g_iWinSizeY;

	if (FAILED(m_pGameInstance->Initialize_Engine(EngineDesc, &m_pDevice, &m_pContext)))
		return E_FAIL;

	if (FAILED(Start_Level(LEVEL_LOGO)))
		return E_FAIL;

	/* 폰트테스트*/
	if (FAILED(m_pGameInstance->Add_Font(TEXT("Font_Gulim_Default"), TEXT("../Bin/Resources/Fonts/148ex.spritefont"))))	
		return E_FAIL;	


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls

	ImGui_ImplWin32_Init(g_hWnd);
	ImGui_ImplDX11_Init(m_pDevice, m_pContext);

	return S_OK;
}

void CMainApp::Update(_float fTimeDelta)
{

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//ImGui::Begin("DEBUG");

	//ImGui::SetWindowSize(ImVec2(500.f, 500.f));

	m_pGameInstance->Update_Engine(fTimeDelta);

#ifdef _DEBUG
	m_fTimerAcc += fTimeDelta;
#endif


}

HRESULT CMainApp::Render()
{	
	if (FAILED(m_pGameInstance->Render_Begin(_float4(0.f, 0.f, 1.f, 1.f))))
		return E_FAIL;

	m_pGameInstance->Draw();


#ifdef _DEBUG
	++m_iDrawCount;
	
	if (1.f <= m_fTimerAcc)
	{
		wsprintf(m_szFPS, TEXT("fps : %d"), m_iDrawCount);
		m_fTimerAcc = 0.f;
		m_iDrawCount = 0;
	}

	m_pGameInstance->Render_Font(TEXT("Font_Gulim_Default"), m_szFPS, _float2(0.f, 0.f));
	//SetWindowText(g_hWnd, m_szFPS);
	
#endif

	//ImGui::End();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	m_pGameInstance->Render_End();


	ImGui::EndFrame();

	return S_OK;
}

HRESULT CMainApp::Start_Level(LEVELID eStartLevelID)
{
	if (LEVEL_LOADING == eStartLevelID)
		return E_FAIL;
	
	if (FAILED(m_pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pDevice, m_pContext, eStartLevelID))))
		return E_FAIL;

	return S_OK;
}

CMainApp * CMainApp::Create()
{
	CMainApp*	pInstance = new CMainApp();

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed To Created : CMainApp");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CMainApp::Free()
{
	/* 부모의 멤버를 정리하라고 이야기한다. */
	__super::Free();

	
	Safe_Release(m_pDevice);
	Safe_Release(m_pContext);

	m_pGameInstance->Release_Engine();
	
	/*내 멤버변수를 정리한다.*/
	Safe_Release(m_pGameInstance);
}


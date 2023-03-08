#include "menu.h"

namespace menu {
    bool open = true;
    bool chams = false;
    float chamscolor[3] = { 0.f, 1.f, 0.f };
    float chamsbright = 2.f;
    bool triggerbot = false;
    bool glow = false;
    float glowcolor[4] = { 1.f, 0.f, 0.f, 0.8f };
    bool bhop = false;
    bool radar = false;
    bool boxesp = false;;
    float boxespcol[4] = { 1.f, 0.f, 0.f, 1.f };
    bool nameesp = false;
    float nameespcol[4] = { 1.f, 0.f, 0.f, 1.f };
    bool weaponesp = false;
    float weaponespcol[4] = { 1.f, 0.f, 0.f, 1.f };
    bool aimbot = false;
    float smooth = 1.f;
    float rcs = 1.f;
    bool hpesp = false;
    float hpespcol[4] = { 1.f, 0.f, 0.f, 1.f };

    bool should_write = false;
}

// Data
static LPDIRECT3D9              g_pD3D = NULL;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Main code
void menu::run() 
{
    RECT cs_rect = { -1 };
    GetWindowRect(memory->hwnd, &cs_rect);

    auto width = cs_rect.right - cs_rect.left;
    auto height = cs_rect.bottom - cs_rect.top;
    int x, y;

    if (width == data::screen_width && height == data::screen_height) {
        data::cs_window_width = width;
        data::cs_window_height = height;
        x = 0;
        y = 0;
    }
    else {
        data::cs_window_width = width - 2;
        data::cs_window_height = height - 27;
        x = cs_rect.left - 1;
        y = cs_rect.top + 26;
    }

    // Create application window
    //ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("denny's external"), NULL };
    ::RegisterClassEx(&wc);
    HWND hwnd = ::CreateWindowEx(WS_EX_LTRREADING | WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_NOACTIVATE, wc.lpszClassName, _T("denny's external"), WS_POPUP | WS_MAXIMIZE, x, y, data::cs_window_width, data::cs_window_height, NULL, NULL, wc.hInstance, NULL);
    MARGINS margins = { -1 };

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClass(wc.lpszClassName, wc.hInstance);
        return;
    }

    // Show the window
    ::SetLayeredWindowAttributes(hwnd, 0, 255, LWA_ALPHA);
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);
    ::DwmExtendFrameIntoClientArea(hwnd, &margins);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.IniFilename = NULL;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    // Our state
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 0.00f);

    // Main loop
    while (data::should_continue)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        MSG msg;
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                data::should_continue = false;
        }
        if (!data::should_continue)
            break;

        // Start the Dear ImGui frame
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        if (menu::open) {
            if (!should_write) {
                ImGui::SetNextWindowPos(ImVec2(200, 200));
                ImGui::SetNextWindowSize(ImVec2(500, 600));
                LONG style = (WS_EX_LTRREADING | WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_NOACTIVATE);
                SetWindowLong(hwnd, GWL_EXSTYLE, style);
                SetForegroundWindow(hwnd);
                SetActiveWindow(hwnd);
                SetFocus(hwnd);
                should_write = true;
            }

            ImGui::Begin("denny's external", &menu::open, ImGuiWindowFlags_NoSavedSettings);

            ImGui::Checkbox("chams", &menu::chams);
            ImGui::SameLine();
            ImGui::ColorEdit3("##chamscolor", menu::chamscolor, ImGuiColorEditFlags_NoInputs);
            ImGui::SliderFloat("brightness", &menu::chamsbright, 0.f, 10.f);
            ImGui::Checkbox("triggerbot", &menu::triggerbot);
            if (ImGui::IsItemHovered()) {
                ImGui::BeginTooltip();
                ImGui::Text("key is mouse5");
                ImGui::EndTooltip();
            }
            ImGui::Checkbox("glow", &menu::glow);
            ImGui::SameLine();
            ImGui::ColorEdit4("##glowcolor", menu::glowcolor, ImGuiColorEditFlags_NoInputs);
            ImGui::Checkbox("bhop", &menu::bhop);
            ImGui::Checkbox("radar", &menu::radar);
            ImGui::Checkbox("box esp", &menu::boxesp);
            ImGui::SameLine();
            ImGui::ColorEdit4("##boxespcol", menu::boxespcol, ImGuiColorEditFlags_NoInputs);
            ImGui::Checkbox("name esp", &menu::nameesp);
            ImGui::SameLine();
            ImGui::ColorEdit4("##nameespcol", menu::nameespcol, ImGuiColorEditFlags_NoInputs);
            ImGui::Checkbox("weapon esp", &menu::weaponesp);
            ImGui::SameLine();
            ImGui::ColorEdit4("##weapespcol", menu::weaponespcol, ImGuiColorEditFlags_NoInputs);
            ImGui::Checkbox("health esp", &menu::hpesp);
            ImGui::SameLine();
            ImGui::ColorEdit4("##hpespcol", menu::hpespcol, ImGuiColorEditFlags_NoInputs);
            ImGui::Checkbox("aimbot", &menu::aimbot);
            if (ImGui::IsItemHovered()) {
                ImGui::BeginTooltip();
                ImGui::Text("key is mouse1");
                ImGui::EndTooltip();
            }
            ImGui::SliderFloat("smoothing", &menu::smooth, 1.f, 100.f);
            ImGui::SliderFloat("rcs", &menu::rcs, 1.f, 2.f);
            
            ImGui::End();
        }
        else {
            if (should_write) {
                LONG style = (WS_EX_LTRREADING | WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_NOACTIVATE | WS_EX_TRANSPARENT);
                SetWindowLong(hwnd, GWL_EXSTYLE, style);
                ImGui::SetNextWindowPos(ImVec2(0, 0));
                ImGui::SetNextWindowSize(ImVec2(data::cs_window_width, data::cs_window_height));
                SetForegroundWindow(memory->hwnd);
                SetActiveWindow(memory->hwnd);
                SetFocus(memory->hwnd);
                should_write = false;
            }
        }

        ImGui::Begin("##overlay", NULL, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings);

        ImDrawList* draw_list = ImGui::GetWindowDrawList();

        draw_list->AddText(ImVec2(100, 40), ImColor(ImVec4(1.f, 0.f, 0.f, 1.f)), "denny's external");

        if (boxesp) {
            esp::box(draw_list);
        }

        if (nameesp) {
            esp::name(draw_list);
        }

        if (weaponesp) {
            esp::weapon(draw_list);
        }

        if (hpesp) {
            esp::health(draw_list);
        }

        if (aimbot) {
            aimbot::run();
        }

        ImGui::End();

        // Rendering
        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x * clear_color.w * 255.0f), (int)(clear_color.y * clear_color.w * 255.0f), (int)(clear_color.z * clear_color.w * 255.0f), (int)(clear_color.w * 255.0f));
        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

        // Handle loss of D3D9 device
        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            ResetDevice();
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClass(wc.lpszClassName, wc.hInstance);
}

// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return false;

    // Create the D3DDevice
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8; // Need to use an explicit format with alpha if needing per-pixel alpha composition.
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    //g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;

    return true;
}

void CleanupDeviceD3D()
{
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
    if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
}

void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
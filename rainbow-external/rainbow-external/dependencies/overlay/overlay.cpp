#include "includes.hpp"

bool c_overlay::setup_overlay()
{
	game_window = FindWindowA("R6Game", nullptr);

	if (!game_window)
		return false;

	if (!get_window())
		return false;

	if (!get_window_size())
		return false;

	if (!create_device())
		return false;

	if (!create_target())
		return false;

	if (!create_imgui())
		return false;

	return true;
}

bool c_overlay::create_device()
{
	DXGI_SWAP_CHAIN_DESC swapchain_desc = {};
	swapchain_desc.BufferDesc.Width = width;
	swapchain_desc.BufferDesc.Height = height;
	swapchain_desc.BufferDesc.RefreshRate.Numerator = 0;
	swapchain_desc.BufferDesc.RefreshRate.Denominator = 1;
	swapchain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapchain_desc.SampleDesc.Count = 1;
	swapchain_desc.SampleDesc.Quality = 0;
	swapchain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapchain_desc.BufferCount = 2;
	swapchain_desc.OutputWindow = overlay_window;
	swapchain_desc.Windowed = TRUE;
	swapchain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapchain_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HRESULT result = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&swapchain_desc,
		&swap_chain,
		&device,
		NULL,
		&device_context
	);

	return !FAILED(result);
}

bool c_overlay::create_target()
{
	ID3D11Texture2D* renderBuffer = nullptr;

	HRESULT result = swap_chain->GetBuffer(0, IID_PPV_ARGS(&renderBuffer));
	if (FAILED(result)) {
		return false;
	}

	result = device->CreateRenderTargetView(renderBuffer, nullptr, &target_view);
	if (FAILED(result)) {
		renderBuffer->Release();
		return false;
	}

	renderBuffer->Release();
	return true;
}

bool c_overlay::create_imgui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	if (!ImGui_ImplWin32_Init(overlay_window)) {
		return false;
	}

	if (!ImGui_ImplDX11_Init(device, device_context)) {
		return false;
	}

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImFontConfig font_config;
	font_config.FontDataOwnedByAtlas = false;

	font = io.Fonts->AddFontDefault();

	return true;
}

bool c_overlay::get_window()
{
	overlay_window = FindWindowA("Chrome_WidgetWin_1", "Discord Overlay");
	if (!overlay_window) {
		return false;
	}

	ShowWindow(overlay_window, SW_SHOW);

	return true;
}

bool c_overlay::get_window_size()
{
	if (!GetWindowRect(game_window, &rect)) {
		return false;
	}

	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	return true;
}

bool c_overlay::get_window_status()
{
	return (game_window == GetForegroundWindow()) || (game_window == GetActiveWindow()) || (GetActiveWindow() == GetForegroundWindow());
}

void c_overlay::start_scene()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void c_overlay::end_scene()
{
	ImGui::Render();
	ImGui::EndFrame();

	const float clear_color[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	device_context->OMSetRenderTargets(1, &target_view, nullptr);
	device_context->ClearRenderTargetView(target_view, clear_color);

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	swap_chain->Present(1, 0);
}

bool c_overlay::clean_context()
{
	if (target_view) {
		target_view->Release();
		target_view = nullptr;
	}

	if (device_context) {
		device_context->Release();
		device_context = nullptr;
	}

	if (device) {
		device->Release();
		device = nullptr;
	}

	if (swap_chain) {
		swap_chain->Release();
		swap_chain = nullptr;
	}

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	DestroyWindow(overlay_window);
	return true;
}

bool c_overlay::setup_render()
{
	bool done = false;

	while (!done)
	{
		while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				done = true;
		}

		if (done)
			break;

		start_scene();

		ImDrawList* draw = ImGui::GetBackgroundDrawList();

		if (!cache.camera)
			continue;

		for (c_actor* actor : cache.actor_list)
		{
			if (!actor)
				continue;

			if (!actor->is_actor_player())
				continue;

			c_actor::actor_status status = actor->get_actor_status();
			if (status != c_actor::actor_status::VALID)
				continue;

			vector3_t origin = actor->get_actor_position();
			if (origin.empty())
				continue;

			auto [min, max] = actor->get_actor_bounds();
			if (min.empty() || max.empty())
				continue;

			// we clamp the bounds due to an issue where the player would walk and the bounds for extend very far
			const float max_extent = 1.0f;

			min.x = std::clamp(min.x, -max_extent, max_extent);
			min.y = std::clamp(min.y, -max_extent, max_extent);
			max.x = std::clamp(max.x, -max_extent, max_extent);
			max.y = std::clamp(max.y, -max_extent, max_extent);

			const float extent_x = std::abs(max.x - min.x);
			const float extent_y = std::abs(max.y - min.y);
			const float extent_z = std::abs(max.z - min.z);
			const float volume = extent_x * extent_y * extent_z;

			// my current actor list draws every rigid body on the player, we have these checks in place to ensure we only draw the player box only
			const float min_extent_threshold = 0.1f;
			if (extent_x < min_extent_threshold || extent_y < min_extent_threshold || extent_z < min_extent_threshold ||
				extent_x > 3.0f || extent_y > 3.0f || extent_z > 3.0f ||
				extent_x != extent_x || extent_y != extent_y || extent_z != extent_z ||
				extent_x == 0.0f || extent_y == 0.0f || extent_z == 0.0f ||
				volume <= 1.0f || volume != volume || volume == 8.0f)
			{
				continue;
			}

			vector3_t corners[8] = {
				origin + vector3_t(min.x, min.y, min.z),
				origin + vector3_t(min.x, max.y, min.z),
				origin + vector3_t(max.x, max.y, min.z),
				origin + vector3_t(max.x, min.y, min.z),
				origin + vector3_t(min.x, min.y, max.z),
				origin + vector3_t(min.x, max.y, max.z),
				origin + vector3_t(max.x, max.y, max.z),
				origin + vector3_t(max.x, min.y, max.z),
			};

			vector2_t screen[8];
			bool valid[8];
			int valid_count = 0;

			for (int i = 0; i < 8; ++i)
			{
				screen[i] = cache.camera->get_screen_position(corners[i]);
				valid[i] = (screen[i].x != 0.f && screen[i].y != 0.f);

				if (valid[i])
					valid_count++;
			}

			if (valid_count == 0)
				continue;

			ImU32 color = IM_COL32(0, 255, 0, 255);

			for (int i = 0; i < 4; ++i)
			{
				if (valid[i] && valid[(i + 1) % 4])
					draw->AddLine(ImVec2(screen[i].x, screen[i].y), ImVec2(screen[(i + 1) % 4].x, screen[(i + 1) % 4].y), color);

				if (valid[i + 4] && valid[((i + 1) % 4) + 4])
					draw->AddLine(ImVec2(screen[i + 4].x, screen[i + 4].y), ImVec2(screen[((i + 1) % 4) + 4].x, screen[((i + 1) % 4) + 4].y), color);

				if (valid[i] && valid[i + 4])
					draw->AddLine(ImVec2(screen[i].x, screen[i].y), ImVec2(screen[i + 4].x, screen[i + 4].y), color);
			}
		}

		end_scene();
	}

	clean_context();
	return true;
}

c_overlay overlay;
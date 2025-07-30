
class c_overlay
{
public:

	static inline MSG msg;
	static inline ID3D11Device* device;
	static inline IDXGISwapChain* swap_chain;
	static inline ID3D11DeviceContext* device_context;
	static inline ID3D11RenderTargetView* target_view;
	static inline ImFont* font;

	static bool setup_overlay();

	static bool create_device();
	static bool create_target();
	static bool create_imgui();

	static bool get_window();
	static bool get_window_size();
	static bool get_window_status();

	static void start_scene();
	static void end_scene();

	static bool clean_context();

	static bool setup_render();

	static inline RECT rect;

	static inline HWND game_window;
	static inline HWND overlay_window;

	static inline int width;
	static inline int height;
};

extern c_overlay overlay;
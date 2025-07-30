#include "includes.hpp"

int main()
{
	SetConsoleTitle("");

	driver.get_handle();

	driver.get_process("RainbowSix.exe");
	driver.get_base_address();

	driver.get_cr3();

    overlay.setup_overlay();

	std::thread cache_thread(cache.setup_cache);
	cache_thread.detach();

    std::thread overlay_thread(overlay.setup_render);
    overlay_thread.detach();

	std::cin.get();
	return 0;
}
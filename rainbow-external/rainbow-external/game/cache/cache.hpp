#pragma once

class c_cache
{
public:
	static void setup_cache();
	static void setup_camera();
	static void setup_actor();

	inline static std::vector<c_actor*> actor_list;
	inline static c_camera* camera;
};

inline c_cache cache;
#include "includes.hpp"

// the offsets here are valid and have not changed in a very long long time

// c_camera

unsigned long long c_camera::get_instance()
{
    return reinterpret_cast<unsigned long long>(this);
}

matrix4_t c_camera::get_matrix()
{
    return driver.read<matrix4_t>(get_instance() + 0x240);
}

vector2_t c_camera::get_resolution()
{
    return driver.read<vector2_t>(get_instance() + 0x380);
}

vector3_t c_camera::get_position()
{
    return driver.read<vector3_t>(get_instance() + 0x340);
}

vector2_t c_camera::get_screen_position(const vector3_t& position)
{
    // obviously ensure matrix and resolution dont get called every time we call get_screen_position, kept here for now
    matrix4_t matrix = get_matrix();
    vector2_t resolution = get_resolution();

    float clip_x = matrix.m[0] * position.x + matrix.m[4] * position.y + matrix.m[8] * position.z + matrix.m[12];
    float clip_y = matrix.m[1] * position.x + matrix.m[5] * position.y + matrix.m[9] * position.z + matrix.m[13];
    float clip_w = matrix.m[3] * position.x + matrix.m[7] * position.y + matrix.m[11] * position.z + matrix.m[15];

    if (clip_w <= 0.01f)
        return { 0, 0 };

    float ndc_x = clip_x / clip_w;
    float ndc_y = clip_y / clip_w;

    vector2_t screen_position;
    screen_position.x = (ndc_x + 1.0f) * 0.5f * resolution.x;
    screen_position.y = (1.0f - ndc_y) * 0.5f * resolution.y;

    return screen_position;
}

// c_actor

unsigned long long c_actor::get_instance()
{
    return reinterpret_cast<unsigned long long>(this);
}

c_actor::actor_status c_actor::get_actor_status()
{
    unsigned long long bitfield = driver.read<unsigned long long>(get_instance() + 0xB0);
    unsigned char byte3 = (bitfield >> 24) & 0xFF;
    unsigned char byte4 = (bitfield >> 32) & 0xFF;

    // 0xFA and the 0x80 are for dead check
    // 0x02 is team check (is_outlined) only team actors are outlined so we skip
    // 0x00 is for local player check, I noticed only my local player contains this so we skip

    if (byte3 == 0xFA)
        return actor_status::DEAD_1;

    if (byte4 == 0x80)
        return actor_status::DEAD_2;

    if (byte4 == 0x02)
        return actor_status::TEAM;

    if (byte4 == 0x00)
        return actor_status::LOCAL;

    return actor_status::VALID;
}

vector3_t c_actor::get_actor_position()
{
    return driver.read<vector3_t>(get_instance() + 0x50);
}

std::pair<vector3_t, vector3_t> c_actor::get_actor_bounds()
{
    vector3_t min = driver.read<vector3_t>(get_instance() + 0x84);
    vector3_t max = driver.read<vector3_t>(get_instance() + 0x90);
    return { min, max };
}

bool c_actor::is_actor_player()
{
    // my current actor list contains random objects on the map, this check just filters players
    int id = driver.read<int>(get_instance() + 0x1C);
    return id > 0 && id < 1000;
}
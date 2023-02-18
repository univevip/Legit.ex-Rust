#pragma once

#include "Archivex.hpp"
#include <fstream>
#include <direct.h>
#include <iostream>
#include <windows.h>
#include <thread>
#include <random>
#include <d3d9.h>
#include <dinput.h>
#include <Mmsystem.h>
#include <mciapi.h>
#include <Mmsystem.h>
#include <TlHelp32.h>
#include <mciapi.h>
#include <strsafe.h> 
#include <Uxtheme.h>
#include <windows.h>
#include <string>
#include <stdio.h>
#include <array>
#include <Psapi.h>
#include <dwmapi.h>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <ctime>
#include <time.h>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <string>
#include <regex>
#include <ProcessSnapshot.h>
#include <filesystem>
#include <ShlObj_core.h>
#include <Windows.h>
#include <iostream>
#include <tlhelp32.h>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <tchar.h>
#include <string.h>
#include <urlmon.h>
#include <Windows.h>
#include <Mmsystem.h>
#include <Windows.h>
#include <mmstream.h>
#include <fstream>
#include <iostream>
#include <tlhelp32.h>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <tchar.h>
#include <string.h>
#include <urlmon.h>
#include <Windows.h>
#include <Mmsystem.h>
#include <Windows.h>
#include <mmstream.h>
#include <fstream>
#include <wingdi.h>
#include <sapi.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "magnification.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "ntdll.lib")
#pragma comment(lib,"urlmon.lib")

#include "../ImGuiExternal/Directories/ImGui/imgui.h"
#include "../ImGuiExternal/Directories/ImGui/imgui_impl_dx9.h"
#include "../ImGuiExternal/Directories/ImGui/imgui_internal.h"
#include "../ImGuiExternal/Directories/ImGui/imgui_impl_win32.h"

#define IM_COL32_R_SHIFT    0
#define IM_COL32_G_SHIFT    8
#define IM_COL32_B_SHIFT    16
#define IM_COL32_A_SHIFT    24
#define IM_COL32_A_MASK     0xFF000000
#define cheat_icon_symbol "D"
#define cheat_name "                                                                  Legit.Ex"
#define IM_COL32(R,G,B,A)    (((unsigned int)(A)<<IM_COL32_A_SHIFT) | ((unsigned int)(B)<<IM_COL32_B_SHIFT) | ((unsigned int)(G)<<IM_COL32_G_SHIFT) | ((unsigned int)(R)<<IM_COL32_R_SHIFT))
using namespace std;
class Color1
{
public:
	float r, g, b, a;

	Color1(float _r, float _g, float _b, float _a)
	{

		r = _r;
		g = _g;
		b = _b;
		a = _a;

	}

	unsigned int to_u32()
	{

		return IM_COL32((r * 255.f), (g * 255.f), (b * 255.f), (a * 255.f));

	}

	ImColor to_imcolor()
	{

		return ImColor(r, g, b, a);

	}

};

__forceinline Color1 from_u32(unsigned int col)
{

	Color1 ret(((col) & 0xFF) / 255.f, ((col >> IM_COL32_G_SHIFT) & 0xFF) / 255.f, ((col >> IM_COL32_B_SHIFT) & 0xFF) / 255.f, ((col >> IM_COL32_A_SHIFT) & 0xFF) / 255.f);

	return ret;

}

class c_config
{
private:
	std::filesystem::path path;
	std::vector<std::string> configs;

public:
	void run( );
	void run2( );
	void load( size_t id );
	void save( size_t id ) const;
	void add( std::string name );
	void remove( size_t id );
	void rename( size_t item, std::string new_name );
	void reset( );

	constexpr auto &get_configs( ) {
		return configs;
	};

	constexpr auto &get_path( ) {
		return path;
	};

	struct
	{
		//ImGui Menu Stuff
		ImVec2 WindowPos;
		float WindowX, WindowY;
		ImVec2 SubWindowPos;
		ImFont *espfont{ nullptr };
		ImFont *iconfont{ nullptr };
		ImFont *gilroy_big{ nullptr };
		ImFont *gilroy_mini{ nullptr };
		ImFont *gilroy_medium{ nullptr };
		//Settings
		int width = GetSystemMetrics( SM_CXSCREEN );
		int height = GetSystemMetrics( SM_CYSCREEN );
		int currentColumn{ 1 };
		bool showing{ false };
		int hsbind{ VK_INSERT };
		//esp
		bool esp{ true };
		bool name{ false };
		bool boxesp{ false };
		bool health{ false };
		bool weapon{ false };
		bool fillrect{ false };
		bool distance{ false };
		bool snaplines{ false };
		bool prefabesp{ true };
		bool ores{ false };
		bool loots{ false };
		bool traps{ false };
		bool collectables{ false };
		int playerdistance{ 100 };
		int prefabdistance{ 100 };
		//aim
		bool aimbot{ false };
		bool silentaim{ false };
		float aimfov{ 100.f };

		//Main
		float m_reload_time{ 0.f };
		float m_reload_duration{ 0.f };
		float fly_height{ 0.f };
		float fly_direction{ 0.f };
		float m_height{ 0.f };
		float m_direction{ 0.f };
		float bulletsize{ 0.5f };
		float RecoilYaw{ 0.5f };
		float RecoilPitch{ 0.5f };
		float repeatdelay{ 0.06f };
		bool timechanger{ false };
		bool fakeadmin{ false };
		bool noanimation{ false };
		bool noflashbang{ false };
		bool noviewdamage{ false };
		bool cullingesp{ false };
		bool nosway{ false };
		bool thickbullet{ false };
		bool flyhackbar{ false };
		bool flyhack{ false };
		bool airjump{ false }; 
		bool chams{ false };
		bool infinitejump{ false };
		bool spiderman{ false };
		bool norecoil{ false };
		bool fastshoot{ false };
		float slowbullet{ 1.2f };
		bool nospread{ false };
		bool reloadindicator{ false };
		bool omnisprint{ false };
		bool antiflyhackkick{ false };
		bool beautifulnight{ false };
		bool instantbow{ false };
		bool instantcompound{ false };
		bool instanteoka{ false };
		bool automatic{ false };
		bool spinbot{ false };
		bool shootincopter{ false };
		float clienttime{ 12.f };
		float playerfov{ 90.f };
		bool skyColor = false;
		bool playerinfoo = true;
		Color1 sky_colord = Color1(1.f, 1.f, 1.f, 1.f);
		float content_animation = 0.0f;
		int selection_count = 0;
		int legit_group_count = 0;
		float size_child = 0;
		bool active = false;
		float accent_colour[4];
		int longneckright = 0;
		int longneckleft = 0;
		int longneckup = 0;
		int aimbotkey = 0;
		int zoomkey = 0;
		float fovcolor[4] = { 3.10f, 0.09f, 2.12f, 1.00f };
		float BoxColor[4] = { 3.10f, 0.09f, 2.12f, 1.00f };
		float BoxfilledColor[4] = { 3.10f, 0.09f, 2.12f, 1.00f };
		float NameColor[4] = { 3.10f, 0.09f, 2.12f, 1.00f };
		float WeaponColor[4] = { 3.10f, 0.09f, 2.12f, 1.00f };
		float distColor[4] = { 3.10f, 0.09f, 2.12f, 1.00f };
	} Includes;
}; inline auto config = c_config( );
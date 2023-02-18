#include "Imports.hpp"
#include "Gui.hpp"
#include "font.h"
#define LOADER_BRAND "rust cheat"
#define WINDOW_WIDTH  475
#define WINDOW_HEIGHT 300
bool loader_active = true;
ImColor cRainbow;
LPCSTR TargetProcess = "RustClient.exe";
bool ShowMenu = true;
bool CreateConsole = true;
std::vector < baseplayer * > enemy_list;
IDirect3DTexture9 *byteImage = nullptr;
IDirect3DTexture9* Rage = nullptr;
ImFont* default_segu = nullptr;
ImFont* ico = nullptr;
ImFont* ico_combo = nullptr;
ImFont* ico_button = nullptr;
ImFont* ico_grande = nullptr;
ImFont* segu = nullptr;
ImFont* bold_segu = nullptr;
using namespace Offsets;
struct CurrentProcess 
{
	DWORD ID;
	HANDLE Handle;
	HWND Hwnd;
	WNDPROC WndProc;
	int WindowWidth;
	int WindowHeight;
	int WindowLeft;
	int WindowRight;
	int WindowTop;
	int WindowBottom;
	LPCSTR Title;
	LPCSTR ClassName;
	LPCSTR Path;
}Process;

struct OverlayWindow {
	WNDCLASSEX WindowClass;
	HWND Hwnd;
	LPCSTR Name;
}Overlay;

struct DirectX9Interface {
	IDirect3D9Ex *IDirect3D9 = NULL;
	IDirect3DDevice9Ex *pDevice = NULL;
	D3DPRESENT_PARAMETERS pParameters = { NULL };
	MARGINS Margin = { -1 };
	MSG Message = { NULL };
}DirectX9;

std::string GetFormattedTime( ) {
	time_t rawtime;
	tm timeinfo = {};
	char buffer[80];
	time( &rawtime );
	localtime_s( &timeinfo, &rawtime );
	auto suffix = timeinfo.tm_hour >= 12 ? ( " pm" ) : ( " am" );
	if ( timeinfo.tm_hour > 12 )
		timeinfo.tm_hour -= 12;
	strftime( buffer, sizeof( buffer ), ( "%H:%M" ), &timeinfo );
	return std::string( buffer ) + suffix;
}

std::string ReadFiles( std::string file )
{
	std::string line;
	std::ifstream myfile( file );
	if ( myfile.is_open( ) )
	{
		while ( getline( myfile, line ) )
		{
			return line;
		}
		myfile.close( );
	}
}

std::string removeSpaces( std::string str )
{
	str.erase( remove( str.begin( ), str.end( ), ' ' ), str.end( ) );
	return str;
}

std::string file_pass = ReadFiles( "C:\\Legit.ex\\login.json" );
std::string fileusername = removeSpaces( file_pass.substr( file_pass.find( ">" ) + 1 ) );

void Crosshair( ) {
	float midX = GetSystemMetrics( SM_CXSCREEN ) / 2;
	float midY = GetSystemMetrics( SM_CYSCREEN ) / 2;

	visuals::Line( { midX, ( midY - 8 ) }, { midX, ( midY - 4 ) }, ImColor( 255, 255, 255 ), 1.f );
	visuals::Line( { ( midX - 8 ), midY }, { ( midX - 4 ), midY }, ImColor( 255, 255, 255 ), 1.f );

	visuals::Line( { midX, ( midY + 8 ) }, { midX, ( midY + 4 ) }, ImColor( 255, 255, 255 ), 1.f );
	visuals::Line( { ( midX + 8 ), midY }, { ( midX + 4 ), midY }, ImColor( 255, 255, 255 ), 1.f );
}

void Watermark( )
{

	auto s = ImVec2( ImGui::GetWindowSize( ).x - ImGui::GetStyle( ).WindowPadding.x * 2, ImGui::GetWindowSize( ).y - ImGui::GetStyle( ).WindowPadding.y * 2 );
	auto p = ImVec2( ImGui::GetWindowPos( ).x + ImGui::GetStyle( ).WindowPadding.x, ImGui::GetWindowPos( ).y + ImGui::GetStyle( ).WindowPadding.y );

	std::string name_software = "Legit.Ex                        |";
	std::string stats = "          " + GetFormattedTime( );

	//1 bg
	ImGui::GetForegroundDrawList( )->AddRectFilledMultiColor( ImVec2( p.x + 25, p.y + 25 ), ImVec2( p.x + 381, p.y + 52 ), ImColor( 14, 14, 14, 110 ), ImColor( 10, 10, 10 ), ImColor( 14, 14, 14, 110 ), ImColor( 10, 10, 10 ) );
	//2 bg
	ImGui::GetForegroundDrawList( )->AddRectFilled( ImVec2( p.x + 29, p.y + 29 ), ImVec2( p.x + 378, p.y + 48 ), ImColor( 10, 10, 10 ), 1 );
	// text
	ImGui::GetForegroundDrawList( )->AddText( ImVec2( p.x + 35, p.y + 33 ), ImColor( 87, 88, 88 ), name_software.c_str( ) );
	ImGui::GetForegroundDrawList( )->AddText( ImVec2( p.x + ImGui::CalcTextSize( name_software.c_str( ) ).x + 40, p.y + 33 ), ImColor( 189, 191, 209 ), fileusername.c_str( ) );
	ImGui::GetForegroundDrawList( )->AddText( ImVec2( p.x + ImGui::CalcTextSize( fileusername.c_str( ) ).x + ImGui::CalcTextSize( stats.c_str( ) ).x * 2.3, p.y + 33 ), ImColor( 87, 88, 88 ), stats.c_str( ) );
}

void PlayerBar(baseplayer* Player)
{
	std::string weapon = Player->GetBeltItems(Player->GetItemsList(), 1);
	std::string weapon2 = Player->GetBeltItems(Player->GetItemsList(), 2);
	std::string weapon3 = Player->GetBeltItems(Player->GetItemsList(), 3);
	std::string weapon4 = Player->GetBeltItems(Player->GetItemsList(), 4);
	std::string weapon5 = Player->GetBeltItems(Player->GetItemsList(), 5);
	std::string weapon6 = Player->GetBeltItems(Player->GetItemsList(), 6);
	std::string armor = Player->GetClothingItems(Player->GetClothingItemsList(), 1);
	std::string armor2 = Player->GetClothingItems(Player->GetClothingItemsList(), 2);
	std::string armor3 = Player->GetClothingItems(Player->GetClothingItemsList(), 3);
	std::string armor4 = Player->GetClothingItems(Player->GetClothingItemsList(), 4);
	std::string armor5 = Player->GetClothingItems(Player->GetClothingItemsList(), 5);
	std::string armor6 = Player->GetClothingItems(Player->GetClothingItemsList(), 6);
	std::string armor7 = Player->GetClothingItems(Player->GetClothingItemsList(), 7);
	std::string name = std::string(Player->display_name());
	std::string healthhh(std::to_string((int)Player->health()));
	ImGui::Begin((""), NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
	{
		ImGui::SetNextWindowSize(ImVec2(1980, 1080));
		ImGuiStyle& style = ImGui::GetStyle();
		style.Colors[ImGuiCol_Text] = cRainbow;
		ImGui::Text(("User "));
		ImGui::SameLine();
		ImGui::Text(name.c_str());
		ImGui::Text(("HP "));
		ImGui::SameLine();
		ImGui::Text(healthhh.c_str());
		ImGui::Text(("Slot  ")); ImGui::SameLine(); ImGui::Text(weapon.c_str()); ImGui::SameLine(); ImGui::Text(("Slot")); ImGui::SameLine(); ImGui::Text(weapon2.c_str());
		ImGui::Text(("Slot  ")); ImGui::SameLine(); ImGui::Text(weapon3.c_str()); ImGui::SameLine(); ImGui::Text(("Slot")); ImGui::SameLine(); ImGui::Text(weapon4.c_str());
		ImGui::Text(("Slot  ")); ImGui::SameLine(); ImGui::Text(weapon5.c_str()); ImGui::SameLine(); ImGui::Text(("Slot")); ImGui::SameLine(); ImGui::Text(weapon6.c_str());
		ImGui::Text(("Wearing ")); ImGui::SameLine(); ImGui::Text(armor.c_str()); ImGui::SameLine(); ImGui::Text(("Wearing")); ImGui::SameLine(); ImGui::Text(armor2.c_str());
		ImGui::Text(("Wearing ")); ImGui::SameLine(); ImGui::Text(armor3.c_str()); ImGui::SameLine(); ImGui::Text(("Wearing")); ImGui::SameLine(); ImGui::Text(armor4.c_str());
		ImGui::Text(("Wearing ")); ImGui::SameLine(); ImGui::Text(armor5.c_str()); ImGui::SameLine(); ImGui::Text(("Wearing")); ImGui::SameLine(); ImGui::Text(armor6.c_str());
		ImGui::Text(("Wearing ")); ImGui::SameLine(); ImGui::Text(armor7.c_str());
		style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
		ImGui::End();
	}
}

void aimmark( )
{
	Vector2 aimpos;
	if ( !loops::aimbone.is_empty( ) )
	{
		if ( entityloop::camera->WorldToScreen( &entityloop::projection_matrix, loops::aimbone, &aimpos ) )
			visuals::StrokeText( aimpos.x - 3.25f, aimpos.y - 9.25f, ImColor( 255, 0, 0 ), "+" );
	}
}

void runplayerinfo() 
{
		for (auto Player : rainy.player_list)
		{
			if (config.Includes.playerinfoo)
			{
				if (features::AimFov(Player) < 110)
				{
					PlayerBar(Player);
				}
			}
		}
}



void Render( ) 
{
	ImVec2 curPos = ImGui::GetCursorPos();
	ImVec2 curWindowPos = ImGui::GetWindowPos();
	curPos.x += curWindowPos.x;
	curPos.y += curWindowPos.y;
	static float flRainbow;
	float flSpeed = 0.0045f;
	flRainbow += flSpeed;
	if (flRainbow > 1.f) flRainbow = 0.f;
	for (int i = 0; i < 485; i++)
	{
		float hue = (1.f / (float)485) * i;
		hue -= flRainbow;
		if (hue < 0.f) hue += 1.f;

		cRainbow = ImColor::HSV(hue, 1.f, 1.f);
	}
	curPos.x += curWindowPos.x;
	curPos.y += curWindowPos.y;
	RECT screen_rect;
	GetWindowRect(GetDesktopWindow(), &screen_rect);
	auto x = float(screen_rect.right - 683.f) / 2.f;
	auto y = float(screen_rect.bottom - 442.f) / 2.f;
	ImGui_ImplDX9_NewFrame( );
	ImGui_ImplWin32_NewFrame( );
	ImGui::NewFrame( );
	{
		if ( GetAsyncKeyState( config.Includes.hsbind ) & 1 )
			config.Includes.showing = !config.Includes.showing;
		if ( config.Includes.showing ) {
			ImGui::SetNextWindowSize( ImVec2(683.f, 442.f) );
			ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_Once);
			ImGui::Begin( "Legit.Ex", nullptr, ImGuiWindowFlags_NoDecoration );
			{
				auto draw = ImGui::GetWindowDrawList();
				ImVec2 pos = ImGui::GetWindowPos();
				ImVec2 size = ImGui::GetWindowSize();

				ImVec2 cheat_name_size = ImGui::CalcTextSize(cheat_name);
				draw->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + 23), ImColor(0, 0, 0), 8.0f, ImDrawFlags_RoundCornersTopLeft);
				draw->AddText(ImVec2(pos.x + 9, pos.y + 4), ImColor(config.Includes.accent_colour[0], config.Includes.accent_colour[1], config.Includes.accent_colour[2]), cheat_icon_symbol);
				draw->AddText(ImVec2(pos.x + 27, pos.y + 4), ImColor(200, 200, 200), cheat_name);
				draw->AddLine(ImVec2(pos.x, pos.y + 23), ImVec2(pos.x + size.x, pos.y + 23), ImColor(46, 46, 46)); // upper line
				draw->AddRectFilledMultiColor(ImVec2(pos.x, pos.y + 24), ImVec2(pos.x + size.x, pos.y + 683.f), ImColor(15, 15, 15), ImColor(0, 0, 0), ImColor(15, 15, 15, 0), ImColor(0, 0, 0, 0));
				ImGui::PushFont(ico);
				ImGui::SetCursorPos(ImVec2(38, 30));
				ImGui::Text("N");
				ImGui::SetCursorPos(ImVec2(38, 30));
				if (ImGui::selection("Rage", Rage, 1 == config.Includes.selection_count))
				{
					config.Includes.selection_count = 1;
					config.Includes.active = true;
				}

				ImGui::SetCursorPos(ImVec2(38, 90));
				ImGui::Text("R");
				ImGui::SetCursorPos(ImVec2(38, 90));
				if (ImGui::selection("Player", Rage, 3 == config.Includes.selection_count))
				{
					config.Includes.selection_count = 3;
					config.Includes.active = true;
				}


				ImGui::SetCursorPos(ImVec2(30, 150));
				ImGui::Text("F");
				ImGui::SetCursorPos(ImVec2(30, 150));
				if (ImGui::selection("world", Rage, 4 == config.Includes.selection_count))
				{
					config.Includes.selection_count = 4;
					config.Includes.active = true;
				}

				ImGui::SetCursorPos(ImVec2(34, 210));
				ImGui::Text("D");
				ImGui::SetCursorPos(ImVec2(34, 220));
				if (ImGui::selection("Keybind", Rage, 5 == config.Includes.selection_count))
				{
					config.Includes.selection_count = 5;
					config.Includes.active = true;
				}

				ImGui::SetCursorPos(ImVec2(30, 280));
				ImGui::Text("K");
				ImGui::SetCursorPos(ImVec2(30, 280));
				if (ImGui::selection("misc", Rage, 2 == config.Includes.selection_count))
				{
					config.Includes.selection_count = 2;
					config.Includes.active = true;
				}
				ImGui::SetCursorPos(ImVec2(30, 350));
				ImGui::Text("S");
				ImGui::SetCursorPos(ImVec2(30, 350));
				if (ImGui::selection("congfig", Rage, 6 == config.Includes.selection_count))
				{
					config.Includes.selection_count = 6;
					config.Includes.active = true;
				}
				ImGui::PopFont();
				if (config.Includes.active)
				{
					if (config.Includes.size_child <= 1200) config.Includes.size_child += 1 / ImGui::GetIO().Framerate * 100000.f;
					else
					{
						config.Includes.active = false; config.Includes.selection_count = config.Includes.selection_count;
					};
				}
				else
				{
					if (config.Includes.size_child >= 0) config.Includes.size_child -= 2 / ImGui::GetIO().Framerate * 1610.f; //if activated it will go up then down simple stuff :)
				}

				if (config.Includes.selection_count == 1)
				{
					ImGui::SetCursorPos(ImVec2(86, 26 - config.Includes.size_child));
					ImGui::BeginChild("Aim Stuff", ImVec2(584, 390), true);
					{
						ImGui::Checkbox("AimBot", &config.Includes.aimbot);
						ImGui::Checkbox("Silent Aim", &config.Includes.silentaim);
						ImGui::SliderFloat("Aim FOV", &config.Includes.aimfov, 5.f, 500.f, "%.2f");
						ImGui::Combo("Aim Bone", &aimBone, aimBoneStr, 5);
					}ImGui::EndChild();

				}

				if (config.Includes.selection_count == 2)
				{
					ImGui::SetCursorPos(ImVec2(86, 26 - config.Includes.size_child));
					ImGui::BeginChild("KeyBinds", ImVec2(584, 390), true);
					{
						ImGui::KeyBind(("Aimbot Key"), config.Includes.aimbotkey, ImVec2(50, 20));
						ImGui::KeyBind(("Longneck Up Key"), config.Includes.longneckup, ImVec2(50, 20));
						ImGui::KeyBind(("Longneck Right Key"), config.Includes.longneckright, ImVec2(50, 20));
						ImGui::KeyBind(("Longneck Left Key"), config.Includes.longneckleft, ImVec2(50, 20));
						ImGui::KeyBind(("Zoom Key"), config.Includes.zoomkey, ImVec2(50, 20));
					}ImGui::EndChild();
				}

				if (config.Includes.selection_count == 3)
				{
					ImGui::SetCursorPos(ImVec2(86, 26 - config.Includes.size_child ));
					ImGui::BeginChild("Player Esp Stuff", ImVec2(584, 390), true);
					{
						ImGui::Checkbox("Box", &config.Includes.boxesp); ImGui::SameLine(200); ImGui::ColorEdit4("boxcolor", config.Includes.BoxColor, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
						ImGui::Checkbox("Filled Box", &config.Includes.fillrect); ImGui::SameLine(200); ImGui::ColorEdit4("boxcolor1", config.Includes.BoxfilledColor, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
						ImGui::Checkbox("Name", &config.Includes.name); ImGui::SameLine(200); ImGui::ColorEdit4("namecolor", config.Includes.NameColor, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
						ImGui::Checkbox("Chams", &config.Includes.chams);
						ImGui::Checkbox("Health", &config.Includes.health);
						ImGui::Checkbox("Weapon", &config.Includes.weapon); ImGui::SameLine(200); ImGui::ColorEdit4("weaponcolor", config.Includes.WeaponColor, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
						ImGui::Checkbox("Distance", &config.Includes.distance); ImGui::SameLine(200); ImGui::ColorEdit4("dis34", config.Includes.distColor, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
						ImGui::Checkbox("SnapLines", &config.Includes.snaplines);
						ImGui::SliderInt("Max Esp Distance", &config.Includes.playerdistance, 5, 375, "%.1f");

					}ImGui::EndChild();
				}

				if (config.Includes.selection_count == 4)
				{
					ImGui::SetCursorPos(ImVec2(86, 26 - config.Includes.size_child ));
					ImGui::BeginChild("World Esp Stuff", ImVec2(584, 390), true);
					{
						ImGui::SliderInt("Max Prefab Distance", &config.Includes.prefabdistance, 5, 250, "%.1f");
						static std::string preview = "";
						if (ImGui::BeginCombo("World Items", preview.c_str()))
						{
							preview = "";
							std::vector<std::string> vec;
							for (size_t i = 0; i < IM_ARRAYSIZE(items); i++)
							{
								ImGui::Selectable(items[i], &selected[i], ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
								if (selected[i])
									vec.push_back(items[i]);
							}
							for (size_t i = 0; i < vec.size(); i++)
							{
								if (vec.size() == 1)
									preview += vec.at(i);
								else if (!(i == vec.size() - 1))
									preview += vec.at(i) + ",";
								else
									preview += vec.at(i);
							}

							ImGui::EndCombo();
						}
					}ImGui::EndChild();


				}

				if (config.Includes.selection_count == 5)
				{
					ImGui::SetCursorPos(ImVec2(86, 26 - config.Includes.size_child ));
					ImGui::BeginChild("Misc", ImVec2(584, 390), true);
					{
						ImGui::Checkbox("Bright Night", &config.Includes.beautifulnight); ImGui::SameLine(200);ImGui::Checkbox("Time Changer", &config.Includes.timechanger); ImGui::SameLine(400);ImGui::Checkbox("Sky Changer", &config.Includes.skyColor); ImGui::SameLine(510); ImGui::ColorEdit4("Sky Color", &config.Includes.sky_colord.r, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
						ImGui::Checkbox("No Sway", &config.Includes.nosway); ImGui::SameLine(200);ImGui::Checkbox("No Recoil", &config.Includes.norecoil); ImGui::SameLine(400); ImGui::Checkbox("Nospread", &config.Includes.nospread);
						ImGui::Checkbox("Instant Compound", &config.Includes.instantbow); ImGui::SameLine(200);ImGui::Checkbox("Automatic", &config.Includes.automatic); ImGui::SameLine(400); ImGui::Checkbox("Fake Admin", &config.Includes.fakeadmin);
						ImGui::Checkbox("Instant Eoka", &config.Includes.instanteoka); ImGui::SameLine(200);ImGui::Checkbox(" Fast Bow", &config.Includes.instantcompound); ImGui::SameLine(400); ImGui::Checkbox("Omnisprint", &config.Includes.omnisprint);
						ImGui::Checkbox("Spiderman", &config.Includes.spiderman); ImGui::SameLine(200); ImGui::Checkbox("Infinite Jump", &config.Includes.infinitejump); ImGui::SameLine(400); ImGui::Checkbox("No Animation", &config.Includes.noanimation);
						ImGui::Checkbox("Shoot In Minicopter", &config.Includes.shootincopter); ImGui::SameLine(200); ImGui::Checkbox("Shoot in Air", &config.Includes.airjump); ImGui::SameLine(400); ImGui::Checkbox("No Flashbang", &config.Includes.noflashbang);
						ImGui::Checkbox("Flyhack Reset", &config.Includes.flyhack); ImGui::SameLine(200); ImGui::Checkbox("Flyhack Bar", &config.Includes.flyhackbar); ImGui::SameLine(400); ImGui::Checkbox("No Flyhack Kick", &config.Includes.antiflyhackkick);
						ImGui::Checkbox("Shoot Threw Wall", &config.Includes.thickbullet); ImGui::SameLine(200); ImGui::Checkbox("Instant Kill", &config.Includes.fastshoot); ImGui::SameLine(400); ImGui::Checkbox("Reload Bar", &config.Includes.reloadindicator);
						ImGui::Checkbox("Spin Bot", &config.Includes.spinbot);
						ImGui::SetCursorPos(ImVec2(550, 340));
						if (ImGui::Button(">"))
						{
							config.Includes.selection_count = 55;
							config.Includes.active = true;
						}
						if (config.Includes.thickbullet) 
						{
							config.Includes.bulletsize = 4.9f;
						}
					}ImGui::EndChild();
				}
				if (config.Includes.selection_count == 55)
				{
					ImGui::SetCursorPos(ImVec2(86, 26 - config.Includes.size_child));
					ImGui::BeginChild("Misc|", ImVec2(584, 390), true);
					{
						ImGui::SliderFloat("Control X", &config.Includes.RecoilYaw, 0.f, 1.f, "%.2f");
						ImGui::SliderFloat("Control Y", &config.Includes.RecoilPitch, 0.f, 1.f, "%.2f");
						ImGui::SliderFloat("Player Fov", &config.Includes.playerfov, 90.f, 150.f, "%.2f");
						ImGui::SliderFloat("Client Time", &config.Includes.clienttime, 0.f, 14.f, "%.1f");
						ImGui::SliderFloat("Delay Instant Kill", &config.Includes.repeatdelay, 0.0f, 0.15f, "%.2f");
						ImGui::SetCursorPos(ImVec2(550, 340));
						if (ImGui::Button("<"))
						{
							config.Includes.selection_count = 5;
							config.Includes.active = true;
						}
					}ImGui::EndChild();
				}
				if (config.Includes.selection_count == 6)
				{
					ImGui::SetCursorPos(ImVec2(86, 26 - config.Includes.size_child));
					ImGui::BeginChild("Config", ImVec2(584, 390), true);
					{

						ImGui::BeginGroup();

						constexpr auto& config_items = config.get_configs();
						static auto current_config = -1;

						if ((size_t)(current_config) >= config_items.size())
							current_config = -1;

						static char buffer[32];

						ImGui::SetNextItemWidth(600);
						if (ImGui::ListBox("##Includes::config_list", &current_config, [](void* data, int idx, const char** out_text)
							{
								auto& vector = *(std::vector<std::string> *)(data);
								*out_text = vector[idx].c_str();
								return true;
							}, &config_items, (int)(config_items.size()), 5) && current_config != -1) strcpy_s(buffer, config_items[current_config].c_str());

							ImGui::SetNextItemWidth(600);
							if (ImGui::InputText("##Includes::config_name", buffer, IM_ARRAYSIZE(buffer), ImGuiInputTextFlags_EnterReturnsTrue))
							{
								if (current_config != -1)
									config.rename(current_config, buffer);
							}

							if (ImGui::Button("Create Config"))
								config.add(buffer);

							ImGui::SameLine();

							if (ImGui::Button("Reset Config"))
								config.reset();

							ImGui::SameLine();

							if (ImGui::Button("Refresh Config"))
								config.run2();

							if (current_config > -1)
							{
								if (ImGui::Button("Save Config"))
									config.save(current_config);

								ImGui::SameLine();

								if (ImGui::Button("Load Config"))
									config.load(current_config);

								ImGui::SameLine();

								if (ImGui::Button("Delete Config"))
									config.remove(current_config);
							}

							ImGui::EndGroup();
					}ImGui::EndChild();
				}

			}
			ImGui::End();
			SetWindowLong( Overlay.Hwnd, GWL_EXSTYLE, WS_EX_TOOLWINDOW );
			UpdateWindow( Overlay.Hwnd );
			SetFocus( Overlay.Hwnd );
		}
		else {
			SetWindowLong( Overlay.Hwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW );
			UpdateWindow( Overlay.Hwnd );
			Crosshair( );
		}
		visuals::draw_loop( );
		visuals::draw_prefab_loop( );
		aimmark( );
		if ( config.Includes.flyhackbar )
		{
			if ( config.Includes.fly_height >= 255.f ) config.Includes.fly_height = 0.f;
			if ( config.Includes.fly_height <= 0.f ) config.Includes.fly_height = 0.f;
			if ( config.Includes.fly_direction >= 255.f ) config.Includes.fly_direction = 0.f;
			if ( config.Includes.fly_direction <= 0.f ) config.Includes.fly_direction = 0.f;

			visuals::FilledRect( config.Includes.width / 2.3, config.Includes.height / 6, 250, 6, ImColor( 56, 55, 55 ) );
			visuals::FilledRect( config.Includes.width / 2.3, config.Includes.height / 6, config.Includes.fly_height, 6, ImColor( 70, 0, 222 ) );

			visuals::FilledRect( config.Includes.width / 2.3, config.Includes.height / 8.35, 250, 6, ImColor( 56, 55, 55 ) );
			visuals::FilledRect( config.Includes.width / 2.3, config.Includes.height / 8.35, config.Includes.fly_direction, 6, ImColor( 70, 0, 222 ) );
		}
		if ( config.Includes.reloadindicator && config.Includes.m_reload_duration > 0.00f && config.Includes.m_reload_time > 0.00f )
		{
			visuals::FilledRect( config.Includes.width / 2.27f, config.Includes.height / 1.60f, config.Includes.m_reload_time * config.Includes.width / config.Includes.m_reload_duration / 10.f, 5, cRainbow);
		}
		Watermark( );
		if ( config.Includes.aimbot || config.Includes.silentaim )
		{
			ImGui::GetBackgroundDrawList( )->AddCircle( ImVec2( config.Includes.width / 2, config.Includes.height / 2 ), config.Includes.aimfov, cRainbow, 0 );
		}
	}
	ImGui::EndFrame( );

	DirectX9.pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB( 0, 0, 0, 0 ), 1.0f, 0 );
	if ( DirectX9.pDevice->BeginScene( ) >= 0 ) {
		ImGui::Render( );
		ImGui_ImplDX9_RenderDrawData( ImGui::GetDrawData( ) );
		DirectX9.pDevice->EndScene( );
	}

	HRESULT result = DirectX9.pDevice->Present( NULL, NULL, NULL, NULL );
	if ( result == D3DERR_DEVICELOST && DirectX9.pDevice->TestCooperativeLevel( ) == D3DERR_DEVICENOTRESET ) {
		ImGui_ImplDX9_InvalidateDeviceObjects( );
		DirectX9.pDevice->Reset( &DirectX9.pParameters );
		ImGui_ImplDX9_CreateDeviceObjects( );
	}
}

void MainLoop( ) {
	static RECT OldRect;
	ZeroMemory( &DirectX9.Message, sizeof( MSG ) );
	while ( DirectX9.Message.message != WM_QUIT ) {
		if ( PeekMessage( &DirectX9.Message, Overlay.Hwnd, 0, 0, PM_REMOVE ) ) {
			TranslateMessage( &DirectX9.Message );
			DispatchMessage( &DirectX9.Message );
		}
		HWND ForegroundWindow = GetForegroundWindow( );
		if ( ForegroundWindow == Process.Hwnd ) {
			HWND TempProcessHwnd = GetWindow( ForegroundWindow, GW_HWNDPREV );
			SetWindowPos( Overlay.Hwnd, TempProcessHwnd, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
		}

		RECT TempRect;
		POINT TempPoint;
		ZeroMemory( &TempRect, sizeof( RECT ) );
		ZeroMemory( &TempPoint, sizeof( POINT ) );

		GetClientRect( Process.Hwnd, &TempRect );
		ClientToScreen( Process.Hwnd, &TempPoint );

		TempRect.left = TempPoint.x;
		TempRect.top = TempPoint.y;
		ImGuiIO &io = ImGui::GetIO( );
		io.ImeWindowHandle = Process.Hwnd;

		if ( TempRect.left != OldRect.left || TempRect.right != OldRect.right || TempRect.top != OldRect.top || TempRect.bottom != OldRect.bottom ) {
			OldRect = TempRect;
			Process.WindowWidth = TempRect.right;
			Process.WindowHeight = TempRect.bottom;
			DirectX9.pParameters.BackBufferWidth = Process.WindowWidth;
			DirectX9.pParameters.BackBufferHeight = Process.WindowHeight;
			SetWindowPos( Overlay.Hwnd, (HWND)0, TempPoint.x, TempPoint.y, Process.WindowWidth, Process.WindowHeight, SWP_NOREDRAW );
			DirectX9.pDevice->Reset( &DirectX9.pParameters );
		}
		Render( );
	}
	ImGui_ImplDX9_Shutdown( );
	ImGui_ImplWin32_Shutdown( );
	ImGui::DestroyContext( );
	if ( DirectX9.pDevice != NULL ) {
		DirectX9.pDevice->EndScene( );
		DirectX9.pDevice->Release( );
	}
	if ( DirectX9.IDirect3D9 != NULL ) {
		DirectX9.IDirect3D9->Release( );
	}
	DestroyWindow( Overlay.Hwnd );
	UnregisterClass( Overlay.WindowClass.lpszClassName, Overlay.WindowClass.hInstance );
}

bool DirectXInit( ) {
	if ( FAILED( Direct3DCreate9Ex( D3D_SDK_VERSION, &DirectX9.IDirect3D9 ) ) ) {
		
		
		
		
		
		;
	}

	D3DPRESENT_PARAMETERS Params = { 0 };
	Params.Windowed = TRUE;
	Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	Params.hDeviceWindow = Overlay.Hwnd;
	Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	Params.BackBufferFormat = D3DFMT_A8R8G8B8;
	Params.BackBufferWidth = Process.WindowWidth;
	Params.BackBufferHeight = Process.WindowHeight;
	Params.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	Params.EnableAutoDepthStencil = TRUE;
	Params.AutoDepthStencilFormat = D3DFMT_D16;
	Params.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	Params.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	if ( FAILED( DirectX9.IDirect3D9->CreateDeviceEx( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Overlay.Hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &Params, 0, &DirectX9.pDevice ) ) ) {
		DirectX9.IDirect3D9->Release( );
		return false;
	}

	IMGUI_CHECKVERSION( );
	ImGui::CreateContext( );

	ImGui_ImplWin32_Init( Overlay.Hwnd );
	ImGui_ImplDX9_Init( DirectX9.pDevice );
	ImGuiIO &io = ImGui::GetIO( ); (void)io;
	ImGuiStyle *style = &ImGui::GetStyle( );
	ImFontConfig font_config;
	io.IniFilename = nullptr;
	font_config.PixelSnapH = false;
	font_config.OversampleH = 5;
	font_config.OversampleV = 5;
	font_config.RasterizerMultiply = 1.2f;

	static const ImWchar ranges[] =
	{
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
		0x2DE0, 0x2DFF, // Cyrillic Extended-A
		0xA640, 0xA69F, // Cyrillic Extended-B
		0xE000, 0xE226, // icons
		0,
	};

	style->Colors[ImGuiCol_WindowBg] = ImColor(15, 15, 15);
	style->Colors[ImGuiCol_ChildBg] = ImColor(15, 15, 15);
	style->Colors[ImGuiCol_Border] = ImColor(26, 26, 26);
	style->Colors[ImGuiCol_TextSelectedBg] = ImColor(255, 255, 255, 50);
	style->Colors[ImGuiCol_FrameBg] = ImColor(34, 34, 34);
	style->Colors[ImGuiCol_FrameBgActive] = ImColor(51, 52, 54);
	style->Colors[ImGuiCol_FrameBgHovered] = ImColor(51, 52, 54);
	style->Colors[ImGuiCol_Button] = ImColor(29, 29, 29);
	style->Colors[ImGuiCol_ButtonHovered] = ImColor(23, 23, 23);
	style->Colors[ImGuiCol_ButtonActive] = ImColor(23, 23, 23);
	style->Colors[ImGuiCol_Text] = ImColor(255, 255, 255);

	font_config.GlyphRanges = ranges;

	io.Fonts->AddFontFromFileTTF( "C:\\Windows\\Fonts\\verdana.ttf", 14, &font_config, ranges );

	io.Fonts->AddFontFromMemoryTTF(&seguoe, sizeof seguoe, 20, NULL, io.Fonts->GetGlyphRangesCyrillic());

	default_segu = io.Fonts->AddFontFromMemoryTTF(&seguoe, sizeof seguoe, 20, NULL, io.Fonts->GetGlyphRangesCyrillic());

	segu = io.Fonts->AddFontFromMemoryTTF(&seguoe, sizeof seguoe, 38, NULL, io.Fonts->GetGlyphRangesCyrillic());

	bold_segu = io.Fonts->AddFontFromMemoryTTF(&bold_segue, sizeof bold_segue, 38, NULL, io.Fonts->GetGlyphRangesCyrillic());

	ico = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 38, NULL, io.Fonts->GetGlyphRangesCyrillic());

	ico_combo = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 38, NULL, io.Fonts->GetGlyphRangesCyrillic());

	ico_button = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 38, NULL, io.Fonts->GetGlyphRangesCyrillic());

	ico_grande = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 38, NULL, io.Fonts->GetGlyphRangesCyrillic());

	DirectX9.IDirect3D9->Release( );
	return true;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
LRESULT CALLBACK WinProc( HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam ) {
	if ( ImGui_ImplWin32_WndProcHandler( hWnd, Message, wParam, lParam ) )
		return true;

	switch ( Message ) {
	case WM_DESTROY:
		if ( DirectX9.pDevice != NULL ) {
			DirectX9.pDevice->EndScene( );
			DirectX9.pDevice->Release( );
		}
		if ( DirectX9.IDirect3D9 != NULL ) {
			DirectX9.IDirect3D9->Release( );
		}
		PostQuitMessage( 0 );
		exit( 4 );
		break;
	case WM_SIZE:
		if ( DirectX9.pDevice != NULL && wParam != SIZE_MINIMIZED ) {
			ImGui_ImplDX9_InvalidateDeviceObjects( );
			DirectX9.pParameters.BackBufferWidth = LOWORD( lParam );
			DirectX9.pParameters.BackBufferHeight = HIWORD( lParam );
			HRESULT hr = DirectX9.pDevice->Reset( &DirectX9.pParameters );
			if ( hr == D3DERR_INVALIDCALL )
				IM_ASSERT( 0 );
			ImGui_ImplDX9_CreateDeviceObjects( );
		}
		break;
	default:
		return DefWindowProc( hWnd, Message, wParam, lParam );
		break;
	}
	return 0;
}

void SetupWindow( ) {
	Overlay.WindowClass = {
		sizeof( WNDCLASSEX ), 0, WinProc, 0, 0, nullptr, LoadIcon( nullptr, IDI_APPLICATION ), LoadCursor( nullptr, IDC_ARROW ), nullptr, nullptr, Overlay.Name, LoadIcon( nullptr, IDI_APPLICATION )
	};

	RegisterClassEx( &Overlay.WindowClass );
	if ( Process.Hwnd ) {
		static RECT TempRect = { NULL };
		static POINT TempPoint;
		GetClientRect( Process.Hwnd, &TempRect );
		ClientToScreen( Process.Hwnd, &TempPoint );
		TempRect.left = TempPoint.x;
		TempRect.top = TempPoint.y;
		Process.WindowWidth = TempRect.right;
		Process.WindowHeight = TempRect.bottom;
	}

	Overlay.Hwnd = CreateWindowEx( NULL, Overlay.Name, Overlay.Name, WS_POPUP | WS_VISIBLE, Process.WindowLeft, Process.WindowTop, Process.WindowWidth, Process.WindowHeight, NULL, NULL, 0, NULL );
	DwmExtendFrameIntoClientArea( Overlay.Hwnd, &DirectX9.Margin );
	SetWindowLong( Overlay.Hwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW );
	ShowWindow( Overlay.Hwnd, SW_SHOW );
	UpdateWindow( Overlay.Hwnd );
}

std::string RandomString( int len ) {
	srand( time( NULL ) );
	std::string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::string newstr;
	int pos;
	while ( newstr.size( ) != len ) {
		pos = ( ( rand( ) % ( str.size( ) - 1 ) ) );
		newstr += str.substr( pos, 1 );
	}
	return newstr;
}

void better_print( const char *buffer, int colour_id )
{
	HANDLE console = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( console, colour_id );
	printf( buffer );
}



int main( )
{
	system("color d");
	std::filesystem::create_directories( "C:\\Legit.ex\\Rust\\Config" );
	config.run( );
	ShowWindow( GetConsoleWindow( ), SW_SHOW );
	bool WindowFocus = false;
	while ( WindowFocus == false ) {
		DWORD ForegroundWindowProcessID;
		GetWindowThreadProcessId( GetForegroundWindow( ), &ForegroundWindowProcessID );
		if ( get_process_id( TargetProcess ) == ForegroundWindowProcessID ) {
			Process.ID = GetCurrentProcessId( );
			Process.Handle = GetCurrentProcess( );
			Process.Hwnd = GetForegroundWindow( );

			RECT TempRect;
			GetWindowRect( Process.Hwnd, &TempRect );
			Process.WindowWidth = TempRect.right - TempRect.left;
			Process.WindowHeight = TempRect.bottom - TempRect.top;
			Process.WindowLeft = TempRect.left;
			Process.WindowRight = TempRect.right;
			Process.WindowTop = TempRect.top;
			Process.WindowBottom = TempRect.bottom;

			char TempTitle[MAX_PATH];
			GetWindowText( Process.Hwnd, TempTitle, sizeof( TempTitle ) );
			Process.Title = TempTitle;

			char TempClassName[MAX_PATH];
			GetClassName( Process.Hwnd, TempClassName, sizeof( TempClassName ) );
			Process.ClassName = TempClassName;

			char TempPath[MAX_PATH];
			GetModuleFileNameEx( Process.Handle, NULL, TempPath, sizeof( TempPath ) );
			Process.Path = TempPath;

			WindowFocus = true;
		}
	}
	Overlay.Name = RandomString( 10 ).c_str( );
	SetupWindow( );
	DirectXInit( );
	driver->initialize( get_process_id( "RustClient.exe" ) );
	game_assembly = driver->get_module_base( "GameAssembly.dll" );
	unity_player = driver->get_module_base( "UnityPlayer.dll" );
	baselib = driver->get_module_base("baselib.dll");
	std::cout << "PID                                        [ " << get_process_id << "] \n";
	std::cout << "Offsets Dumped And Loaded           " << std::endl;
	std::cout << "game_assembly                              [ " << game_assembly << "] \n";
	std::cout << "unity_player                               [ " << unity_player << "] \n";
	std::cout << "baselib                                    [ " << baselib << "] \n";
	LoopSetup( );
	MainLoop( );
}
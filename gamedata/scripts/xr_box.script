
local item_by_community = {}
local mul_by_level = {}
local count_by_level = {}

ph_item_box_manager = nil
function get_box_manager()
	if not (ph_item_box_manager) then 
		ph_item_box_manager = ph_item_box()
	end 
	return ph_item_box_manager
end 

class "ph_item_box"
function ph_item_box:__init()
	local death_ini = ini_file("items\\settings\\ph_box_generic.ltx")
	
	local diff = game_difficulties.get_eco_factor("loots") or 1
	local diff_multi = (diff - 0.2) or 0.8
	local result, id, value = "", "", ""
	local n = 0
	
	local community_list = { "def_box", "small_box_generic", "small_box_ussr", "small_box_nato", "small_box_army", "small_box_science", "big_box_generic", "big_box_dungeons", "big_box_arsenal"}
	for k,v in pairs(community_list) do
		item_by_community[v] = {}
		if death_ini:section_exist(v) then
			n = death_ini:line_count(v)
			for i=0,n-1 do
				result, id, value = death_ini:r_line(v,i,"","")
				local temp = not (death_ini:line_exist("exclude_from_multi",id)) and diff_multi or 1
				item_by_community[v][id] = tonumber(value)*temp or 0
			end
		end
	end

	local level_name = level.name()

	if not death_ini:section_exist(level_name) then
		level_name = "default"
	end

	n = death_ini:line_count(level_name)
	for i=0,n-1 do
		result, id, value = death_ini:r_line(level_name,i,"","")
		mul_by_level[id] = tonumber(value) or 0
	end

	local item_count_section = "item_count_0"
	n = death_ini:line_count(item_count_section)
	for i=0,n-1 do
		result, id, value	= death_ini:r_line(item_count_section,i,"","")

		local t = parse_nums(value)
		local min = t[1] or 1
		local max = t[2] or min

		min = tonumber(min) * (mul_by_level[id] or 0)
		max = tonumber(max) * (mul_by_level[id] or 0)

		count_by_level[id] = {min, max}
	end
end

function ph_item_box:spawn_items(obj,who,spawn_ini)
	local community
	if (spawn_ini) then -- Disabled hardcoded items
		--create_obligatory_items(obj,spawn_ini)
		--community = spawn_ini:r_string_ex("drop_box","community")
	end

	if (community == nil or community == "def_box") then
		local community_list = {"small_box_generic", "small_box_ussr", "small_box_nato", "small_box_army", "small_box_science"}
		community = community_list[math.random(#community_list)]
	end

	local spawn_list = community and item_by_community[community]
	if not (spawn_list) then
		return 
	end
	
	-- %25 more chance for all possible items
	local ach = 1
	if (game_achievements.has_achievement("infantile_pleasure")) then
		ach = 1.33
	end
	
	for k,v in pairs(spawn_list) do
		if (v * ach > 0) then
			local number = count_by_level[k] and math.random(count_by_level[k][1], count_by_level[k][2]) or math.random(0,1)
			if (number > 0) then
				create_items(obj, k, number, v * ach)
			end
		end
	end
end

function create_items(obj, section, number, rnd)
	if ini_sys:section_exist(section) and  (not ini_sys:line_exist(section,"cform")) then 
		return 
	end
	
	local pos = vector():set(obj:position())
	pos.y = obj:position().y + 0.3 --+ math.random(30,50)/100
	if IsItem("ammo",section) then
		if math.random() <= rnd then
			alife_create_item(section, {pos, obj:level_vertex_id(), obj:game_vertex_id()} , {ammo = number})
		end
	else
		for i=1,number do
			if math.random() <= rnd then
				alife_create_item(section, {pos, obj:level_vertex_id(), obj:game_vertex_id()})
			end
		end
	end
end

function create_obligatory_items(obj, spawn_ini)
	if not (spawn_ini and spawn_ini:line_exist("drop_box","items")) then
		return
	end
	
	local items = parse_names(spawn_ini:r_string_ex("drop_box", "items"))
	local size_t = #items
	if (size_t > 0) then
		local pos = vector():set(0,0,0)
		pos.x = obj:position().x
		pos.z = obj:position().z
		pos.y = obj:position().y + 0.3
			
		local sim = alife()
		for i=1,size_t do
			local section = items[i]
			if not (ini_sys:section_exist(section) and ini_sys:line_exist(section,"cform")) then 
				return 
			end
			
			alife_create_item(section, {pos, obj:level_vertex_id(), obj:game_vertex_id()})
		end
	end
end
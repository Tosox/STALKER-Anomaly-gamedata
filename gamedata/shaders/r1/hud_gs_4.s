function normal		(shader, t_base, t_second, t_detail)
	shader:begin	("null","gasmask_dudv")
			: fog	(false)
			: zb 	(false,false)
	shader:sampler	("s_base")	:texture("$user$rendertarget")	: clamp() : f_linear ()
	shader:sampler	("s_base0")	:texture("shaders\\gasmasks\\mask_nm_4")	: clamp() : f_linear ()
end



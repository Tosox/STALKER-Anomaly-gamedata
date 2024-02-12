function normal		(shader, t_base, t_second, t_detail)
	shader:begin	("null","combine")
			: fog	(false)
			: zb 	(false,false)
	shader:sampler	("s_image")	:texture(t_rt)		: clamp() : f_linear ()
end



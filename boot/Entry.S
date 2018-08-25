.text
	.code 32

	.global vector_start
	.global vector_end

	vector_start:
		LDR		R0, =0x10000000
		LDR		R1, [R0]
	vector_end:
		.space 1024, 0
.end

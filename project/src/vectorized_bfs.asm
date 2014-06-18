global vectorized_bfs_no_branching
global vectorized_bfs_branching

extern malloc
extern free
;extern printf

%define offset_initial 			0
%define offset_rows				8
%define offset_bytes_per_row	12
%define size_of_bmatrix			16

section .data
align 16

mask_copy_lowest: 	db 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
zero:				dq 0x0

section .text

%macro print 2
	push rdi
	push rsi
	push rax
	push rbx
	push rcx
	push rdx
	mov rax, 1
	mov rdi, %1
	mov rsi, %2
	call printf		;printf(%1, %2)
	pop rdx
	pop rcx
	pop rbx
	pop rax
	pop rsi
	pop rdi
%endmacro

%macro pushr 0
	push rdi
	push rsi
	push r8
	push r9
%endmacro

%macro popr 0
	pop r9
	pop r8
	pop rsi
	pop rdi
%endmacro

; void vectorized_bfs_no_branching(bmatrix *adj, bmatrix *sources);
vectorized_bfs_no_branching:
	;rdi = adj
	;rsi = sources
	%define adj rdi
	%define marked rsi
	%define i r12
	%define j r13
	%define k r14
	%define n r15
	%define xmm_marked xmm0
	%define xmm_row xmm1
	%define xmm_mask_copy_lowest xmm2
	
	movdqu xmm_mask_copy_lowest, [mask_copy_lowest]
	
	push rbp
	mov rbp, rsp
	push rbx
	push r12
	push r13
	push r14
	push r15
	sub rsp, 8			; aligned
	
	mov r15d, [adj + offset_rows]	;n
	
	xor i, i
	.for_i:
		cmp i, n
		je .end_for_i
		
		xor k, k
		.for_k:
			cmp k, n
			je .end_for_k
			
			;marked[k] = (*(marked->initial + k / 8) & (1 << offset)) >> offset, where offset = 7 - (k % 8) 
			xor rcx, rcx
			mov rcx, [marked + offset_initial]				; rcx = marked->initial
			mov rax, k
			mov rbx, 8
			xor rdx, rdx
			div rbx											; rax = k / 8, rdx = k % 8
			add rcx, rax									; rcx = marked->initial + k / 8
			xor rbx, rbx									; rbx = 0
			mov bl, [rcx]									; bl = *(marked->initial + k / 8)
			mov cl, 7										; cl = 7
			sub cl, dl										; cl = 7 - (k % 8) = offset
			mov dl, 1										; dl = 1
			shl dl, cl										; dl = 1 << offset
			and bl, dl										; bl = 0 0 0 marked[k] 0 0 0
			shr bl, cl										; bl = 0 0 0 ... 0 0 marked[k]
			not rbx											; rbx = 1 1 1 ... 1 1 ~marked[k]
			inc rbx											; rbx = 0 0 0 ... 0 0 0 si marked[k] = 0
															;  ó  = 1 1 1 ... 1 1 1 si marked[k] = 1
			movq xmm_marked, rbx							; xmm_marked = |x|x|x|x|x|x|x|marked[k] ... marked[k]|
			pshufb xmm_marked, xmm_mask_copy_lowest			; xmm_marked = |marked[k] ... marked[k]| ... |marked[k] ... marked[k]|	
			
			
			; we compute the address of the k-th row of adj
			; adj[k] = adj->initial + adj->bytes_per_row * k
			mov eax, [adj + offset_bytes_per_row]
			mul k
			add rax, [adj + offset_initial]
			
			xor j, j
			mov ebx, [adj + offset_bytes_per_row]
						
			.for_j:
				cmp j, rbx
				je .end_for_j
				
				movdqu xmm_row, [rax + j]					; xmm_row = row
				pand xmm_row, xmm_marked
				
				; modify the marked bit array
				
				mov rcx, [marked + offset_initial]
				movdqu xmm10, [rcx + j]
				por xmm10, xmm_row
				movdqu [rcx + j], xmm10
			
				add j, 16
				jmp .for_j
			.end_for_j:
			
			inc k
			jmp .for_k
		.end_for_k:
		
		inc i
		jmp .for_i
	.end_for_i:
	
	add rsp, 8
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbx
	pop rbp

	ret
	

; void vectorized_bfs_asm_branching(bmatrix *adj, bmatrix *sources);
vectorized_bfs_branching:
	;rdi = adj
	;rsi = sources
	%define adj rdi
	%define sources rsi
	%define marked rsi
	%define prev r8
	%define next r9
	%define i r12
	%define j r13
	%define k r14
	%define n r15
	%define xmm_marked xmm0
	%define xmm_not_marked xmm2
	%define xmm_row xmm1
	%define xmm_next xmm3
	
	push rbp
	mov rbp, rsp
	push rbx
	push r12
	push r13
	push r14
	push r15
	sub rsp, 8
	
	mov rbx, sources
	pushr
	; allocate memory for helper arrays
	mov rdi, size_of_bmatrix
	call malloc
	popr
	
	mov prev, rax
		
	pushr
	mov rdi, size_of_bmatrix
	call malloc
	popr
	
	mov next, rax
	
	pushr
	mov edi, [rbx + offset_bytes_per_row]
	call malloc
	popr
	
	mov [prev + offset_initial], rax
	mov dword [prev + offset_rows], 1
	mov eax, [rbx + offset_bytes_per_row]
	mov [prev + offset_bytes_per_row], eax
	
	pushr
	mov edi, [rbx + offset_bytes_per_row]
	call malloc
	popr
	
	mov [next + offset_initial], rax
	mov dword [next + offset_rows], 1
	mov eax, [rbx + offset_bytes_per_row]
	mov [next + offset_bytes_per_row], eax
	
	pushr	
	; copy sources->initial into prev->initial
	mov edx, [sources + offset_bytes_per_row]
	mov rsi, [sources + offset_initial]
	mov rdi, [prev + offset_initial]
	call memcpy_m16
	popr
	
	mov r15d, [adj + offset_rows]
	;~ 
	xor i, i
	.for_i:
		cmp i, n
		je .end_for_i
		
		; clear next
		pushr
		mov rdi, [next + offset_initial]
		mov esi, [marked + offset_bytes_per_row]
		call clear_m16
		popr
		
		xor k, k
		.for_k:
			cmp k, n
			je .end_for_k
			
			; prev[k] = (*(prev->initial + k / 8) & (1 << offset)) >> offset, where offset = 7 - (k % 8) 
			xor rcx, rcx
			mov rcx, [prev + offset_initial]					; rcx = prev->initial
			mov rax, k
			mov rbx, 8
			xor rdx, rdx
			div rbx											; rax = k / 8, rdx = k % 8
			add rcx, rax									; rcx = prev->initial + k / 8
			xor rbx, rbx									; rbx = 0
			mov bl, [rcx]									; bl = *(prev->initial + k / 8)
			mov cl, 7										; cl = 7
			sub cl, dl										; cl = 7 - (k % 8) = offset
			mov dl, 1										; dl = 1
			shl dl, cl										; dl = 1 << offset
			and bl, dl										; bl = 0 0 0 prev[k] 0 0 0
			shr bl, cl										; bl = 0 0 0 ... 0 0 prev[k]
			
			.if:
				cmp bl, 1
				jne .endif
				
				; we compute the address of the k-th row of adj
				; adj[k] = adj->initial + adj->bytes_per_row * k
				mov eax, [adj + offset_bytes_per_row]
				mul k
				add rax, [adj + offset_initial]				; rax = adj[k]
				
				mov rcx, next
				mov rcx, [rcx + offset_initial]				; rcx = next
				
				mov rdx, marked
				mov rdx, [rdx + offset_initial]				; rdx = marked
				
				xor j, j
				xor rbx, rbx
				mov ebx, [adj + offset_bytes_per_row]		; ebx = bytes_per_row
				.for_j:
					cmp j, rbx
					je .end_for_j
					
					movdqu xmm_next, [rcx + j]
					
					movdqu xmm_marked, [rdx + j]
					
					; We want to negate (logically) xmm_marked.
					; Since there are no native operations to do this, we
					; are gonna do it manually.
					; Suppose xmm_marked = | qword_1 | qword_2 |
					
					; First we load qword_1 into r10, to negate it.
					mov r10, [rdx + j + 8]					; r10 = qword_1
					not r10									; r10 = ~qword_1
					movq xmm6, r10							; xmm6 = | 0 ... 0  | ~qword_1 | 
					pslldq xmm6, 8							; xmm6 = | ~qword_1 | 0 ... 0  |
					
					; Now we store qword_2 in r11, and negate it.
					mov r11, [rdx + j]						; q11 = qword_2 
					not r11									; q11 = ~qword_2
					movq xmm_not_marked, r11				; xmm_not_marked = | 0 ... 0 | ~qword_2 |
					
					; Now we merge these two xmm
					por xmm_not_marked, xmm6				; xmm_not_marked = | ~qword_1 | ~qword_2 |
					
					movdqu xmm_row, [rax + j]
					
					pand xmm_row, xmm_not_marked
					por xmm_next, xmm_row					; next = next OR (adj[k] AND ~marked)
					
					por xmm_marked, xmm_next				; marked = marked OR next
					
					; Store this calculations on memory
					movdqu [rdx + j], xmm_marked
					movdqu [rcx + j], xmm_next
					
					add j, 16
					jmp .for_j
				.end_for_j:
				
			.endif:
			
			inc k
			jmp .for_k
		.end_for_k:
		
		; copy next into prev
		pushr
		mov edx, [marked + offset_bytes_per_row]
		mov rsi, [next + offset_initial]
		mov rdi, [prev + offset_initial]
		call memcpy_m16
		popr
		
		inc i
		jmp .for_i
	.end_for_i:
	
	pushr
	mov rdi, [prev + offset_initial]
	call free												; free(prev->initial)
	popr
	
	pushr
	mov rdi, prev
	call free												; free(prev)
	popr
	
	pushr
	mov rdi, [next + offset_initial]
	call free												; free(next->initial)
	popr
	
	pushr
	mov rdi, next
	call free												; free(next)
	popr
	
	add rsp, 8
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbx
	pop rbp
	
	ret

; void memcpy_m16(void *to, void *from, uint size);
memcpy_m16:
	;rdi = to
	;rsi = from
	;rdx = size
	%define to rdi
	%define from rsi
	%define size rdx
	%define k r14
	
	push r14						;aligned
	
	xor k, k
	.while_k:
		cmp k, size
		je .end_while_k
		
		movdqu xmm0, [from + k]
		movdqu [to + k], xmm0
		
		add k, 16
		jmp .while_k
	.end_while_k:

	pop r14

	ret
	
; void clear_m16(void *to, uint size);
clear_m16:
	;rdi = to
	;rsi = size
	%define to rdi
	%define size rsi
	%define k r14
	
	push r14						;aligned
	
	movdqu xmm0, [zero]
	
	xor k, k
	.while_k:
		cmp k, size
		je .end_while_k
		
		movdqu [to + k], xmm0
		
		add k, 16
		jmp .while_k
	.end_while_k:

	pop r14

	ret

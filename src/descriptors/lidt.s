global lidt
section .text
lidt:
	mov eax, [esp + 4] 
	lidt [eax]
	ret

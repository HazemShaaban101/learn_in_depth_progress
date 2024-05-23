.global RESET
RESET:
    ldr sp, = STACK_TOP
    bl PRINT_EXIT_CODE

EXIT:
    b EXIT

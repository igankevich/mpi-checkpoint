/*
MPI-CHECKPOINT — C library that implements user-level MPI checkpoints.
© 2021 Ivan Gankevich

This file is part of MPI-CHECKPOINT.

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

const char* symbols[] = {
    "mpi_checkpoint_create",
    "mpi_checkpoint_restore",
    "mpi_checkpoint_close",
    "mpi_checkpoint_init",
    "mpi_checkpoint_finalize",
    "mpi_checkpoint_write",
    "mpi_checkpoint_read",
};

void generate_weak_symbols() {
    const int nsymbols = sizeof(symbols) / sizeof(const char*);
    char newname[4096];
    for (int i=0; i<nsymbols; ++i) {
        const size_t n = strlen(symbols[i]);
        // uppercase
        strncpy(newname, symbols[i], sizeof(newname));
        for (int j=0; j<n; ++j) { newname[j] = toupper(newname[j]); }
        fprintf(stdout, "#pragma weak %s = %s_\n", newname, symbols[i]);
        // lowercase
        strncpy(newname, symbols[i], sizeof(newname));
        fprintf(stdout, "#pragma weak %s = %s_\n", symbols[i], symbols[i]);
        // double underscores
        fprintf(stdout, "#pragma weak %s__ = %s_\n", symbols[i], symbols[i]);
        // underscore + f
        fprintf(stdout, "#pragma weak %s_f = %s_\n", symbols[i], symbols[i]);
        // underscore + f08
        fprintf(stdout, "#pragma weak %s_f08 = %s_\n", symbols[i], symbols[i]);
    }
}

int main() {
    generate_weak_symbols();
    return 0;
}

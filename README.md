Crash with `cc main.c -lvulkan && ./a.out`. I already made a core dump on my machine and stored the output of `coredumpctl gdb` in `coredump.txt`.

The source code of the crashing shader is in `crash.tese`, and its SPIRV is in `crash.tese.spv` (created using `glslc crash.tese -o crash.tese.spv`).
Similarly, the source code and SPIRV of the non-crashing shader variant are in `nocrash.tese` and `nocrash.tese.spv`. The difference between the
two shaders is that the crashing shader uses `layout(constant_id = 0) const int MAX_NUM_DESCRIPTOR_IMAGES = 100;` whereas the non-crashing shader
uses `const int MAX_NUM_DESCRIPTOR_IMAGES = 100;`

The crash in `main.c` can be avoided by either:
- running without validation layers
- using `nocrash.tese.spv` instead of `crash.tese.spv`

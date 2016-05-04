clang -S -emit-llvm mm2.c -o mm2.s -msse3


opt -S -mem2reg -loop-simplify mm2.s > mm2.ll



opt -load /home/zhangyalin/llvm_build/lib/LLVMTileSize.so -tilesize mm2.ll > re.ll



opt -O3 re.ll >re3.ll
llc re3.ll -o re3.s
gcc re3.s -o mm.myopt
./mm.myopt





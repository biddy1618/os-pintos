git remote add origin https://github.com/biddy1618/os-pintos.git
git add .
git commit -m "First comming with implemented thread sleep procedure"
git push -u origin master
git add .
git commit -m "Edited some comments, and remove printf(...) statements"
git push -u origin master
cd pintos/src/threads/
make
cd build/
make check
cd ..
make
pintos -v -- -q run alarm-priority
make
pintos -v -- -q run alarm-priority
make
cd build/
make check
cd tests/threads/
ls
cd ..
cd .
cd ..
make
pintos -v -- -q run alarm-priority
make
pintos -v -- -q run alarm-priority
make
pintos -v -- -q run alarm-priority
make
pintos -v -- -q run alarm-priority
make
pintos -v -- -q run alarm-priority
make
pintos -v -- -q run alarm-priority
make
pintos -v -- -q run alarm-priority
make
pintos -v -- -q run alarm-priority
make
pintos -v -- -q run alarm-priority
make
pintos -v -- -q run alarm-priority
make
pintos -v -- -q run alarm-priority
make
pintos -v -- -q run alarm-priority
make
pintos -v -- -q run alarm-priority
cd build/
make check
cd ..
make
pintos -v -- -q run alarm-priority
make check
cd ..
git add .
git commit -m "Priority scheduling implemented, test passed"
git push -u origin master
cd pintos/src/threads/
make
cd build/
make check
cd ..
pintos -v -- -q run priority-change
make
pintos -v -- -q run priority-change
make check
make
pintos -v -- -q run priority-change
pintos -v -- -q run priority-donate-one
make
cd build/
make check 
cd ..
cd ~
git add .
git commit -m "Added thread_yield() when priority changes"
git status
git reset --hard HEAD^
git status
git add .
git status
git commit -m "Added thread_yield() when priority changes"
git push -u remote origin
git push -u origin master
cd pintos/src/threads/
make
pintos -v -- -q run alarm-priority
make
pintos -v -- -q run alarm-priority
make
pintos -v -- -q run alarm-priority
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
backtrace ./build/kernel.o  0xc0107516 0xc0100c38 0xc0102c18 0xc010932e 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0102a9e 0xc0109346 0xc01093cd 0xc0105a1b 0xc0100056
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
backtrace build/kernel.o 0xc0107516 0xc0100c38 0xc0102c18 0xc0102a6e 0xc0109346 0xc01093cd 0xc0105a1b 0xc01027bf 0xc0102aa9 0xc0109346 0xc01093cd 0xc0105a1b 0xc01027bf 0xc0102aa9 0xc0109346 0xc01093cd 0xc0105a1b 0xc01027bf 0xc0102aa9 0xc0109346 0xc01093cd 0xc0105a1b 0xc01027bf 0xc0102aa9 0xc0109346 0xc01093cd 0xc0105a1b 0xc01027bf 0xc0102aa9 0xc0109346 0xc01093cd 0xc0105a1b 0xc01027bf 0xc0102aa9 0xc0109346 0xc01093cd 0xc0105a1b 0xc01027bf 0xc0102aa9 0xc0109346 0xc01093cd 0xc0105a1b 0xc01027bf 0xc0102aa9 0xc0109346 0xc01093cd 0xc0105a1b 0xc01027bf 0xc0102aa9 0xc0109346 0xc01093cd 0xc0105a1b 0xc01027bf 0xc0102aa9 0xc0109346 0xc01093cd 0xc0105a1b 0xc01027bf 0xc0102aa9 0xc0109346 0xc01093cd 0xc0105a1b 0xc01027bf 0xc0102aa9 0xc0109346 0xc01093cd 0xc0105a1b 0xc01027bf 0xc0102aa9 0xc0109346 0xc01093cd 0xc0105a1b 0xc01027bf 0xc0102aa9 0xc0109346 0xc01093cd 0xc0105a1b 0xc01027bf 0xc0102aa9 0xc0109346 0xc01093cd 0xc0105a1b 0xc01027bf 0xc0102aa9 0xc0109346 0xc01093cd 0xc0105a1b 0xc01027bf 0xc0102aa9 0xc0109346 0xc01093cd 0xc0105a1b 0xc01027bf 0xc0102aa9 0xc0109346 0xc01093cd 0xc0105a1b 0xc01027bf 0xc0102aa9 0xc0109346 0xc01093cd 0xc0105a1b 0xc01027bf 0xc0102aa9 0xc0109346 0xc01093cd 0xc0105a1b 0xc01027bf 0xc0102aa9 0xc0109346 0xc01093cd 0xc0105a1b 0xc01027bf 0xc0102aa9 0xc0109346 0xc01093cd 0xc0105a1b 0xc01027bf 0xc0102aa9 0xc0109346 0xc01093cd 0xc0105a1b 0xc01027bf 0xc0102aa9 0xc0109346 0xc01093cd 0xc0105a1b 0xc01027bf 0xc0102aa9 0xc0109346 0xc01093cd 0xc0105a1b 0xc01027bf 0xc0102aa9 0xc0109346 0xc01093cd 0xc0105a1b 0xc01027bf 0xc0102aa9 0xc0109346 0xc01093cd 0xc0105a1b 0xc0100056
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
backtrace build/kernel.o Call stack: 0xc0107536 0xc01012c1 0xc0100b09 0xc01027e4 0xc0102acf 0xc01012f9 0xc0100749 0xc0100036.
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
backtrace build/kernel.o 0xc0107536 0xc01012c1 0xc0100b09 0xc01027e4 0xc0102acf 0xc01012f9 0xc0100749 0xc0100036
make
pintos -v -- -q run priority-donate-one
backtrace build/kernel.o 0xc0107526 0xc01012c1 0xc0100b09 0xc01027d8 0xc0102ac1 0xc01012f9 0xc0100749 0xc0100036
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run alarm-priority
make
pintos -v -- -q run alarm-priority
make
pintos -v -- -q run alarm-priority
backtrace build/kernel.o 0xc0107596 0xc0100b6f 0xc01028d2 0xc0100f17 0xc0100f6c
pintos -v -- -q run alarm-priority
make
pintos -v -- -q run a
backtrace build/kernel.o 0xc0107526 0xc01012c1 0xc0100b09 0xc01027d8 0xc0102ac1 0xc01012f9 0xc0100749 0xc0100036
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make check
make clean
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
backtrace ./build/kernel.o 0xc0107636 0xc01012c1 0xc0100b09 0xc01027e4 0xc0102b34 0xc0109466 0xc0109527 0xc0102cc7 0xc010949d 0xc0109513 0xc0105b3b 0xc0100056
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
backtrace build/kernel.o 0xc0107616 0xc01031b3 0xc01031d9 0xc01000fa 0xc0100065
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make check
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
make clean
make
pintos -v -- -q run priority-donate-one
make clean
make check
pintos -v -- -q run priority-donate-lower
make
make clean
make
cd build/
make check
cd ..
make clean
make
make check
pintos -v -- -q run priority-donate-one
pintos -v -- -q run priority-donate-sema
cd ~
cd pintos/src/threads/
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make check
cd make
git add .
git status
git ignore
git help gitignore
git commit -m "Some changes in priority donation"
git push -u origin master
make
pintos -v -- -q run priority-donate-one
pintos -v -- -q run priority-donate-multiple
make
pintos -v -- -q run priority-donate-multiple
make check
pintos -v -- -q run priority-donate-one
make check
make
pintos -v -- -q run priority-donate-one
pintos -v -- -q run priority-donate-multiple
make
pintos -v -- -q run priority-donate-multiple
make
pintos -v -- -q run priority-donate-multiple
make
pintos -v -- -q run priority-donate-multiple
make
pintos -v -- -q run priority-donate-multiple
pintos -v -- -q run priority-donate-one
pintos -v -- -q run priority-donate-multiple2
pintos -v -- -q run priority-donate-one
make check
make 
make check
pintos -v -- -q run priority-donate-one
make check
make
pintos -v -- -q run priority-donate-one
make
make check
pintos -v -- -q run priority-donate-one
pintos -v -- -q run priority-donate-multiple
pintos -v -- -q run priority-donate-
pintos -v -- -q run priority-donate-nest
make
pintos -v -- -q run priority-donate-multiple
pintos -v -- -q run priority-donate-one
pintos -v -- -q run priority-donate-multiple2
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
backtrace build/kernel.o 0xc0107716 0xc0108360 0xc0102be8 0xc0101314 0xc0100749 0xc0100036D
make
pintos -v -- -q run priority-donate-one
backtrace build/kernel.o 
backtrace build/kernel.o 0xc0107716 0xc01077ea 0xc0107dc8 0xc0102d80 0xc010132e 0xc0100749 0xc0100036
make
pintos -v -- -q run priority-donate-one
backtrace build/kernel.o 0xc0107716 0xc0107d1f 0xc0102a93 0xc01083df 0xc0102be8 0xc010322b 0xc01032e1 0xc01009fb 0xc010a18d 0xc010978a 0xc010052f 0xc01005f6 0xc010009e
make
pintos -v -- -q run priority-donate-one
backtrace build/kernel.o 
backtrace build/kernel.o 0xc0107756 0xc010782a 0xc0107e08 0xc0107d2f 0xc0102dcb 0xc010328f 0xc0103319 0xc01009fb 0xc010a1cd 0xc01097ca 0xc010052f 0xc01005f6 0xc010009e
make
pintos -v -- -q run priority-donate-one
backtrace build/kernel.o 0xc0107756 0xc01019d8 0xc0101b6b 0xc0107841 0xc010842b 0xc0102c1f 0xc0109586 0xc010960d 0xc0105c5b 0xc01097f8 0xc010a23b 0xc01097ca 0xc010052f 0xc01005f6 0xc010009e
backtrace build/kernel.o 0xc0107716 0xc0107d1f 0xc0102a93 0xc01083df 0xc0102be8 0xc010322b 0xc01032e1 0xc01009fb 0xc010a18d 0xc010978a 0xc010052f 0xc01005f6 0xc010009e
make
ps aux | grep bochs
ps aux | grep bochs | grep 2
ps aux | grep bochs | grep 2a
ps aux | grep bochs | grep 2b
make
pintos -v -- -q run priority-donate-one
pintos -v -- -q run priority-donate-multiple
pintos -v -- -q run priority-donate-multiple2
make check
pintos -v -- -q run alarm-single
pintos -v -- -q run priority-donate-nest
m
pintos -v -- -q run priority-donate-nest
pintos -v -- -q run alarm-single
make check
make
make check
make
make check
cd ~
git add .
git commit -m "Few changes on the priority"
git push -u origin master
cd pintos/src/threads/
pintos -v -- -q run priority-donate-one
backtrace build/kernel.o 0xc01077b6 0xc01078f9 0xc010848b 0xc0102c37 0xc01095e6 0xc010966d 0xc0105cbb 0xc0109858 0xc010a29b 0xc010982a 0xc010052f 0xc01005f6 0xc010009e
make
pintos -v -- -q run priority-donate-one
pintos -v -- -q run priority-donate-nest
pintos -v -- -q run priority-donate-one
backtrace build/kernel.o 0xc01077b6 0xc01078f9 0xc010848b 0xc0102c37 0xc01095e6 0xc010966d 0xc0105cbb 0xc0109858 0xc010a29b 0xc010982a 0xc010052f 0xc01005f6 0xc010009e
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make grade
make check
pintos -v -- -q run priority-donate-one
cd pintos/src/threads/
pintos-gdb build/kernel.o
cd pintos/src/threads/
pintos -v -- -q run priority-donate-one
pintos ---gdb --- -v -- -q run priority-donate-one
pintos --gdb -- -v -- -q run priority-donate-one
pintos -v -- --gdb --  -q run priority-donate-one
pintos -v --gdb -- -q run priority-donate-one
pintos -v --gdb -- -q run priority-donate-multiple
cd pintos/src/threads/
pintos-gdb ./build/kernel.o
exit
cd pintos/src/threads/
make
make clear
make
pintos -v --gdb -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
clear
ps -au |grep bochs
ps -au | grep bochs
pintos -v -- -q run priority-donate-one
exit
cd pintos/src/threads/
make
pintos -v -- -q run priority-donate-one
backtrace build/kernel.o 0xc0107756 0xc0107d5f 0xc0102db0 0xc0103293 0xc010331d 0xc01009fb 0xc010a1cd 0xc01097ca 0xc010052f 0xc01005f6 0xc010009e
make
pintos -v -- -q run priority-donate-one
make check
make
pintos -v -- -q run priority-donate-one
make check
make
pintos -v -- -q run priority-donate-one
make check
make
pintos -v -- -q run priority-donate-one
make check
make
make check
make
make check
make
make check
make
make clear
make clean
make
make check
cd ~
git add .
git status
git add .
git status
git reset
git status
git add .
git status
git ignore
git --help
git reset
git rm -r --cache .
git add .
git status
git commit -m "Some changes to synch. 11 tests still fail. 4 of them from donation."
git push -u origin master
cd pintos/src/trh
cd pintos/src/threads/
make check
make
make check
make
make check
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
backtrace build/kernel.o 0xc0107766 0xc01019e8 0xc0101b7b 0xc01027f7 0xc0100798 0xc010007f
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
backtrace build/kernel.o 0xc0107766 0xc01019e8 0xc0101b7b 0xc01027f7 0xc0100798 0xc010007f
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
backtrace build/kernel.o 0xc01077c6 0xc01019e8 0xc0101b7b 0xc0102851 0xc0102c48 0xc010a307 0xc0100f7c
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
pintos -v -- -q run priority-donate-lower
make
pintos -v -- -q run priority-donate-lower
make
pintos -v -- -q run priority-donate-lower
make
pintos -v -- -q run priority-donate-lower
cd pintos/src/threads/
make
make check
make
make check
pintos -v -- -q run priority-donate-one
make
pintos -v -- -q run priority-donate-one
make check

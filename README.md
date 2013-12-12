SI
==

Proyecto de Sistemas Inteligentes


=======================
||||||||Building|||||||
=======================

		cd <project>

		mkdir build && cd build

		cmake ../ -DDEBUG_BUILD:BOOL=ON

		make

========================
!!!!!!!!IMPORTANT!!!!!!!
========================

Eclipse does not support well out-of-source builds
so the best solution in that case is create the build directory
outside

		cd <project>

		mkdir <project>-build && cd <project>-build

		cmake ../<project> -DDEBUG_BUILD:BOOL=ON

		make


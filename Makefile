.PHONY: all

all:
	@$(MAKE) -C src

doxygen:
	mkdir -p doc && doxygen

pack:
	zip -r xkrato67-xivanu00.zip *

clean:
	rm -rf doc/ src/CMakeFiles/ src/CMakeCache.txt src/cmake_install.cmake
	rm -rf CMakeCache.txt CMakeFiles/ cmake_install.cmake src/icp_project_autogen/ src/icp_project build-src-Desktop-Debug/

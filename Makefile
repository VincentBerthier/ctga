all: base

base:
	/bin/bash build.sh -f -C
debug:
	/bin/bash build.sh -d build_deb -b debug -c clang -f -F -C
release:
	/bin/bash build.sh -d build -b release -c gnu -f -F -C
rel-stat:
	/bin/bash build.sh -d build_stat -b release -c gnu -f -F -C -DSTATIC=ON
intel:
	/bin/bash build.sh -d build_int -b release -c intel -f -F -C -DSTATIC=ON -DBOOST_ROOT=/cm/shared/apps/boost/

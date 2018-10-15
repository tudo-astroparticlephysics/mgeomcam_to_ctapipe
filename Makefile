all: build/MAGICII.camgeom.fits.gz


build/extract_magic_geom: extract_magic_geom.cxx | build
# check if root and MARS are available
ifndef ROOTSYS
  $(error ROOTSYS is undefined, source /path/to/root/bin/thisroot.sh)
endif
ifndef MARSSYS
  $(error MARSSYS is undefined, export MARSSYS=/path/to/mars)
endif

	$(CXX) extract_magic_geom.cxx \
		-O2 --std=c++11 \
		`root-config --cflags --libs` \
		-o build/extract_magic_geom \
		-I$$MARSSYS -lmars -L$$MARSSYS \
		-Wl,-rpath,$$MARSSYS \
		-Wl,-rpath,$$ROOTSYS/lib


build/geom_magic_2.json: build/extract_magic_geom
	./build/extract_magic_geom

build/MAGICII.camgeom.fits.gz: build/geom_magic_2.json convert_json_geom_to_fits.py
	python convert_json_geom_to_fits.py


build: 
	mkdir -p build

clean: 
	rm -rf build

.PHONY: clean all

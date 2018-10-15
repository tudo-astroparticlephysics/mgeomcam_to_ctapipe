#include <vector>
#include <fstream>

#include "mbase/MParContainer.h"
#include "mgeom/MGeomCamMagicTwo.h"
#include "mgeom/MGeomPix.h"
#include "TObjArray.h"

#include "json.hpp"

using json = nlohmann::json;


int main(int argc, char** args) {
	std::vector<double> pixel_x;
	std::vector<double> pixel_y;
	std::vector<double> pixel_area;
	std::vector<unsigned int> pixel_id;
	std::vector<double> pixel_rotation;

	MGeomCamMagicTwo geom;
	TObjArray pixels = geom.GetPixels();

	for (unsigned int i = 0; i < 1039; ++i) {
		MGeomPix* pixel = (MGeomPix*) pixels[i];

		pixel_x.push_back(pixel->GetX());
		pixel_y.push_back(pixel->GetY());
		pixel_area.push_back(pixel->GetA());
		pixel_rotation.push_back(pixel->GetAngle());
		pixel_id.push_back(i);
	}

	json j;
	j["pixel_id"] = pixel_id;
	j["pixel_x"] = pixel_x;
	j["pixel_y"] = pixel_y;
	j["pixel_area"] = pixel_area;
	j["pixel_rotation"] = pixel_rotation;

	std::ofstream output("build/geom_magic_2.json");
	output << j.dump() << std::endl;
	output.close();

	return 0;
}

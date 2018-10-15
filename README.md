# MAGIC camera geometry to ctapipe conversion


MAGIC Camera Geometries are defined in MARS as subclasses
of `MGeomCam`,
here we extract the pixel positions, areas and rotation angles
to json and convert that json to a fits file compatible
with `ctapipe`'s `CameraGeometry` class.

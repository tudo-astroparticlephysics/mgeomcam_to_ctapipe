import json
from astropy.table import Table
from astropy.io import fits
import astropy.units as u
import subprocess as sp
import re

with open('build/geom_magic_2.json') as f:
    data = json.load(f)


output = sp.check_output(['mars', '--version']).decode('utf-8')
m = re.search('MARS V([\d.]+)', output)
mars_version = m.groups()[0]

t = Table()
t['pix_id'] = data['pixel_id']
t['pix_x'] = u.Quantity(data['pixel_x'], u.mm).to(u.m)
t['pix_y'] = u.Quantity(data['pixel_y'], u.mm).to(u.m)
t['pix_area'] = u.Quantity(data['pixel_area'], u.mm**2).to(u.m**2)

t.write('build/MAGICII.camgeom.fits.gz', overwrite=True)

f = fits.open('build/MAGICII.camgeom.fits.gz', mode='update')
f[1].header['PIX_TYPE'] = 'hexagonal'
f[1].header['PIX_ROT'] = data['pixel_rotation'][0]
f[1].header['CAM_ROT'] = 0.0
f[1].header['CAM_ID'] = 'MAGIC-II'
f[1].header['SOURCE'] = f'MARS V{mars_version}'
f.flush()

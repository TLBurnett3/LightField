# Aperture

Aperture is a light-field synthetic aperture renderer and demonstrates SAR rendering in C++, OpenCV, and OpenGL GLSL

Usage: Aperture <path to .png directory> 

## Aperture Instructions
  
  Input .png files need to of the form "name_y_x_v_u.png" and the .png files should be rectified and cropped.

  See the New Stanford Light Field Archive (https://graphics.stanford.edu/data/LF/lfs.html) for details and example datasets.
  
  
| key           | Description                                                                       | Note                                                    |
|:--------------|:----------------------------------------------------------------------------------|:--------------------------------------------------------|
| Insert        | Move focal plane back                                                             |                                                         |
| Delete        | Move focal plane forward                                                          |                                                         |
| PageUp        | Increase aperture                                                                 |                                                         |
| PageDown      | Decrease aperture                                                                 |                                                         |
| Home          | Reset                                                                             |                                                         |
| End           | Save screenshot/framebuffer                                                       |                                                         |
| Left Arrow    | Decrease horizontal subimage index                                                |                                                         |
| Right Arrow   | Increase horizontal subimage index                                                |                                                         |
| Up Arrow      | Decrease vertical subimage index                                                  |                                                         |
| Down Arrow    | Increase vertical subimage index                                                  |                                                         |
| Esc           | Quit                                                                              |                                                         |
| 0             | SarNone: No synthetic aperture rendering, view full lightfield image              |                                                         |
| 1             | SarCpp:  Synthetic aperture rendering in C++                                      |                                                         |
| 2             | SarCV:   Synthetic aperture rendering using OpenCV                                |                                                         |
| 3             | SarGL:   Synthetic aperture rendering using OpenGL GLSL                           |                                                         |
  
Or left mouse click and drag the mini light-field image in the upper right corner of the window


# Lightfield Radiance Image Viewer

Viewer is a light-field radiance image viewer that uses a directory of hogel .avi files for input.

Usage: Viewer <path to hogel .avi directory> -gb # -fov #

Viewer loads as much of the radiance image into memory as defined by the command line -gb parameter.  The -gb parameter defines the maximum amount of memory that should be used by Viewer to storage the radiance image in main memory.  The -fov paramater defines the field of view of hogels.

The view can be rotated via the mouse (left-button drag) and/or the arrow keys; this simulates a perspective correct view into the light-field. The home or backspace key will reset the view to center. 

# WorldEditor
World Editor for Caronte Engine

# TODO
- Implement the button: "Save Copy As"
- Create different subwindows for every Operator (Scale, Resize, Crop, ...) instead of using just a single window.
- Add a Scene Window where to put all layers.
- Add a Log window and handle errors reported by ImageMagick Framework (wxLog).
	- See ImageMagick errors: https://imagemagick.org/script/exception.php and https://imagemagick.org/api/exception.php
- Make Flip (Horizontal and vertical)
- Add the possibility to handle and create texture atlas as well as split texture atlas.
	- See: https://imagemagick.org/api/magick-image.php#MagickMontageImage
- Add the possibility to create animations based on textures.
- Add a drawing tool to draw into the texture.
- Add a paint tool to paint the level using textures. (See: MagickImportImagePixels or MagickCompositeImage/MagickCompositeLayers)
- Add a grid over the image (and add the possibility to configure as orthogonal, isometric, hexagonal, rectangular...)
- Export the texture to the game engine (as binary).
- Use OpenGL as Graphics API instead of wxImage/wxBitmap.
- Beware to deal with different kind of images (RGB, RGBA, CYMK, CYMKA, ...)
- Add a reset button to reset (or reload) the image to the default.
- Add a button to change the background color to transparent.
- Add support to copy&paste regions of pixels.
- Add custom filter to the finder so we can find Tiles, Decals or whatever...
- Add a ruler on the image.
- Create a custom Directory control where to show all files (Change the wxGenericDirCtrl by a custom control).
- Add support to Undo/Redo.
- Add icon to the main frame.
- Particle Editor.
- Sound.
- Add Fade In/Out (see Blend/Disolve in ImageMagick)

# NOTE
- Zoom in/out is dangerous because when zooming too much, we lost the image. We should find another way to zoom in/out the image without losing the image.

# ImageMagick Framework (MagickWand)
- ImageMagick Main page: https://imagemagick.org/
- URL: https://imagemagick.org/api/magick-image.php

# ICONS
- https://www.flaticon.com/

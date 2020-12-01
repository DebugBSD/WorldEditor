# WorldEditor
World Editor for Caronte Engine

# TODO
- See how to add a zoom in/out of all textures (See Scale or Resize).
- Create an empty canvas where to draw.
- Add icon to the main frame.
- Add a Scene Window where to put all layers.
- Add a Log window and handle errors reported by ImageMagick Framework (wxLog).
	- See ImageMagick errors: https://imagemagick.org/script/exception.php and https://imagemagick.org/api/exception.php
- Particle Editor.
- Sound.
- Add the possibility to handle and create texture atlas.
- Add the possibility to create animations based on textures.
- Add a drawing tool to draw into the texture.
- Add a paint tool to paint the level using textures. (See: MagickImportImagePixels)
- Add a ruler on the image.
- Add a grid over the image (and add the possibility to configure as orthogonal, isometric, hexagonal, rectangular...)
- Add the possibility to make transparent the texture.
- Make Flip (Horizontal and vertical)
- Export the texture to the game engine.
- Use OpenGL as Graphics API instead of wxImage/wxBitmap.
- Beware to deal with different kind of images (RGB, RGBA, CYMK, CYMKA, ...)
- Add a reset button to reset (or reload) the image to the default.
- Add a button to change the background color to transparent.
- Add support to copy&paste regions of pixels.
- Add support to open multiple texture files.
- Add custom filter to the finder so we can find Tiles, Decals or whatever...

# NOTE
- Zoom in/out is dangerous because when zooming too much, we lost the image. We should find another way to zoom in/out the image without losing the image.
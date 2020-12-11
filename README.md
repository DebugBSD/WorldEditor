# WorldEditor
World Editor for Caronte Engine

# TODO
- Detect changes in the image and ask for save before quit the program or close the application.
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
- Create a custom Directory control where to show all files (Change the wxGenericDirCtrl by a custom control). Images must be shown as thumbnails.
- Add support to Undo/Redo.
- Add icon to the main frame.
- Particle Editor.
- Sound.
- Add Fade In/Out (see Blend/Disolve in ImageMagick)
- Think carefully about how to update all views.
- Improve the User Interface.

# NOTE
- Zoom in/out is dangerous because when zooming too much, we lost the image. We should find another way to zoom in/out the image without losing the image.
- The Canvas shows strange pixelswhen scrolling huge images. It's like transparent channel (or alpha channel) is not working propertly. See why!

# ImageMagick Framework (MagickWand)
- ImageMagick Main page: https://imagemagick.org/
- URL: https://imagemagick.org/api/magick-image.php

# ICONS
- https://www.flaticon.com/

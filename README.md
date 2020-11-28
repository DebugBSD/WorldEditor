# WorldEditor
World Editor for Caronte Engine

# TODO
- See how to add a zoom in/out of all textures.
- Add icon to the main frame.
- Add a Scene Window where to put all layers.
- Add a Log window.
- Particle Editor.
- Sound.
- Add the possibility to handle and create texture atlas.
- Add the possibility to create animations based on textures.
- Add a drawing tool to draw into the texture.
- Add a paint tool to paint the level using textures.
- Add a ruler on the image.
- Add a grid over the image (and add the possibility to configure as orthogonal, isometric, hexagonal, rectangular...)
- Add the possibility to make transparent the texture.
- Make Flip (Horizontal and vertical)
- Export the texture to the game engine.
- Use OpenGL as Graphics API instead of wxImage/wxBitmap.


1� Pensar en como vamos a obtener los pixels del canvas creado por ImageMagick
	- He conseguido leer los pixels de la imagen mediante GetAuthenticPixels. Mirar weImage::readPixelsFromImage();
2� Pensar en como vamos a renderizar la imagen (Tenemos SFML, SDL u OpenGL, wxWidgets queda descartado por su complejidad)
	- Usar wxImage/wxBitmap
3� Implementar la clase (weImage) y todos sus metodos para transformar la imagen (rotarla, escalarla, redimensionarla, ...)
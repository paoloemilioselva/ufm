(u)sd (f)rom (m)etadata
-----------------------

A fileformat plugin to be able to read USD data from metadata of PNG files (and EXR with small changes).

After you have done a render of your USD stage, you can save its content directly in the PNG metadata "usd:data", as string.

It could be a fully flattened USD or just referencing local files, it depends on your pipeline/folder structure.

You can drag&drop the following PNG file directly into a sublayer node in Houdini or load it in usdview, as any other USD file.

<img width="1280" height="720" alt="ufm_test" src="https://github.com/user-attachments/assets/2e0a403b-a68d-441e-b81f-b667b1e2c42d" />

Add metadata to PNGs
--------------------

The following is an example script to add the necessary metadata for the UFM plugin

```
from PIL import Image
from PIL.PngImagePlugin import PngInfo

filepath = "myrender.png"

img = Image.open(filepath)

metadata = PngInfo()

metadata.add_text("usd:data", """#usda 1.0
def Sphere "mySphere"
{
  double radius = 0.5
}
""")

img.save(filepath, pnginfo=metadata)

```

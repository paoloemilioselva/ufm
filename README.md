(u)sd (f)rom (m)etadata
-----------------------

A fileformat plugin to be able to read USD data from metadata of PNG files (and EXR with small changes).

After you have done a render of your USD stage, you can save its content directly in the PNG metadata "usd:data", as string.

It could be a fully flattened USD or just referencing local files, it depends on your pipeline/folder structure.

You can drag&drop the following PNG file directly into a sublayer node in Houdini or load it in usdview, as any other USD file.



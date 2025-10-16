(u)sd (f)rom (m)etadata
-----------------------

FileFormat plugin to be able to load USD (files or data) from metadata of most known file-formats like EXRs and PNGs.

Providing a path like "ufm:filename.exr", the fileformat plugin will intercept the file, reading its metadata, searching for usd files or data from the metadata entries `usd:filename` and `usd:data`, as strings.

A workflow in which you render a USD file into an EXR, you could write the usd-data that generated that EXR directly in its metadata, so that you can recreate the USD stage that generated the EXR/PNG.



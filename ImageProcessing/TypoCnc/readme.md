CNC Typocarver
==========

Engraving single line letters with CNC is pretty simple task. But what if we want to engrave some bold text? At first we would engrave the outline of each letter and then considering the diameter of the engraving tool, we would engrave the inner parts of the letter. We would continue engraving until there are no untouched places inside. This can be done manually, or using Polygon Offset tool in Adobe Illustrator or other software. But I wanted to somehow automate this process, so I would just design the wanted text and use some utility that will calculate optimal paths for chosen drill tool diameter.

This script transforms SVG shapes into series of paths which can be used for engraving bold letters by CNC machine. What is missing is the final conversion of XY paths into G code and optimization with arcs. 

Script implements these features:
- custom SVG parser
- SVG to XY path converter
- Path expanding, contour calculation - using Angus Johnson's [Javascript Clipper](http://sourceforge.net/projects/jsclipper/)
- Rendering paths using SVG element

Task list:
- Export to G-code
- Optimization of polylines to lines and arcs
- User interface for entering text, font, size and drill diameter with realtime rendering
- User interface for configuring the depth of drilling / multiple passes drilling


![Image 1](sample.png)

The target shape (gabo) is shown in yellow. You can only see it as light brown because it is covered with semitransparent blue lines representing the path a CNC drill 
will cut. Where multiple paths are overlapping, we can see blue lines. Black lines are the final calculated paths for CNC drill.

![Image 1](sample_detail.png)

Yellow edges: Because of the diameter of the drill tool, some sharp parts of the SVG shape cannot be cut.

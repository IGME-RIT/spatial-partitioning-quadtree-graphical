Documentation & Tutorial Author: Sanketh Bhat, 2019

This tutorial was designed for Visual Studio 2017 / 2019
If the solution does not compile, retarget the solution
to a different version of the Windows SDK. If you do not
have any version of the Windows SDK, it can be installed
from the Visual Studio Installer Tool

Pre-requisites: Quadtree

Graphical Quadtree

>Quadtrees do a great job in partitioning 2D space for optimized collision detection. In this example, a large number of entities are randomly placed on the screen.
>A quadtree is then constructed by inserting each point into a recursive insert method. This method determines if the current quad will be split into 4 child quads, 
> or if the point is added into the quad itself. The code comments go into further detail.







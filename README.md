### NVParse

This repository exists because I needed to make the old Nvidia NVParse module work with some legacy code.

I did not want to clone all of osg or Ogre just to get this one module.

NVidia has already deprecated NVParse. The [original link](https://developer.nvidia.com/object/nvparse.html) now leads to a 404 page, so I don't know what license Nvidia used to have.

This code is adapted from old source code I dug up from elsewhere.

### Building
Use CMake to generate the project files.
You will need GNU Bison and Flex.

### Important notes
- Compiles successfully on Windows and Linux, but it _HAS NOT BEEN DEBUGGED_.
- I only needed the files to link, so this is as far as I will go.
- I have no intention of providing bugfixes.
- However, if you want to submit a pull request, you are welcome. I may look at it once in a while.
- Issues will likely be ignored unless it is trivial to fix.

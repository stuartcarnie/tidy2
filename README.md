# tidy2
libtidy bindings for node.js

## usage
    var tidy = require('tidy');
    var cleaned = tidy.tidyString(inputHTML)

## compatibility
tidy2 has been tested on OS X 10.8 and Ubuntu 12.04

## future
* Expose all options as dictionary to `tidyString`

## dependencies

### Ubuntu
  * libtidy-dev – `sudo apt-get install libtidy-dev`
  
## attributions
tidy2 was based on the original tidy bindings by [Martyn Garcia](mailto:martyn.garcia@gmail.com)

## changelog

### v0.0.2
* Converted tidy, which would not build on OS X or Ubuntu
* Removed jsdom and other unnecessary dependencies
* Fixed significant memory leak
* Added additional options for sane conversion
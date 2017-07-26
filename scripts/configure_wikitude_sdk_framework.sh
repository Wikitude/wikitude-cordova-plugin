#!/bin/sh
#
#  configure_wikitude_sdk_framework.sh
#
#  Created by Andreas Schacherbauer on 07/24/17.
#
#

set -e

# Because the WikitudeSDK.framework contains a file larger 100 MB, this file is split up into multiple smaller ones.
# Once the Wikitude Cordova plugin is installing, these files are combined again into a single file.
# This is needed because linking the final application would fail otherwise.

echo 'Reconstructing WikitudeSDK.framework content. In case this script fails, please contact Wikitude support.'

# Find all occurences of the WikitudeSDK.framework in the Cordova application directory structure (The current working directory is the project root directory)
find . -type d -name "WikitudeSDK.framework" | while read dir; do

  # Inside the WikitudeSDK.framework, all WikitudeSDK-* files need to be combined into a single one again
  SINGLE_ARCHITECTURE_SLICES_PATHS="$(find "${dir}" -name "WikitudeSDK-*" -print)"
  SINGLE_ARCHITECTURE_SLICES_PATHS=$(echo "$SINGLE_ARCHITECTURE_SLICES_PATHS" | sed 's|/Plugin |/Plugin\\ |g') # The project path might contain blanks. This should prepare the paths to be usable by `lipo`

  # ... this is done using `lipo`
  LIPO_COMMAND="$(xcrun --sdk iphoneos --find lipo) -create $SINGLE_ARCHITECTURE_SLICES_PATHS -output \"$dir\"/WikitudeSDK"
  eval $LIPO_COMMAND

  # After lipo is done, all WikitudeSDK-* files can be deleted
  RM_COMMAND="rm $SINGLE_ARCHITECTURE_SLICES_PATHS"
  eval $RM_COMMAND
done

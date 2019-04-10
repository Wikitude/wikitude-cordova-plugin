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

  # Verify the content of the .framework. If there are multiple files named 'WikitudeSDK-*, we need to merge them together.
  NUMBER_OF_ARCHITECTURE_FILES="$(find "${dir}" -name "WikitudeSDK-*" | wc -l)"
  if [ $NUMBER_OF_ARCHITECTURE_FILES -gt 1 ]; then
    # Inside the WikitudeSDK.framework, all WikitudeSDK-* files need to be combined into a single one
    SINGLE_ARCHITECTURE_SLICES_PATHS="$(find "${dir}" -name "WikitudeSDK-*" -exec echo -n '"{}" ' \;)"

    # ... this is done using `lipo`
    LIPO_COMMAND="$(xcrun --sdk iphoneos --find lipo) -create $SINGLE_ARCHITECTURE_SLICES_PATHS -output \"$dir\"/WikitudeSDK"
    eval $LIPO_COMMAND

    # After lipo is done, all WikitudeSDK-* files can be deleted
    RM_COMMAND="rm $SINGLE_ARCHITECTURE_SLICES_PATHS"
    eval $RM_COMMAND
  fi

  # At the end there is only one file, so we verify it's content. It's expected to have 2 architecture slices (arm64[device], x86_64[simulator])
  ARCHITECTURES_IN_COMBINED_LIBRARY=$($(xcrun --sdk iphoneos --find lipo) -info "${dir}"/WikitudeSDK | sed -En -e 's/^(Non-|Architectures in the )fat file: .+( is architecture| are): (.*)$/\3/p' | wc -w)
  if [ $ARCHITECTURES_IN_COMBINED_LIBRARY -ne 2 ]; then
    echo "Unexpected number of architectures found in WikitudeSDK. lipo output following"
    $(xcrun --sdk iphoneos --find lipo) -info "$dir"/WikitudeSDK
    exit -1
  else
    echo "'"${dir}"' is a valid Wikitude SDK."
  fi
done

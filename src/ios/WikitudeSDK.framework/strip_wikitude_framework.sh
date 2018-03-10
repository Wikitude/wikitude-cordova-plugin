#!/bin/sh
#
#  strip_wikitude_framework.sh
#
#  Created by Andreas Schacherbauer on 09/13/17.
#
#

# global variables
SHOW_ARCHITECTURE_INFORMATION=false
STRIP_SIMULATOR_ARCHITECTURES=false
WIKITUDE_FRAMEWORK_PATH=""

FRAMEWORK_MANIPULATION_SCRIPTS=( "strip_wikitude_framework.sh" "wikitude_bitcode.sh" )
FRAMEWORK_LIBRARY_NAME=Wikitude*SDK

usage() {
cat <<EOF
Usage: $0 [options] [--]

    Arguments:

    -h, --help
    Display this usage message and exit.

    -i <val>, --info
    Prints all architectures that are included in the Wikitude SDK

    -s <val>, --strip_simulator
    Strips simulator architectures (i386 and x86_64) from

    -p <val>, --path
    The path to the Wikitude .framework that should be used when running this script
EOF
}

while [ "$#" -gt 0 ]; do
    arg=$1
    case $1 in
        # convert "--opt=the value" to --opt "the value".
        # the quotes around the equals sign is to work around a
        # bug in emacs' syntax parsing
        --*'='*) shift; set -- "${arg%=*}" "${arg#*=}" "$@"; continue;;
        -i|--info) shift; SHOW_ARCHITECTURE_INFORMATION=true;;
        -s|--strip_simulator) shift; STRIP_SIMULATOR_ARCHITECTURES=true;;
        -p|--path) shift; WIKITUDE_FRAMEWORK_PATH=$1;;
        -h|--help) usage; exit 0;;
        --) shift; break;;
        -*) echo "unknown option: '$1'";;
        *) break;; # reached the list of file names
    esac
done

# In case the -p parameter is not given, this script tries to interpret the last parameter as the .framework path
if [ ${#WIKITUDE_FRAMEWORK_PATH} -eq 0 ]; then
  WIKITUDE_FRAMEWORK_PATH=$1
fi

if [ ! -d "${WIKITUDE_FRAMEWORK_PATH}" ]; then
  echo 'No valid .framework path is given. Exiting'
  exit -1
fi

# This script can only perform one action at a time. The following if assures that only one action is running
if [ $SHOW_ARCHITECTURE_INFORMATION == true ] && [ $STRIP_SIMULATOR_ARCHITECTURES == true ]; then
  echo 'invalid combination or parameter given'
else
  if [ $SHOW_ARCHITECTURE_INFORMATION == true ]; then
    echo 'reading architecture information'
    $(xcrun --sdk iphoneos --find lipo) -info "${WIKITUDE_FRAMEWORK_PATH}"/$FRAMEWORK_LIBRARY_NAME
  elif [ $STRIP_SIMULATOR_ARCHITECTURES == true ]; then
    echo 'removing architectures'

    WIKITUDE_SDK_ARCHS=$($(xcrun --sdk iphoneos --find lipo) -info "${WIKITUDE_FRAMEWORK_PATH}"/$FRAMEWORK_LIBRARY_NAME | sed -En -e 's/^(Non-|Architectures in the )fat file: .+( is architecture| are): (.*)$/\3/p')
    IFS=', ' read -r -a WIKITUDE_SDK_ARCHS_ARRAY <<< "$WIKITUDE_SDK_ARCHS"

    # check if $ARCHS is empty: if so, set it to the three default architectures
    if [ ${#ARCHS} -eq 0 ]; then
      ARCHS="armv7 armv7s arm64"
    fi

    for WIKITUDE_SDK_ARCH in ${WIKITUDE_SDK_ARCHS_ARRAY[@]}
    do
      if [[ ! "${ARCHS}" == *"$WIKITUDE_SDK_ARCH"* ]]; then
        echo 'removing ' $WIKITUDE_SDK_ARCH ' architecture'
        $(xcrun --sdk iphoneos --find lipo) -remove ${WIKITUDE_SDK_ARCH} -o "${WIKITUDE_FRAMEWORK_PATH}"/$FRAMEWORK_LIBRARY_NAME "${WIKITUDE_FRAMEWORK_PATH}"/$FRAMEWORK_LIBRARY_NAME
      fi
    done

    if [ "$ACTION" == "install" ]; then
        for FRAMEWORK_MANIPULATION_SCRIPT in ${FRAMEWORK_MANIPULATION_SCRIPTS[@]}
        do
            FULL_FRAMEWORK_MANIPULATION_SCRIPT_PATH="${WIKITUDE_FRAMEWORK_PATH}"/$FRAMEWORK_MANIPULATION_SCRIPT
            if [ -e "${FULL_FRAMEWORK_MANIPULATION_SCRIPT_PATH}" ]; then
                rm -f "${FULL_FRAMEWORK_MANIPULATION_SCRIPT_PATH}"
            fi
        done
    fi

    $(xcrun --sdk iphoneos --find codesign) --force --sign ${EXPANDED_CODE_SIGN_IDENTITY} --preserve-metadata=identifier,entitlements "${WIKITUDE_FRAMEWORK_PATH}"/$FRAMEWORK_LIBRARY_NAME
  else
    echo 'unknown option'
  fi
fi

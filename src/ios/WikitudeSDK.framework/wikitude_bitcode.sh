#!/bin/sh
#
#  strip_bitcode.sh
#
#  Created by Andreas Schacherbauer on 09/12/17.
#
#

# Global variables
SHOW_BITCODE_INFORMATION=false
STRIP_BITCODE_INFORMATION=false
WIKITUDE_FRAMEWORK_PATH=""

usage() {
cat <<EOF
Usage: $0 [options] [--]

    Arguments:

    -h, --help
    Display this usage message and exit.

    -i <val>, --info <val>
    Returns if the Wikitude SDK contains bitcode information or not

    -s <val>, --strip_bitcode <val>
    Removes bitcode information from the Wikitude SDK

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
        -i|--info) shift; SHOW_BITCODE_INFORMATION=true;;
        -s|--strip_bitcode) shift; STRIP_BITCODE_INFORMATION=true;;
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
if [ $SHOW_BITCODE_INFORMATION == true ] && [ $STRIP_BITCODE_INFORMATION == true ]; then
    echo 'invalid combination of parameter given'
else
    if [ $SHOW_BITCODE_INFORMATION == true ]; then
        echo 'Reading bitcode information'
        WIKITUDE_SDK_ARCHS=$($(xcrun --sdk iphoneos --find lipo) -info "${WIKITUDE_FRAMEWORK_PATH}"/WikitudeSDK | sed -En -e 's/^(Non-|Architectures in the )fat file: .+( is architecture| are): (.*)$/\3/p')

        DEFAULT_DEVICE_ARCHS=( "armv7" "armv7s" "arm64" )
        IFS=', ' read -r -a WIKITUDE_SDK_ARCHS_ARRAY <<< "$WIKITUDE_SDK_ARCHS"
        OTOOL_OUTPUT=""
        BITCODE_ENABLED_ARCHS=()
        for WIKITUDE_SDK_ARCH in "${WIKITUDE_SDK_ARCHS_ARRAY[@]}"
        do
          if [[ " ${DEFAULT_DEVICE_ARCHS[@]} " =~ " ${WIKITUDE_SDK_ARCH} " ]]; then
              ARCHITECTURE_BITCODE_INFORMATION=$(otool -arch ${WIKITUDE_SDK_ARCH} -l "${WIKITUDE_FRAMEWORK_PATH}"/WikitudeSDK | grep LLVM)
              if [ ${#ARCHITECTURE_BITCODE_INFORMATION} -gt 0 ]; then
                  BITCODE_ENABLED_ARCHS+=(${WIKITUDE_SDK_ARCH})
              fi
              OTOOL_OUTPUT=$OTOOL_OUTPUT$ARCHITECTURE_BITCODE_INFORMATION
          fi
        done
        if [ ${#OTOOL_OUTPUT} -gt 0 ]; then
            echo "${WIKITUDE_FRAMEWORK_PATH}"" contains bitcode information for the following architectures: "${BITCODE_ENABLED_ARCHS[*]}
            exit 0
        else
            echo "${WIKITUDE_FRAMEWORK_PATH}"" doesn't contain any bitcode information"
            exit 0
        fi
    elif [ $STRIP_BITCODE_INFORMATION ]; then
        echo 'Stripping bitcode information'
        $(xcrun --sdk iphoneos --find bitcode_strip) -r "${WIKITUDE_FRAMEWORK_PATH}"/WikitudeSDK -o "${WIKITUDE_FRAMEWORK_PATH}"/WikitudeSDK
    else
        echo 'unknown option'
    fi
fi

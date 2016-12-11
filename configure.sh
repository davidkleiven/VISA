#!/bin/bash
VISAPATH="/usr/local"

###
# Configure: Example
# bash configure.sh --prefix=/usr/local/
# This call will put libvisa.so in /usr/local/lib
# The header files will be put in /usr/local/include/visa
###

# Parse command line arguments
for i in "$@"
do
  case $i in --prefix=*)
    VISAPATH="${i#*=}"
    shift
    ;;
  --help*)
    echo "Usage: bash configure --prefix=/path/to/library"
    shift
    exit
    ;;
  *)
    echo "Unknown argument $i"
    exit
  ;;
  esac
done

PATHFILE="visaInstall.mk"

rm -f "$PATHFILE"

echo "VISA_INSTALLPATH=${VISAPATH}" >> $PATHFILE
echo "VISA_HEADER_PATH=${VISAPATH}/include/visa" >> $PATHFILE
echo "VISA_LIB_PATH=${VISAPATH}/lib" >> $PATHFILE

#!/bin/bash
usage="$(basename "$0")

where:
    -l  show this help text
    -d  download library
    "
readonly argv_0=$(basename $0)
readonly argc=$#

while getopts "ld:" opt; do
	case "$opt" in
	l) ;;
	d)
		# executable
		libName=$OPTARG
		URI="https://raw.githubusercontent.com/dennis0324/Clib/main/datastructure/${libName}_type.h"
		doCurl=true
		;;
	*)
		printf "%s: option '-%s' " $argv_0 $OPTARG
		printf "is invalid\n"

		;;
	esac
done

if [ $argc = 0 ]; then
	# help
	echo "$usage"
	exit 0
fi

if [[ $doCurl = true ]]; then
	echo $URI
	curl -sS "$URI" --output "${libName}_type.h"
fi

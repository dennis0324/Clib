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
		URI="https://raw.githubusercontent.com/dennis0324/make/main/makefiles/build-executable/Makefile"
		doCurl=true
		;;
	*)
		printf "%s: option '-%s' " $argv_0 $OPTARG
		printf "is invalid\n"

		;;
	esac
done

[[ ! -z $PROJECT_NAME ]] && name=$PROJECT_NAME
[[ ! -z $PROJECT_AUTHOR ]] && author=$PROJECT_AUTHOR

if [ $argc = 0 ]; then
	# help
	echo "$usage"
	exit 0
fi

if [[ $initialize = true ]]; then
	echo "making folder structure"
	[[ ! -d src ]] && mkdir src
	[[ ! -d include ]] && mkdir include
	[[ ! -d bin ]] && mkdir bin
fi

if [[ $redownload = true ]]; then
	echo "redownloading makefile"
	if [[ -f "Makefile" ]]; then
		rm Makefile
	fi
fi

if [[ ! -f "Makefile" ]] && [[ $doCurl = true ]]; then
	echo $URI
	curl -sS "$URI" --output "Makefile"
	sed -i "s/PROJECT_NAME = .*/PROJECT_NAME = $name/g" Makefile
	sed -i "s/PROJECT_AUTHOR = .*/PROJECT_AUTHOR = $author/g" Makefile
	if [ ! -f ".makeOnlineConfig" ]; then
		curl -sS "https://raw.githubusercontent.com/dennis0324/make/main/config/.makeOnlineConfig" --output ".makeOnlineConfig"
		sed -i "s/PROJECT_NAME=.*/PROJECT_NAME=$name/g" .makeOnlineConfig
		sed -i "s/PROJECT_AUTHOR=.*/PROJECT_AUTHOR=$author/g" .makeOnlineConfig
	fi
fi

if [[ -f "Makefile" ]] && [[ ! $rename ]]; then
	echo "runing makefile"
	make -f Makefile PROJECT_NAME="$name" PROJECT_AUTHOR="$author"
fi

if [[ $clean = true ]]; then
	echo "removing makefile"
	rm Makefile
fi

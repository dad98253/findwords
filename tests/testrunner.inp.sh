#! /bin/bash
case $BASH_VERSION in ''|[123].*|4.[012]) echo "ERROR: Bash 4.3 required" >&2; exit 1;; esac

# Run test suite 1
scriptName="${0##*/}"

declare -i DEFAULT_TIMEOUT=9
declare -i DEFAULT_INTERVAL=1

# Timeout.
declare -i timeout=DEFAULT_TIMEOUT
# Interval between checks if the process is still alive.
declare -i interval=DEFAULT_INTERVAL
# Option to generate new checksums
declare -i -g GenerateSums=0


function printUsage() {
    cat <<EOF

Synopsis
    $scriptName [-t timeout] [-i interval] [-g] [-h] InputFile
    Run passwin test suite 1.

    -t timeout
        Number of seconds to wait for process completion.
        Positive integer, default value: $DEFAULT_TIMEOUT seconds.

    -i interval
        Interval between checks if the process is still alive.
        Positive integer, default value: $DEFAULT_INTERVAL seconds.

    -g
        Flag to force the generation of new result checksums.

    -h
        Flag to force the printing of this help message.

As of today, Bash does not support floating point arithmetic,
therefore all delay/time values must be integers.
EOF
}


# Options.
while getopts ":t:i:gh" option; do
        case "$option" in
            t) timeout=$OPTARG ;;
	    i) interval=$OPTARG ;;
            g) GenerateSums=1 ;;
            h) printUsage; exit 1 ;;
        esac
done
shift $((OPTIND - 1))

# $# should be exactly 1 (the input file to execute),
if (($# != 1 || timeout <= 0 || interval <= 0)); then
        printUsage
        exit 1
fi

option=$1
declare -i -x ti=timeout
declare -i -x numfailed=0

#----------------------------------------------------------------------------------
runjob () {
echo "checking $1"     
let length=30-${#1}
v=$(printf "%$length.${length}s" ".............................")
echo "$1 $v is starting"

#export DBFDIR=./$1.dir
#source ../params.sh
#export PROJ="."

/usr/bin/logger "running $1 using testrunner.inp.sh from $PWD"

#rm -rf $1.dir
#valgrind --tool=memcheck --error-limit=no --track-origins=yes --max-stackframe=20000000 
#gdb ../bin/findwords
#ddd ../bin/findwords
../../../bin/findwords >$1.stdout 2>$1.stderr
#/usr/local/bin/findwords >$1.stdout 2>$1.stderr

if [[ $GenerateSums -eq 1 ]]; then
	/usr/bin/logger "generating new checksums for $1 using testrunner.inp.sh from $PWD"
#cat $1.out    | sha1sum -c $1.out.O0.sha1
	cat $1.stdout  | sha1sum > ../../$1.stdout.O0.sha1 2>&1
	cat $1.stderr  | sha1sum > ../../$1.stderr.O0.sha1 2>&1
#	find $1.dir -type f -exec sha1sum {} \; | sort -k 2 | sha1sum > ../../$1.dir.O0.sha1 2>&1
fi
#cat $1.out    | sha1sum -c $1.out.O0.sha1
/usr/bin/logger "validating checksums for $1"
rm $1.shalog
cat $1.stdout  | sha1sum -c ../../$1.stdout.O0.sha1 >> $1.shalog 2>&1
cat $1.stderr  | sha1sum -c ../../$1.stderr.O0.sha1 >> $1.shalog 2>&1
#find $1.dir -type f -exec sha1sum {} \; | sort -k 2 | sha1sum -c ../../$1.dir.O0.sha1 >> $1.shalog 2>&1
if [[ $GenerateSums -eq 1 ]]; then
	cat $1.shalog  | sha1sum > ../../$1.shalog.O0.sha1
fi
cat $1.shalog  | sha1sum -c ../../$1.shalog.O0.sha1

if (($? == 0)); then
	echo "$1 $v passed"
	/usr/bin/logger "$1 $v passed"
	return 0
else
	((numfailed ++))
	echo "$1 $v failed" 
	/usr/bin/logger "$1 $v $numfailed failed"
#	sleep 2
	return numfailed
fi
}
#----------------------------------------------------------------------------------


# fire off job
runjob $option

# if the job failed, return exit 1 to the calling routine
if (($? == 0)); then
	/usr/bin/logger "$1 $v job passed"
        exit 0
else
	/usr/bin/logger "$1 $v has failed"
#       sleep 2
        exit 1
fi

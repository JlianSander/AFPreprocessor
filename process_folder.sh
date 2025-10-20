#!/usr/bin/bash
#set -x

echo "process_folder v1.0"
echo "created by Julian Sander"

if [ "$#" -ne 3 ]
  then
    echo "analyseResults.sh <path_preprocessor> <path_input_afs> <path_output_afs>"
    echo "<path_preprocessor>       Path to the executable of AFPreprocessor used to simplify the frameworks\n"
    echo "<path_input_afs>          Path to the folder containing the frameworks in .i23 format to simplify.\n"
    echo "<path_output_afs>         Path to the folder in which the simplified frameworks are to be saved to.\n"
    exit 1    
fi

path_preprocessor=$1
dir_input_afs=$2
dir_output_afs=$3
    
# Check if irectory
if [ ! -d "$dir_input_afs" ]; then
    echo "$dir_input_afs"
    echo "Path does not lead to a directory"
    exit 1
fi

# Check if irectory
if [ ! -d "$dir_output_afs" ]; then
    echo "$dir_output_afs"
    echo "Path does not lead to a directory"
    exit 1
fi

# count files
num_files=0
for file_input_af in "$dir_input_afs"/*.i23; do
    ((num_files++))
done

# iterate through files of the input
num_processed=0
for file_input_af in "$dir_input_afs"/*.i23; do
    file_basename_af="$(basename -- $file_input_af .i23)"

    file_output_af=$dir_output_afs"/"$file_basename_af"_simp.i23"
    file_output_args=$dir_output_afs"/"$file_basename_af"_simp_args.txt"
    
    ./build/AFPreprocessor -f "$file_input_af" -a 1 -r "$file_output_af" -e "$file_output_args" --quiet
    ((num_processed++))
    echo "Processed ($num_processed/$num_files)"
done